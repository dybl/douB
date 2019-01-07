#ifndef READER_ID_FORM_H
#define READER_ID_FORM_H

#include <QWidget>

namespace Ui {
class ReaderIDForm;
}

class ReaderIDForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderIDForm(QWidget *parent = 0);
    ~ReaderIDForm();

private:
signals:
    void sendReaderID(QString);

private slots:
    void on_ensure_btn_clicked();
    void on_cancel_btn_clicked();

private:
    Ui::ReaderIDForm *ui;
};

#endif // READER_ID_FORM_H
