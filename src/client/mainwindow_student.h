#ifndef MAINWINDOW_STUDENT_H
#define MAINWINDOW_STUDENT_H

#include <QLabel>
#include <QTimer>
#include <QMainWindow>
#include <QStandardItemModel>

#include "include.h"
#include "envir_widget.h"

namespace Ui {
class MainWindow_student;
}

class MainWindow_student : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_student(Envir_widget* envir_widget, QWidget *parent = 0);
    ~MainWindow_student();

    void initActivex();       //控件信息初始化
    void creatAction();

    void showInfo();           //显示用户信息
    void updateTable();        //表格信息初始化

    void setEnvirWidget(Envir_widget* envir_widget);
    void setUserModel(User_model user);   //设置当前登录用户

    void initStatusBar();

private slots:
    void action_login_triggered();
    void action_quit_triggered();
    void action_course_o_triggered();
    void action_course_e_triggered();
    void action_start_course_triggered();
    void action_about_triggered();
    void action_help_triggered();
    void action_change_pass_triggered();

    void add_course_slots();
    void delete_course_slots();

    void updateStatusBar();

    void sort_course_o(int);
    void sort_course_e(int);

    void flush_btn_clicked();

private:
    Ui::MainWindow_student *ui;
    Envir_widget* m_envir_widget;
    QStandardItemModel* ui_course_model_o;
    QStandardItemModel* ui_course_model_e;
    QStandardItemModel* ui_course_model_s;

    User_model m_user;

    QLabel* ui_label_status;
    QLabel* ui_label_time;
    QTimer* m_timer_status;
};

#endif // MAINWINDOW_STUDENT_H
