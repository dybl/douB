#include "delete_book_form.h"
#include "ui_delete_book_form.h"
#include "delete_ensure_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDesktopWidget>


DeleteBookForm::DeleteBookForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteBookForm)
{
    ui->setupUi(this);
    this->setWindowTitle("图书删除");
}


DeleteBookForm::~DeleteBookForm()
{
    delete ui;
}


void DeleteBookForm::on_ensure_btn_clicked()
{
    QString book_id;
    QSqlQuery query;

    book_id = ui->bno_le->text().trimmed();
    query.exec("select bno from book where bno = '" + book_id + "'");

    if (query.next())
    {
        query.prepare("delete from book where bno = :bno_id");
        query.bindValue(":bno_id", book_id);
        query.exec();

        if (query.isActive())
        {
            DeleteEnsureForm *delete_ensure = new DeleteEnsureForm();
            delete_ensure->show();
            delete_ensure->move((QApplication::desktop()->width() - delete_ensure->width()) / 2,
                                (QApplication::desktop()->height() - delete_ensure->height()) / 2);
        }
    }
    else
        QMessageBox::warning(this, tr("错误"), tr("没有这个书号，不能删除！"));
}


void DeleteBookForm::on_cancel_btn_clicked()
{
    this->close();
}
