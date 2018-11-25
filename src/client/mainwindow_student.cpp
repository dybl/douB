/**
 * Name: mainwindow_student.cpp
 * User: L.Laddie
 * Function: 学生界面
 */

#include <vector>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

#include "fun.h"
#include "model_struct.h"
#include "mainwindow_student.h"
#include "ui_mainwindow_student.h"

MainWindow_student::MainWindow_student(Envir_widget* envir_widget, QWidget *parent) :
    QMainWindow(parent),
    m_envir_widget(envir_widget),
    ui(new Ui::MainWindow_student)
{
    ui->setupUi(this);
    setFixedSize(800, 500);         //禁止更改大小

    initActivex();          //初始化控件
    creatAction();          //链接槽函数
    initStatusBar();        //初始化状态栏
}

MainWindow_student::~MainWindow_student()
{
    delete ui_label_status;
    delete ui_label_time;
    delete m_timer_status;
    delete ui;

    delete ui_course_model_e;
    delete ui_course_model_o;
    delete ui_course_model_s;
}

void MainWindow_student::setEnvirWidget(Envir_widget* envir_widget)
{
    this->m_envir_widget = envir_widget;
}

void MainWindow_student::setUserModel(User_model user)
{
    this->m_user = user;
}

//初始化状态栏信息
void MainWindow_student::initStatusBar()
{
    ui_label_time->setAlignment(Qt::AlignRight);

    ui->statusbar->addWidget(ui_label_status, 1);
    ui->statusbar->addWidget(ui_label_time, 6);
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}, *{font-size : 8px}"));
}

//定时更新状态栏
void MainWindow_student::updateStatusBar()
{
    //设置实时人数信息
    int obligatory_num = this->ui_course_model_o->rowCount();
    int elective_num = this->ui_course_model_e->rowCount();
    int select_num = this->ui_course_model_s->rowCount();

    QString course_num = "必修课：" + QString::number(obligatory_num) + "个"
            + " 选修课：" + QString::number(elective_num) + "个" +
            " 可选课程：" + QString::number(select_num) + "个";
    ui_label_status->setText("实时信息：" + course_num);

    //设置实时系统时间
    QDateTime cur_time = QDateTime::currentDateTime();
    QString cur_time_str = cur_time.toString("hh:mm:ss");
    ui_label_time->setText("系统时间：" + cur_time_str);
}

//初始化相关控件
void MainWindow_student::initActivex()
{
    ui_course_model_o = new QStandardItemModel();
    ui_course_model_e = new QStandardItemModel();
    ui_course_model_s = new QStandardItemModel();

    ui->tableView_course_o->setModel(ui_course_model_o);
    ui->tableView_course_e->setModel(ui_course_model_e);
    ui->tableView_course_s->setModel(ui_course_model_s);

    ui_label_status = new QLabel();
    ui_label_time = new QLabel();
    m_timer_status = new QTimer(this);
}

//初始进入界面时更新界面
void MainWindow_student::showInfo()
{
    ui->label_id->setText(QString::fromStdString(m_user.id));
    ui->label_name->setText(QString::fromStdString(m_user.name));
    ui->label_institude->setText(QString::fromStdString(m_user.institude));
    ui->label_class->setText(QString::fromStdString(m_user.class_name));
    updateTable();

    updateStatusBar();
    m_timer_status->start(1000);        //每一秒刷新一次状态栏
}

void MainWindow_student::updateTable()
{
    ui_course_model_o->clear();
    ui_course_model_e->clear();
    ui_course_model_s->clear();

    //设置必修课程列表
    ui_course_model_o->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("课程编号")));
    ui_course_model_o->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("课程名称")));
    ui_course_model_o->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("课程学分")));
    ui_course_model_o->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("课程类型")));
    ui_course_model_o->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("课程容量")));
    ui_course_model_o->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("课程成绩")));
    ui_course_model_o->setHorizontalHeaderItem(6, new QStandardItem(QString::fromLocal8Bit("课程绩点")));

    //设置选修课列表
    ui_course_model_e->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("课程编号")));
    ui_course_model_e->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("课程名称")));
    ui_course_model_e->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("课程学分")));
    ui_course_model_e->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("课程类型")));
    ui_course_model_e->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("课程容量")));
    ui_course_model_e->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("课程成绩")));
    ui_course_model_e->setHorizontalHeaderItem(6, new QStandardItem(QString::fromLocal8Bit("课程绩点")));

    //设置选课列表
    ui_course_model_s->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("课程编号")));
    ui_course_model_s->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("课程名称")));
    ui_course_model_s->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("课程学分")));
    ui_course_model_s->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("课程类型")));
    ui_course_model_s->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("课程人数")));
    ui_course_model_s->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("课程容量")));

    int row1 = 0, row2 = 0;

    //更新必修和选修课
    std::vector<Course_model> oe_course;
    try
    {
        oe_course = m_envir_widget->getConvey()->getCurCourse();
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit(e.what()));
        return;
    }

    for (auto i : oe_course)
    {
        if(!i.course_type){
            ui_course_model_e->setItem(row2, 0, new QStandardItem(QString::fromStdString(i.id)));
            ui_course_model_e->setItem(row2, 1, new QStandardItem(QString::fromStdString(i.name)));
            ui_course_model_e->setItem(row2, 2, new QStandardItem(QString::number(i.credit)));
            ui_course_model_e->setItem(row2, 3, new QStandardItem(QString::fromLocal8Bit("选修")));
            ui_course_model_e->setItem(row2, 4, new QStandardItem(QString::number(i.capacity)));
            ui_course_model_e->setItem(row2, 5, new QStandardItem(i.grade != -1 ? QString("%1").arg(i.grade) : QString::fromLocal8Bit("无")));
            ui_course_model_e->setItem(row2, 6, new QStandardItem(QString("%1").arg(i.gpa)));
            row2++;
        }
        else{
            ui_course_model_o->setItem(row1, 0, new QStandardItem(QString::fromStdString(i.id)));
            ui_course_model_o->setItem(row1, 1, new QStandardItem(QString::fromStdString(i.name)));
            ui_course_model_o->setItem(row1, 2, new QStandardItem(QString::number(i.credit)));
            ui_course_model_o->setItem(row1, 3, new QStandardItem(QString::fromLocal8Bit("必修")));
            ui_course_model_o->setItem(row1, 4, new QStandardItem(QString::number(i.capacity)));
            ui_course_model_o->setItem(row1, 5, new QStandardItem(i.grade != -1 ? QString("%1").arg(i.grade) : QString::fromLocal8Bit("无")));
            ui_course_model_o->setItem(row1, 6, new QStandardItem(QString("%1").arg(i.gpa)));
            row1++;
        }
    }

    //更新可选课程列表
    int row = 0;
    std::vector<Course_model> s_course;
    try
    {
        s_course = m_envir_widget->getConvey()->getSelCourse();
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit(e.what()));
        return;
    }
    for(auto i : s_course)
    {
        ui_course_model_s->setItem(row, 0, new QStandardItem(QString::fromStdString(i.id)));
        ui_course_model_s->setItem(row, 1, new QStandardItem(QString::fromStdString(i.name)));
        ui_course_model_s->setItem(row, 2, new QStandardItem(QString::number(i.credit)));
        ui_course_model_s->setItem(row, 3, new QStandardItem(QString::fromLocal8Bit("选修")));
        ui_course_model_s->setItem(row, 4, new QStandardItem(QString::number(i.cur_num)));
        ui_course_model_s->setItem(row, 5, new QStandardItem(QString::number(i.capacity)));
        row++;
    }

    ui_course_model_o->sort(0);
    ui_course_model_e->sort(0);
    ui_course_model_s->sort(0);
}

//链接各项槽函数
void MainWindow_student::creatAction()
{
    //菜单栏
    connect(ui->action_login, SIGNAL(triggered()), this, SLOT(action_login_triggered()));
    connect(ui->action_quit, SIGNAL(triggered()), this, SLOT(action_quit_triggered()));
    connect(ui->action_course_o, SIGNAL(triggered()), this, SLOT(action_course_o_triggered()));
    connect(ui->action_course_e, SIGNAL(triggered()), this, SLOT(action_course_e_triggered()));
    connect(ui->action_course_start, SIGNAL(triggered()), this, SLOT(action_start_course_triggered()));
    connect(ui->action_about, SIGNAL(triggered()), this, SLOT(action_about_triggered()));
    connect(ui->action_help, SIGNAL(triggered()), this, SLOT(action_help_triggered()));
    connect(ui->action_password, SIGNAL(triggered()), this, SLOT(action_change_pass_triggered()));

    //学生选课和删除课程事件
    connect(ui->tableView_course_s, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(add_course_slots()));
    connect(ui->tableView_course_e, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(delete_course_slots()));

    //状态栏计时器
    connect(m_timer_status, SIGNAL(timeout()), this, SLOT(updateStatusBar()));

    //表头点击排序事件
    connect(ui->tableView_course_o->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sort_course_o(int)));
    connect(ui->tableView_course_e->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sort_course_e(int)));

    //刷新按钮
    connect(ui->flush_btn, SIGNAL(clicked()), this, SLOT(flush_btn_clicked()));
}

//对必修课程排序
void MainWindow_student::sort_course_o(int column)
{
    static bool reverse = false;

    //重新构建表格项目的vector向量
    std::vector<Course_model> course_o;
    for(auto i : m_envir_widget->getConvey()->getCurCourse())
    {
        if(i.course_type)
            course_o.push_back(i);
    }

    //判断需要对哪一项排序
    switch(column)
    {
    case 0:
    {
        Sort::sortVectorCourse(course_o, "id", reverse);
        reverse = !reverse;
        break;
    }

    case 5:
    {
        Sort::sortVectorCourse(course_o, "grade", reverse);
        reverse = !reverse;
        break;
    }

    case 6:
    {
        Sort::sortVectorCourse(course_o, "gpa", reverse);
        reverse = !reverse;
        break;
    }

    default:
        return;
    }

    //更新表格信息
    for(int i = 0; i < course_o.size(); i++)
    {
        ui_course_model_o->setItem(i, 0, new QStandardItem(QString::fromStdString(course_o[i].id)));
        ui_course_model_o->setItem(i, 1, new QStandardItem(QString::fromStdString(course_o[i].name)));
        ui_course_model_o->setItem(i, 2, new QStandardItem(QString::number(course_o[i].credit)));
        ui_course_model_o->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit("必修")));
        ui_course_model_o->setItem(i, 4, new QStandardItem(QString::number(course_o[i].capacity)));
        ui_course_model_o->setItem(i, 5, new QStandardItem(course_o[i].grade != -1 ? QString("%1").arg(course_o[i].grade) : QString::fromLocal8Bit("无")));
        ui_course_model_o->setItem(i, 6, new QStandardItem(QString("%1").arg(course_o[i].gpa)));
    }
}

//对选修课程排序
void MainWindow_student::sort_course_e(int column)
{
    static bool reverse = false;

    std::vector<Course_model> course_e;
    for(auto i : m_envir_widget->getConvey()->getCurCourse())
    {
        if(!i.course_type)
            course_e.push_back(i);
    }

    switch(column)
    {
    case 0:
    {
        Sort::sortVectorCourse(course_e, "id", reverse);
        reverse = !reverse;
        break;
    }

    case 5:
    {
        Sort::sortVectorCourse(course_e, "grade", reverse);
        reverse = !reverse;
        break;
    }

    case 6:
    {
        Sort::sortVectorCourse(course_e, "gpa", reverse);
        reverse = !reverse;
        break;
    }

    default:
        return;
    }

    for(int i = 0; i < course_e.size(); i++)
    {
        ui_course_model_e->setItem(i, 0, new QStandardItem(QString::fromStdString(course_e[i].id)));
        ui_course_model_e->setItem(i, 1, new QStandardItem(QString::fromStdString(course_e[i].name)));
        ui_course_model_e->setItem(i, 2, new QStandardItem(QString::number(course_e[i].credit)));
        ui_course_model_e->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit("选修")));
        ui_course_model_e->setItem(i, 4, new QStandardItem(QString::number(course_e[i].capacity)));
        ui_course_model_e->setItem(i, 5, new QStandardItem(course_e[i].grade != -1 ? QString("%1").arg(course_e[i].grade) : QString::fromLocal8Bit("无")));
        ui_course_model_e->setItem(i, 6, new QStandardItem(QString("%1").arg(course_e[i].gpa)));
    }
}

void MainWindow_student::action_login_triggered()
{
    if(m_timer_status->isActive()){
        m_timer_status->stop();         //停止状态栏计时器
    }
    this->close();
    m_envir_widget->showLoginWidget();
}

void MainWindow_student::action_quit_triggered()
{
    if(m_timer_status->isActive()){
        m_timer_status->stop();         //停止状态栏计时器
    }
    this->close();

    m_envir_widget->getConvey()->destroyConnect();
}

void MainWindow_student::action_course_o_triggered()
{
    ui->tabWidget_student->setCurrentIndex(0);
}

void MainWindow_student::action_course_e_triggered()
{
    ui->tabWidget_student->setCurrentIndex(1);
}

void MainWindow_student::action_start_course_triggered()
{
    ui->tabWidget_student->setCurrentIndex(2);
}

void MainWindow_student::action_change_pass_triggered()
{

}

void MainWindow_student::action_about_triggered()
{
    QMessageBox::about(this, QString::fromLocal8Bit("关于"),
          QString::fromLocal8Bit(" <font color='red'>Students` Grade Manage System 3.9.0 (opensource)</font>"
                                 "<br>项目主页：https://github.com/laddie132/StudentsGradeManageSystem"
                                 " <br>作者：L.Laddie"
                               "  <br><br>Copyright 2016-2016 The Qt Company Ltd. All rights reserved." ));
}

void MainWindow_student::action_help_triggered()
{

}

//选择选修课
void MainWindow_student::add_course_slots()
{
    int row = ui->tableView_course_s->currentIndex().row();
    QString id = ui_course_model_s->item(row, 0)->text();

    try{
        m_envir_widget->getConvey()->sendSelCourse(id);

        updateTable();      //更新用户列表信息
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("选择课程成功"));
    }
    catch(std::exception& e){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit(e.what()));
    }
}

//删除选修课
void MainWindow_student::delete_course_slots()
{
    int row = ui->tableView_course_e->currentIndex().row();
    QString id = ui_course_model_e->item(row, 0)->text();
    try{
        m_envir_widget->getConvey()->sendDelCourse(id);

        updateTable();
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("删除课程成功"));
    }
    catch(std::exception& e){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromStdString(e.what()));
    }
}

void MainWindow_student::flush_btn_clicked()
{
    updateTable();
}

