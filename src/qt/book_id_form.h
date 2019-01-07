#ifndef BOOK_ID_FORM_H
#define BOOK_ID_FORM_H

#include <QWidget>

namespace Ui {
class BookIDForm;
}

class BookIDForm : public QWidget
{
    Q_OBJECT

public:
    explicit BookIDForm(QWidget *parent = 0);
    ~BookIDForm();

private:
signals:
    void sendBookID(QString);

private slots:
    void on_ensure_btn_clicked();
    void on_cancel_btn_clicked();

private:
    Ui::BookIDForm *ui;
};

#endif // BOOK_ID_FORM_H
