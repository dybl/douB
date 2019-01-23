#include "book_id_form.h"
#include "ui_book_id_form.h"
#include "alter_book_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDesktopWidget>


BookIDForm::BookIDForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookIDForm)
{
    ui->setupUi(this);
    this->setWindowTitle("图书号输入");
}


BookIDForm::~BookIDForm()
{
    delete ui;
}


void BookIDForm::on_ensure_btn_clicked()
{
    QString book_id;
    QSqlQuery query;

    book_id = ui->bno_le->text().trimmed();
    query.exec("select bno from book where bno = '" + book_id + "'");

    if (query.next())
    {
        AlterBookForm *alter_book = new AlterBookForm();
        alter_book->show();
        alter_book->move((QApplication::desktop()->width() - alter_book->width()) / 2,
                         (QApplication::desktop()->height() - alter_book->height()) / 2);
        connect(this, SIGNAL(sendBookID(QString)), alter_book, SLOT(displayAllInformation(QString)));
        emit sendBookID(book_id);

        this->close();
    }
    else
        QMessageBox::warning(this, tr("错误"), tr("没有这个书号，不能修改！"));
}


void BookIDForm::on_cancel_btn_clicked()
{
    this->close();
}
