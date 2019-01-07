#include "delete_reader_form.h"
#include "ui_delete_reader_form.h"
#include "delete_ensure_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDesktopWidget>


DeleteReaderForm::DeleteReaderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteReaderForm)
{
    ui->setupUi(this);
    this->setWindowTitle("删除读者");
}


DeleteReaderForm::~DeleteReaderForm()
{
    delete ui;
}


void DeleteReaderForm::on_ensure_btn_clicked()
{
    QString reader_id;
    QSqlQuery query;

    reader_id = ui->rno_le->text().trimmed();
    query.exec("select rno from reader where rno = '" + reader_id + "'");

    if (query.next())
    {
        query.prepare("delete from reader where rno = :rno_id");
        query.bindValue(":rno_id", reader_id);
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
        QMessageBox::warning(this, tr("错误"), tr("没有这个读者号，不能删除！"));
}


void DeleteReaderForm::on_cancel_btn_clicked()
{
    this->close();
}
