#ifndef DELETE_ENSURE_FORM_H
#define DELETE_ENSURE_FORM_H

#include <QWidget>

namespace Ui {
class DeleteEnsureForm;
}

class DeleteEnsureForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteEnsureForm(QWidget *parent = 0);
    ~DeleteEnsureForm();

private slots:
    void on_yes_btn_clicked();
    void on_no_btn_clicked();

private:
    Ui::DeleteEnsureForm *ui;
};

#endif // DELETE_ENSURE_FORM_H
