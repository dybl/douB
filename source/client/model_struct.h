#ifndef MODEL_STRUCT_H
#define MODEL_STRUCT_H

#include "include.h"

//课程结构体
struct course_model{
    std::string id = "";
    std::string name = "";
    int credit = 0;
    int capacity = 0;
    int cur_num = 0;
    float grade = 0;
    float gpa = 0;
    int course_type = 0;
    std::string teacher_id = "";

    bool operator < (const struct course_model &a) const
    {
        return id < a.id;
    }
};

//用户结构体
struct user_model
{
    std::string id = "";
    std::string name = "";
    std::string class_name = "";
    std::string institude = "";
    float grade = 0;
    float gpa = 0;
    int user_type = 0;

    bool operator < (const struct user_model &a) const
    {
        return id < a.id;
    }

};

typedef struct user_model User_model;
typedef struct course_model Course_model;

#endif // MODEL_STRUCT_H
