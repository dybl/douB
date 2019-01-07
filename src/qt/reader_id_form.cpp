#include "reader_id_form.h"
#include "ui_reader_id_form.h"
#include "alter_reader_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDesktopWidget>


ReaderIDForm::ReaderIDForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderIDForm)
{
    ui->setupUi(this);
    this->setWindowTitle("输入读者账号");
}


ReaderIDForm::~ReaderIDForm()
{
    delete ui;
}


void ReaderIDForm::on_ensure_btn_clicked()
{
    QString reader_id;
    QSqlQuery query;

    reader_id = ui->rno_le->text().trimmed();
    query.exec("select rno from reader where rno = '" + reader_id + "'");

    if (query.next())
    {
        AlterReaderForm *alter_reader = new AlterReaderForm();
        alter_reader->show();
        alter_reader->move((QApplication::desktop()->width() - alter_reader->width()) / 2,
                         (QApplication::desktop()->height() - alter_reader->height()) / 2);
        connect(this, SIGNAL(sendReaderID(QString)), alter_reader, SLOT(displayAllInformation(QString)));
        emit sendReaderID(reader_id);

        this->close();
    }
    else
        QMessageBox::warning(this, tr("错误"), tr("没有这个读者号，不能修改！"));
}


void ReaderIDForm::on_cancel_btn_clicked()
{
    this->close();
}
