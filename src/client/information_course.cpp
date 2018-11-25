/**
 * Name: information_course.cpp
 * User: L.Laddie
 * Function: 添加/编辑课程信息
 */

#include <QDebug>
#include <QMessageBox>

#include "information_course.h"
#include "ui_information_course.h"
#include "include.h"

Information_course::Information_course(Envir_widget* envir_widget, QWidget *parent) :
    m_envir_widget(envir_widget),
    QDialog(parent),
    ui(new Ui::Information_course)
{
    ui->setupUi(this);
    creatActivex();
}

Information_course::~Information_course()
{
    delete ui;
}

void Information_course::setCourse(QString id)
{
    m_course_id = id;
}

void Information_course::creatActivex()
{
    ui_student_model_n = new QStandardItemModel();
    ui_student_model_y = new QStandardItemModel();

    ui_student_model_n->sort(0);
    ui_student_model_y->sort(0);

    ui->tableView_student_n->setModel(ui_student_model_n);
    ui->tableView_student_y->setModel(ui_student_model_y);

    ui->tableView_student_n->resizeColumnsToContents();
    ui->tableView_student_y->resizeColumnsToContents();

    ui->checkBox_start_course->close();
}

void Information_course::showInfo()
{
    ui->comboBox_teacher->clear();
    ui->comboBox_teacher->addItem(QString::fromLocal8Bit("无"));
    m_all_user = m_envir_widget->getConvey()->getUser();
    for(auto i : m_all_user)
    {
        if(i.first.user_type == 1)
            ui->comboBox_teacher->addItem(QString::fromStdString(i.first.id));
    }
    ui->comboBox_teacher->setCurrentIndex(0);

    //编辑课程时
    if(m_course_id != ""){
        cur_course = m_envir_widget->getConvey()->getCourseInfo(m_course_id);

        ui->lineEdit_course_id->setText(QString::fromStdString(cur_course.first.id));
        ui->lineEdit_course_id->setEnabled(false);
        ui->lineEdit_course_name->setText(QString::fromStdString(cur_course.first.name));
        ui->lineEdit_course_name->setEnabled(false);
        ui->lineEdit_course_credit->setText(QString::number(cur_course.first.credit));
        ui->lineEdit_course_credit->setEnabled(false);
        ui->comboBox_type->setEnabled(false);
        ui->lineEdit_course_capicity->setText(QString::number(cur_course.first.capacity));
        ui->label_course_student->setText(QString::number(cur_course.first.cur_num));
        ui->comboBox_type->setCurrentIndex(!cur_course.first.course_type);
        ui->add_btn->setEnabled(false);
        ui->update_btn->setEnabled(true);
        ui->del_btn->setEnabled(true);
        if(cur_course.first.teacher_id != ""){
            int i = 0;
            for(i = 0; i <= ui->comboBox_teacher->count(); i++)
            {
                if(ui->comboBox_teacher->itemText(i).toStdString() ==  cur_course.first.teacher_id){
                    ui->comboBox_teacher->setCurrentIndex(i);
                    break;
                }
            }
        }
    }

    //添加课程时
    else{
        ui->lineEdit_course_id->clear();
        ui->lineEdit_course_capicity->clear();
        ui->lineEdit_course_credit->clear();
        ui->lineEdit_course_name->clear();
        ui->lineEdit_course_id->setEnabled(true);
        ui->lineEdit_course_name->setEnabled(true);
        ui->lineEdit_course_credit->setEnabled(true);
        ui->comboBox_type->setEnabled(true);
        ui->add_btn->setEnabled(true);
        ui->update_btn->setEnabled(false);
        ui->del_btn->setEnabled(false);
    }
    updateStudent();
}

void Information_course::updateStudent()
{
    ui_student_model_n->clear();
    ui_student_model_y->clear();

    int row1 = 0;
    int row2 = 0;
    if(m_course_id != ""){
        for(auto i : m_all_user)
        {
            if(i.first.user_type == 2)
            {
                //判断该学生是否已在课程中
                int flag = 0;
                for(auto j : cur_course.second)
                {
                    if(j.id == i.first.id)
                    {
                        flag = 1;
                        break;
                    }
                }

                if(!flag)
                {
                    ui_student_model_n->setItem(row2, 0, new QStandardItem(QString::fromStdString(i.first.id)));
                    ui_student_model_n->setItem(row2, 1, new QStandardItem(QString::fromStdString(i.first.name)));
                    row2++;
                }
                else{
                    ui_student_model_y->setItem(row1, 0, new QStandardItem(QString::fromStdString(i.first.id)));
                    ui_student_model_y->setItem(row1, 1, new QStandardItem(QString::fromStdString(i.first.name)));
                    row1++;
                }
            }
        }
    }
    else{
        for(auto i : m_all_user)
        {
            if(i.first.user_type == 2)
            {
                ui_student_model_n->setItem(row2, 0, new QStandardItem(QString::fromStdString(i.first.id)));
                ui_student_model_n->setItem(row2, 1, new QStandardItem(QString::fromStdString(i.first.name)));
                row2++;
            }
        }
    }

    ui_student_model_n->sort(0);
    ui_student_model_y->sort(0);
}

void Information_course::on_add_btn_clicked()
{
    Course_model new_course;
    std::vector<std::string> new_stu_list;

    std::string id = ui->lineEdit_course_id->text().toStdString();
    if(id == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("课程ID不能为空"));
        ui->lineEdit_course_id->setFocus();
        return;
    }
    new_course.id = id;

    std::string name = ui->lineEdit_course_name->text().toStdString();
    if(name == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("课程名称不能为空"));
        ui->lineEdit_course_name->setFocus();
        return;
    }
    new_course.name = name;

    QString credit_string = ui->lineEdit_course_credit->text();
    if(credit_string == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("课程学分不能为空"));
        ui->lineEdit_course_credit->setFocus();
        return;
    }
    int credit = credit_string.toInt();
    new_course.credit = credit;

    int capicity = ui->lineEdit_course_capicity->text().toInt();
    new_course.capacity = capicity;

    if(ui->comboBox_teacher->currentText() != QString::fromLocal8Bit("无")){
        new_course.teacher_id = ui->comboBox_teacher->currentText().toStdString();
    }

    if(ui->comboBox_type->currentIndex())
    {
        new_course.course_type = 0;
    }
    else
    {
        new_course.course_type = 1;
    }

    new_stu_list = addStudent();

    try{
        m_envir_widget->getConvey()->sendAddCourse(new_course, new_stu_list);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加课程成功"));
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("提示"), e.what());
        ui->lineEdit_course_id->clear();
        ui->lineEdit_course_id->setFocus();
        return;
    }

    emit updateCourse();
}

void Information_course::on_cancel_btn_clicked()
{
    this->close();
}

void Information_course::on_comboBox_type_currentIndexChanged(int index)
{
    if(!index){
        ui->checkBox_start_course->close();
    }
    else ui->checkBox_start_course->show();
}

void Information_course::on_update_btn_clicked()
{
    if(m_course_id == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("无课程信息"));
        return;
    }

    Course_model new_course = cur_course.first;
    std::vector<std::string> stu_list;

    new_course.capacity = ui->lineEdit_course_capicity->text().toInt();

    if(ui->comboBox_teacher->currentText() != QString::fromLocal8Bit("无")){
        new_course.teacher_id = ui->comboBox_teacher->currentText().toStdString();
    }

    stu_list = addStudent();

    try{
        m_envir_widget->getConvey()->sendUpdateCourse(new_course, stu_list);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("更新课程成功"));
    }
    catch(std::exception& e)
    {
        this->showInfo();
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromStdString(e.what()));
    }

    emit updateCourse();
}

void Information_course::on_del_btn_clicked()
{
    if(m_course_id == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("无课程信息"));
        return;
    }

    m_envir_widget->getConvey()->sendDelCourse(m_course_id);
    QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("删除课程成功"));

    emit updateCourse();
}

void Information_course::on_select_student_btn_clicked()
{
    int row = ui->tableView_student_n->currentIndex().row();
    if(row == -1){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("未选中学生信息"));
        return;
    }
    ui_student_model_y->insertRow(0, ui_student_model_n->takeRow(row));
}

void Information_course::on_cancel_student_btn_clicked()
{
    int row = ui->tableView_student_y->currentIndex().row();
    if(row == -1){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("未选中学生信息"));
        return;
    }
    ui_student_model_n->insertRow(0, ui_student_model_y->takeRow(row));
}

std::vector<std::string> Information_course::addStudent()
{
    std::vector<std::string> stu_list;
    int row = ui_student_model_y->rowCount();
    if(row != -1){
        for(int i = 0; i < row; i++)
        {
            QString id = ui_student_model_y->item(i, 0)->text();
            stu_list.push_back(id.toStdString());
        }
    }
    return stu_list;
}

void Information_course::on_comboBox_teacher_currentIndexChanged(const QString &arg1)
{
    if(m_course_id != "" && cur_course.first.teacher_id != ""){
        std::string teacher_name;
        for(auto i : m_all_user)
        {
            if(i.first.user_type == 1)
            {
                if(i.first.id == arg1.toStdString())
                {
                    teacher_name = i.first.name;
                    break;
                }
            }
        }
        ui->label_teacher_name->setText(QString::fromStdString(teacher_name));
    }
    else{
        ui->label_teacher_name->setText("无");
    }
}
