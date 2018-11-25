#ifndef MAINWINDOW_TEACHER_H
#define MAINWINDOW_TEACHER_H

#include <QLabel>
#include <QTimer>
#include <QMainWindow>
#include <QStandardItemModel>

#include "include.h"
#include "envir_widget.h"

namespace Ui {
class MainWindow_teacher;
}

class MainWindow_teacher : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_teacher(Envir_widget* envir_widget, QWidget *parent = 0);
    ~MainWindow_teacher();

    void initActivex();       //控件信息初始化
    void creatAction();

    void showInfo();           //显示用户信息
    void updateTable();      //表格信息更新
    void updateStudent();       //更新学生列表

    void setEnvirWidget(Envir_widget* envir_widget);
    void setUserModel(User_model user);   //设置当前登录用户

    void initStatusBar();

signals:
    void updateConfig();

private slots:
    void action_login_triggered();
    void action_quit_triggered();
    void action_course_triggered();
    void action_set_grade_triggered();
    void action_about_triggered();
    void action_help_triggered();
    void action_change_pass_triggered();

    void on_comboBox_course_currentIndexChanged(int index);

    void on_cancel_btn_clicked();
    void on_confirm_btn_clicked();

    void updateStatusBar();
    void sort_student(int);

    void flush_btn_clicked();

private:
    Ui::MainWindow_teacher *ui;
    Envir_widget* m_envir_widget;
    QStandardItemModel* ui_course_model;
    QStandardItemModel* ui_student_model;

    User_model m_user;

    QLabel* ui_label_status;
    QLabel* ui_label_time;
    QTimer* m_timer_status;
};

#endif // MAINWINDOW_TEACHER_H
