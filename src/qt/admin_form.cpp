#include "admin_form.h"
#include "ui_admin_form.h"
#include "user_login.h"
#include "add_book_form.h"
#include "delete_book_form.h"
#include "add_reader_form.h"
#include "delete_reader_form.h"
#include "book_id_form.h"
#include "reader_id_form.h"
#include "ui_reader_form.h"

#include <QTimer>
#include <QDate>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QDesktopWidget>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QSqlQuery>
#include <QSqlRecord>


AdminForm::AdminForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminForm)
{
    ui->setupUi(this);
    this->setWindowTitle("管理员by dybl");
    ui->admin_tw->setCurrentIndex(0);

    book_manage_model = new QSqlTableModel(this);
    book_manage_model->setTable("book");
    book_manage_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    book_manage_model->setHeaderData(0, Qt::Horizontal, tr("图书号"));
    book_manage_model->setHeaderData(1, Qt::Horizontal, tr("图书名"));
    book_manage_model->setHeaderData(2, Qt::Horizontal, tr("图书类别号"));
    book_manage_model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    book_manage_model->setHeaderData(4, Qt::Horizontal, tr("作者"));
    book_manage_model->setHeaderData(5, Qt::Horizontal, tr("馆藏量"));
    book_manage_model->removeColumn(book_manage_model->fieldIndex("ano"));
    book_manage_model->select();

    ui->booklist_tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->booklist_tv->setModel(book_manage_model);
    ui->booklist_tv->show();

    reader_manage_model = new QSqlTableModel(this);
    reader_manage_model->setTable("reader");
    reader_manage_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    reader_manage_model->setHeaderData(0, Qt::Horizontal, tr("读者帐号"));
    reader_manage_model->setHeaderData(1, Qt::Horizontal, tr("读者姓名"));
    reader_manage_model->setHeaderData(2, Qt::Horizontal, tr("读者密码"));
    reader_manage_model->setHeaderData(3, Qt::Horizontal, tr("读者电话"));
    reader_manage_model->setHeaderData(4, Qt::Horizontal, tr("读者性别"));
    reader_manage_model->setHeaderData(5, Qt::Horizontal, tr("管理员号"));
    reader_manage_model->select();

    ui->reader_tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reader_tw->setModel(reader_manage_model);
    ui->reader_tw->show();

    borrow_manage_model = new QSqlTableModel(this);
    borrow_manage_model->setTable("borrow");
    borrow_manage_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    borrow_manage_model->setHeaderData(0, Qt::Horizontal, tr("读者帐号"));
    borrow_manage_model->setHeaderData(1, Qt::Horizontal, tr("图书号"));
    borrow_manage_model->setHeaderData(2, Qt::Horizontal, tr("借阅日期"));
    borrow_manage_model->setHeaderData(3, Qt::Horizontal, tr("截止日期"));
    borrow_manage_model->setHeaderData(4, Qt::Horizontal, tr("归还日期"));
    borrow_manage_model->setHeaderData(5, Qt::Horizontal, tr("借阅状态"));
    borrow_manage_model->select();

    ui->borrow_tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->borrow_tv->setModel(borrow_manage_model);
    ui->borrow_tv->show();

    this->emptyMap();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdateView()));
    timer->start(5000);
}


AdminForm::~AdminForm()
{
    delete ui;
}


void AdminForm::emptyMap()
{
    QString reader_id;
    QSqlQuery query;
    QSqlRecord record;
    query.exec("select * from reader");

    while (query.next())
    {
        record = query.record();
        reader_id = query.value(record.indexOf("rno")).toString();
        reader_borrow_map.insert(reader_id, 1);
    }
}


void AdminForm::timerUpdateView()
{
//    book_manage_model->setFilter(QObject::tr("bno like '%1'").arg("%"));
//    book_manage_model->select();

//    reader_manage_model->setFilter(QObject::tr("rno like '%1'").arg("%"));
//    reader_manage_model->select();

    borrow_manage_model->setFilter(QObject::tr("rno like '%1'").arg("%"));
    borrow_manage_model->select();
}


void AdminForm::on_dis_all_btn_1_clicked()
{
    book_manage_model->setFilter(QObject::tr("bno like '%1'").arg("%"));
    book_manage_model->select();
}


void AdminForm::on_query_btn_clicked()
{
    QString query_type;
    QString query_text;
    QString select_text;

    query_type = ui->type_cbx->currentText();
    query_text = ui->query_le->text();

    if (query_type == tr("书名"))
        select_text += "bname like'" + query_text + "%'";
    if (query_type == tr("书号"))
        select_text = "bno like'" + query_text + "%'";

    book_manage_model->setFilter(select_text);
    book_manage_model->select();
}


void AdminForm::on_add_btn_1_clicked()
{
    AddBookForm *add_book = new AddBookForm();
    add_book->show();
    add_book->move((QApplication::desktop()->width() - add_book->width()) / 2,
                   (QApplication::desktop()->height() - add_book->height()) / 2);
}


void AdminForm::on_alter_btn_1_clicked()
{
    BookIDForm *book_id = new BookIDForm();
    book_id->show();
    book_id->move((QApplication::desktop()->width() - book_id->width()) / 2,
                  (QApplication::desktop()->height() - book_id->height()) / 2);
}


void AdminForm::on_dele_btn_1_clicked()
{
    DeleteBookForm *delete_book = new DeleteBookForm();
    delete_book->show();
    delete_book->move((QApplication::desktop()->width() - delete_book->width()) / 2,
                      (QApplication::desktop()->height() - delete_book->height()) / 2);
}


void AdminForm::on_dis_all_btn_2_clicked()
{
    reader_manage_model->setFilter("rno like '%'");
    reader_manage_model->select();
}


void AdminForm::on_add_btn_2_clicked()
{
    AddReaderForm *add_reader = new AddReaderForm();
    add_reader->show();
    add_reader->move((QApplication::desktop()->width() - add_reader->width()) / 2,
                     (QApplication::desktop()->height() - add_reader->height()) / 2);
}


void AdminForm::on_alter_btn_2_clicked()
{
    ReaderIDForm *reader_id = new ReaderIDForm();
    reader_id->show();
    reader_id->move((QApplication::desktop()->width() - reader_id->width()) / 2,
                    (QApplication::desktop()->height() - reader_id->height()) / 2);
}


void AdminForm::on_dele_btn_2_clicked()
{
    DeleteReaderForm *delete_reader = new DeleteReaderForm();
    delete_reader->show();
    delete_reader->move((QApplication::desktop()->width() - delete_reader->width()) / 2,
                        (QApplication::desktop()->height() - delete_reader->height()) / 2);
}


void AdminForm::on_b_acc_btn_clicked()
{
    QString book_id;
    QString book_num;
    QString reader_id;
    QString flag;
    QSqlQuery query;
    QSqlQuery query_delete;
    QSqlQuery query_update;
    QDate end_date;
    QDate current_date = QDate::currentDate();

    QModelIndex index = ui->borrow_tv->currentIndex();
    book_id = borrow_manage_model->record(index.row()).value("bno").toString();
    reader_id = borrow_manage_model->record(index.row()).value("rno").toString();
    flag = borrow_manage_model->record(index.row()).value("flag").toString();

    query.exec("select * from borrow where rno = '" + reader_id + "'");

    while (query.next())
    {
        QSqlRecord record = query.record();
        end_date = query.value(record.indexOf("edate")).toDate();
        flag = query.value(record.indexOf("flag")).toString();
        int days = current_date.daysTo(end_date);

        if (days < 0)
        {
            if (flag == "同意借阅请求" || "同意续借请求")
            {
                QMessageBox::warning(this, tr("警告"),
                                     tr("已借书的借阅或续借时间超过最终期限并且未归还，无法借阅新书！"));
                query_delete.exec("delete from borrow where bno = '" + book_id +
                                  "' and rno = '" + reader_id +
                                  "' and flag = '借阅请求'");

                if (query_delete.isActive())
                {
                    QMessageBox::information(this, tr("提示"), tr("管理员取消读者借阅权利！"));
                    borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
                    borrow_manage_model->select();

                    query_update.prepare("update book set bnum = :bnum where bno = :bno");
                    query_update.bindValue(":bno", book_id);
                    query_update.bindValue(":bnum", book_num + 1);
                    query_update.exec();

                    if (query_update.isActive())
                    {
                        QMessageBox::information(this, tr("提示"), tr("更新图书表成功！"));
                        book_manage_model->setFilter(QObject::tr("bno like '%'"));
                        book_manage_model->select();
                    }
                }
                return ;
            }
        }
    }

    query.exec("select * from book where bno = '" + book_id + "'");

    if (query.next())
    {
        QSqlRecord record = query.record();
        book_num = query.value(record.indexOf("bnum")).toInt();
    }

    if (flag == "借阅请求")
    {
        query.prepare("update borrow set flag = :flag where rno = '" +
                      reader_id + "' and bno = '" +
                      book_id + "' and flag = '" + flag + "'");
        query.bindValue(":flag", QString("同意借阅请求"));
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("管理员同意读者借阅请求！"));
            borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
            borrow_manage_model->select();
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没法更新读者借阅请求！"));
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("当前没有读者的借阅请求！"));
}


void AdminForm::on_b_refu_btn_clicked()
{
    QString book_id;
    QString reader_id;
    QString flag;
    int book_num;

    QSqlQuery query;
    QSqlQuery query_update;
    QSqlQuery query_delete;

    QModelIndex index = ui->borrow_tv->currentIndex();
    book_id = borrow_manage_model->record(index.row()).value("bno").toString();
    reader_id = borrow_manage_model->record(index.row()).value("rno").toString();
    flag = borrow_manage_model->record(index.row()).value("flag").toString();

    query.exec("select * from book where bno = '" + book_id + "'");

    if (query.next())
    {
        QSqlRecord record = query.record();
        book_num = query.value(record.indexOf("bnum")).toInt();
    }

    if (flag == "借阅请求")
    {
        query_delete.exec("delete from borrow where bno = '" + book_id +
                          "' and rno = '" + reader_id +
                          "' and flag = '" + flag + "'");

        if (query_delete.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("管理员拒绝读者借阅请求！"));
            borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
            borrow_manage_model->select();

            query_update.prepare("update book set bnum = :bnum where bno = :bno");
            query_update.bindValue(":bno", book_id);
            query_update.bindValue(":bnum", book_num + 1);
            query_update.exec();

            if (query_update.isActive())
            {
                QMessageBox::information(this, tr("提示"), tr("更新图书表成功！"));
                book_manage_model->setFilter(QObject::tr("bno like '%'"));
                book_manage_model->select();
            }
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没法删除读者借阅请求"));
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("当前没有读者的借阅请求！"));
}


void AdminForm::on_c_fresh_btn_clicked()
{
    QString book_id;
    QString reader_id;
    QSqlQuery query;

    query.exec("select * from borrow where flag = '续借请求'");
    if (query.next())
    {
        QSqlRecord record = query.record();
        book_id = query.value(record.indexOf("bno")).toString();
        reader_id = query.value(record.indexOf("rno")).toString();

        ui->c_rno_le->setText(reader_id);
        ui->c_bno_le->setText(book_id);
    }
    else
        QMessageBox::information(this, tr("提示"), tr("读者没有续借请求"));
}


void AdminForm::on_r_fresh_btn_clicked()
{
    QString book_id;
    QString reader_id;
    QSqlQuery query;

    query.exec("select * from borrow where flag = '还书请求'");
    if (query.next())
    {
        QSqlRecord record = query.record();
        book_id = query.value(record.indexOf("bno")).toString();
        reader_id = query.value(record.indexOf("rno")).toString();

        ui->r_rno_le->setText(reader_id);
        ui->r_bno_le->setText(book_id);
    }
    else
        QMessageBox::information(this, tr("提示"), tr("读者没有还书请求"));
}


void AdminForm::on_c_acc_btn_clicked()
{
    QString book_id;
    QString reader_id;
    QSqlQuery query;
    QSqlQuery query_update;

    book_id = ui->c_bno_le->text();
    reader_id = ui->c_rno_le->text();

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '续借请求'");

    if (!query.next())
    {
        QMessageBox::warning(this, tr("警告"), tr("借阅表中没有对应的读者续借请求！"));
        return ;
    }

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '续借请求'");

    while (query.next())
    {
        query_update.prepare("update borrow set flag = :flag where rno = '" +
                             reader_id + "' and bno = '" + book_id +
                             "' and flag = '续借请求'");
        query_update.bindValue(":flag", QString("同意续借请求"));
        query_update.exec();

        if (query_update.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("管理员同意读者续借请求！"));
            borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
            borrow_manage_model->select();
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没法更新读者续借请求"));
    }
}


void AdminForm::on_c_refu_btn_clicked()
{
    QString book_id;
    QString reader_id;
    QString end_date;
    QString properties;
    QDate start_date;
    QSqlQuery query;
    QSqlQuery query_update;

    book_id = ui->c_bno_le->text();
    reader_id = ui->c_rno_le->text();

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '续借请求'");

    if (!query.next())
    {
        QMessageBox::warning(this, tr("警告"), tr("借阅表中没有对应的读者续借请求！"));
        return ;
    }

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '续借请求'");

    while (query.next())
    {
        QSqlRecord record = query.record();
        start_date = query.value(record.indexOf("sdate")).toDate();

        properties = " edate = :edate, flag = :flag ";
        end_date = start_date.addDays(30).toString("yyyy-MM-dd");
        query_update.prepare("update borrow set" + properties +
                             "where rno = '" + reader_id + "' and bno = '" +
                             book_id + "' and flag = '续借请求'");
        query_update.bindValue(":edate", end_date);
        query_update.bindValue(":flag", QString("拒绝续借请求"));
        query_update.exec();

        if (query_update.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("管理员拒绝读者续借请求！"));
            borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
            borrow_manage_model->select();
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没法更新读者续借请求！"));
    }
}


void AdminForm::on_r_acc_btn_clicked()
{
    QString book_id;
    QString reader_id;
    int book_num;

    QSqlQuery query;
    QSqlQuery query_update;

    book_id = ui->r_bno_le->text();
    reader_id = ui->r_rno_le->text();

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '还书请求'");

    if (!query.next())
    {
        QMessageBox::warning(this, tr("警告"), tr("借阅表中没有对应的读者还书请求！"));
        return ;
    }

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '还书请求'");

    while (query.next())
    {
        query.exec("select * from book where bno = '" + book_id + "'");

        if (query.next())
        {
            QSqlRecord record = query.record();
            book_num = query.value(record.indexOf("bnum")).toInt();
        }

        query_update.prepare("update borrow set flag = :flag where rno = '" +
                             reader_id + "' and bno = '" + book_id +
                             "' and flag = '还书请求'");
        query_update.bindValue(":flag", "同意还书请求");
        query_update.exec();

        if (query_update.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("管理员同意读者还书请求！"));
            borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
            borrow_manage_model->select();

            query_update.prepare("update book set bnum = :bnum where bno = :bno");
            query_update.bindValue(":bno", book_id);
            query_update.bindValue(":bnum", book_num + 1);
            query_update.exec();

            if (query_update.isActive())
            {
                QMessageBox::information(this, tr("提示"), tr("更新图书表成功！"));
                book_manage_model->setFilter(QObject::tr("bno like '%'"));
                book_manage_model->select();
            }
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没法更新读者还书请求"));
    }
}


void AdminForm::on_r_refu_btn_clicked()
{
    QString book_id;
    QString reader_id;
    QString properties;
    QSqlQuery query;
    QSqlQuery query_update;

    book_id = ui->r_bno_le->text();
    reader_id = ui->r_rno_le->text();

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '还书请求'");

    if (!query.next())
    {
        QMessageBox::warning(this, tr("警告"), tr("借阅表中没有对应的读者还书请求！"));
        return ;
    }

    query.exec("select * from borrow where rno = '" + reader_id +"' and bno = '" +
               book_id + "' and flag = '还书请求'");

    while (query.next())
    {
        properties = " rdate = :rdate, flag = :flag ";
        query_update.prepare("update borrow set" + properties +
                             "where rno = '" + reader_id + "' and bno = '" +
                             book_id + "' and flag = '还书请求");
        query_update.bindValue(":rdate", "");
        query_update.bindValue(":flag", "拒绝还书请求");
        query_update.exec();

        if (query_update.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("管理员拒绝读者还书请求！"));
            borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
            borrow_manage_model->select();
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没法更新读者还书请求"));
    }
}


void AdminForm::on_quit_btn_clicked()
{
    this->close();
//    UserLogin *user_login = new UserLogin();
//    user_login->show();
//    user_login->move((QApplication::desktop()->width() - user_login->width()) / 2,
//                     (QApplication::desktop()->height() - user_login->height()) / 2);
}


void AdminForm::on_fresh_btn_clicked()
{
    borrow_manage_model->setFilter(QObject::tr("bno like '%'"));
    borrow_manage_model->select();

    book_manage_model->setFilter(QObject::tr("bno like '%'"));
    book_manage_model->select();
}
