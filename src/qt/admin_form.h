#ifndef ADMIN_FORM_H
#define ADMIN_FORM_H

#include <QWidget>
#include <QString>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class AdminForm;
}

class AdminForm : public QWidget
{
    Q_OBJECT

public:
    explicit AdminForm(QWidget *parent = 0);
    ~AdminForm();

private:
    void emptyMap();

private slots:
    void on_dis_all_btn_1_clicked();
    void on_query_btn_clicked();
    void on_add_btn_1_clicked();
    void on_alter_btn_1_clicked();
    void on_dele_btn_1_clicked();
    void on_dis_all_btn_2_clicked();
    void on_add_btn_2_clicked();
    void on_alter_btn_2_clicked();
    void on_dele_btn_2_clicked();
    void on_b_acc_btn_clicked();
    void on_b_refu_btn_clicked();
    void on_c_acc_btn_clicked();
    void on_c_refu_btn_clicked();
    void on_r_acc_btn_clicked();
    void on_r_refu_btn_clicked();
    void on_quit_btn_clicked();
    void on_fresh_btn_clicked();
    void on_c_fresh_btn_clicked();
    void on_r_fresh_btn_clicked();
    void timerUpdateView();

private:
    Ui::AdminForm  *ui;
    QSqlTableModel *book_manage_model;
    QSqlTableModel *reader_manage_model;
    QSqlTableModel *borrow_manage_model;
    QString         book_id_global;
    QMap<QString, bool> reader_borrow_map;
    QMap<QString, bool>::iterator reader_borrow_itera;
};

#endif // ADMIN_FORM_H
