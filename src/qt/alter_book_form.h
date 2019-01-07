#ifndef ALTER_BOOK_FORM_H
#define ALTER_BOOK_FORM_H

#include <QWidget>

namespace Ui {
class AlterBookForm;
}

class AlterBookForm : public QWidget
{
    Q_OBJECT

public:
    explicit AlterBookForm(QWidget *parent = 0);
    ~AlterBookForm();

private slots:
    void on_ensure_btn_clicked();
    void on_reset_btn_clicked();
    void on_cancel_btn_clicked();
    void displayAllInformation(QString data);

private:
    Ui::AlterBookForm *ui;
    QString book_id_global;
};

#endif // ALTER_BOOK_FORM_H
