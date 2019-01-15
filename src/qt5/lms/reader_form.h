#ifndef READER_FORM_H
#define READER_FORM_H

#include <QVector>
#include <QMap>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>


namespace Ui {
class ReaderForm;
}

class ReaderForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderForm(QWidget *parent = 0);
    ~ReaderForm();

private:
    void bnoBind();
    void emptyBookMap();
    void emptyBorrowMap();
    void emptySomeMap(QString book_id);

private slots:
    void on_search_btn_clicked();
    void on_dis_all_btn_clicked();
    void on_reset_btn_1_clicked();
    void on_locate_btn_clicked();
    void on_bname_ckx_clicked();
    void on_bprint_ckx_clicked();
    void on_bauthor_ckx_clicked();
    void on_add_btn_clicked();
    void on_delete_btn_clicked();
    void on_reset_btn_2_clicked();
    void on_done_btn_clicked();
    void on_add_btn_2_clicked();
    void on_accept_btn_clicked();
    void on_cancel_btn_clicked();
    void on_accept_btn_2_clicked();
    void on_cancel_btn_2_clicked();
    void on_quit_btn_clicked();
    void on_fresh_btn_clicked();
    void timerUpdateView();

private:
    Ui::ReaderForm *ui;
    QSqlQueryModel *book_query_model;
    QSqlTableModel *book_borrow_model;
    QString properties;
    QString tables;
    QVector<QString>   book_id_order;
    QMap<QString, int> book_num_map;
    QMap<QString, int>::iterator book_itera;
    QMap<QString, int> renew_num_map;
    QMap<QString, int>::iterator renew_itera;
};

#endif // READER_FORM_H
