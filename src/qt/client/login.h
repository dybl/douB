#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "include.h"
#include "envir_widget.h"
#include "convey.h"
#include "model_struct.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void setEnvir(Envir_widget* envir_widget);        //设置系统运行环境

private slots:
    void on_login_btn_clicked();

    void on_cancel_btn_clicked();

private:
    Ui::Login *ui;
    Envir_widget* m_envir_widget;
};

#endif // LOGIN_H
