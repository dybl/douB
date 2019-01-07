#ifndef ADD_READER_FORM_H
#define ADD_READER_FORM_H

#include <QWidget>

namespace Ui {
class AddReaderForm;
}

class AddReaderForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddReaderForm(QWidget *parent = 0);
    ~AddReaderForm();

private slots:
    void on_ensure_btn_clicked();
    void on_reset_btn_clicked();
    void on_cancel_btn_clicked();

private:
    Ui::AddReaderForm *ui;
};

#endif // ADD_READER_FORM_H
