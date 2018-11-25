#ifndef CONVEY_SERVER_H
#define CONVEY_SERVER_H

#include <QObject>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>

#include "convey_thread.h"
#include "config.h"

class Convey_server: public QTcpServer
{
    Q_OBJECT

public:
    Convey_server(QObject *parent = 0);

    void setEnvir(Envir* envir);
    void setConfig(Config_file* config);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:
    QVector<int> m_client;

    Envir* m_envir;
    Config_file* m_config;
};

#endif // CONVEY_SERVER_H
