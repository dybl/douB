#ifndef ENVIR_WIDGET_H
#define ENVIR_WIDGET_H

#include <QApplication>

#include "include.h"
#include "convey.h"
#include "model_struct.h"
#include "mainwindow_admin.h"
#include "mainwindow_student.h"
#include "mainwindow_teacher.h"

//界面环境
class Envir_widget : public QObject
{
    Q_OBJECT

public:
    explicit Envir_widget(){}

    void setWidget(Login* login, MainWindow_student* student, MainWindow_teacher* teacher, MainWindow_admin* admin);

    //打开指定界面
    void showLoginWidget();
    void showAdminWidget(User_model user);
    void showStudentWidget(User_model user);
    void showTeacherWidget(User_model user);

    //获取传送模块
    void setConvey(Convey* convey);
    Convey* getConvey();

private:
    //保存当前界面指针
    Login* m_widget_login;
    MainWindow_admin* m_widget_admin;
    MainWindow_student* m_widget_student;
    MainWindow_teacher* m_widget_teacher;

    //保存通信模块
    Convey* m_convey;
};

#endif // ENVIR_WIDGET_H
