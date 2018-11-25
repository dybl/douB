/**
 * Name: user.cpp
 * User: L.Laddie
 * Function: 用户对象
 */

#include <QDebug>
#include <QString>
#include "user.h"

//User基类函数实现

std::string User::getID()
{
	return m_ID;
}

std::string User::getName()
{
	return m_name;
}

std::string User::getInsititude()
{
	return m_insititude;
}

//学生函数实现

std::string Student::getClass()
{
	return m_class;
}

void Student::setClass(std::string class_name)
{
	this->m_class = class_name;
}

std::map<Course_student*, float> Student::getGrade()
{
	std::map<Course_student*, float> ans;
	for (auto& i : m_course)
	{
		float grade = i->getMyGrade(this);
		ans.insert(std::make_pair(i, grade));
	}
	return ans;
}

std::set<Course_student*> Student::getCourse()
{
	return m_course;
}

std::set<Course_student*> Student::getSelectCourse()
{
    return m_select_course;
}

Course_student* Student::findCourse(std::string id)
{
    Course_student* cur_course = NULL;
    for(auto i : m_course)
    {
        if(i->getID() == id)
        {
            cur_course = i;
        }
    }
    return cur_course;
}

Course_student* Student::findSelCourse(std::string id)
{
    Course_student* cur_course = NULL;
    for(auto i : m_select_course)
    {
        if(i->getID() == id)
        {
            cur_course = i;
        }
    }
    return cur_course;
}

void Student::addCourse(Course_student* course)
{
    course->addElectiveStudent(this);
    this->m_course.insert(course);
    this->m_select_course.erase(course);
}

bool Student::deleteCourse(Course_student* course)
{
    if (course->deleteElectiveStudent(this)) {
		this->m_course.erase(course);
        this->m_select_course.insert(course);
		return true;
	}
	return false;
}

void Student::initCourse(std::set<Course_student *> course, std::set<Course_student *> select_course)
{
    eraseCourse();
    m_course = course;
    m_select_course = select_course;
}

void Student::eraseCourse()
{
    for(auto i : m_course)
    {
        delete i;
    }
    m_course.clear();
    for(auto i : m_select_course)
    {
        delete i;
    }
    m_select_course.clear();
}

user_type Student::getUserType()
{
    return user_type::student;
}

//教师函数实现

std::set<Course_teacher*> Teacher::getCourse()
{
	return m_course;
}

void Teacher::initCourse(std::set<Course_teacher *> course)
{
    eraseCourse();
    m_course = course;
}

void Teacher::eraseCourse()
{
    for(auto i : m_course)
    {
        delete i;
    }
    m_course.clear();
}


user_type Teacher::getUserType()
{
    return user_type::teacher;
}

Course_teacher* Teacher::findCourse(std::string id)
{
    Course_teacher* temp = NULL;
    for(auto i : m_course)
    {
        if(i->getID() == id){
            temp = i;
            break;
        }
    }
    return temp;
}

//管理员函数实现

user_type Admin::getUserType()
{
    return user_type::admin;
}

void Admin::activateEnvir(Envir* envir)
{
	m_envir = envir;
}

Envir* Admin::getEnvir()
{
    return m_envir;
}

/*
void Admin::addObligatoryCourse(std::string ID, std::string name, int credit)
{
    m_envir->addObligatoryCourse(ID, name, credit);
}

void Admin::addElectiveCourse(std::string ID, std::string name, int credit)
{
    m_envir->addElectiveCourse(ID, name, credit);
}

void Admin::addUserStudent(std::string ID, std::string name, std::string insititude)
{
    m_envir->addUserStudent(ID, name, insititude);
}

void Admin::addUserTeacher(std::string ID, std::string name, std::string insititude)
{
    m_envir->addUserTeacher(ID, name, insititude);
}

void Admin::addUserAdmin(std::string ID, std::string name, std::string insititude)
{
    m_envir->addUserAdmin(ID, name, insititude);
}

std::map<Student*, std::string> Admin::getUserStudent()
{
    return m_envir->getUserStudent();
}

std::map<Teacher*, std::string> Admin::getUserTeacher()
{
    return m_envir->getUserTeacher();
}

std::map<Admin*, std::string> Admin::getUserAdmin()
{
    return m_envir->getUserAdmin();
}
*/

std::istream& operator >> (std::istream& input, User& user)
{
    input >> user.m_ID >> user.m_name >> user.m_insititude;
}

std::ostream& operator << (std::ostream& output, User& user)
{
    output << user.m_ID << ' ' << user.m_name << ' ' << user.m_insititude;
}

std::istream& operator >> (std::istream& input, Student& student)
{
    input >> student.m_ID >> student.m_name >> student.m_insititude >> student.m_class;
}

std::ostream& operator << (std::ostream& output, Student& student)
{
    output << student.m_ID << ' ' << student.m_name << ' ' << student.m_insititude << ' ' << student.m_class;
}
