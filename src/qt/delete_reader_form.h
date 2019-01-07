#ifndef DELETE_READER_FORM_H
#define DELETE_READER_FORM_H

#include <QWidget>

namespace Ui {
class DeleteReaderForm;
}

class DeleteReaderForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteReaderForm(QWidget *parent = 0);
    ~DeleteReaderForm();

private slots:
    void on_ensure_btn_clicked();
    void on_cancel_btn_clicked();

private:
    Ui::DeleteReaderForm *ui;
};

#endif // DELETE_READER_FORM_H
