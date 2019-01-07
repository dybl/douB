#include "add_reader_form.h"
#include "ui_add_reader_form.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>


AddReaderForm::AddReaderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddReaderForm)
{
    ui->setupUi(this);
    this->setWindowTitle("添加读者");
}


AddReaderForm::~AddReaderForm()
{
    delete ui;
}


void AddReaderForm::on_ensure_btn_clicked()
{
    QString reader_id;
    QString reader_name;
    QString reader_tel;
    QString reader_key;
    QString reader_sex;
    QString reader_admin;
    QSqlQuery query;

    reader_id = ui->rno_le->text().trimmed();
    reader_name = ui->rname_le->text().trimmed();
    reader_tel = ui->rtel_le->text().trimmed();
    reader_key = ui->rkey_le->text().trimmed();
    reader_sex = ui->rsex_cbx->currentText().trimmed();
    reader_admin = "0000";

    query.exec("select rno from reader where rno = '" + reader_id + "'");

    if (!query.next())
    {
        if (reader_id != "" && reader_name != "" && reader_tel != "" && reader_key != "")
        {
                query.prepare(tr("insert into reader values(:id, :name, :tel, :key, :sex, :admin)"));
                query.bindValue(":id", reader_id);
                query.bindValue(":name", reader_name);
                query.bindValue(":tel", reader_tel);
                query.bindValue(":key", reader_key);
                query.bindValue(":sex", reader_sex);
                query.bindValue(":admin", reader_admin);
                query.exec();

                if (query.isActive())
                {
                    query.numRowsAffected();
                    QMessageBox::information(this, tr("信息"), tr("数据插入成功！"));
                }
            }
        else
            QMessageBox::warning(this, tr("警告"), tr("读者号、密码、姓名、电话不能为空！"));
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("读者号号是唯一的，不能重复！"));
        return ;
    }
}


void AddReaderForm::on_reset_btn_clicked()
{
    ui->rno_le->setText("");
    ui->rname_le->setText("");
    ui->rtel_le->setText("");
    ui->rkey_le->setText("");
    ui->rsex_cbx->setCurrentText("");
}


void AddReaderForm::on_cancel_btn_clicked()
{
    this->close();
}
