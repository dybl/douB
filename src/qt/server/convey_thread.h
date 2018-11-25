#ifndef CONVEY_THREAD_H
#define CONVEY_THREAD_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>

#include "environment.h"
#include "config.h"

class Convey_thread: public QThread
{
    Q_OBJECT

public:
    Convey_thread(int socketDescriptor, Envir* envir, Config_file* config, QObject *parent);

    void run() Q_DECL_OVERRIDE;

    void setConfig(Config_file* config);

    //响应客户端请求并解析
    QByteArray translateClient(QJsonDocument jsondoc);
    QByteArray translateVerify(QJsonObject jsonobj);
    QByteArray translateGet(QJsonValue jsonvalue);
    QByteArray translatePost(QJsonObject jsonobj);

    QJsonObject generateAck(bool ack_flag);             //生成ack的Json对象
    QJsonObject generateUser(User* user);               //生成User的json对象
    QJsonObject generateCourse(Course* course);         //生成Course的json对象
    QJsonObject generateCourse(Course_user* course);

    User* translateJsonUser(QJsonObject jsonobj);
    Course* translateJsonCourse(QJsonObject jsonobj);

signals:
    void error(QTcpSocket::SocketError socketError);

private slots:
    void changeState();

private:
    int m_socketDescriptor;
    Envir* m_envir;
    Config_file* m_config;

    bool m_valid = true;        //当前连接是否断开
    std::pair<std::string, int> m_client;       //客户端信息

    User* m_user = NULL;
};

#endif // CONVEY_THREAD_H
