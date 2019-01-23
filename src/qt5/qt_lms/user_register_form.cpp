#include "user_register_form.h"
#include "ui_user_register_form.h"

#include <QMessageBox>
#include <QString>
#include <QSqlQuery>


UserRegisterForm::UserRegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserRegisterForm)
{
    ui->setupUi(this);
    this->setWindowTitle("读者注册");
}


UserRegisterForm::~UserRegisterForm()
{
    delete ui;
}


void UserRegisterForm::on_yes_btn_clicked()
{
    QString reader_name;
    QString reader_id;
    QString reader_pwd;
    QString reader_pwd_confim;
    QString reader_tel;
    QString reader_sex;
    QString properties;
    QString values;

    QSqlQuery query;

    if (!ui->rname_le->text().trimmed().isEmpty())
        reader_name = ui->rname_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("用户名不能为空！"));
        return ;
    }

    if (!ui->rno_le->text().trimmed().isEmpty())
        reader_id = ui->rno_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("账号不能为空！"));
        return ;
    }

    if (!ui->rpwd_le->text().trimmed().isEmpty())
        reader_pwd = ui->rpwd_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("密码不能为空！"));
        return ;
    }

    if (!ui->rpwd_confim_le->text().trimmed().isEmpty())
        reader_pwd_confim = ui->rpwd_confim_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("确认密码不能为空！"));
        return ;
    }

    reader_tel = ui->rtel_le->text().trimmed();
    reader_sex = ui->rsex_cmx->currentText().trimmed();

    if (reader_pwd.compare(reader_pwd_confim) != 0)
    {
        QMessageBox::warning(this, tr("警告"), tr("确认密码与密码不同！"));
        return ;
    }

    query.exec("select * from reader where rno = '" + reader_id + "'");

    if(!query.next())
    {
        properties = "rno, rname, rkey, rtel, rsex, ano";
        values = ":rno, :rname, :rkey, :rtel, :rsex, :ano";
        query.prepare("insert into reader(" + properties + ") values(" +
                      values + ")");
        query.bindValue(":rno", reader_id);
        query.bindValue(":rname", reader_name);
        query.bindValue(":rkey", reader_pwd);
        query.bindValue(":rtel", reader_tel);
        query.bindValue(":rsex", reader_sex);
        query.bindValue(":ano", QString("0000"));
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("注册成功"));
            this->close();
        }
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("用户名已经存在！"));
}


void UserRegisterForm::on_no_btn_clicked()
{
    this->close();
}
