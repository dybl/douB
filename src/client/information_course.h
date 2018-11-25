#ifndef INFORMATION_COURSE_H
#define INFORMATION_COURSE_H

#include <QDialog>
#include <QStandardItemModel>

#include "include.h"
#include "convey.h"
#include "envir_widget.h"

namespace Ui {
class Information_course;
}

class Information_course : public QDialog
{
    Q_OBJECT

public:
    explicit Information_course(Envir_widget* envir_widget, QWidget *parent = 0);
    ~Information_course();

    void setCourse(QString id);

    void showInfo();
    void updateStudent();

    void creatActivex();

    std::vector<std::string> addStudent();       //从选择框获取学生

signals:
    void updateCourse();

private slots:
    void on_add_btn_clicked();

    void on_cancel_btn_clicked();

    void on_comboBox_type_currentIndexChanged(int index);

    void on_update_btn_clicked();

    void on_del_btn_clicked();

    void on_select_student_btn_clicked();

    void on_cancel_student_btn_clicked();

    void on_comboBox_teacher_currentIndexChanged(const QString &arg1);

private:
    Ui::Information_course *ui;
    QStandardItemModel* ui_student_model_n;
    QStandardItemModel* ui_student_model_y;

    QString m_course_id = "";
    Envir_widget* m_envir_widget;

    std::pair<Course_model, std::vector<User_model> > cur_course;
    std::map<User_model, std::string> m_all_user;
};

#endif // INFORMATION_COURSE_H
