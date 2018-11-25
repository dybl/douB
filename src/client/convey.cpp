#include "convey.h"
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

Convey::Convey()
{
    this->m_convey_socket.setSocketOption(QAbstractSocket::LowDelayOption, "1");    //启用nagle低延迟算法
    this->m_convey_socket.setSocketOption(QAbstractSocket::KeepAliveOption, "1");   //设置保持连接状态
    connect(&m_convey_socket, SIGNAL(disconnected()), this, SLOT(destroyConnect()));
}

void Convey::connectToHost(QString hostname, int port)
{
    this->m_convey_socket.connectToHost(hostname, port);
    bool connected =  this->m_convey_socket.waitForConnected(3000);
    if(!connected)
        throw std::runtime_error("连接失败");
}

void Convey::destroyConnect()
{
    this->m_convey_socket.disconnectFromHost();
    this->m_convey_socket.waitForDisconnected();
}

void Convey::sendJsonDoc(QJsonDocument jsondoc)
{
    if(m_convey_socket.isValid() && !jsondoc.isEmpty()){
        this->m_convey_socket.write(jsondoc.toJson(QJsonDocument::Compact));
        this->m_convey_socket.waitForBytesWritten();
    }
    else{
        qDebug() << "Socket Error!";
    }
}

QJsonDocument Convey::revJsondoc()
{
    QByteArray jsonbyte;

    bool readable = this->m_convey_socket.waitForReadyRead();
    if(readable){

        //注意这里需要不断循环，保证大容量字节流的顺利读取
        do{
            jsonbyte += this->m_convey_socket.readAll();
        }while(m_convey_socket.waitForReadyRead(1));
    }

//    qDebug() << jsonbyte;

    QJsonParseError json_error;
    QJsonDocument jsondoc, nulldoc;
    jsondoc = QJsonDocument::fromJson(jsonbyte, &json_error);
    if(json_error.error == QJsonParseError::NoError){
        return jsondoc;
    }
    return nulldoc;
}

User_model Convey::verifyUser(QString username, QString password)
{
    User_model cur_user;

    //发送json数据包
    QJsonObject tempobj, jsonobj;
    tempobj.insert("username", username);
    tempobj.insert("password", password);
    jsonobj.insert("verify", tempobj);

    QJsonDocument jsondoc;
    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收json数据包
    jsondoc = revJsondoc();
    if(!jsondoc.isNull()){
        if(jsondoc.isObject()){
            jsonobj = jsondoc.object();
            QJsonValue jsonvalue;

            //判断用户合法性
            if(jsonobj.contains("ack"))
            {
                jsonvalue = jsonobj.take("ack");
                if(jsonvalue.isBool())
                {
                    bool verify_true = jsonvalue.toBool();
                    if(!verify_true)
                        return cur_user;
                }
            }

            //验证通过后接收用户信息
            if(jsonobj.contains("user"))
            {
                jsonvalue = jsonobj.take("user");
                if(jsonvalue.isObject())
                {
                    cur_user = translateJsonUser(jsonvalue.toObject());
                }
            }
        }
    }
    else{
        qDebug() << "连接超时";
    }

    return cur_user;
}

std::vector<Course_model> Convey::getCourse(QString mode)
{
    std::vector<Course_model> course_list;
    Course_model temp_course;

    //发送json数据包
    QJsonObject jsonobj;
    jsonobj.insert("get", mode);

    QJsonDocument jsondoc;
    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收json数据包
    jsondoc = revJsondoc();
    if(!jsondoc.isNull()){
        if(jsondoc.isObject()){
            jsonobj = jsondoc.object();
            QJsonValue jsonvalue;
            QJsonArray jsonarray;

            if(jsonobj.contains(mode))
            {
                jsonvalue = jsonobj.take(mode);
                if(jsonvalue.isArray())
                {
                    jsonarray = jsonvalue.toArray();

                    for(auto i : jsonarray)
                    {
                        if(i.isObject())
                        {
                            temp_course = translateJsonCourse(i.toObject());
                            course_list.push_back(temp_course);
                        }
                    }
                }
            }

            if(jsonobj.contains("ack"))
            {
                if(!translateJsonAck(jsonobj))
                {
                    throw std::runtime_error("获取失败！");
                }
            }
        }
    }

    return course_list;
}

std::vector<Course_model> Convey::getCurCourse()
{
    return getCourse("cur_course");
}

std::vector<Course_model> Convey::getSelCourse()
{
    return getCourse("sel_course");
}

User_model Convey::translateJsonUser(QJsonObject jsonobj)
{
    QJsonValue jsonvalue;
    User_model cur_user;

    if(jsonobj.contains("id"))
    {
        jsonvalue = jsonobj.take("id");
        if(jsonvalue.isString())
        {
            cur_user.id = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("name"))
    {
        jsonvalue = jsonobj.take("name");
        if(jsonvalue.isString())
        {
            cur_user.name = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("class_name"))
    {
        jsonvalue = jsonobj.take("class_name");
        if(jsonvalue.isString())
        {
            cur_user.class_name = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("institude"))
    {
        jsonvalue = jsonobj.take("institude");
        if(jsonvalue.isString())
        {
            cur_user.institude = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("grade"))
    {
        jsonvalue = jsonobj.take("grade");
        if(jsonvalue.isDouble())
        {
            cur_user.grade = jsonvalue.toDouble();
        }
    }

    if(jsonobj.contains("user_type"))
    {
        jsonvalue = jsonobj.take("user_type");
        if(jsonvalue.isDouble())
        {
            cur_user.user_type = jsonvalue.toVariant().toInt();
        }
    }

    return cur_user;
}

Course_model Convey::translateJsonCourse(QJsonObject jsonobj)
{
    QJsonValue jsonvalue;
    Course_model cur_course;

    if(jsonobj.contains("id"))
    {
        jsonvalue = jsonobj.take("id");
        if(jsonvalue.isString())
        {
            cur_course.id = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("name"))
    {
        jsonvalue = jsonobj.take("name");
        if(jsonvalue.isString())
        {
            cur_course.name = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("credit"))
    {
        jsonvalue = jsonobj.take("credit");
        if(jsonvalue.isDouble())
        {
            cur_course.credit = jsonvalue.toVariant().toInt();
        }
    }

    if(jsonobj.contains("cur_num"))
    {
        jsonvalue = jsonobj.take("cur_num");
        if(jsonvalue.isDouble())
        {
            cur_course.cur_num = jsonvalue.toVariant().toInt();
        }
    }

    if(jsonobj.contains("capacity"))
    {
        jsonvalue = jsonobj.take("capacity");
        if(jsonvalue.isDouble())
        {
            cur_course.capacity = jsonvalue.toVariant().toInt();
        }
    }

    if(jsonobj.contains("grade"))
    {
        jsonvalue = jsonobj.take("grade");
        if(jsonvalue.isDouble())
        {
            cur_course.grade = jsonvalue.toDouble();
        }
    }

    if(jsonobj.contains("gpa"))
    {
        jsonvalue = jsonobj.take("gpa");
        if(jsonvalue.isDouble())
        {
            cur_course.gpa = jsonvalue.toDouble();
        }
    }

    if(jsonobj.contains("course_type"))
    {
        jsonvalue = jsonobj.take("course_type");
        if(jsonvalue.isDouble())
        {
            cur_course.course_type = jsonvalue.toVariant().toInt();
        }
    }

    if(jsonobj.contains("teacher_id"))
    {
        jsonvalue = jsonobj.take("teacher_id");
        if(jsonvalue.isString())
        {
            cur_course.teacher_id = jsonvalue.toString().toStdString();
        }
    }

    return cur_course;
}

bool Convey::translateJsonAck(QJsonObject jsonobj)
{
    QJsonValue jsonvalue;

    if(jsonobj.contains("ack"))
    {
        jsonvalue = jsonobj.take("ack");
        if(jsonvalue.isBool())
        {
            bool verify_true = jsonvalue.toBool();
            if(verify_true)
                return true;
        }
    }
    return false;
}

QJsonObject Convey::generateJsonCourse(Course_model cur_course)
{
    QJsonObject jsonobj;
    jsonobj.insert("id", QString::fromStdString(cur_course.id));
    jsonobj.insert("name", QString::fromStdString(cur_course.name));
    jsonobj.insert("credit", cur_course.credit);
    jsonobj.insert("capacity", cur_course.capacity);
    jsonobj.insert("course_type", cur_course.course_type);
    jsonobj.insert("cur_num", cur_course.cur_num);
    jsonobj.insert("teacher_id", QString::fromStdString(cur_course.teacher_id));
    jsonobj.insert("grade", cur_course.grade);
    jsonobj.insert("gpa", cur_course.gpa);

    return jsonobj;
}

QJsonObject Convey::generateJsonUser(User_model cur_user)
{
    QJsonObject jsonobj;
    jsonobj.insert("id", QString::fromStdString(cur_user.id));
    jsonobj.insert("name", QString::fromStdString(cur_user.name));
    jsonobj.insert("class_name", QString::fromStdString(cur_user.class_name));
    jsonobj.insert("grade", cur_user.grade);
    jsonobj.insert("institude", QString::fromStdString(cur_user.institude));
    jsonobj.insert("user_type", cur_user.user_type);

    return jsonobj;
}

void Convey::sendPost(QString id, QString mode)
{
    //发送json数据包
    QJsonObject jsonobj, tempobj;
    tempobj.insert(mode, id);
    jsonobj.insert("post", tempobj);

    QJsonDocument jsondoc;
    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收json数据包
    jsondoc = revJsondoc();
    if(!jsondoc.isNull())
    {
        if(jsondoc.isObject())
        {
            jsonobj = jsondoc.object();
            if(translateJsonAck(jsonobj))
                return;
        }
    }

    throw std::runtime_error("修改失败！");
}

void Convey::sendSelCourse(QString course_id)
{
    sendPost(course_id, "sel_course");
}

void Convey::sendDelCourse(QString course_id)
{
    sendPost(course_id, "del_course");
}

void Convey::sendDelUser(QString user_id)
{
    sendPost(user_id, "del_user");
}

void Convey::sendStuGrade(QString course_id, QMap<QString, QVariant> stu_grade)
{
    //发送json数据包
    QJsonArray jsonarray;
    QJsonObject jsonobj, tempobj;
    QJsonDocument jsondoc;

    jsondoc = QJsonDocument::fromVariant(QVariant(stu_grade));

    tempobj.insert("stu_grade", jsondoc.object());
    tempobj.insert("course_id", course_id);
    jsonobj.insert("post", tempobj);

    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收json数据包
    jsondoc = revJsondoc();
    if(!jsondoc.isNull())
    {
        if(jsondoc.isObject())
        {
            jsonobj = jsondoc.object();
            if(translateJsonAck(jsonobj))
                return;
        }
    }

    throw std::runtime_error("修改失败！");
}

std::pair<Course_model, std::vector<User_model> > Convey::getCourseInfo(QString course_id)
{
    std::vector<User_model> student_list;
    Course_model temp_course;

    //发送json数据包
    QJsonObject jsonobj, tempobj;
    tempobj.insert("course_info", course_id);
    jsonobj.insert("get", tempobj);

    QJsonDocument jsondoc;
    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收json数据包
    jsondoc = revJsondoc();
    if(!jsondoc.isNull()){
        if(jsondoc.isObject())
        {
            QJsonValue jsonvalue;
            jsonobj = jsondoc.object();
            if(jsonobj.contains("course_info"))
            {
                jsonvalue = jsonobj.take("course_info");
                if(jsonvalue.isObject())
                {
                    jsonobj = jsonvalue.toObject();
                    if(jsonobj.contains("course"))
                    {
                        jsonvalue = jsonobj.take("course");
                        if(jsonvalue.isObject())
                        {
                            temp_course = translateJsonCourse(jsonvalue.toObject());
                        }
                    }

                    if(jsonobj.contains("student"))
                    {
                        jsonvalue = jsonobj.take("student");
                        if(jsonvalue.isArray())
                        {
                            QJsonArray jsonarray = jsonvalue.toArray();
                            for(auto i : jsonarray)
                            {
                                if(i.isObject())
                                {
                                    User_model temp_user = translateJsonUser(i.toObject());
                                    student_list.push_back(temp_user);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return std::make_pair(temp_course, student_list);
}

std::map<User_model, std::string> Convey::getUser()
{
    std::map<User_model, std::string> user_list;
    User_model temp_course;

    //发送json数据包
    QJsonObject jsonobj;
    jsonobj.insert("get", "user");

    QJsonDocument jsondoc;
    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收json数据包
    jsondoc = revJsondoc();
    if(!jsondoc.isNull()){
        if(jsondoc.isObject())
        {
            QJsonValue jsonvalue;
            jsonobj = jsondoc.object();
            if(jsonobj.contains("user"))
            {
                jsonvalue = jsonobj.take("user");
                if(jsonvalue.isArray())
                {
                    QJsonArray jsonarray = jsonvalue.toArray();

                    for(auto i : jsonarray)
                    {
                        if(i.isObject())
                        {
                            jsonobj = i.toObject();
                            temp_course = translateJsonUser(jsonobj);
                            std::string password = "";
                            if(jsonobj.contains("password"))
                            {
                                jsonvalue = jsonobj.take("password");
                                if(jsonvalue.isString())
                                {
                                    password = jsonvalue.toString().toStdString();
                                }
                            }
                            user_list[temp_course] = password;
                        }
                    }
                }
            }
        }
    }
    return user_list;
}

void Convey::sendCourseInfo(Course_model cur_course, std::vector<std::string> course_stu, QString mode)
{
    QJsonArray jsonarray;
    QJsonDocument jsondoc;
    QJsonObject jsonobj, postobj, tempobj, info_obj;
    QJsonValue jsonvalue;

    //生成jsondocument并发送
    tempobj = generateJsonCourse(cur_course);
    info_obj.insert("course", tempobj);

    for(auto i : course_stu)
    {
        jsonarray.append(QString::fromStdString(i));
    }
    info_obj.insert("course_stu", jsonarray);

    postobj.insert(mode, info_obj);
    jsonobj.insert("post", postobj);

    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收服务端回复
    jsondoc = revJsondoc();
    if(!jsondoc.isNull())
    {
        if(jsondoc.isObject())
        {
            jsonobj = jsondoc.object();
            if(!translateJsonAck(jsonobj))
            {
                //解析服务端提示信息
                if(jsonobj.contains("hint"))
                {
                    jsonvalue = jsonobj.take("hint");
                    if(jsonvalue.isString())
                    {
                       throw std::runtime_error(jsonvalue.toString().toStdString());
                    }
                }
            }
        }
    }
}

void Convey::sendAddCourse(Course_model cur_course, std::vector<std::string> course_stu)
{
    sendCourseInfo(cur_course, course_stu, "add_course");
}

void Convey::sendUpdateCourse(Course_model cur_course, std::vector<std::string> course_stu)
{
    sendCourseInfo(cur_course, course_stu, "update_course");
}

void Convey::sendUserInfo(User_model cur_user, QString password, std::vector<std::string> user_course, QString mode)
{
    QJsonArray jsonarray;
    QJsonDocument jsondoc;
    QJsonObject jsonobj, postobj, tempobj, info_obj;
    QJsonValue jsonvalue;

    //生成jsondocument并发送
    tempobj = generateJsonUser(cur_user);
    tempobj.insert("password", password);
    info_obj.insert("user", tempobj);

    for(auto i : user_course)
    {
        jsonarray.append(QString::fromStdString(i));
    }
    info_obj.insert("user_course", jsonarray);

    postobj.insert(mode, info_obj);
    jsonobj.insert("post", postobj);

    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收服务端回复
    jsondoc = revJsondoc();
    if(!jsondoc.isNull())
    {
        if(jsondoc.isObject())
        {
            jsonobj = jsondoc.object();
            if(!translateJsonAck(jsonobj))
            {
                //解析服务端提示信息
                if(jsonobj.contains("hint"))
                {
                    jsonvalue = jsonobj.take("hint");
                    if(jsonvalue.isString())
                    {
                       throw std::runtime_error(jsonvalue.toString().toStdString());
                    }
                }
            }
        }
    }
}

void Convey::sendAddUser(User_model cur_user, QString password, std::vector<std::string> user_course)
{
    sendUserInfo(cur_user, password, user_course, "add_user");
}

void Convey::sendUpdateUser(User_model cur_user, QString password, std::vector<std::string> user_course)
{
    sendUserInfo(cur_user, password, user_course, "update_user");
}

std::pair<User_model, std::vector<Course_model> > Convey::getUserInfo(QString user_id)
{
    std::vector<Course_model> course_list;
    User_model temp_user;

    //发送json数据包
    QJsonObject jsonobj, tempobj;
    tempobj.insert("user_info", user_id);
    jsonobj.insert("get", tempobj);

    QJsonDocument jsondoc;
    jsondoc.setObject(jsonobj);
    sendJsonDoc(jsondoc);

    //接收json数据包
    jsondoc = revJsondoc();
    if(!jsondoc.isNull()){
        if(jsondoc.isObject())
        {
            QJsonValue jsonvalue;
            jsonobj = jsondoc.object();
            if(jsonobj.contains("user_info"))
            {
                jsonvalue = jsonobj.take("user_info");
                if(jsonvalue.isObject())
                {
                    jsonobj = jsonvalue.toObject();
                    if(jsonobj.contains("user"))
                    {
                        jsonvalue = jsonobj.take("user");
                        if(jsonvalue.isObject())
                        {
                            temp_user = translateJsonUser(jsonvalue.toObject());
                        }
                    }

                    if(jsonobj.contains("course"))
                    {
                        jsonvalue = jsonobj.take("course");
                        if(jsonvalue.isArray())
                        {
                            QJsonArray jsonarray = jsonvalue.toArray();
                            for(auto i : jsonarray)
                            {
                                if(i.isObject())
                                {
                                    Course_model temp_course = translateJsonCourse(i.toObject());
                                    course_list.push_back(temp_course);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return std::make_pair(temp_user, course_list);
}
