#ifndef USER_LOGIN_H
#define USER_LOGIN_H

#include "admin_form.h"
#include "reader_form.h"
#include <QDialog>
#include <QString>
#include <QMap>


namespace Ui {
class UserLogin;
}


class UserLogin : public QDialog
{
    Q_OBJECT

public:
    explicit UserLogin(QWidget *parent = 0);
    ~UserLogin();

private slots:
    void on_login_btn_clicked();
    void on_quit_btn_clicked();
    void on_reg_btn_clicked();

private:
    Ui::UserLogin *ui;
    int admin_counter;
    int reader_counter;
    int counter;
};

#endif // USER_LOGIN_H
