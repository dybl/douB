#ifndef ALTER_READER_FORM_H
#define ALTER_READER_FORM_H

#include <QWidget>

namespace Ui {
class AlterReaderForm;
}

class AlterReaderForm : public QWidget
{
    Q_OBJECT

public:
    explicit AlterReaderForm(QWidget *parent = 0);
    ~AlterReaderForm();

private slots:
    void on_ensure_btn_clicked();
    void on_reset_btn_clicked();
    void on_cancel_btn_clicked();
    void displayAllInformation(QString data);

private:
    Ui::AlterReaderForm *ui;
    QString reader_id_global;
};

#endif // ALTER_READER_FORM_H
