#ifndef INFORMATION_USER_H
#define INFORMATION_USER_H

#include <QDialog>
#include <QStandardItemModel>

#include "include.h"
#include "convey.h"
#include "envir_widget.h"

namespace Ui {
class Information_user;
}

class Information_user : public QDialog
{
    Q_OBJECT

public:
    explicit Information_user(Envir_widget* envir_widget, QWidget *parent = 0);
    ~Information_user();

    void setUser(QString id);

    void showInfo();
    void updateCourse();

    void creatActivex();

    std::vector<std::string> addCourse();       //将所选择课程添加到列表

signals:
    void updateUser();

private slots:
    void on_cancel_btn_clicked();

    void on_comboBox_user_type_currentIndexChanged(int index);

    void on_add_btn_clicked();

    void on_update_btn_clicked();

    void on_del_btn_clicked();

    void on_select_course_btn_clicked();

    void on_cancel_course_btn_clicked();

private:
    Ui::Information_user *ui;
    QStandardItemModel* ui_course_model_n;
    QStandardItemModel* ui_course_model_y;

    QString m_user_id = "";
    Envir_widget* m_envir_widget;

    std::pair<User_model, std::vector<Course_model> > cur_user;
    std::vector<Course_model> m_all_course;
};

#endif // INFORMATION_USER_H
