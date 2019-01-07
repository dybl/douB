#ifndef ADD_BOOK_FORM_H
#define ADD_BOOK_FORM_H

#include <QWidget>

namespace Ui {
class AddBookForm;
}

class AddBookForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddBookForm(QWidget *parent = 0);
    ~AddBookForm();

private slots:
    void on_ensure_btn_clicked();
    void on_reset_btn_clicked();
    void on_cancel_btn_clicked();

private:
    Ui::AddBookForm *ui;
};

#endif // ADD_BOOK_FORM_H
