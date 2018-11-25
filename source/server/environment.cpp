/**
 * Name: environment.cpp
 * User: L.Laddie
 * Function: 系统环境
 */

#include <QCryptographicHash>
#include <QString>
#include <QDebug>

#include "environment.h"

//析构函数实现
Envir::~Envir()
{
    for (auto i : m_obligatory_course)
	{
		delete i;
	}

    for (auto i : m_elective_course)
	{
		delete i;
	}

    for (auto i : m_student)
	{
		delete i.first;
	}

    for (auto i : m_teacher)
	{
		delete i.first;
	}

    for (auto i : m_admin)
	{
		delete i.first;
	}
}

//添加和删除课程函数实现

void Envir::addObligatoryCourse(Obligatory_course* course)
{
    Course* flag_course = findCourse(course->getID());

    if(!flag_course)
    {
        m_obligatory_course.insert(course);
    }
    else
    {
        throw std::runtime_error("课程ID重复");
    }
}

void Envir::addElectiveCourse(Elective_course* course)
{
    Course* flag_course = findCourse(course->getID());

    if(!flag_course)
    {
        m_elective_course.insert(course);
    }
    else
    {
        throw std::runtime_error("课程ID重复");
    }
}

std::set<Course*> Envir::getElectiveCourse()
{
    return m_elective_course;
}

std::set<Course*> Envir::getObligatoryCourse()
{
    return m_obligatory_course;
}

void Envir::deleteCourse(Course *course)
{
    if(!course)
        return;
    auto i = m_obligatory_course.find(course);
    if(i == m_obligatory_course.end()){
        i = m_elective_course.find(course);
        m_elective_course.erase(i);
    }
    else m_obligatory_course.erase(i);
    delete (*i);
}

//对用户权限课程类操作

void Envir::setCourseStudent(Student* student)
{
    std::set<Course_student*> temp_set, temp_select;
    for(auto i : m_obligatory_course)
    {
        if(i->checkStudent(student)){
            Course_student *temp = new Course_student(i);
            temp_set.insert(temp);
        }
    }
    for(auto i : m_elective_course)
    {
        if(i->checkStudent(student)){
            Course_student *temp = new Course_student(i);
            temp_set.insert(temp);
        }
        else{
            Course_student *temp = new Course_student(i);
            temp_select.insert(temp);
        }
    }
    student->initCourse(temp_set, temp_select);
}

void Envir::setCourseTeacher(Teacher *teacher)
{
    std::set<Course_teacher*> temp_set;
    for(auto i : m_obligatory_course)
    {
        if(i->checkTeacher(teacher)){
            Course_teacher *temp = new Course_teacher(i);
            temp_set.insert(temp);
        }
    }
    for(auto i : m_elective_course)
    {
        if(i->checkTeacher(teacher)){
            Course_teacher *temp = new Course_teacher(i);
            temp_set.insert(temp);
        }
    }
    teacher->initCourse(temp_set);
}
/*
void Envir::setCourseAdmin(Admin *admin)
{
    std::set<Course_admin*> temp_set;
    for(auto i : m_obligatory_course)
    {
        Course_admin *temp = new Course_admin(i);
        temp_set.insert(temp);
    }
    for(auto i : m_elective_course)
    {
        Course_admin *temp = new Course_admin(i);
        temp_set.insert(temp);
    }
    admin->initCourse(temp_set);
}*/

Course* Envir::findCourse(std::string id)
{
    for(auto i : m_obligatory_course)
    {
        if(i->getID() == id){
            return i;
        }
    }
    for(auto i : m_elective_course)
    {
        if(i->getID() == id){
            return i;
        }
    }
    return NULL;
}

//添加用户函数实现

void Envir::addUserStudent(Student* student, std::string password)
{
    User* flag_user = findUser(student->getID());
    if(!flag_user)
    {
        m_student.insert(std::make_pair(student, password));
    }
    else
    {
        throw std::runtime_error("用户ID重复");
    }
}

void Envir::addUserTeacher(Teacher* teacher, std::string password)
{
    User* flag_user = findUser(teacher->getID());
    if(!flag_user)
    {
        m_teacher.insert(std::make_pair(teacher, password));
    }
    else
    {
        throw std::runtime_error("用户ID重复");
    }
}

void Envir::addUserAdmin(Admin* admin, std::string password)
{
    User* flag_user = findUser(admin->getID());
    if(!flag_user)
    {
        m_admin.insert(std::make_pair(admin, password));
    }
    else
    {
        throw std::runtime_error("用户ID重复");
    }
}

//获取用户函数实现

std::map<Student*, std::string> Envir::getUserStudent()
{
	return m_student;
}

std::map<Teacher*, std::string> Envir::getUserTeacher()
{
	return m_teacher;
}

std::map<Admin*, std::string> Envir::getUserAdmin()
{
	return m_admin;
}

Student* Envir::checkUserStudent(std::string username, std::string password)
{
    for (auto i : m_student)
    {
        if (i.first->getID() == username) {
            if(i.second == password){
                return i.first;
            }
            break;
        }
    }
    return NULL;
}

Teacher* Envir::checkUserTeacher(std::string username, std::string password)
{
    for (auto i : m_teacher)
    {
        if (i.first->getID() == username) {
            if(i.second == password){
                return i.first;
            }
            break;
        }
    }
    return NULL;
}

Admin* Envir::checkUserAdmin(std::string username, std::string password)
{
    for (auto i : m_admin)
    {
        if (i.first->getID() == username) {
            if(i.second == password){
                return i.first;
            }
            break;
        }
    }
    return NULL;
}

User* Envir::findUser(std::string id)
{
    for(auto i : m_student)
    {
        if(i.first->getID() == id){
            return (User*)i.first;
        }
    }

    for(auto i : m_teacher)
    {
        if(i.first->getID() == id){
            return (User*)i.first;
        }
    }

    for(auto i : m_admin)
    {
        if(i.first->getID() == id){
            return (User*)i.first;
        }
    }
    return NULL;
}

void Envir::changeUserPass(User *user, std::string pass)
{
    switch(user->getUserType())
    {
    case user_type::student:
    {
        auto i = m_student.find((Student*)user);
        if(i != m_student.end()){
            i->second = pass;
        }
        break;
    }

    case user_type::teacher:
    {
        auto i = m_teacher.find((Teacher*)user);
        if(i != m_teacher.end()){
            i->second = pass;
        }
        break;
    }

    case user_type::admin:
    {
        auto i = m_admin.find((Admin*)user);
        if(i != m_admin.end()){
            i->second = pass;
        }
        break;
    }

    default:
        break;
    }
}

void Envir::deleteUser(User *user)
{
    switch(user->getUserType())
    {
    case user_type::student:
    {
        Student* student = (Student*)user;
        for(auto i : student->getCourse())
        {
            Course* temp = this->findCourse(i->getID());
            temp->deleteStudent(student);
        }
        m_student.erase(student);
        delete student;
        break;
    }

    case user_type::teacher:
    {
        Teacher* teacher = (Teacher*)user;
        for(auto i : teacher->getCourse())
        {
            Course* temp = this->findCourse(i->getID());
            temp->setTeacher(NULL);
        }
        m_teacher.erase(teacher);
        delete teacher;
        break;
    }

    case user_type::admin:
    {
        Admin* admin = (Admin*)user;
        m_admin.erase(admin);
        delete admin;
        break;
    }

    default:
        break;
    }
}
