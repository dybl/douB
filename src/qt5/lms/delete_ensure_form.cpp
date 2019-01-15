#include "delete_ensure_form.h"
#include "ui_delete_ensure_form.h"
#include <QMessageBox>


DeleteEnsureForm::DeleteEnsureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteEnsureForm)
{
    ui->setupUi(this);
    this->setWindowTitle("删除确认");
}


DeleteEnsureForm::~DeleteEnsureForm()
{
    delete ui;
}


void DeleteEnsureForm::on_yes_btn_clicked()
{
    QMessageBox::information(this, tr("信息"), tr("删除信息成功！"));
    this->close();
}


void DeleteEnsureForm::on_no_btn_clicked()
{
    this->close();
}
