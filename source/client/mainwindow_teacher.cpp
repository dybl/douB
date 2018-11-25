/**
 * Name: mainwindow_teacher.cpp
 * User: L.Laddie
 * Function: 教师界面
 */

#include <QDebug>
#include <QMap>
#include <QDateTime>
#include <QMessageBox>

#include "fun.h"
#include "model_struct.h"
#include "mainwindow_teacher.h"
#include "ui_mainwindow_teacher.h"

MainWindow_teacher::MainWindow_teacher(Envir_widget* envir_widget, QWidget *parent) :
    QMainWindow(parent),
    m_envir_widget(envir_widget),
    ui(new Ui::MainWindow_teacher)
{
    ui->setupUi(this);
    setFixedSize(800, 500);         //禁止更改大小

    initActivex();                  //初始化控件
    creatAction();                  //链接槽函数
    initStatusBar();                //初始化状态栏
}

MainWindow_teacher::~MainWindow_teacher()
{
    delete ui_label_status;
    delete ui_label_time;
    delete m_timer_status;
    delete ui;

    delete ui_course_model;
    delete ui_student_model;
}

void MainWindow_teacher::setEnvirWidget(Envir_widget* envir_widget)
{
    this->m_envir_widget = envir_widget;
}

void MainWindow_teacher::setUserModel(User_model user)
{
    this->m_user = user;
}

//初始化状态栏信息
void MainWindow_teacher::initStatusBar()
{
    ui_label_time->setAlignment(Qt::AlignRight);

    ui->statusbar->addWidget(ui_label_status, 1);
    ui->statusbar->addWidget(ui_label_time, 6);
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}, *{font-size : 8px}"));
}

//定时更新状态栏
void MainWindow_teacher::updateStatusBar()
{
    //设置实时人数信息
    int num = this->ui_course_model->rowCount();

    QString course_num = "所属课程：" + QString::number(num) + "个";
    ui_label_status->setText("实时信息：" + course_num);

    //设置实时系统时间
    QDateTime cur_time = QDateTime::currentDateTime();
    QString cur_time_str = cur_time.toString("hh:mm:ss");
    ui_label_time->setText("系统时间：" + cur_time_str);
}

//初始化控件
void MainWindow_teacher::initActivex()
{
    ui_course_model = new QStandardItemModel();
    ui_student_model = new QStandardItemModel();

    ui->tableView_course->setModel(ui_course_model);
    ui->tableView_student->setModel(ui_student_model);

    ui_label_status = new QLabel();
    ui_label_time = new QLabel();
    m_timer_status = new QTimer(this);
}

//更新课程表格
void MainWindow_teacher::updateTable()
{
    ui_course_model->clear();

    //设置必修课程列表
    ui_course_model->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("课程编号")));
    ui_course_model->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("课程名称")));
    ui_course_model->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("课程学分")));
    ui_course_model->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("课程类型")));
    ui_course_model->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("课程人数")));
    ui_course_model->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("课程容量")));

    int row = 0;
    std::vector<Course_model> cur_course;
    try
    {
        cur_course = m_envir_widget->getConvey()->getCurCourse();
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit(e.what()));
        return;
    }

    for(auto i : cur_course)
    {
        ui_course_model->setItem(row, 0, new QStandardItem(QString::fromStdString(i.id)));
        ui_course_model->setItem(row, 1, new QStandardItem(QString::fromStdString(i.name)));
        ui_course_model->setItem(row, 2, new QStandardItem(QString::number(i.credit)));
        ui_course_model->setItem(row, 3, new QStandardItem(i.course_type ? QString::fromLocal8Bit("必修") : QString::fromLocal8Bit("选修")));
        ui_course_model->setItem(row, 4, new QStandardItem(QString::number(i.cur_num)));
        ui_course_model->setItem(row, 5, new QStandardItem(QString::number(i.capacity)));
        row++;
    }

    ui_course_model->sort(0);
}

//初始化进入界面
void MainWindow_teacher::showInfo()
{
    ui->label_id->setText(QString::fromStdString(m_user.id));
    ui->label_name->setText(QString::fromStdString(m_user.name));
    ui->label_institude->setText(QString::fromStdString(m_user.institude));

    updateTable();

    //更新学生成绩界面
    ui->comboBox_course->clear();
    int num = ui_course_model->rowCount();
    for(int i = 0; i < num; i++)
    {
        ui->comboBox_course->addItem(ui_course_model->item(i, 0)->text());
        ui->comboBox_course->setCurrentIndex(0);
    }
    updateStudent();

    updateStatusBar();
    m_timer_status->start(1000);        //每一秒刷新一次状态栏
}

//更新学生表格
void MainWindow_teacher::updateStudent()
{
    if(ui->comboBox_course->currentIndex() != -1){
        //查找指定课程详细信息
        QString id = ui->comboBox_course->currentText();
        std::pair<Course_model, std::vector<User_model> > course_info = m_envir_widget->getConvey()->getCourseInfo(id);

        if(course_info.first.id == "")
            return;

        ui->label_course_id->setText(QString::fromStdString(course_info.first.id));
        ui->label_course_name->setText(QString::fromStdString(course_info.first.name));
        ui->label_course_credit->setText(QString::number(course_info.first.credit));
        ui->label_course_type->setText(course_info.first.course_type ? QString::fromLocal8Bit("必修") : QString::fromLocal8Bit("选修"));

        //更新学生表格信息
        ui_student_model->clear();

        ui_student_model->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("学号")));
        ui_student_model->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("姓名")));
        ui_student_model->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("班级")));
        ui_student_model->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("学院")));
        ui_student_model->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("成绩")));

        int row = 0;
        for(auto i : course_info.second)
        {
            ui_student_model->setItem(row, 0, new QStandardItem(QString::fromStdString(i.id)));
            ui_student_model->setItem(row, 1, new QStandardItem(QString::fromStdString(i.name)));
            ui_student_model->setItem(row, 2, new QStandardItem(QString::fromStdString(i.class_name)));
            ui_student_model->setItem(row, 3, new QStandardItem(QString::fromStdString(i.institude)));
            ui_student_model->setItem(row, 4, new QStandardItem(QString("%1").arg(i.grade)));
            row++;
        }
        ui_student_model->sort(0);
    }
}

//对学生排序
void MainWindow_teacher::sort_student(int column)
{
    static bool reverse = false;

    if(ui->comboBox_course->currentIndex() != -1){
        //查找当前选择课程
        QString id = ui->comboBox_course->currentText();
        auto course_info = m_envir_widget->getConvey()->getCourseInfo(id);

//        if(!course_info)
//            return;

        auto student_list = course_info.second;

        //判断当前需要对哪一项排序
        switch(column)
        {
        case 0:
        {
            Sort::sortVectorCourse(student_list, "id", reverse);
            reverse = !reverse;
            break;
        }

        case 4:
        {
            Sort::sortVectorCourse(student_list, "grade", reverse);
            reverse = !reverse;
            break;
        }

        default:
            return;
        }

        //重新更新表格
        for(int i = 0; i < student_list.size(); i++)
        {
            ui_student_model->setItem(i, 0, new QStandardItem(QString::fromStdString(student_list[i].id)));
            ui_student_model->setItem(i, 1, new QStandardItem(QString::fromStdString(student_list[i].name)));
            ui_student_model->setItem(i, 2, new QStandardItem(QString::fromStdString(student_list[i].class_name)));
            ui_student_model->setItem(i, 3, new QStandardItem(QString::fromStdString(student_list[i].institude)));
            ui_student_model->setItem(i, 4, new QStandardItem(QString("%1").arg(student_list[i].grade)));
        }
    }
}

//链接菜单栏按钮的槽函数
void MainWindow_teacher::creatAction()
{
    //菜单栏
    connect(ui->action_login, SIGNAL(triggered()), this, SLOT(action_login_triggered()));
    connect(ui->action_quit, SIGNAL(triggered()), this, SLOT(action_quit_triggered()));
    connect(ui->action_course, SIGNAL(triggered()), this, SLOT(action_course_triggered()));
    connect(ui->action_set_grade, SIGNAL(triggered()), this, SLOT(action_set_grade_triggered()));
    connect(ui->action_about, SIGNAL(triggered()), this, SLOT(action_about_triggered()));
    connect(ui->action_help, SIGNAL(triggered()), this, SLOT(action_help_triggered()));
    connect(ui->action_password, SIGNAL(triggered()), this, SLOT(action_change_pass_triggered()));

    //界面按钮
    connect(ui->set_grade_btn, SIGNAL(clicked()), this, SLOT(action_set_grade_triggered()));

    //状态栏计时器
    connect(m_timer_status, SIGNAL(timeout()), this, SLOT(updateStatusBar()));

    //表头点击排序
    connect(ui->tableView_student->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sort_student(int)));

    //刷新按钮
    connect(ui->flush_btn, SIGNAL(clicked()), this, SLOT(flush_btn_clicked()));
}

void MainWindow_teacher::action_login_triggered()
{
    if(m_timer_status->isActive()){
        m_timer_status->stop();         //停止状态栏计时器
    }
    this->close();
    m_envir_widget->showLoginWidget();
}

void MainWindow_teacher::action_quit_triggered()
{
    if(m_timer_status->isActive()){
        m_timer_status->stop();         //停止状态栏计时器
    }
    this->close();

    m_envir_widget->getConvey()->destroyConnect();
}

void MainWindow_teacher::action_course_triggered()
{
    ui->tabWidget_teacher->setCurrentIndex(0);
}

void MainWindow_teacher::action_set_grade_triggered()
{
    ui->tabWidget_teacher->setCurrentIndex(1);
}

void MainWindow_teacher::action_change_pass_triggered()
{

}

void MainWindow_teacher::action_about_triggered()
{
    QMessageBox::about(this, QString::fromLocal8Bit("关于"),
          QString::fromLocal8Bit(" <font color='red'>Students` Grade Manage System 3.9.0 (opensource)</font>"
                                 "<br>项目主页：https://github.com/laddie132/StudentsGradeManageSystem"
                                 " <br>作者：L.Laddie"
                               "  <br><br>Copyright 2016-2016 The Qt Company Ltd. All rights reserved." ));
}

void MainWindow_teacher::action_help_triggered()
{

}

void MainWindow_teacher::on_comboBox_course_currentIndexChanged(int index)
{
    updateStudent();
}

//取消修改按钮
void MainWindow_teacher::on_cancel_btn_clicked()
{
    updateStudent();
}

//确认修改按钮
void MainWindow_teacher::on_confirm_btn_clicked()
{
    if(ui->comboBox_course->currentIndex() != -1){
        QString course_id = ui->comboBox_course->currentText();
        QMap<QString, QVariant> student_grade;

        int row = ui_student_model->rowCount();
        for(int i = 0; i < row; i++)
        {
            QString student_id = ui_student_model->item(i, 0)->text();
            QVariant grade(ui_student_model->item(i, 4)->text().toFloat());
            student_grade.insert(student_id, grade);
        }

        try{
            m_envir_widget->getConvey()->sendStuGrade(course_id, student_grade);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改学生成绩成功"));
        }
        catch(std::exception& e){
            updateStudent();
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromStdString(e.what()));
        }
    }
}

void MainWindow_teacher::flush_btn_clicked()
{
    updateTable();
    ui->comboBox_course->clear();
    int num = ui_course_model->rowCount();
    for(int i = 0; i < num; i++)
    {
        ui->comboBox_course->addItem(ui_course_model->item(i, 0)->text());
        ui->comboBox_course->setCurrentIndex(0);
    }

    updateStudent();
}
