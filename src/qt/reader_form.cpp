#include "reader_form.h"
#include "ui_reader_form.h"
#include "user_login.h"
#include "admin_form.h"

#include <QTimer>
#include <QtMath>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QModelIndex>
#include <QDate>
#include <QDateTime>
#include <QTableWidget>
#include <QDesktopWidget>
#include <QAbstractItemView>
#include <QSqlQuery>
#include <QSqlRecord>


ReaderForm::ReaderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderForm)
{
    ui->setupUi(this);
    this->setWindowTitle("读者");

    ui->reader_tw->setCurrentIndex(0);
    ui->bname_le->setEnabled(false);
    ui->bprint_le->setEnabled(false);
    ui->bauthor_le->setEnabled(false);

    properties = " bno, bname, tname, bprint, bauthor, bnum, tloc ";
    tables = " book, type ";

    book_query_model = new QSqlQueryModel(this);
    book_query_model->setQuery("select" + properties + "from" + tables +
                               "where btno = tno");
    book_query_model->setHeaderData(0, Qt::Horizontal, tr("图书号"));
    book_query_model->setHeaderData(1, Qt::Horizontal, tr("图书名"));
    book_query_model->setHeaderData(2, Qt::Horizontal, tr("图书类别"));
    book_query_model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    book_query_model->setHeaderData(4, Qt::Horizontal, tr("作者"));
    book_query_model->setHeaderData(5, Qt::Horizontal, tr("馆藏量"));
    book_query_model->setHeaderData(6, Qt::Horizontal, tr("位置"));

    ui->book_tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->book_tv->setModel(book_query_model);
    ui->book_tv->show();

    book_borrow_model = new QSqlTableModel(this);
    book_borrow_model->setTable("book");
    book_borrow_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    book_borrow_model->setHeaderData(0, Qt::Horizontal, tr("图书号"));
    book_borrow_model->setHeaderData(1, Qt::Horizontal, tr("图书名"));
    book_borrow_model->setHeaderData(2, Qt::Horizontal, tr("出版社"));
    book_borrow_model->setHeaderData(3, Qt::Horizontal, tr("作者"));
    book_borrow_model->setHeaderData(4, Qt::Horizontal, tr("馆藏量"));
    book_borrow_model->removeColumn(book_borrow_model->fieldIndex("btno"));
    book_borrow_model->removeColumn(book_borrow_model->fieldIndex("ano"));
    book_borrow_model->select();

    ui->borrow_tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->borrow_tv->setModel(book_borrow_model);
    ui->borrow_tv->show();

    ui->borrow_tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QDate date = QDate::currentDate();
    ui->renew_de->setDate(date);

    this->bnoBind();

    this->emptyBookMap();
    this->emptyBorrowMap();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdateView()));
    timer->start(5000);
}


ReaderForm::~ReaderForm()
{
    delete ui;
}


void ReaderForm::timerUpdateView()
{
//    properties = " bno, bname, tname, bprint, bauthor, bnum, tloc ";
//    tables = " book, type ";

//    book_query_model = new QSqlQueryModel(this);
//    book_query_model->setQuery("select" + properties + "from" + tables +
//                               "where btno = tno");
//    book_query_model->setHeaderData(0, Qt::Horizontal, tr("图书号"));
//    book_query_model->setHeaderData(1, Qt::Horizontal, tr("图书名"));
//    book_query_model->setHeaderData(2, Qt::Horizontal, tr("图书类别"));
//    book_query_model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
//    book_query_model->setHeaderData(4, Qt::Horizontal, tr("作者"));
//    book_query_model->setHeaderData(5, Qt::Horizontal, tr("馆藏量"));
//    book_query_model->setHeaderData(6, Qt::Horizontal, tr("位置"));
//    ui->book_tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->book_tv->setModel(book_query_model);
//    ui->book_tv->show();

    book_borrow_model->setFilter(QObject::tr("bno like '%'"));
    book_borrow_model->select();
}


void ReaderForm::emptyBookMap()
{
    QSqlQuery query;
    QSqlRecord record;
    QString book_id;
    query.exec("select bno from book");

    while(query.next())
    {
        record = query.record();
        book_id = query.value(record.indexOf("bno")).toString();
        book_num_map.insert(book_id ,0);
    }
}


void ReaderForm::emptyBorrowMap()
{
    QSqlQuery query;
    QSqlRecord record;
    QString book_id;
    query.exec("select bno from book");

    while(query.next())
    {
        record = query.record();
        book_id = query.value(record.indexOf("bno")).toString();
        renew_num_map.insert(book_id ,0);
    }
}


void ReaderForm::emptySomeMap(QString book_id)
{
    book_num_map[book_id] = 0;
}


void ReaderForm::on_search_btn_clicked()
{
    QString book_name;
    QString book_print;
    QString book_author;

    book_name = ui->bname_le->text().trimmed();
    book_print = ui->bprint_le->text().trimmed();
    book_author = ui->bauthor_le->text().trimmed();

    QSqlQueryModel *model = new QSqlQueryModel;

    if (ui->bname_ckx->isChecked())
    {
        if (ui->bprint_ckx->isChecked())
            if (ui->bauthor_ckx->isChecked())
                model->setQuery("select" + properties + "from" + tables +
                                "where btno = tno and bname like '" + book_name +
                                "%'" + "and bprint like '" + book_print + "%'" +
                                "and bauthor like '" + book_author + "%'");
            else
                model->setQuery("select" + properties + "from" + tables +
                                "where btno = tno and bname like '" + book_name +
                                "%'" + "and bprint like '" + book_print + "%'");
        else if (ui->bauthor_ckx->isChecked())
            model->setQuery("select" + properties + "from" + tables +
                            "where btno = tno and bname like '" + book_name + "%'" +
                            "and bauthor like '" + book_author + "%'");
        else
            model->setQuery("select" + properties + "from" + tables +
                            "where btno = tno and bname like '" + book_name + "%'");
    }
    else if (ui->bprint_ckx->isChecked())
    {
        if (ui->bauthor_ckx->isChecked())
            model->setQuery("select" + properties + "from" + tables +
                            "where btno = tno and bprint like '" + book_print + "%'" +
                            "and bauthor like '" + book_author + "%'");
        else
            model->setQuery("select" + properties + "from" + tables +
                            "where btno = tno and bprint like '" + book_print + "%'");
    }
    else if (ui->bauthor_ckx->isChecked())
        model->setQuery("select" + properties + "from" + tables +
                        "where btno = tno and bauthor like '" + book_author + "%'");

    model->setHeaderData(0, Qt::Horizontal, tr("图书号"));
    model->setHeaderData(1, Qt::Horizontal, tr("图书名"));
    model->setHeaderData(2, Qt::Horizontal, tr("图书类别"));
    model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, tr("作者"));
    model->setHeaderData(5, Qt::Horizontal, tr("馆藏量"));
    model->setHeaderData(6, Qt::Horizontal, tr("位置"));

    ui->book_tv->setModel(model);
    ui->book_tv->show();
}


void ReaderForm::on_dis_all_btn_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select" + properties + "from" + tables +
                          "where btno = tno");
    model->setHeaderData(0, Qt::Horizontal, tr("图书号"));
    model->setHeaderData(1, Qt::Horizontal, tr("图书名"));
    model->setHeaderData(2, Qt::Horizontal, tr("图书类别"));
    model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, tr("作者"));
    model->setHeaderData(5, Qt::Horizontal, tr("馆藏量"));
    model->setHeaderData(6, Qt::Horizontal, tr("位置"));

    ui->book_tv->setModel(model);
    ui->book_tv->show();
}


void ReaderForm::on_reset_btn_1_clicked()
{
    ui->bname_le->setText("");
    ui->bprint_le->setText("");
    ui->bauthor_le->setText("");
    ui->bno_cmx->setCurrentText("0000");
}


void ReaderForm::on_locate_btn_clicked()
{
    QString book_id;

    book_id = ui->bno_cmx->currentText().trimmed();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select" + properties + "from" + tables +
                    "where btno = tno and bno = '" + book_id + "'");
    model->setHeaderData(0, Qt::Horizontal, tr("图书号"));
    model->setHeaderData(1, Qt::Horizontal, tr("图书名"));
    model->setHeaderData(2, Qt::Horizontal, tr("图书类别"));
    model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, tr("作者"));
    model->setHeaderData(5, Qt::Horizontal, tr("馆藏量"));
    model->setHeaderData(6, Qt::Horizontal, tr("位置"));

    ui->book_tv->setModel(model);
    ui->book_tv->show();
}


void ReaderForm::bnoBind()
{
    ui->bno_cmx->clear();

    QSqlQuery query;
    query.exec("select bno from book");

    while(query.next())
    {
        ui->bno_cmx->insertItem(0, query.value(0).toString());
    }
}


void ReaderForm::on_bname_ckx_clicked()
{
    if (ui->bname_ckx->isChecked())
        ui->bname_le->setEnabled(true);
    else
        ui->bname_le->setEnabled(false);
}


void ReaderForm::on_bprint_ckx_clicked()
{
    if (ui->bprint_ckx->isChecked())
        ui->bprint_le->setEnabled(true);
    else
        ui->bprint_le->setEnabled(false);
}


void ReaderForm::on_bauthor_ckx_clicked()
{
    if (ui->bauthor_ckx->isChecked())
        ui->bauthor_le->setEnabled(true);
    else
        ui->bauthor_le->setEnabled(false);
}


void ReaderForm::on_add_btn_clicked()
{
    QString book_id;
    QString book_name;
    QString book_author;
    QString book_print;
    QString borrow_book_name;

    int book_num;
    int book_num_all;
    int repeat_flag = 0;

    if (ui->borrow_tv->currentIndex().row() < 0)
    {
        QMessageBox::warning(this, tr("提示"), tr("请添加书籍！"));
        return ;
    }

    QModelIndex index = ui->borrow_tv->currentIndex();

    book_id = book_borrow_model->record(
                            index.row()).value("bno").toString();
    book_name  = book_borrow_model->record(
                            index.row()).value("bname").toString();
    book_author = book_borrow_model->record(
                            index.row()).value("bauthor").toString();
    book_print = book_borrow_model->record(
                            index.row()).value("bprint").toString();
    book_num = book_borrow_model->record(
                            index.row()).value("bnum").toInt();

    book_itera = book_num_map.find(book_id);
    book_num_all = 1 + book_itera.value();

    if (book_num_all <= book_num)
    {
        book_id_order.append(book_id);

        for (int i = 0; i < ui->borrow_tw->rowCount(); i++)
        {
            borrow_book_name = ui->borrow_tw->item(i, 0)->text();

            if (borrow_book_name == book_name)
            {
                QTableWidgetItem *item = new QTableWidgetItem(
                                         QString::number(book_num_all));
                ui->borrow_tw->setItem(i, 2, item);
    //            QTableWidgetItem *item = new QTableWidgetItem(QString::number());
    //            QTableWidgetItem *item = ui->borrow_tw->item(i, 2);
    //            after_borrow_bnum = item->text().toInt();
    //            after_borrow_bnum++;
    //            item->setText(QString::number(after_borrow_bnum));
    //            ui->borrow_tw->setItem(i, 2, item);
                repeat_flag = 1;
                break;
            }
        }

        if (repeat_flag == 0)
        {
            QTableWidgetItem *item0 = new QTableWidgetItem(book_name);
            QTableWidgetItem *item1 = new QTableWidgetItem(book_author);
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(
                                                           book_num_all));
            QTableWidgetItem *item3 = new QTableWidgetItem(book_print);

            int row = ui->borrow_tw->rowCount();

            ui->borrow_tw->setRowCount(row + 1);
            ui->borrow_tw->setItem(row, 0, item0);
            ui->borrow_tw->setItem(row, 1, item1);
            ui->borrow_tw->setItem(row, 2, item2);
            ui->borrow_tw->setItem(row, 3, item3);
        }
        book_num_map[book_id] = book_num_all;
        ui->bno_le->setText(book_id);
        ui->bnum_le->setText(QString::number(book_num_all));
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("书的总数量超过馆藏容量！"));
        book_num_all = book_num_all - 1;
    }
}


void ReaderForm::on_add_btn_2_clicked()
{
    QString book_id;
    QString book_author;
    QString book_print;
    QString book_name;
    QString borrow_book_name;
    int book_num_in;
    int book_num_all;
    int repeat_flag = 0;
    QSqlQuery query;

    book_id = ui->bno_le->text().trimmed();
    book_num_in = ui->bnum_le->text().trimmed().toInt();

    if (book_id != "" && book_num_in != 0)
    {
        query.exec("select * from book where bno = '" + book_id + "'");

        if (query.next())
        {
            QSqlRecord record = query.record();

            book_itera = book_num_map.find(book_id);
            book_num_all = book_num_in + book_itera.value();

            if (book_num_all <= query.value(record.indexOf("bnum")).toInt())
            {
                book_id_order.append(book_id);

                book_name = query.value(record.indexOf("bname")).toString();
                book_author = query.value(record.indexOf("bauthor")).toString();
                book_print = query.value(record.indexOf("bprint")).toString();

                for (int i = 0; i < ui->borrow_tw->rowCount(); i++)
                {
                    borrow_book_name = ui->borrow_tw->item(i, 0)->text();

                    if (borrow_book_name == book_name)
                    {
                        QTableWidgetItem *item = new QTableWidgetItem(
                                                 QString::number(book_num_all));
                        ui->borrow_tw->setItem(i, 2, item);
                        repeat_flag = 1;
                        break;
                    }
                }

                if (repeat_flag == 0)
                {
                    QTableWidgetItem *item0 = new QTableWidgetItem(
                                                  book_name);
                    QTableWidgetItem *item1 = new QTableWidgetItem(
                                                  book_author);
                    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(
                                                  book_num_all));
                    QTableWidgetItem *item3 = new QTableWidgetItem(
                                                  book_print);

                    int row = ui->borrow_tw->rowCount();

                    ui->borrow_tw->setRowCount(row + 1);
                    ui->borrow_tw->setItem(row, 0, item0);
                    ui->borrow_tw->setItem(row, 1, item1);
                    ui->borrow_tw->setItem(row, 2, item2);
                    ui->borrow_tw->setItem(row, 3, item3);
                }
                book_num_map[book_id] = book_num_all;
            }
            else
            {
                QMessageBox::warning(this, tr("警告"), tr("书的总数量超过馆藏容量！"));
                book_num_all = book_num_all - book_num_in;
            }
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没有对应的图书号！"));
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("书号或数量不能为空！"));
}


void ReaderForm::on_delete_btn_clicked()
{
    QString book_id;
    QModelIndex index;

    int current_row = ui->borrow_tw->currentIndex().row();
    ui->borrow_tw->removeRow(current_row);

    index = ui->borrow_tv->currentIndex();
    book_id = book_borrow_model->record(index.row()).value("bno").toString();
    this->emptySomeMap(book_id);
}


void ReaderForm::on_reset_btn_2_clicked()
{   
    ui->rno_le->setText("");
    ui->bno_le->setText("");
    ui->bnum_le->setText("");
    ui->rkey_le->setText("");

    book_id_order.clear();;

    this->emptyBookMap();
}


void ReaderForm::on_done_btn_clicked()
{
    QString reader_id;
    QString reader_pwd;
    QSqlQuery query_check;
    int row;

    reader_id = ui->rno_le->text().trimmed();
    reader_pwd = ui->rkey_le->text().trimmed();
    row = ui->borrow_tw->rowCount();

    if (reader_id.isEmpty() || reader_pwd.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("读者号或密码不能为空！"));
        return ;
    }
    if (row == 0)
    {
        QMessageBox::warning(this, tr("警告"), tr("请选择需要借阅的书！"));
        return ;
    }

    query_check.exec("select rno, rkey from reader where rno = '" + reader_id + "'");

    if (query_check.next())
    {
        QSqlRecord rec = query_check.record();
        if (reader_pwd == query_check.value(rec.indexOf("rkey")).toString())
        {
            QSqlQuery query;
            QSqlQuery query_update;
            QSqlQuery query_insert;

            QString book_id;
            int book_num;
            int insert_success_flag;
            int update_success_flag;

            for (int i = 0; i < book_id_order.size(); i++)
            {
                book_id = book_id_order[i];

                query.exec("select bnum from book where bno = '" + book_id + "'");
                if (query.next())
                {
                    QSqlRecord record = query.record();
                    book_num = query.value(record.indexOf("bnum")).toInt();
                }
                else
                    continue;

                QString properties = "rno, bno, edate, sdate, rdate, flag";
                QString values = ":rno, :bno, :edate, :sdate, :rdate, :flag";
                QDate date = QDate::currentDate();
                QString start_date = date.toString("yyyy-MM-dd");
                QString end_date = date.addDays(30).toString("yyyy-MM-dd");

                query_insert.prepare("insert into borrow (" + properties + ") values ("
                                     + values + ")");
                query_insert.bindValue(":rno", reader_id);
                query_insert.bindValue(":bno", book_id);
                query_insert.bindValue(":sdate", start_date);
                query_insert.bindValue(":edate", end_date);
                query_insert.bindValue(":flag", QString("借阅请求"));
                query_insert.exec();

                if (query_insert.isActive())
                {
                    insert_success_flag = 1;
//                    QMessageBox::information(this,tr("提示"), tr("借阅请求申请成功！"));
                    book_num--;
                }
                else
                {
                    insert_success_flag = 0;
//                    QMessageBox::warning(this, tr("警告"), tr("借阅请求申请失败！"));
                    return ;
                }
                query_update.prepare("update book set bnum = :bnum where bno = :bno");
                query_update.bindValue(":bno", book_id);
                query_update.bindValue(":bnum", book_num);
                query_update.exec();

                if (query_update.isActive())
                {
                    update_success_flag = 1;
//                    QMessageBox::information(this, tr("提示"), tr("更新图书数据表成功！"));
                }
                else
                {
                    update_success_flag = 0;
//                    QMessageBox::warning(this, tr("警告"), tr("更新图书数据表失败！"));
                }
            }
            book_id_order.clear();
            if (insert_success_flag == 1)
                QMessageBox::information(this,tr("提示"), tr("借阅请求申请成功！"));
            else
                QMessageBox::warning(this, tr("警告"), tr("借阅请求申请失败！"));
            if (update_success_flag == 1)
                QMessageBox::information(this, tr("提示"), tr("更新图书数据表成功！"));
            else
                QMessageBox::warning(this, tr("警告"), tr("更新图书数据表失败！"));
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), tr("密码错误！"));
            return ;
        }
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("读者身份验证失败！"));

    book_borrow_model->setFilter(QObject::tr("bno like '%'"));
    book_borrow_model->select();
}


void ReaderForm::on_accept_btn_clicked()
{
    QString reader_id;
    QString book_id;
    QString properties;
    QSqlQuery query;
    int renew_num;

    reader_id = ui->rno_le_2->text().trimmed();
    book_id = ui->bno_le_2->text().trimmed();

    if (reader_id.isEmpty() || book_id.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("读者号或书号不能为空！"));
        return ;
    }

    query.prepare("select * from borrow where rno = :rno and bno = :bno");
    query.bindValue(":rno", reader_id);
    query.bindValue(":bno", book_id);
    query.exec();

    if (!query.next())
    {
        QMessageBox::warning(this, tr("警告"), tr("借阅表中没有对应的读者图书信息！"));
        return ;
    }

    query.prepare("select * from borrow where rno = :rno and bno = :bno");
    query.bindValue(":rno", reader_id);
    query.bindValue(":bno", book_id);
    query.exec();

    while (query.next())
    {
        QSqlRecord record = query.record();
        QString flag = query.value(record.indexOf("flag")).toString();
        QDate end_date = query.value(record.indexOf("edate")).toDate();
//        QDate current_date = QDate::currentDate();
        QDate current_date = ui->renew_de->date();

        int days = current_date.daysTo(end_date);

        renew_itera = renew_num_map.find(book_id);
        renew_num = renew_itera.value();

        if (flag == "同意续借请求")
        {
            QMessageBox::information(this, tr("提示"), tr("已经续借过一次，没法再次续借！"));
            return ;
        }

        if (flag == "同意借阅请求")
        {
            if (renew_num == 0)
            {
                if (days > 0)
                {
                    QMessageBox::information(this, tr("提示"), tr("没有超过截止期限，无法续借"));
                    return ;
                }
                else if ((days <= 0) && (days >= -5))
                {
                    properties = " edate = :edate, flag = :flag ";
                    QString new_end_date;
                    new_end_date = end_date.addDays(abs(days) + 10).toString("yyyy-MM-dd");
                    query.prepare("update borrow set" + properties +
                                  "where rno = :rno and bno = :bno and flag = '同意借阅请求'");
                    query.bindValue(":rno", reader_id);
                    query.bindValue(":bno", book_id);
                    query.bindValue(":edate", new_end_date);
                    query.bindValue(":flag", QString("续借请求"));
                    query.exec();

                    if (query.isActive())
                    {
                        QMessageBox::information(this, tr("提示"), tr("续借请求申请成功！"));
                        renew_num_map[book_id] = 1;
                    }
                    else
                        QMessageBox::warning(this, tr("警告"), tr("续借请求申请失败！"));
                }
                else
                    QMessageBox::warning(this, tr("警告"), tr("已超过截止期限5天，无法续借！"));
            }
            else
                QMessageBox::warning(this, tr("警告"), tr("已经续借过一次，没法再次续借！"));
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没有读者已经借阅的信息！"));
    }
}


void ReaderForm::on_cancel_btn_clicked()
{
    QDate date = QDate::currentDate();
    ui->rno_le_2->setText("");
    ui->bno_le_2->setText("");
    ui->renew_de->setDate(date);
}


void ReaderForm::on_accept_btn_2_clicked()
{
    QString reader_id;
    QString book_id;
    QString flag;
    QString properties;
    QSqlQuery query;

    reader_id = ui->rno_le_3->text().trimmed();
    book_id = ui->bno_le_3->text().trimmed();

    if (reader_id.isEmpty() || book_id.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("读者号或书号不能为空！"));
        return ;
    }

    query.prepare("select * from borrow where rno = :rno and bno = :bno");
    query.bindValue(":rno", reader_id);
    query.bindValue(":bno", book_id);
    query.exec();

    if (!query.next())
    {
        QMessageBox::warning(this, tr("警告"), tr("借阅表中没有对应的读者图书信息！"));
        return ;
    }

    query.prepare("select * from borrow where rno = :rno and bno = :bno");
    query.bindValue(":rno", reader_id);
    query.bindValue(":bno", book_id);
    query.exec();

    while (query.next())
    {
        QSqlRecord record = query.record();
        flag = query.value(record.indexOf("flag")).toString();

        if (flag == "同意借阅请求" || flag == "同意续借请求")
        {
            properties = " rdate = :rdate, flag = :flag ";
            QDate date = QDate::currentDate();
            QString return_date = date.toString("yyyy-MM-dd");
            query.prepare("update borrow set" + properties + "where rno = '" +
                          reader_id + "' and bno = '" + book_id + "' and flag = '" +
                          flag + "'");
            query.bindValue(":rdate", return_date);
            query.bindValue(":flag", QString("还书请求"));
            query.exec();

            if (query.isActive())
                QMessageBox::information(this, tr("提示"), tr("还书请求申请成功！"));
            else
                QMessageBox::warning(this, tr("警告"), tr("还书请求申请失败！"));
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("没有读者已借阅或续借的信息！"));
    }
}


void ReaderForm::on_cancel_btn_2_clicked()
{
    ui->rno_le_3->setText("");
    ui->bno_le_3->setText("");
}


void ReaderForm::on_quit_btn_clicked()
{
    this->close();
//    UserLogin *user_login = new UserLogin();
//    user_login->show();
//    user_login->move((QApplication::desktop()->width() - user_login->width()) / 2,
//                     (QApplication::desktop()->height() - user_login->height()) / 2);
}


void ReaderForm::on_fresh_btn_clicked()
{
    book_borrow_model->setFilter(QObject::tr("bno like '%'"));
    book_borrow_model->select();
}
