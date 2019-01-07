#include "alter_book_form.h"
#include "ui_alter_book_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>


AlterBookForm::AlterBookForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlterBookForm)
{
    ui->setupUi(this);
    this->setWindowTitle("修改图书信息");
}


AlterBookForm::~AlterBookForm()
{
    delete ui;
}


void AlterBookForm::displayAllInformation(QString data)
{
    QString book_id;
    QSqlQuery query;

    book_id = data;
    book_id_global = data;

    query.exec("select * from book where bno = '" + book_id + "'");

    if (query.next())
    {
        ui->bno_le->setText(query.value(0).toString());
        ui->bname_le->setText(query.value(1).toString());
        ui->btype_le->setText(query.value(2).toString());
        ui->bprint_le->setText(query.value(3).toString());
        ui->bauthor_le->setText(query.value(4).toString());
        ui->bnum_le->setText(query.value(5).toString());
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("没有有关此书的相关信息！"));
}


void AlterBookForm::on_ensure_btn_clicked()
{
    QString book_id;
    QString book_name;
    QString book_type;
    QString book_author;
    QString book_print;
    QString book_number;
    QString book_admin;
    QSqlQuery query;

    book_id = ui->bno_le->text();
    book_name = ui->bname_le->text();
    book_type = ui->btype_le->text();
    book_author = ui->bauthor_le->text();
    book_print = ui->bprint_le->text();
    book_number = ui->bnum_le->text();
    book_admin = "0000";

    if (book_id == book_id_global)
    {
        query.prepare("update book set bname = :name, btno = :type, bauthor = :author, bprint = :print, bnum = :num where bno = :id");
        query.bindValue(":id", book_id);
        query.bindValue(":name", book_name);
        query.bindValue(":type", book_type);
        query.bindValue(":author", book_author);
        query.bindValue(":print", book_print);
        query.bindValue(":num", book_number);
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("信息"), tr("图书信息修改成功！"));
            this->close();
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("图书信息修改失败！"));
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("图书号不能修改！"));
        ui->bno_le->setText(book_id_global);
    }
}


void AlterBookForm::on_reset_btn_clicked()
{
    ui->bname_le->setText("");
    ui->btype_le->setText("");
    ui->bprint_le->setText("");
    ui->bauthor_le->setText("");
    ui->bnum_le->setText("");
}


void AlterBookForm::on_cancel_btn_clicked()
{
    this->close();
}
