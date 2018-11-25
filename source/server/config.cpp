/**
 * Name: config.cpp
 * User: L.Laddie
 * Function: 配置文件
 */

#include <QDebug>
#include <QString>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include "config.h"
#include "include.h"

Config_file::Config_file()
{

}

Config_file::~Config_file()
{

}

void Config_file::setEnvir(Envir *envir)
{
    this->m_envir = envir;
}

void Config_file::readConfig()
{
    //打开配置文件
    std::ifstream file;
    file.open("config.ini", std::ios_base::in);
    if(!file)
        throw std::runtime_error("No Config File!!!");

    //定义正则表达式匹配配置文件
    std::regex pattern("\\[(.*)\\]");
    std::string str;
    std::match_results<std::string::const_iterator> result;

    //一行一行读取
    config_state state = config_state::nop;
    while(!file.eof()){
        std::getline(file, str);
        if(str[0] == '#' || str == "")       //一行为注释或者为空
            continue;

        //确定下一个状态
        if(std::regex_match(str, result, pattern)){
            if(result[1] == "student")
                state = config_state::student;
            else if(result[1] == "teacher")
                state = config_state::teacher;
            else if(result[1] == "admin")
                state = config_state::admin;
            else if(result[1] == "obligatory")
                state = config_state::obligatory;
            else if(result[1] == "elective")
                state = config_state::elective;

            continue;
        }

        std::stringstream file_line(str);
        switch (state) {
        case config_state::student:
        {
            Student* new_student = new Student();
            std::string pass;
            file_line >> *new_student >> pass;
            this->m_envir->addUserStudent(new_student, pass);
            break;
        }

        case config_state::teacher:
        {
            Teacher* new_teacher = new Teacher();
            std::string pass;
            file_line >> *new_teacher >> pass;
            this->m_envir->addUserTeacher(new_teacher, pass);
            break;
        }

        case config_state::admin:
        {
            Admin* new_admin = new Admin();
            std::string pass;
            file_line >> *new_admin >> pass;
            this->m_envir->addUserAdmin(new_admin, pass);
            break;
        }

        case config_state::obligatory:
        {
            Obligatory_course* new_course = new Obligatory_course();
            std::string id = "";
            file_line >> *new_course >> id;

            if(id != "-1"){
                User* teacher = this->m_envir->findUser(id);
                if(teacher->getUserType() == user_type::teacher){
                    new_course->setTeacher((Teacher*)teacher);
                }
            }

            std::regex pattern2("<([\\d.]*)\\s*,\\s*([\\d.-]*)>");
            std::sregex_iterator pos(str.begin(), str.end(), pattern2);
            std::sregex_iterator end;
            while(pos != end){
                User* student = this->m_envir->findUser((*pos)[1]);
                new_course->addStudent((Student*)student);

                if(std::atof((*pos)[2].str().c_str()) != -1)        //成绩不为-1时，给学生设置一个成绩
                    new_course->setGrade(std::make_pair((Student*)student, std::atof((*pos)[2].str().c_str())));
//                qDebug() << QString::fromStdString((*pos)[1]) << ' ' << QString::fromStdString((*pos)[2]) << endl;
                pos++;
            }

            this->m_envir->addObligatoryCourse(new_course);
            break;
        }

        case config_state::elective:
        {
            Elective_course* new_course = new Elective_course();
            std::string id = "";
            file_line >> *new_course >> id;

            if(id != "-1"){
                User* teacher = this->m_envir->findUser(id);
                if(teacher->getUserType() == user_type::teacher){
                    new_course->setTeacher((Teacher*)teacher);
                }
            }

            std::regex pattern2("<([\\d.]*)\\s*,\\s*([\\d.-]*)>");
            std::sregex_iterator pos(str.begin(), str.end(), pattern2);
            std::sregex_iterator end;
            while(pos != end){
                User* student = this->m_envir->findUser((*pos)[1]);
                new_course->addStudent((Student*)student);
                if(std::atof((*pos)[2].str().c_str()) != -1)        //成绩不为-1时，给学生设置一个成绩
                    new_course->setGrade(std::make_pair((Student*)student, std::atof((*pos)[2].str().c_str())));
//                qDebug() << QString::fromStdString((*pos)[1]) << ' ' << QString::fromStdString((*pos)[2]) << endl;
                pos++;
            }

            this->m_envir->addElectiveCourse(new_course);
            break;
        }

        default:
            break;
        }
    }
    file.close();
}

void Config_file::writeConfig()
{
    std::ofstream file;
    file.open("config.ini", std::ios_base::out);
    file << "#This is a config file\n" << "[user]\n";

    file << "\n[student]\n" << "#学号-姓名-学院-班级-md5密码\n";
    for(auto i : this->m_envir->getUserStudent())
    {
        file << *(i.first) << " " << i.second << "\n";
    }

    file << "\n[teacher]\n" << "#工号-姓名-学院-md5密码\n";
    for(auto i : this->m_envir->getUserTeacher())
    {
        file << *(i.first) << " " << i.second << "\n";
    }

    file << "\n[admin]\n" << "#用户名-姓名-学院-md5密码\n";
    for(auto i : this->m_envir->getUserAdmin())
    {
        file << *(i.first) << " " << i.second << "\n";
    }

    file << "\n[course]\n";

    file << "\n[obligatory]\n" << "#课程编号-课程名称-学分-课程容量-教师工号-学生及成绩\n";
    for(auto i : this->m_envir->getObligatoryCourse())
    {
        file << *i;
        if(i->getTeacher()){
            file << " " << i->getTeacher()->getID();
        }
        else
            file << " -1";
        for(auto j : i->getStudentGrade())
        {
            file << " <" << j.first->getID() << ", " << j.second << ">";
        }
        file << "\n";
    }

    file << "\n[elective]\n" << "#课程编号-课程名称-学分-课程容量-教师工号-学生及成绩\n";
    for(auto i : this->m_envir->getElectiveCourse())
    {
        file << *i;
        if(i->getTeacher()){
            file << " " << i->getTeacher()->getID();
        }
        else
            file << " -1";
        for(auto j : i->getStudentGrade())
        {
            file << " <" << j.first->getID() << ", " << j.second << ">";
        }
        file << "\n";
    }
    file.close();
}
