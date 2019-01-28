#include "alter_reader_form.h"
#include "ui_alter_reader_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>


AlterReaderForm::AlterReaderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlterReaderForm)
{
    ui->setupUi(this);
    this->setWindowTitle("修改读者信息");
}


AlterReaderForm::~AlterReaderForm()
{
    delete ui;
}


void AlterReaderForm::displayAllInformation(QString data)
{
    QString reader_id;
    QSqlQuery query;

    reader_id = data;
    reader_id_global = data;

    query.exec("select * from reader where rno = '" + reader_id + "'");

    if (query.next())
    {
        ui->rno_le->setText(query.value(0).toString());
        ui->rname_le->setText(query.value(1).toString());
        ui->rtel_le->setText(query.value(2).toString());
        ui->rkey_le->setText(query.value(3).toString());
        ui->rsex_cbx->setCurrentText(query.value(4).toString());
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("没有有关此读者的相关信息！"));
}


void AlterReaderForm::on_ensure_btn_clicked()
{
    QString reader_id;
    QString reader_name;
    QString reader_tel;
    QString reader_key;
    QString reader_sex;
    QString reader_admin;
    QSqlQuery query;

    reader_id = ui->rno_le->text();
    reader_name = ui->rname_le->text();
    reader_tel = ui->rtel_le->text();
    reader_key = ui->rkey_le->text();
    reader_sex = ui->rsex_cbx->currentText();
    reader_admin = "0000";

    if (reader_id == reader_id_global)
    {
        query.prepare("update reader set rname = :name, rtel = :tel, rkey = :key, rsex = :sex where rno = :id");
        query.bindValue(":id", reader_id);
        query.bindValue(":name", reader_name);
        query.bindValue(":tel", reader_tel);
        query.bindValue(":key", reader_key);
        query.bindValue(":sex", reader_sex);
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("信息"), tr("读者信息修改成功！"));
            this->close();
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("读者信息修改失败！"));
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("读者账号不能修改！"));
        ui->rno_le->setText(reader_id_global);
    }
}


void AlterReaderForm::on_reset_btn_clicked()
{
    ui->rname_le->setText("");
    ui->rtel_le->setText("");
    ui->rkey_le->setText("");
    ui->rsex_cbx->setCurrentText("");
}


void AlterReaderForm::on_cancel_btn_clicked()
{
    this->close();
}
