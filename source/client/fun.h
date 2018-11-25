/**
 * Name: fun.h
 * User: L.Laddie
 * Function: 常用自定义函数
 */

#ifndef FUN_H
#define FUN_H

#include <QDebug>
#include "include.h"

//泛型排序算法
namespace Sort {
    template<typename T>

    //mode可以选择按某一项进行排序，reverse可以选择是否反向排序
    void sortVectorCourse(std::vector<T>& course, std::string mode, bool reverse = false)
    {
        bool flag = true;
        for(int i = 0; i < course.size(); i++)
        {
            flag = true;
            for(int j = i; j < course.size(); j++)
            {
                if(mode == "id"){
                    if(!reverse && course[i].id > course[j].id)
                    {
                        std::swap(course[i], course[j]);
                        flag = false;
                    }
                    if(reverse && course[i].id < course[j].id)
                    {
                        std::swap(course[i], course[j]);
                        flag = false;
                    }
                }
                else if(mode == "grade"){
                    if(!reverse && course[i].grade > course[j].grade)
                    {
                        std::swap(course[i], course[j]);
                        flag = false;
                    }
                    if(reverse && course[i].grade < course[j].grade)
                    {
                        std::swap(course[i], course[j]);
                        flag = false;
                    }
                }
                else if(mode == "gpa"){
                    if(!reverse && course[i].gpa > course[j].gpa)
                    {
                        std::swap(course[i], course[j]);
                        flag = false;
                    }
                    if(reverse && course[i].gpa < course[j].gpa)
                    {
                        std::swap(course[i], course[j]);
                        flag = false;
                    }
                }
            }
            if(flag){
//                return;
            }
        }
    }
}
#endif // FUN_H
