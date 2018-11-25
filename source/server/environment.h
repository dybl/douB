#pragma once

#include "include.h"
#include "user.h"
#include "course.h"

//系统工作环境（最高权限访问）
class Envir
{
public:
    Envir(){}
    ~Envir();

    void addObligatoryCourse(Obligatory_course* course);
    void addElectiveCourse(Elective_course* course);

    Course* findCourse(std::string id);

    std::set<Course*> getObligatoryCourse();
    std::set<Course*> getElectiveCourse();

    void deleteCourse(Course* course);

    //对于学生和教师重新包装课程权限后使用
    void setCourseStudent(Student* student);
    void setCourseTeacher(Teacher* teacher);

    void addUserStudent(Student* student, std::string password);
    void addUserTeacher(Teacher* teacher, std::string password);
    void addUserAdmin(Admin* admin, std::string password);

    std::map<Student*, std::string> getUserStudent();
    std::map<Teacher*, std::string> getUserTeacher();
    std::map<Admin*, std::string> getUserAdmin();

    User* findUser(std::string id);
    void changeUserPass(User* user, std::string pass);

    void deleteUser(User* user);

    Student* checkUserStudent(std::string username, std::string password);
    Teacher* checkUserTeacher(std::string username, std::string password);
    Admin* checkUserAdmin(std::string username, std::string password);

private:
	//保存当前系统课程
	std::set<Course*> m_obligatory_course;
	std::set<Course*> m_elective_course;

	//保存用户登录信息(md5密码)
    std::map<Student*, std::string> m_student;
    std::map<Teacher*, std::string> m_teacher;
    std::map<Admin*, std::string> m_admin;
};
