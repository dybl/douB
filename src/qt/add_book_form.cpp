#include "add_book_form.h"
#include "ui_add_book_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>


AddBookForm::AddBookForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddBookForm)
{
    ui->setupUi(this);
    this->setWindowTitle("添加图书");
}


AddBookForm::~AddBookForm()
{
    delete ui;
}


void AddBookForm::on_ensure_btn_clicked()
{
    QString book_id;
    QString book_name;
    QString book_type;
    QString book_author;
    QString book_print;
    QString book_number;
    QString book_admin;
    QSqlQuery query;

    book_id = ui->bno_le->text().trimmed();
    book_name = ui->bname_le->text().trimmed();
    book_type = ui->btype_le->text().trimmed();
    book_author = ui->bauthor_le->text().trimmed();
    book_print = ui->bprint_le->text().trimmed();
    book_number = ui->bnum_le->text().trimmed();
    book_admin = "0000";

    query.exec("select bno from book where bno = '" + book_id + "'");

    if (!query.next())
    {
        if (book_id != "" && book_name != "" && book_type != "")
        {
            if (book_print != "" && book_author != "" && book_number != "")
            {
                query.prepare(tr("insert into book values(:id, :name, :type, :author, :print, :num, :admin)"));
                query.bindValue(":id", book_id);
                query.bindValue(":name", book_name);
                query.bindValue(":type", book_type);
                query.bindValue(":author", book_author);
                query.bindValue(":print", book_print);
                query.bindValue(":num", book_number);
                query.bindValue(":admin", book_admin);
                query.exec();

                if (query.isActive())
                {
                    query.numRowsAffected();
                    QMessageBox::information(this, tr("信息"), tr("数据插入成功！"));
                }
            }
            else
                QMessageBox::warning(this, tr("警告"), tr("出版社、作者、图书数量不能为空！"));
            }
        else
            QMessageBox::warning(this, tr("警告"), tr("书号、书名、书类型不能为空！"));
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("图书号是唯一的，不能重复！"));
        return ;
    }
}


void AddBookForm::on_reset_btn_clicked()
{
    ui->bno_le->setText("");
    ui->bname_le->setText("");
    ui->btype_le->setText("");
    ui->bprint_le->setText("");
    ui->bauthor_le->setText("");
    ui->bnum_le->setText("");
}


void AddBookForm::on_cancel_btn_clicked()
{
    this->close();
}
