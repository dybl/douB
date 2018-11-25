#include <QtCore>

#include "convey_thread.h"

Convey_thread::Convey_thread(int socketDescriptor, Envir* envir, Config_file* config, QObject *parent):
    m_socketDescriptor(socketDescriptor),
    m_envir(envir),
    m_config(config),
    QThread(parent)
{

}

void Convey_thread::run()
{
    QTcpSocket socket;
    if(!socket.setSocketDescriptor(m_socketDescriptor))
    {
        emit error(socket.error());
        return;
    }

    socket.setSocketOption(QAbstractSocket::LowDelayOption, "1");    //启用nagle低延迟算法
    socket.setSocketOption(QAbstractSocket::KeepAliveOption, "1");   //设置保持连接状态

    //断开连接时退出循环关闭线程
    connect(&socket, SIGNAL(disconnected()), this, SLOT(changeState()));

    //保存客户端地址和端口
    m_client.first = socket.peerAddress().toString().toStdString();
    m_client.second = socket.peerPort();

    std::cout << "Client " << m_client.first << ":"
              << m_client.second << " connect successfully\n";

    //有效循环
    while(m_valid)
    {
        //等待客户端请求事件
        socket.waitForReadyRead(10000000);
        QByteArray byte;
        do{
            byte += socket.readAll();
        }while(socket.waitForReadyRead(2));

        QJsonDocument jsondoc;
        QJsonParseError jsonerror;
        jsondoc = QJsonDocument::fromJson(byte, &jsonerror);
        if(jsonerror.error == QJsonParseError::NoError)
        {
            std::cout << m_client.first << ":" << m_client.second << "\n";
            std::cout << jsondoc.toJson(QJsonDocument::Indented).toStdString();

            //回复客户端请求
            QByteArray send_byte = translateClient(jsondoc);
            socket.write(send_byte);
            socket.waitForBytesWritten();
        }
    }

    std::cout << "Client " << m_client.first << ":" << m_client.second << " disconnected\n";
}

QByteArray Convey_thread::translateClient(QJsonDocument jsondoc)
{
    QJsonObject jsonobj;
    QJsonValue jsonvalue;
    if(jsondoc.isObject())
    {
        jsonobj = jsondoc.object();

        //客户端请求验证
        if(jsonobj.contains("verify"))
        {
            jsonvalue = jsonobj.take("verify");
            if(jsonvalue.isObject())
            {
                return translateVerify(jsonvalue.toObject());
            }
        }

        //客户端请求数据
        if(jsonobj.contains("get"))
        {
            jsonvalue = jsonobj.take("get");
            return translateGet(jsonvalue);
        }

        //客户端请求修改数据
        if(jsonobj.contains("post"))
        {
            jsonvalue = jsonobj.take("post");
            if(jsonvalue.isObject())
            {
                return translatePost(jsonvalue.toObject());
            }
        }
    }
}

QByteArray Convey_thread::translateVerify(QJsonObject jsonobj)
{
    QJsonValue jsonvalue;
    QJsonObject tempobj;

    QString username, password;
    if(jsonobj.contains("username"))
    {
        jsonvalue = jsonobj.take("username");
        if(jsonvalue.isString())
        {
            username = jsonvalue.toString();
        }
    }
    if(jsonobj.contains("password"))
    {
        jsonvalue = jsonobj.take("password");
        if(jsonvalue.isString())
        {
            password = jsonvalue.toString();
        }
    }

    User* temp_user = m_envir->checkUserStudent(username.toStdString(), password.toStdString());
    if(!temp_user){
        temp_user = m_envir->checkUserTeacher(username.toStdString(), password.toStdString());
        if(!temp_user){
            temp_user = m_envir->checkUserAdmin(username.toStdString(), password.toStdString());
        }
    }

    //验证用户成功
    if(temp_user){
        tempobj.insert("ack", true);
        tempobj.insert("user", generateUser(temp_user));

        m_user = m_envir->findUser(username.toStdString());     //缓存用户对象指针
        if(m_user->getUserType() == user_type::student)
        {
            m_envir->setCourseStudent((Student*)m_user);
        }
        else if(m_user->getUserType() == user_type::teacher)
        {
            m_envir->setCourseTeacher((Teacher*)m_user);
        }
        else if(m_user->getUserType() == user_type::admin)
        {
            ((Admin*)m_user)->activateEnvir(m_envir);
        }
    }
    else{
        tempobj.insert("ack", false);

        m_user = NULL;
    }

    QJsonDocument jsondoc;
    jsondoc.setObject(tempobj);
    return jsondoc.toJson();
}

QByteArray Convey_thread::translateGet(QJsonValue get_value)
{
    QJsonValue jsonvalue;
    QJsonDocument jsondoc;
    QJsonArray jsonarray;
    QJsonObject jsonobj, tempobj;

    if(!m_user)
    {
        jsonobj = generateAck(false);
        jsondoc.setObject(jsonobj);
        return jsondoc.toJson(QJsonDocument::Compact);
    }

    if(get_value.isString())
    {
        QString get_string = get_value.toString();

        //获取当前课程
        if(get_string == "cur_course")
        {
            if(m_user->getUserType() == user_type::student)
            {
                Student* cur_student = (Student*)m_user;
                m_envir->setCourseStudent(cur_student);

                for(auto i : cur_student->getCourse())
                {
                    jsonarray.append(generateCourse(i));
                }
            }
            else if(m_user->getUserType() == user_type::teacher)
            {
                Teacher* cur_teacher = (Teacher*)m_user;
                m_envir->setCourseTeacher(cur_teacher);

                for(auto i : cur_teacher->getCourse())
                {
                    jsonarray.append(generateCourse(i));
                }
            }
            else if(m_user->getUserType() == user_type::admin)
            {
                Admin* cur_admin = (Admin*)m_user;
                for(auto i : cur_admin->getEnvir()->getElectiveCourse())
                {
                    jsonarray.append(generateCourse(i));
                }
                for(auto i : cur_admin->getEnvir()->getObligatoryCourse())
                {
                    jsonarray.append(generateCourse(i));
                }
            }

            jsonobj.insert("cur_course", jsonarray);
        }

        //学生获取可选课程
        else if(get_string == "sel_course")
        {
            if(m_user->getUserType() == user_type::student)
            {
                Student* cur_student = (Student*)m_user;
                for(auto i : cur_student->getSelectCourse())
                {
                    jsonarray.append(generateCourse(i));
                }
                jsonobj.insert("sel_course", jsonarray);
            }
        }

        //管理员获取所有用户
        else if(get_string == "user")
        {
            if(m_user->getUserType() == user_type::admin)
            {
                Admin* cur_admin = (Admin*)m_user;
                for(auto i : cur_admin->getEnvir()->getUserStudent())
                {
                    tempobj = generateUser(i.first);
                    tempobj.insert("password", QString::fromStdString(i.second));
                    jsonarray.append(tempobj);
                }
                for(auto i : cur_admin->getEnvir()->getUserTeacher())
                {
                    tempobj = generateUser(i.first);
                    tempobj.insert("password", QString::fromStdString(i.second));
                    jsonarray.append(tempobj);
                }
                for(auto i : cur_admin->getEnvir()->getUserAdmin())
                {
                    tempobj = generateUser(i.first);
                    tempobj.insert("password", QString::fromStdString(i.second));
                    jsonarray.append(tempobj);
                }
                jsonobj.insert("user", jsonarray);
            }
        }
    }

    else if(get_value.isObject())
    {
        QJsonObject get_object = get_value.toObject();

        //获取课程详细信息
        if(get_object.contains("course_info"))
        {
            QJsonObject info_obj;

            jsonvalue = get_object.take("course_info");
            if(jsonvalue.isString())
            {
                QString course_id = jsonvalue.toString();

                if(m_user->getUserType() == user_type::teacher)
                {
                    Teacher* cur_teacher = (Teacher*)m_user;
                    Course_teacher* cur_course = cur_teacher->findCourse(course_id.toStdString());
                    info_obj.insert("course", generateCourse(cur_course));  //插入课程信息

                    for(auto i : cur_course->getStudentGrade()) //生成学生名单
                    {
                        tempobj = generateUser(i.first);
                        tempobj.insert("grade", i.second);
                        jsonarray.append(tempobj);
                    }

                    info_obj.insert("student", jsonarray);          //插入学生信息
                }
                else if(m_user->getUserType() == user_type::admin)
                {
                    Admin* cur_admin = (Admin*)m_user;
                    Course* cur_course = cur_admin->getEnvir()->findCourse(course_id.toStdString());
                    if(cur_course)
                    {
                        info_obj.insert("course", generateCourse(cur_course));

                        for(auto i : cur_course->getStudent())
                        {
                            jsonarray.append(generateUser(i));
                        }

                        info_obj.insert("student", jsonarray);
                    }
                }

                jsonobj.insert("course_info", info_obj);
            }
        }

        //获取用户详细信息
        if(get_object.contains("user_info"))
        {
            jsonvalue = get_object.take("user_info");
            QJsonObject info_obj;

            if(jsonvalue.isString())
            {
                QString user_id = jsonvalue.toString();

                if(m_user->getUserType() == user_type::admin)
                {
                    Admin* cur_admin = (Admin*)m_user;
                    User* cur_user = cur_admin->getEnvir()->findUser(user_id.toStdString());
                    if(cur_user)
                    {
                        info_obj.insert("user", generateUser(cur_user));

                        if(cur_user->getUserType() == user_type::student)
                        {
                            Student* cur_student = (Student*)cur_user;
                            cur_admin->getEnvir()->setCourseStudent(cur_student);
                            for(auto i : cur_student->getCourse())
                            {
                                jsonarray.append(generateCourse(i));
                            }
                        }
                        else if(cur_user->getUserType() == user_type::teacher)
                        {
                            Teacher* cur_teacher = (Teacher*)cur_user;
                            cur_admin->getEnvir()->setCourseTeacher(cur_teacher);
                            for(auto i : cur_teacher->getCourse())
                            {
                                jsonarray.append(generateCourse(i));
                            }
                        }

                        info_obj.insert("course", jsonarray);
                    }
                }
                jsonobj.insert("user_info", info_obj);
            }
        }
    }

    jsondoc.setObject(jsonobj);
    return jsondoc.toJson(QJsonDocument::Compact);
}

QByteArray Convey_thread::translatePost(QJsonObject jsonobj)
{
    if(!m_user)
        return QByteArray("");

    QJsonDocument jsondoc;
    QJsonObject rtnobj = generateAck(false), tempobj;
    QJsonValue jsonvalue;
    QJsonArray jsonarray;

    //学生选择选修课
    if(jsonobj.contains("sel_course"))
    {
        jsonvalue = jsonobj.take("sel_course");
        if(jsonvalue.isString())
        {
            QString course_id = jsonvalue.toString();
            if(m_user->getUserType() == user_type::student)
            {
                Student* cur_student = (Student*)m_user;
                Course_student* cur_course = cur_student->findSelCourse(course_id.toStdString());

                if(cur_course)
                {
                    cur_student->addCourse(cur_course);
                    rtnobj = generateAck(true);

                    if(m_config)
                    {
                        m_config->writeConfig();
                    }
                }
            }
        }
    }

    //学生删除选修课或者管理员删除课程
    if(jsonobj.contains("del_course"))
    {
        jsonvalue = jsonobj.take("del_course");
        if(jsonvalue.isString())
        {
            QString course_id = jsonvalue.toString();

            //学生删除选修课
            if(m_user->getUserType() == user_type::student)
            {
                Student* cur_student = (Student*)m_user;
                Course_student* cur_course = cur_student->findCourse(course_id.toStdString());

                if(cur_course)
                {
                    cur_student->deleteCourse(cur_course);
                    rtnobj = generateAck(true);

                    if(m_config)
                    {
                        m_config->writeConfig();
                    }
                }
            }

            //管理员删除课程
            else if(m_user->getUserType() == user_type::admin)
            {
                Admin* cur_admin = (Admin*)m_user;
                Course* course = cur_admin->getEnvir()->findCourse(course_id.toStdString());
                cur_admin->getEnvir()->deleteCourse(course);
                rtnobj = generateAck(true);

                if(m_config)
                {
                    m_config->writeConfig();
                }
            }
        }
    }

    //获取当前课程id
    QString course_id = "";
    if(jsonobj.contains("course_id"))
    {
        jsonvalue = jsonobj.take("course_id");
        if(jsonvalue.isString())
        {
            course_id = jsonvalue.toString();
        }
    }

    //教师更改学生成绩
    if(jsonobj.contains("stu_grade"))
    {
        jsonvalue = jsonobj.take("stu_grade");
        if(m_user->getUserType() == user_type::teacher)
        {
            Teacher* cur_teacher = (Teacher*)m_user;
            Course_teacher* cur_course = cur_teacher->findCourse(course_id.toStdString());

            if(cur_course)
            {
                if(jsonvalue.isObject())
                {
                    QJsonObject tempobj = jsonvalue.toObject();
                    for(auto i : tempobj.keys())
                    {
                        Student* pre_student = cur_course->findStudent(i.toStdString());
                        float grade = tempobj.take(i).toDouble();
                        try{
                            cur_course->setGrade(std::make_pair(pre_student, grade));
                            rtnobj = generateAck(true);

                            if(m_config)
                            {
                                m_config->writeConfig();
                            }
                        }
                        catch(std::invalid_argument& e)
                        {
                            qDebug() << e.what();
                        }
                    }
                }
            }
        }
    }

    //管理员删除用户
    if(jsonobj.contains("del_user"))
    {
        jsonvalue = jsonobj.take("del_user");
        if(jsonvalue.isString())
        {
            QString user_id = jsonvalue.toString();
            if(m_user->getUserType() == user_type::admin)
            {
                Admin* cur_admin = (Admin*)m_user;
                User* pre_user = cur_admin->getEnvir()->findUser(user_id.toStdString());
                cur_admin->getEnvir()->deleteUser(pre_user);

                rtnobj = generateAck(true);
                if(m_config)
                {
                    m_config->writeConfig();
                }
            }
        }
    }

    //管理员添加课程
    if(jsonobj.contains("add_course"))
    {
        jsonvalue = jsonobj.take("add_course");
        if(jsonvalue.isObject())
        {
            tempobj = jsonvalue.toObject();
            Course* cur_course = NULL;

            if(tempobj.contains("course"))
            {
                jsonvalue = tempobj.take("course");
                if(jsonvalue.isObject())
                {
                    cur_course = translateJsonCourse(jsonvalue.toObject());
                }
            }

            if(!cur_course)
            {
                rtnobj = generateAck(false);
                rtnobj.insert("hint", "课程生成失败！");
            }
            else
            {
                try
                {
                    if(tempobj.contains("course_stu"))
                    {
                        jsonvalue = tempobj.take("course_stu");
                        if(jsonvalue.isArray())
                        {
                            jsonarray = jsonvalue.toArray();
                            for(auto i : jsonarray)
                            {
                                if(i.isString())
                                {
                                    User* cur_user = m_envir->findUser(i.toString().toStdString());
                                    if(cur_user && cur_user->getUserType() == user_type::student)
                                    {
                                        Student* cur_student = (Student*)cur_user;
                                        cur_course->addStudent(cur_student);
                                    }
                                }
                            }
                        }
                    }

                    if(cur_course->getCourseType())
                    {
                        m_envir->addObligatoryCourse((Obligatory_course*)cur_course);
                    }
                    else
                    {
                        m_envir->addElectiveCourse((Elective_course*)cur_course);
                    }

                    rtnobj = generateAck(true);

                    if(m_config)
                    {
                        m_config->writeConfig();
                    }
                }
                catch(std::exception& e)
                {
                    delete cur_course;
                    rtnobj = generateAck(false);
                    rtnobj.insert("hint", QString::fromLocal8Bit(e.what()));
                }
            }
        }
    }

    //管理员更新课程
    if(jsonobj.contains("update_course"))
    {
        jsonvalue = jsonobj.take("update_course");
        if(jsonvalue.isObject())
        {
            tempobj = jsonvalue.toObject();
            Course* new_course = NULL;

            if(tempobj.contains("course"))
            {
                jsonvalue = tempobj.take("course");
                if(jsonvalue.isObject())
                {
                    new_course = translateJsonCourse(jsonvalue.toObject());
                }
            }

            if(!new_course)
            {
                rtnobj = generateAck(false);
                rtnobj.insert("hint", "课程生成失败！");
            }
            else
            {
                try
                {
                    //设置课程属性
                    std::string id = new_course->getID();
                    Course* cur_course = m_envir->findCourse(id);
                    if(!cur_course)
                        throw std::runtime_error("未找到课程!");

                    cur_course->setCapicity(new_course->getCapicity());
                    cur_course->setTeacher(new_course->getTeacher());

                    //提前删除课程中学生
                    for(auto i : cur_course->getStudent())
                    {
                        cur_course->deleteStudent(i);
                    }

                    if(tempobj.contains("course_stu"))
                    {
                        jsonvalue = tempobj.take("course_stu");
                        if(jsonvalue.isArray())
                        {
                            jsonarray = jsonvalue.toArray();
                            for(auto i : jsonarray)
                            {
                                if(i.isString())
                                {
                                    User* cur_user = m_envir->findUser(i.toString().toStdString());
                                    if(cur_user && cur_user->getUserType() == user_type::student)
                                    {
                                        Student* cur_student = (Student*)cur_user;
                                        cur_course->addStudent(cur_student);
                                    }
                                }
                            }
                        }
                    }

                    rtnobj = generateAck(true);

                    if(m_config)
                    {
                        m_config->writeConfig();
                    }
                }
                catch(std::exception& e)
                {
                    rtnobj = generateAck(false);
                    rtnobj.insert("hint", QString::fromLocal8Bit(e.what()));
                }
                delete new_course;
            }
        }
    }

    //管理员添加用户
    if(jsonobj.contains("add_user"))
    {
        jsonvalue = jsonobj.take("add_user");
        if(jsonvalue.isObject())
        {
            tempobj = jsonvalue.toObject();
            User* cur_user = NULL;
            QString password = "";

            if(tempobj.contains("user"))
            {
                jsonvalue = tempobj.take("user");
                if(jsonvalue.isObject())
                {
                    QJsonObject userobj = jsonvalue.toObject();
                    cur_user = translateJsonUser(userobj);
                    if(userobj.contains("password"))
                        password = userobj.take("password").toString();
                }
            }

            if(!cur_user)
            {
                rtnobj = generateAck(false);
                rtnobj.insert("hint", "用户生成失败！");
            }
            else
            {
                try
                {
                    //向课程中添加学生
                    if(tempobj.contains("user_course"))
                    {
                        jsonvalue = tempobj.take("user_course");
                        if(jsonvalue.isArray())
                        {
                            jsonarray = jsonvalue.toArray();
                            for(auto i : jsonarray)
                            {
                                if(i.isString())
                                {
                                    Course* cur_course = m_envir->findCourse(i.toString().toStdString());
                                    if(cur_course)
                                    {
                                        if(cur_user->getUserType() == user_type::student)
                                        {
                                            cur_course->addStudent((Student*)cur_user);
                                        }
                                        else if(cur_user->getUserType() == user_type::teacher)
                                        {
                                            cur_course->setTeacher((Teacher*)cur_user);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if(cur_user->getUserType() == user_type::student)
                    {
                        m_envir->addUserStudent((Student*)cur_user, password.toStdString());
                    }
                    else if(cur_user->getUserType() == user_type::teacher)
                    {
                        m_envir->addUserTeacher((Teacher*)cur_user, password.toStdString());
                    }
                    else if(cur_user->getUserType() == user_type::admin)
                    {
                        m_envir->addUserAdmin((Admin*)cur_user, password.toStdString());
                    }

                    rtnobj = generateAck(true);

                    if(m_config)
                    {
                        m_config->writeConfig();
                    }
                }
                catch(std::exception& e)
                {
                    delete cur_user;
                    rtnobj = generateAck(false);
                    rtnobj.insert("hint", QString::fromLocal8Bit(e.what()));
                }
            }
        }
    }

    //管理员更新用户
    if(jsonobj.contains("update_user"))
    {
        jsonvalue = jsonobj.take("update_user");
        if(jsonvalue.isObject())
        {
            tempobj = jsonvalue.toObject();
            User* new_user = NULL;
            QString password = "";

            if(tempobj.contains("user"))
            {
                jsonvalue = tempobj.take("user");
                if(jsonvalue.isObject())
                {
                    QJsonObject userobj = jsonvalue.toObject();
                    new_user = translateJsonUser(userobj);
                    if(userobj.contains("password"))
                        password = userobj.take("password").toString();
                }
            }

            if(!new_user)
            {
                rtnobj = generateAck(false);
                rtnobj.insert("hint", "用户生成失败！");
            }
            else
            {
                try
                {
                    User* cur_user = m_envir->findUser(new_user->getID());
                    if(!cur_user)
                        throw std::runtime_error("未找到用户！");
                    if(password != "")
                        m_envir->changeUserPass(cur_user, password.toStdString());

                    //提前从课程删除学生
                    if(cur_user->getUserType() == user_type::student)
                    {
                        Student* cur_student = (Student*)cur_user;
                        for(auto i : cur_student->getCourse())
                        {
                            Course* flag_course = m_envir->findCourse(i->getID());
                            if(flag_course)
                                flag_course->deleteStudent(cur_student);
                        }

                        cur_student->setClass(((Student*)new_user)->getClass());
                    }
                    else if(cur_user->getUserType() == user_type::teacher)
                    {
                        Teacher* cur_teacher = (Teacher*)cur_user;
                        for(auto i : cur_teacher->getCourse())
                        {
                            Course* flag_course = m_envir->findCourse(i->getID());
                            if(flag_course)
                                flag_course->setTeacher(NULL);
                        }
                    }

                    //向课程中添加学生
                    if(tempobj.contains("user_course"))
                    {
                        jsonvalue = tempobj.take("user_course");
                        if(jsonvalue.isArray())
                        {
                            jsonarray = jsonvalue.toArray();
                            for(auto i : jsonarray)
                            {
                                if(i.isString())
                                {
                                    Course* cur_course = m_envir->findCourse(i.toString().toStdString());
                                    if(cur_course)
                                    {
                                        if(cur_user->getUserType() == user_type::student)
                                        {
                                            cur_course->addStudent((Student*)cur_user);
                                        }
                                        else if(cur_user->getUserType() == user_type::teacher)
                                        {
                                            cur_course->setTeacher((Teacher*)cur_user);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    rtnobj = generateAck(true);

                    if(m_config)
                    {
                        m_config->writeConfig();
                    }
                }
                catch(std::exception& e)
                {
                    rtnobj = generateAck(false);
                    rtnobj.insert("hint", QString::fromLocal8Bit(e.what()));
                }
                delete new_user;
            }
        }
    }

    jsondoc.setObject(rtnobj);
    return jsondoc.toJson(QJsonDocument::Compact);
}

QJsonObject Convey_thread::generateAck(bool ack_flag)
{
    QJsonObject jsonobj;
    jsonobj.insert("ack", ack_flag);
    return jsonobj;
}

QJsonObject Convey_thread::generateUser(User *user)
{
    QJsonObject jsonobj;

    jsonobj.insert("id", QString::fromStdString(user->getID()));
    jsonobj.insert("name", QString::fromStdString(user->getName()));
    jsonobj.insert("institude", QString::fromStdString(user->getInsititude()));

    switch(user->getUserType())
    {
    case user_type::student:
    {
        Student* temp_student = (Student*)user;
        jsonobj.insert("class_name", QString::fromStdString(temp_student->getClass()));
        jsonobj.insert("user_type", 2);
        break;
    }

    case user_type::teacher:
    {
        Teacher* temp_teacher = (Teacher*)user;
        jsonobj.insert("user_type", 1);
        break;
    }

    case user_type::admin:
    {
        Admin* temp_admin = (Admin*)user;
        jsonobj.insert("user_type", 0);
        break;
    }

    default:
        break;
    }

    return jsonobj;
}

QJsonObject Convey_thread::generateCourse(Course *course)
{
    QJsonObject jsonobj;
    if(!m_user)
        return jsonobj;
    jsonobj.insert("id", QString::fromStdString(course->getID()));
    jsonobj.insert("name", QString::fromStdString(course->getName()));
    jsonobj.insert("credit", course->getCredit());
    jsonobj.insert("capacity", course->getCapicity());
    jsonobj.insert("course_type", course->getCourseType());
    jsonobj.insert("cur_num", (int)course->getStudent().size());
    if(course->getTeacher())
    {
        jsonobj.insert("teacher_id", QString::fromStdString(course->getTeacher()->getID()));
    }
    else
    {
        jsonobj.insert("teacher_id", "");
    }
    return jsonobj;
}

QJsonObject Convey_thread::generateCourse(Course_user *course)
{
    QJsonObject jsonobj;
    if(!m_user)
        return jsonobj;
    jsonobj.insert("id", QString::fromStdString(course->getID()));
    jsonobj.insert("name", QString::fromStdString(course->getName()));
    jsonobj.insert("credit", course->getCredit());
    jsonobj.insert("capacity", course->getCapicity());
    jsonobj.insert("course_type", course->getCourseType());

    if(m_user->getUserType() == user_type::student)
    {
        Course_student* cur_course = (Course_student*)course;
        jsonobj.insert("cur_num", cur_course->getElectiveNum());
        jsonobj.insert("grade", cur_course->getMyGrade((Student*)m_user));
        jsonobj.insert("gpa", cur_course->calculateGPA((Student*)m_user));
        jsonobj.insert("teacher_id", QString::fromStdString(cur_course->getTeacherName()));
    }
    else if(m_user->getUserType() == user_type::teacher)
    {
        Course_teacher* cur_course = (Course_teacher*)course;
        jsonobj.insert("cur_num", (int)cur_course->getStudent().size());
    }

    return jsonobj;
}

void Convey_thread::changeState()
{
    this->m_valid = false;
}

User* Convey_thread::translateJsonUser(QJsonObject jsonobj)
{
    QJsonValue jsonvalue;
    User* cur_user = NULL;
    std::string id, name, institude;

    if(jsonobj.contains("id"))
    {
        jsonvalue = jsonobj.take("id");
        if(jsonvalue.isString())
        {
            id = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("name"))
    {
        jsonvalue = jsonobj.take("name");
        if(jsonvalue.isString())
        {
            name = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("institude"))
    {
        jsonvalue = jsonobj.take("institude");
        if(jsonvalue.isString())
        {
            institude = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("user_type"))
    {
        jsonvalue = jsonobj.take("user_type");
        if(jsonvalue.isDouble())
        {
             int cur_type = jsonvalue.toVariant().toInt();
             if(cur_type == 0)
             {
                 cur_user = new Admin(id, name, institude);
             }
             else if(cur_type == 1)
             {
                 cur_user = new Teacher(id, name, institude);
             }
             else if(cur_type == 2)
             {
                 cur_user = new Student(id, name, institude);
             }
        }
    }

    if(!cur_user)
        return NULL;

    if(jsonobj.contains("class_name"))
    {
        jsonvalue = jsonobj.take("class_name");
        if(jsonvalue.isString())
        {
            std::string class_name = jsonvalue.toString().toStdString();
            if(cur_user->getUserType() == user_type::student)
            {
                ((Student*)cur_user)->setClass(class_name);
            }
        }
    }

    return cur_user;
}

Course* Convey_thread::translateJsonCourse(QJsonObject jsonobj)
{
    QJsonValue jsonvalue;
    Course* cur_course;

    std::string id, name;
    int credit;

    if(jsonobj.contains("id"))
    {
        jsonvalue = jsonobj.take("id");
        if(jsonvalue.isString())
        {
            id = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("name"))
    {
        jsonvalue = jsonobj.take("name");
        if(jsonvalue.isString())
        {
            name = jsonvalue.toString().toStdString();
        }
    }

    if(jsonobj.contains("credit"))
    {
        jsonvalue = jsonobj.take("credit");
        if(jsonvalue.isDouble())
        {
            credit = jsonvalue.toVariant().toInt();
        }
    }

    if(jsonobj.contains("course_type"))
    {
        jsonvalue = jsonobj.take("course_type");
        if(jsonvalue.isDouble())
        {
            int course_type = jsonvalue.toVariant().toInt();
            if(course_type)
            {
                cur_course = new Obligatory_course(id, name, credit);
            }
            else
            {
                cur_course = new Elective_course(id, name, credit);
            }
        }
    }

    if(!cur_course)
        return NULL;

    if(jsonobj.contains("capacity"))
    {
        jsonvalue = jsonobj.take("capacity");
        if(jsonvalue.isDouble())
        {
            int capacity = jsonvalue.toVariant().toInt();
            cur_course->setCapicity(capacity);
        }
    }

    if(jsonobj.contains("teacher_id"))
    {
        jsonvalue = jsonobj.take("teacher_id");
        if(jsonvalue.isString())
        {
            std::string teacher_id = jsonvalue.toString().toStdString();
            User* cur_teacher = m_envir->findUser(teacher_id);
            if(cur_teacher && cur_teacher->getUserType() == user_type::teacher)
            {
                cur_course->setTeacher((Teacher*)cur_teacher);
            }
        }
    }

    return cur_course;
}
