#ifndef DELETE_BOOK_FORM_H
#define DELETE_BOOK_FORM_H

#include <QWidget>

namespace Ui {
class DeleteBookForm;
}

class DeleteBookForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteBookForm(QWidget *parent = 0);
    ~DeleteBookForm();

private slots:
    void on_ensure_btn_clicked();
    void on_cancel_btn_clicked();

private:
    Ui::DeleteBookForm *ui;
};

#endif // DELETE_BOOK_FORM_H
