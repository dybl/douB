/**
 * Name: course.cpp
 * User: L.Laddie
 * Function: 课程对象
 */

#include <QString>
#include <cmath>
#include "course.h"
#include "user.h"

//课程基类函数实现

Course::Course(std::string id, std::string name, int credit)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_credit = credit;
}

Course::~Course()
{

}

std::string Course::getID()
{
	return m_ID;
}

std::string Course::getName()
{
	return m_name;
}

int Course::getCredit()
{
	return m_credit;
}

int Course::getCapicity()
{
    return this->m_capicity;
}

void Course::setCapicity(int num)
{
    if(this->m_student.size() <= num){
        this->m_capicity = num;
    }
    else{
        throw std::out_of_range(QString::fromLocal8Bit("课程容量过小").toStdString());
    }
}

Teacher* Course::getTeacher()
{
	return m_teacher;
}

void Course::setTeacher(Teacher* teacher)
{
	this->m_teacher = teacher;
}

std::set<Student*> Course::getStudent()
{
	std::set<Student*> s;
	for (auto& i : m_student)
	{
		s.insert(i.first);
	}
	return s;
}

void Course::addStudent(Student* student)
{
    if ((int)m_student.size() < m_capicity) {
        auto i = m_student.find(student);
        if (i == m_student.end()) {
			m_student.insert(std::make_pair(student, -1));
		}
	}
    else{
        throw std::out_of_range(QString::fromLocal8Bit("超出课程容量").toStdString());
    }
}

bool Course::deleteStudent(Student* student)
{
    auto i = m_student.find(student);
	if (i != m_student.end())
	{
		m_student.erase(i);
        return true;
	}
	return false;
}

void Course::clearStudent()
{
    m_student.clear();
}

bool Course::checkStudent(Student *student)
{
    if(m_student.find(student) != m_student.end()){
        return true;
    }
    return false;
}

bool Course::checkTeacher(Teacher* teacher)
{
    if(m_teacher == teacher) return true;
    return false;
}

Student* Course::findStudent(std::string id)
{
    Student* ans = NULL;
    for(auto i : m_student)
    {
        if(i.first->getID() == id)
        {
            ans = i.first;
        }
    }
    return ans;
}

std::map<Student*, float> Course::getStudentGrade()
{
	return m_student;
}

void Course::setGrade(std::pair<Student*, float> student_grade)
{
    auto i = m_student.find(student_grade.first);
	if (i != m_student.end()) {
        if(student_grade.second >= 0){
            i->second = student_grade.second;
        }
        else{
            throw std::invalid_argument(QString::fromLocal8Bit("Can not set grade with negative number").toStdString());
        }
	}
}

float Course::getMyGrade(Student* student)
{
    auto i = m_student.find(student);
	if (i != m_student.end())
	{
		return i->second;
	}
	return -1;
}

//必修课函数实现

float Obligatory_course::calculateGPA(Student* student)
{
	int student_num = m_student.size();
	float grade_sum = 0;
    for (auto i : m_student)
	{
        if(i.second >= 0){
            grade_sum += i.second;
        }
	}
	float my_grade = this->getMyGrade(student);
    float gpa = 0;
    if(grade_sum != 0 && my_grade != -1){
        gpa = (student_num * 100 / grade_sum) * (my_grade / 100) * this->getCredit();
    }
	return gpa;
}

int Obligatory_course::getCourseType()
{
	return 1;
}

//选修课函数实现

float Elective_course::calculateGPA(Student* student)
{
    float my_grade = 0;
    if(this->getMyGrade(student) >= 0){
        my_grade = this->getMyGrade(student);
    }
	float gpa = (sqrt(my_grade) / 10) * this->getCredit();
	return gpa;
}

int Elective_course::getCourseType()
{
	return 0;
}

//Course_user类函数实现

std::string Course_user::getID()
{
	return m_course->getID();
}

std::string Course_user::getName()
{
	return m_course->getName();
}

int Course_user::getCredit()
{
	return m_course->getCredit();
}

int Course_user::getCourseType()
{
	return m_course->getCourseType();
}

int Course_user::getCapicity()
{
    return m_course->getCapicity();
}

//Course_student类函数实现

float Course_student::getMyGrade(Student* student)
{
	return m_course->getMyGrade(student);
}

float Course_student::calculateGPA(Student* student)
{
	return m_course->calculateGPA(student);
}

std::string Course_student::getTeacherName()
{
    if(m_course->getTeacher())
    {
        return m_course->getTeacher()->getName();
    }
    return "";
}

int Course_student::getElectiveNum()
{
    if(!this->getCourseType()){
        return m_course->getStudent().size();
    }
    return -1;
}

void Course_student::addElectiveStudent(Student* student)
{
	//判断待增加课程是否为选修课
	if (!this->getCourseType()) {
        m_course->addStudent(student);
	}
    else{
        throw AuthorityError();
    }
}

bool Course_student::deleteElectiveStudent(Student* student)
{
	if (!this->getCourseType()) {
		return m_course->deleteStudent(student);
	}
	return false;
}

//Course_teacher类函数实现

std::set<Student*> Course_teacher::getStudent()
{
	return m_course->getStudent();
}

Student* Course_teacher::findStudent(std::string id)
{
    return m_course->findStudent(id);
}

std::map<Student*, float> Course_teacher::getStudentGrade()
{
	return m_course->getStudentGrade();
}

void Course_teacher::setGrade(std::pair<Student*, float> student_grade)
{
    m_course->setGrade(student_grade);
}
/*
//Course_admin类函数实现

Teacher* Course_admin::getTeacher()
{
    return Course_student::m_course->getTeacher();
}

void Course_admin::setTeacher(Teacher* teacher)
{
    Course_student::m_course->setTeacher(teacher);
}

bool Course_admin::addStudent(Student* student)
{
    return Course_student::m_course->addStudent(student);
}

bool Course_admin::deleteStudent(Student* student)
{
    return Course_student::m_course->deleteStudent(student);
}

void Course_admin::setCapicity(int num)
{
    Course_student::m_course->setCapicity(num);
}
*/

//重载运算符
bool operator < (const Course& course1, const Course& course2)
{
    return course1.m_ID < course2.m_ID;
}

bool operator < (const Course_user& course1, const Course_user& course2)
{
    return course1.m_course < course2.m_course;
}

std::istream& operator >> (std::istream& input, Course& course)
{
    input >> course.m_ID >> course.m_name >> course.m_credit >> course.m_capicity;
}

std::ostream& operator << (std::ostream& output, Course& course)
{
    output << course.m_ID << ' ' << course.m_name << ' ' << course.m_credit << ' ' << course.m_capicity;
}
