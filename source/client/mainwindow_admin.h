#ifndef MAINWINDOW_ADMIN_H
#define MAINWINDOW_ADMIN_H

#include <QLabel>
#include <QTimer>
#include <QMainWindow>
#include <QStandardItemModel>

#include "envir_widget.h"
#include "model_struct.h"
#include "information_course.h"
#include "information_user.h"

namespace Ui {
class MainWindow_admin;
}

class MainWindow_admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_admin(Envir_widget* envir_widget, QWidget *parent = 0);
    ~MainWindow_admin();

    void setEnvirWidget(Envir_widget* envir_widget);
    void setUserModel(User_model user);   //设置当前登录用户

    void creatAction();

    void showInfo();         //显示用户信息
    void initActivex();      //控件信息初始化
    void updateTable();    //表格信息更新

    void initStatusBar();

private slots:
    void action_login_triggered();
    void action_quit_triggered();
    void action_course_o_triggered();
    void action_course_e_triggered();
    void action_course_add_triggered();
    void action_student_d_triggered();
    void action_teacher_d_triggered();
    void action_admin_d_triggered();
    void action_user_add_triggered();
    void action_start_course_triggered();
    void action_about_triggered();
    void action_help_triggered();

    void updateTable_slots();
    void update_course_slots();
    void update_user_slots();

    void updateStatusBar();

private:
    Ui::MainWindow_admin *ui;
    Envir_widget* m_envir_widget;
    User_model m_user;

    QStandardItemModel* ui_course_model_o;
    QStandardItemModel* ui_course_model_e;
    QStandardItemModel* ui_student_model;
    QStandardItemModel* ui_teacher_model;
    QStandardItemModel* ui_admin_model;

    Information_course* m_info_course_widget;
    Information_user* m_info_user_widget;

    QLabel* ui_label_status;
    QLabel* ui_label_time;
    QTimer* m_timer_status;
};

#endif // MAINWINDOW_ADMIN_H
