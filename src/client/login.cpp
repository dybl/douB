/**
 * Name: login.cpp
 * User: L.Laddie
 * Function: 登录界面
 */

#include <QDebug>
#include <QString>
#include <QCryptographicHash>
#include <QMessageBox>

#include "login.h"
#include "ui_login.h"
#include "envir_widget.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->wrong_label->close();
//    ui->hello_label->setAttribute(Qt::WA_TranslucentBackground);
//    ui->password_label->setAttribute(Qt::WA_TranslucentBackground);
//    ui->username_label->setAttribute(Qt::WA_TranslucentBackground);
//    ui->gridLayoutWidget->setAttribute(Qt::WA_TranslucentBackground);
//    ui->horizontalLayoutWidget->setAttribute(Qt::WA_TranslucentBackground);
//    ui->wrong_label->setAttribute(Qt::WA_TranslucentBackground);
//    ui->cancel_btn->setAttribute(Qt::WA_TranslucentBackground);
//    ui->login_btn->setAttribute(Qt::WA_TranslucentBackground);
}

Login::~Login()
{
    delete ui;
}

void Login::setEnvir(Envir_widget* envir_widget)
{
    this->m_envir_widget = envir_widget;
}

void Login::on_login_btn_clicked()
{
    QString username = ui->username_edit->text();
    QString password = ui->passowrd_edit->text();

    ui->passowrd_edit->clear();
    ui->wrong_label->close();

    //密码采用md5加密
    QByteArray temp = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5);
    QString md5_password = temp.toHex();

    //寻找输入用户
    User_model cur_user = m_envir_widget->getConvey()->verifyUser(username, md5_password);

    //验证失败
    if(cur_user.id == ""){
        ui->wrong_label->show();
        return;
    }

    //判断用户类型
    switch(cur_user.user_type)
    {

    //设置管理员界面
    case 0:
    {
        this->close();
        m_envir_widget->showAdminWidget(cur_user);
        break;
    }

    //设置教师界面
    case 1:
    {
        this->close();
        m_envir_widget->showTeacherWidget(cur_user);
        break;
    }

    //设置学生界面
    case 2:
    {
        this->close();
        m_envir_widget->showStudentWidget(cur_user);
        break;
    }

    default:
        break;
    }
}

void Login::on_cancel_btn_clicked()
{
    this->close();
    exit(0);
}
