#include "user_login.h"
#include "connect_database.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserLogin w;
    w.show();

    return a.exec();
}
