/**
 * Name: information_user.cpp
 * User: L.Laddie
 * Function: 添加/编辑用户信息
 */

#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>

#include "information_user.h"
#include "ui_information_user.h"
#include "include.h"

Information_user::Information_user(Envir_widget* envir_widget, QWidget *parent) :
    m_envir_widget(envir_widget),
    QDialog(parent),
    ui(new Ui::Information_user)
{
    ui->setupUi(this);
    creatActivex();
}

Information_user::~Information_user()
{
    delete ui;
}

void Information_user::setUser(QString id)
{
    m_user_id = id;
}

void Information_user::creatActivex()
{
    ui_course_model_n = new QStandardItemModel();
    ui_course_model_y = new QStandardItemModel();

    ui_course_model_n->sort(0);
    ui_course_model_y->sort(0);

    ui->tableView_course_n->setModel(ui_course_model_n);
    ui->tableView_course_y->setModel(ui_course_model_y);

    ui->tableView_course_n->resizeColumnsToContents();
    ui->tableView_course_y->resizeColumnsToContents();

    ui->lineEdit_user_password->setPlaceholderText("默认用户ID");
}

void Information_user::showInfo()
{
    m_all_course = m_envir_widget->getConvey()->getCurCourse();

    //编辑用户时
    if(m_user_id != ""){
        cur_user = m_envir_widget->getConvey()->getUserInfo(m_user_id);

        ui->lineEdit_user_id->setText(QString::fromStdString(cur_user.first.id));
        ui->lineEdit_user_id->setEnabled(false);
        ui->lineEdit_user_name->setText(QString::fromStdString(cur_user.first.name));
        ui->lineEdit_user_name->setEnabled(false);
        ui->lineEdit_user_institude->setText(QString::fromStdString(cur_user.first.institude));
        ui->lineEdit_user_institude->setEnabled(false);
        ui->lineEdit_user_password->clear();
        ui->comboBox_user_type->setEnabled(false);
        ui->add_btn->setEnabled(false);
        ui->update_btn->setEnabled(true);
        ui->del_btn->setEnabled(true);
        switch(cur_user.first.user_type)
        {
        case 2:
        {
            ui->comboBox_user_type->setCurrentIndex(0);
            ui->lineEdit_user_class->setText(QString::fromStdString(cur_user.first.class_name));
            break;
        }

        case 1:
            ui->comboBox_user_type->setCurrentIndex(1);
            break;

        case 0:
            ui->comboBox_user_type->setCurrentIndex(2);
            break;

        default:
            break;
        }
    }

    //添加用户时
    else{
        ui->lineEdit_user_id->clear();
        ui->lineEdit_user_class->clear();
        ui->lineEdit_user_institude->clear();
        ui->lineEdit_user_name->clear();
        ui->lineEdit_user_password->clear();
        ui->lineEdit_user_id->setEnabled(true);
        ui->lineEdit_user_name->setEnabled(true);
        ui->lineEdit_user_institude->setEnabled(true);
        ui->comboBox_user_type->setEnabled(true);
        ui->comboBox_user_type->setCurrentIndex(0);
        ui->add_btn->setEnabled(true);
        ui->update_btn->setEnabled(false);
        ui->del_btn->setEnabled(false);
    }
    updateCourse();
}

void Information_user::updateCourse()
{
    ui_course_model_n->clear();
    ui_course_model_y->clear();

    int row1 = 0;
    int row2 = 0;
    if(m_user_id != ""){

        if(cur_user.first.user_type != 0)
        {
            for(auto i : m_all_course)
            {
                int flag = 0;
                for(auto j : cur_user.second)
                {
                    if(j.id == i.id)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag)
                {
                    ui_course_model_y->setItem(row1, 0, new QStandardItem(QString::fromStdString(i.id)));
                    ui_course_model_y->setItem(row1, 1, new QStandardItem(QString::fromStdString(i.name)));
                    row1++;
                }
                else
                {
                    ui_course_model_n->setItem(row2, 0, new QStandardItem(QString::fromStdString(i.id)));
                    ui_course_model_n->setItem(row2, 1, new QStandardItem(QString::fromStdString(i.name)));
                    row2++;
                }
            }
        }
    }

    //添加一个用户显示的课程
    else{
        for(auto i : m_all_course)
        {
            ui_course_model_n->setItem(row2, 0, new QStandardItem(QString::fromStdString(i.id)));
            ui_course_model_n->setItem(row2, 1, new QStandardItem(QString::fromStdString(i.name)));
            row2++;
        }
    }

    ui_course_model_n->sort(0);
    ui_course_model_y->sort(0);
}

void Information_user::on_cancel_btn_clicked()
{
    this->close();
}

void Information_user::on_add_btn_clicked()
{
    User_model new_user;
    std::vector<std::string> new_course_list;

    std::string id = ui->lineEdit_user_id->text().toStdString();
    if(id == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("用户ID不能为空"));
        ui->lineEdit_user_id->setFocus();
        return;
    }
    new_user.id = id;

    std::string name = ui->lineEdit_user_name->text().toStdString();
    if(name == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("用户姓名不能为空"));
        ui->lineEdit_user_name->setFocus();
        return;
    }
    new_user.name = name;

    std::string institude = ui->lineEdit_user_institude->text().toStdString();
    if(institude == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("用户学院不能为空"));
        ui->lineEdit_user_institude->setFocus();
        return;
    }
    new_user.institude = institude;

    QString password;
    if(ui->lineEdit_user_password->text() == ""){
        password = QCryptographicHash::hash(ui->lineEdit_user_id->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    }
    else{
        password = QCryptographicHash::hash(ui->lineEdit_user_password->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    }

    switch (ui->comboBox_user_type->currentIndex()) {
    //添加学生用户
    case 0:
    {
        new_user.user_type = 2;

        std::string class_name = ui->lineEdit_user_class->text().toStdString();
        new_user.class_name = class_name;
        break;
    }

    //添加教师用户
    case 1:
    {
        new_user.user_type = 1;
        break;
    }

    //添加管理员用户
    case 2:
    {
        new_user.user_type = 0;
        break;
    }

    default:
        break;
    }

    new_course_list = addCourse();

    try{
        m_envir_widget->getConvey()->sendAddUser(new_user, password, new_course_list);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加用户成功"));
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromStdString(e.what()));
        return;
    }

    emit updateUser();
}

void Information_user::on_comboBox_user_type_currentIndexChanged(int index)
{
    if(index != 0){
        ui->label_user_class->setEnabled(false);
        ui->lineEdit_user_class->setEnabled(false);
    }
    else{
        ui->label_user_class->setEnabled(true);
        ui->lineEdit_user_class->setEnabled(true);
    }
    if(index == 2){
        ui->label_course->setEnabled(false);
        ui->tableView_course_n->setEnabled(false);
        ui->tableView_course_y->setEnabled(false);
        ui->select_course_btn->setEnabled(false);
        ui->cancel_course_btn->setEnabled(false);
    }
    else{
        ui->label_course->setEnabled(true);
        ui->tableView_course_n->setEnabled(true);
        ui->tableView_course_y->setEnabled(true);
        ui->select_course_btn->setEnabled(true);
        ui->cancel_course_btn->setEnabled(true);
    }
}

void Information_user::on_update_btn_clicked()
{
    if(m_user_id == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("无用户信息"));
        return;
    }

    User_model new_user = cur_user.first;
    std::vector<std::string> course_list;

    QString password = ui->lineEdit_user_password->text();
    if(password != ""){
        password = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5).toHex();
    }

    if(cur_user.first.user_type == 2){
        new_user.class_name = ui->lineEdit_user_class->text().toStdString();
    }

    course_list = addCourse();

    try{
        m_envir_widget->getConvey()->sendUpdateUser(new_user, password, course_list);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改用户成功"));
    }
    catch(std::exception& e){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromStdString(e.what()));
        this->showInfo();
    }

    emit updateUser();
}

void Information_user::on_del_btn_clicked()
{
    if(m_user_id == ""){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("无用户信息"));
        return;
    }

    try{
        m_envir_widget->getConvey()->sendDelUser(m_user_id);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("删除用户成功"));
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), e.what());
        return;
    }

    emit updateUser();
}

void Information_user::on_select_course_btn_clicked()
{
    int row = ui->tableView_course_n->currentIndex().row();
    if(row == -1){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("未选中课程信息"));
        return;
    }
    ui_course_model_y->insertRow(0, ui_course_model_n->takeRow(row));
}

void Information_user::on_cancel_course_btn_clicked()
{
    int row = ui->tableView_course_y->currentIndex().row();
    if(row == -1){
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("未选中课程信息"));
        return;
    }
    ui_course_model_n->insertRow(0, ui_course_model_y->takeRow(row));
}

std::vector<std::string> Information_user::addCourse()
{
    std::vector<std::string> course_list;

    int row = ui_course_model_y->rowCount();
    if(row != -1){
        for(int i = 0; i < row; i++)
        {
            QString id = ui_course_model_y->item(i, 0)->text();
            course_list.push_back(id.toStdString());
        }
    }
    return course_list;
}
