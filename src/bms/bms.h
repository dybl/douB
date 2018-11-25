#ifndef _BMS_H  
#define _BMS_H  
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#define LEN sizeof(struct readerinf)
#define LON sizeof(struct bookinf)
FILE *pf,*pb;
struct borrow /*定义被借图书简单信息*/
{
    long int book;
    int outyear; /*为查看用户信息时，可以查看书本超期时间所定*/
    int outmonth;
    int outday;
    long int tim; /*为简化超期罚款函数所定*/
};
struct bookinf /*定义图书结构体*/
{
    char name[31];
    char author[21];
    char pubcompany[100]; /*出版社*/
    char pubdate[20]; /*出版时间*/
    int price; /*价格*/
    long int ISBN; /*图书编号*/
    char category[30]; /*分类*/
    int condition; /*是否在架 1:在架 0:已借 2:再借*/
    int borrowednum; /*借阅次数*/
    struct bookinf *next;
};
struct readerinf /*定义学生结构体*/
{
    char name[30];
    char sex[4];
    char birthday[20]; /*出生年月*/
    char college[20]; /*学院*/
    char secretnum[10]; /*secretnum=(密码-20)*2 */
    long int ID; /*学号*/
    char type[20]; /*读者类型*/
    int balance; /*账户余额*/
    int bornum; /*当前借阅数*/
    int outdatenum; /*超期图书数*/
    struct borrow b[30]; /*一个结构体变量，记录图书和超期时间*/
    struct readerinf *next; /*指向下一位同学的指针*/
};
struct readerinf *head1,*p1,*p2;
struct bookinf *head2,*b1,*b2;
int loadone(); /*登陆*/
void managementone(); /*进入管理员的各种操作*/
struct readerinf *creat(); /*初始化链表函数*/
struct readerinf *addperson(struct readerinf *head); /*添加用户函数*/
struct readerinf *delperson(struct readerinf *head); /*删除用户函数*/
void showperson(struct readerinf *head); /*查看用户信息*/
void delsecret(struct readerinf *head); /*清空用户密码*/
void storagereader(struct readerinf *p); /*将链表信息存至文件*/
int loadtwo(); /*登陆*/
void managementtwo(); /*进入管理员的各种操作*/
struct bookinf *addbook(struct bookinf *head); /*添加图书*/
struct bookinf *delbook(struct bookinf *head); /*删除图书*/
void rewritebook(struct bookinf *b); /*修改图书信息*/
void recharge(struct readerinf *p); /*用户充值*/
struct readerinf *loadthree(); /*登陆*/
void operation();
struct bookinf *begin(); /*初始化链表函数*/
void borrowbook(struct bookinf *b1,struct readerinf *p); /*借书*/
void renewbook(struct readerinf *p); /*续借*/
void returnbook(struct readerinf *p); /*还书*/
void checkbook(struct bookinf *b); /*查找图书*/
void rewritereader(struct readerinf *p3); /*修改读者信息*/
void storagebook(struct bookinf *b); /*将链表信息存至文件*/
void statistic(); /*统计功能*/
void fine(); /*超期罚款函数*/
int fh1=4;/*返回上层功能所需，方便修改*/
int zh=1000;/*系统管理员的账户、mima=(密码-20)*2*/
char a[5]={'<','@','D','H'},c;/*实际密码为2468*/
struct librarian/*图书管理员的账户、加密后密码=(密码-20)*2*/
{
    int z;
    char m[20];
}liber[5]={{1001,"<<<<"},{1002,"@@@@"},{1003,"DDDD"},{1004,"HHHH"},{1005,"<@DH"}};
#endif 