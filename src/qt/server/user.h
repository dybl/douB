#pragma once

#include "include.h"
#include "course.h"
#include "environment.h"

//User类代表所有用户类型
class User
{
public:
    User(){}
	User(std::string ID, std::string name, std::string insititude) : 
			m_name(name), m_ID(ID), m_insititude(insititude) {}
	~User(){}

    friend std::istream& operator >> (std::istream& input, User& user);
    friend std::ostream& operator << (std::ostream& output, User& user);

    std::string getID();
    std::string getName();
    std::string getInsititude();

    virtual user_type getUserType() {}	//获取用户类型

protected:
	std::string m_name;			//用户姓名
	std::string m_ID;			//用户学号或者教工号
	std::string m_insititude;	//用户所属学院
};

//由User类派生出学生子类，代表学生用户
class Student: public User
{
public:
	using User::User;
	~Student() {
        eraseCourse();
	}

    friend std::istream& operator >> (std::istream& input, Student& student);
    friend std::ostream& operator << (std::ostream& output, Student& student);

	std::string getClass();
	void setClass(std::string class_name);

    void initCourse(std::set<Course_student*> course, std::set<Course_student *> select_course);  //同步学生课程列表
    void eraseCourse();

	std::map<Course_student*, float> getGrade();	//学生获取自己的课程及其对应成绩
	std::set<Course_student*> getCourse();			//学生获取自己的课程（可对其课程进行设置）

    Course_student* findCourse(std::string id);     //学生查找自己课程
    Course_student* findSelCourse(std::string id);  //学生查找可选课程

    std::set<Course_student*> getSelectCourse();    //学生获取可选课程

    void addCourse(Course_student* course);			//学生选课
	bool deleteCourse(Course_student* course);		//学生删除已选课程

    user_type getUserType() final override;				//获取用户类型

private:
	std::string m_class;							//学生所属班级
	std::set<Course_student*> m_course;				//学生对应课程
    std::set<Course_student*> m_select_course;      //学生对应可选课程
};

//由User类派生出教师子类，代表教师用户
class Teacher : public User
{
public:
	using User::User;
    ~Teacher(){
        eraseCourse();
    }

    void initCourse(std::set<Course_teacher*> course);
    void eraseCourse();

    Course_teacher* findCourse(std::string id);

	std::set<Course_teacher*> getCourse();	//教师获取自己课程列表

    user_type getUserType() final override;		//获取用户类型

private:
	std::set<Course_teacher*> m_course;		//教师任课课程
};

//超级管理员用户
class Admin : public User
{
public:
	using User::User;
    ~Admin(){}

	void activateEnvir(Envir* envir);		//激活当前工作环境

    user_type getUserType() final override;		//获取用户类型

    Envir* getEnvir();                      //获取当前系统环境

/*    void addObligatoryCourse(std::string ID, std::string name, int credit);
    void addElectiveCourse(std::string ID, std::string name, int credit);

	void addUserStudent(std::string ID, std::string name, std::string insititude);
	void addUserTeacher(std::string ID, std::string name, std::string insititude);
	void addUserAdmin(std::string ID, std::string name, std::string insititude);

    std::map<Student*, std::string> getUserStudent();
    std::map<Teacher*, std::string> getUserTeacher();
    std::map<Admin*, std::string> getUserAdmin();
*/
private:
	Envir* m_envir;							//当前系统环境
};
