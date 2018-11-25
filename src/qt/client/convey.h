#ifndef CONVEY_H
#define CONVEY_H

#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QtCore>
#include <QMap>
#include "include.h"
#include "model_struct.h"

class Convey: public QObject
{
    Q_OBJECT

public:
    Convey();

    void connectToHost(QString hostname, int port);

    void sendJsonDoc(QJsonDocument jsondoc);                //发送jsondoc对象
    QJsonDocument revJsondoc();

    bool translateJsonAck(QJsonObject jsonobj);             //解析服务器端返回的确认包
    User_model translateJsonUser(QJsonObject jsonobj);      //解析jsonobj到User结构体
    Course_model translateJsonCourse(QJsonObject jsonobj);  //解析jsonobj到Course结构体

    QJsonObject generateJsonUser(User_model cur_user);               //从结构体生成json对象
    QJsonObject generateJsonCourse(Course_model cur_course);

    User_model verifyUser(QString username, QString password);     //登录验证用户

    std::vector<Course_model> getCourse(QString mode);
    std::vector<Course_model> getCurCourse();           //获取当前用户课程
    std::vector<Course_model> getSelCourse();           //学生获取可选课程

    std::map<User_model, std::string> getUser();      //管理员获取用户

    //获取对应课程或用户的详细信息
    std::pair<Course_model, std::vector<User_model> > getCourseInfo(QString course_id);
    std::pair<User_model, std::vector<Course_model> > getUserInfo(QString user_id);

    //通过mode选择添加还是删除课程或者用户
    void sendPost(QString id, QString mode);
    void sendSelCourse(QString course_id);
    void sendDelCourse(QString course_id);
    void sendDelUser(QString user_id);

    void sendStuGrade(QString course_id, QMap<QString, QVariant> stu_grade);

    //管理员修改指定课程或者用户的详细信息
    void sendCourseInfo(Course_model cur_course, std::vector<std::string> course_stu, QString mode);
    void sendAddCourse(Course_model cur_course, std::vector<std::string> course_stu);
    void sendUpdateCourse(Course_model cur_course, std::vector<std::string> course_stu);

    void sendUserInfo(User_model cur_user, QString password, std::vector<std::string> user_course, QString mode);
    void sendAddUser(User_model cur_user, QString password, std::vector<std::string> user_course);
    void sendUpdateUser(User_model cur_user, QString password, std::vector<std::string> user_course);

public slots:
    void destroyConnect();  //断开连接

private:
    QTcpSocket m_convey_socket;
};

#endif // CONVEY_H
