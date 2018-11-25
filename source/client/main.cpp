/**
 * Name: main.cpp
 * User: L.Laddie
 * Function: 主函数入口
 */

#include <QDialog>
#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include <QMessageBox>
#include <QCryptographicHash>

#include "login.h"
#include "convey.h"
#include "include.h"
#include "envir_widget.h"
#include "mainwindow_admin.h"
#include "mainwindow_student.h"
#include "mainwindow_teacher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/image/icon.ico"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    //设置通信模块
    Convey convey;

    //设置界面环境
    Envir_widget envir_widget;
    envir_widget.setConvey(&convey);

    //设置登录界面
    Login widget_login;
    widget_login.setEnvir(&envir_widget);

    //设置主界面
    MainWindow_admin widget_main_admin(&envir_widget);
    MainWindow_teacher widget_main_teacher(&envir_widget);
    MainWindow_student widget_main_student(&envir_widget);

    //保存所有主界面指针
    envir_widget.setWidget(&widget_login, &widget_main_student, &widget_main_teacher, &widget_main_admin);

    //尝试登陆
    try{
        convey.connectToHost("127.0.0.1", 10010);
    }
    catch(std::exception &e){
        QMessageBox::warning(&widget_main_student, QString::fromLocal8Bit("警告"), QString::fromStdString(e.what()));
        exit(1);
    }

    //显示登录界面
    widget_login.show();

    return a.exec();
}
