#include "bms.h"
void main()

{
    int op;
    fine();
    printf("==============================================================|\n");
    printf("|                           图书管理系统                       |\n");
    printf("+-------------------------------------------------------------+\n");
    while(1)
    {
        printf("| <1>                  系统管理员请按1                          \n");
        printf("| <2>                  图书管理员按2                            \n");
        printf("| <3>                  读者游客请按3                            \n");
        printf("| <4>                  查看最受欢迎的书请按4                     \n");
        printf("| <5>                  退出请按0                                \n");
        printf("| <6>                  请输入0--4,其他指令不可用!                \n");
        printf("+-------------------------------------------------------------+\n");
        printf(">>>>>>>>");
        scanf("%d",&op);
        switch(op)
        {
            case 1: if(loadone()==1)managementone();break;
            case 2:if(loadtwo()==1)managementtwo();break;
            case 3:if((p1=loadthree())!=NULL)operation();break;
            case 0:exit(0);break;
            case 4:statistic();break;
            default : printf("没有对应的系统指令，请查证重输\n");
        }
    }
}

int loadone()
{
    int i,n=0,z1;
    char c;
    printf("返回上层请按4\n");
    printf("请输入用户名\n");
    scanf("%d",&z1);
    if(fh1==z1)
    return(0);
    while(zh!=z1)
    {
        printf("该用户不存在\n");
        scanf("%d",&z1);
    };
    printf("请输入密码\n");
    while(n!=i)
    {
        n=0;
        for(i=0;a[i]!='\0';i++)
        {
            c=getch();if(a[i]==(c-20)*2)
            n++;
        }
        if(n!=i)
        printf("您输入的密码有误\n");
    }
    return(1);
}

void managementone()
{
    int choice=0;
    head1=creat();
    while(choice!=fh1)
    {
        printf("============================================================= |\n");
        printf("|                           图书管理系统                       |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("| <1>                    添加用户请按0                          \n");
        printf("| <2>                    删除用户请按1                          \n");
        printf("| <3>                    查看用户信息请按2                      \n");
        printf("| <4>                    清空用户密码请按3                      \n");
        printf("| <5>                    返回上层请按4                          \n");
        printf("| <6>                    请输入0--4,其他指令不可用!              \n");
        printf("+-------------------------------------------------------------+\n");
        printf(">>>>>>>>");
        scanf("%d",&choice);
        switch (choice)
        {
            case 0:head1=addperson(head1);break; /*添加用户*/
            case 1:head1=delperson(head1);break; /*删除用户*/
            case 2:showperson(head1);break; /*查看用户信息*/
            case 3:delsecret(head1);break; /*清空用户密码*/
            case 4:choice=4;break; /*返回*/
            default: printf("没有对应的系统指令，请查证重输\n");break;
        }
    }
    storagereader(head1);
}

struct readerinf *creat(void) /*初始化读者信息链表函数*/
{
    int i;
    struct readerinf *head;
    pf=fopen("reader.txt","r+");
    if(pf==NULL)
    {
        printf("不能打开文件\n");
        exit(0);
    }
    if(pf==-1) /*若文件为空文件*/
    head=NULL;
    else
    {
        p2=(struct readerinf*)malloc(LEN);
        fscanf(pf,"%s %s %s %s %s %d %s %d %d %d",p2->name,p2->sex,p2->birthday,p2->college,p2->secretnum,&p2->ID,p2->type,&p2->balance,&p2->bornum,&p2->outdatenum);
        for(i=0;i<(p2->bornum);i++)
        {
            fscanf(pf,"%d%d%d%d%d",&p2->b[i].book,&p2->b[i].outyear,
            &p2->b[i].outmonth,&p2->b[i].outday,&p2->b[i].tim);
        }
        head=p2;
        while(!feof(pf))
        {
            p1=(struct readerinf*)malloc(LEN); /*申请一块空间给P1*/
            fscanf(pf,"%s %s %s %s %s %d %s %d %d %d",p1->name,p1->sex,p1->birthday,p1->college,p1->secretnum,&p1->ID,p1->type,&p1->balance,&p1->bornum,&p1->outdatenum);/*读取信息*/
            for(i=0;i<(p1->bornum);i++)
            {
                fscanf(pf,"%d%d%d%d%d",&p1->b[i].book,&p1->b[i].outyear,&p1->b[i].outmonth,&p1->b[i].outday,&p1->b[i].tim);
            }
            p2->next=p1;
            p2=p1;
        }
        p2->next=NULL;
        fclose(pf);
    }
    return(head);
}

struct readerinf *addperson(struct readerinf *head)
{
    int j;
    struct readerinf *p,*p3;
    printf("请输入要添加用户的信息\n");
    printf("姓名 性别 出生年月 学院 密码 学号/工号 读者类型 账户余额 借书数 超期图书数:\n");
    if(head==NULL)
    {
        head=(struct readerinf*)malloc(LEN);
        scanf("%s %s %s %s %s %d %s %d %d %d",
        head->name,head->sex,head->birthday,head->college,head->secretnum,&head->ID,head->type,&head->balance,&head->bornum,&head->outdatenum);
        head->next=NULL;
        for(j=0;head->secretnum[j]!='\0';j++)
        head->secretnum[j]=(head->secretnum[j]-20)*2;
        printf("添加成功！\n");
    }
    else
    {
        p3=head; /*每次添加一本图书，不用多输入数据以判断添加是否结束*/
        while(p3->next!=NULL)
        p3=p3->next; /*找到链表末尾节点*/
        p=(struct readerinf*) malloc(LEN);
        p->next=NULL;
        scanf("%s %s %s %s %s %d %s %d %d %d",p->name,p->sex,p->birthday,p->college,p->secretnum,&p->ID,p->type,&p->balance,&p->bornum,&p->outdatenum);
        for(j=0;p->secretnum[j]!='\0';j++)
        p->secretnum[j]=(p->secretnum[j]-20)*2;
        p3->next=p; /*将p连接到链表末尾节点之后*/
        printf("添加成功！\n");
    }
    return(head); /*因为有空链表的情况，头指针可能改变，所以需要返回值*/
}

struct readerinf *delperson(struct readerinf *head)
{
    int n;
    struct readerinf *p,*p3;
    printf("请输入要删除用户的ID\n");
    scanf("%d",&n);
    if(head->ID==n)
    head=head->next;
    else
    {
        p3=head;
        while(p3->ID!=n&&p3->next!=NULL)
        {
            p=p3;
            p3=p3->next;
        }
        if(p3->ID==n)
        {
            p->next=p3->next;
            printf("删除成功！\n");
        }
        else
        printf("无此用户\n");
    }
    return(head); /*因为存在头指针改变的情况，所以需要返回值*/
}

void showperson(struct readerinf *head)
{
    int n,m,i,j;
    char a[10];
    struct readerinf *p;
    struct bookinf *b,*b1;
    b=begin();
    p=head;
    printf("请输入要查看用户的ID\n");
    scanf("%d",&n);
    while(p->ID!=n&&p->next!=NULL)
    p=p->next;
    if(p->ID==n)
    {
        strcpy(a,p->secretnum);
        for(j=0;a[j]!='\0';j++)
        a[j]=(a[j]/2+20);
        m=p->bornum;
        printf("姓名 性别 出生年月 学院 密码 学号/工号 读者类型 账户余额 借书数 超期图书数:\n");
        printf("%s %s %s %s %s %d %s %d %d %d\n",p->name,p->sex,p->birthday,p->college,a,p->ID,p->type,p->balance,p->bornum,p->outdatenum);
        printf("所借图书信息:\n");
        printf("书名 作者 出版社 出版时间 价格 图书编号 分类 是否在架 借阅次数 超期时间\n");
        for(i=0;i<m;i++)
        {
            b1=b;
            while(b1->ISBN!=p->b[i].book&&b1->next!=NULL)
            b1=b1->next;
            printf("%s %s %s %s %d %d %s %d %d %d年%d月%d日\n",
            b1->name,b1->author,b1->pubcompany,
            b1->pubdate,b1->price,b1->ISBN,
            b1->category,b1->condition,b1->borrowednum,
            p->b[i].outyear,p->b[i].outmonth,p->b[i].outday);
        }
    }
    else
    printf("无此用户\n");
}

void delsecret(struct readerinf *head)
{
    int n;
    struct readerinf *p;
    p=head;
    printf("请输入清空密码用户的ID\n");
    scanf("%d",&n);
    while(p->ID!=n&&p->next!=NULL)
    p=p->next;
    if(p->ID==n)
    strcpy(p->secretnum, "8888");/*实际密码为0000*/
    else
    printf("无此用户\n");
}

void storagereader(struct readerinf *p)
{
    int n=1,i=0;
    pf=fopen("reader.txt","w+");
    while(p!=NULL)
    {
        if(n!=1)
        fprintf(pf,"\n");
        fprintf(pf,"%s %s %s %s %s %d %s %d %d %d",p->name,p->sex,p->birthday,p->college,p->secretnum,p->ID,p->type,p->balance,p->bornum,p->outdatenum);
        for(i=0;i<(p->bornum);i++)/*依据所借图书数目，将被借图书简单信息存至文件*/
        {
            fprintf(pf," %d %d %d %d %d",p->b[i].book,p->b[i].outyear,p->b[i].outmonth,p->b[i].outday,p->b[i].tim);/*此处输出格式前必须加个空格*/
        }
        n++;
        p1=p;
        p=p->next;
        free(p1);
    }
    fclose(pf);
}

int loadtwo()
{
    int i=0,j=1,n=0,z1;
    char c;
    printf("返回上层请按4\n");
    printf("请输入用户名\n");
    scanf("%d",&z1);
    if(fh1==z1)
    return(0);
    while(liber[i].z!=z1&&i<5)
    i++;
    if(liber[i].z==z1)
    {
        printf("请输入密码\n");
        while(n!=j)
        {
            n=0;
            for(j=0;liber[i].m[j]!='\0';j++)
            {
                c=getch();
                if(liber[i].m[j]==(c-20)*2)
                n++;
            }
            if(n!=j)
            printf("您输入的密码有误\n");
        }
        return(1);
    }
    else
    {
        printf("用户不存在\n");
        return(0);
    }
}

void managementtwo()
{
    int choice=0;
    head2=begin();
    while(choice!=fh1)
    {
        printf("============================================================= |\n");
        printf("|                           图书管理系统                       |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("| <1>            添加图书请按0                                  \n");
        printf("| <2>            删除图书请按1                                  \n");
        printf("| <3>            修改图书信息请按2                              \n");
        printf("| <4>            用户充值请按3                                  \n");
        printf("| <5>            返回上层请按4                                  \n");
        printf("| <6>            请输入0--4,其他指令不可用!                      \n");
        printf("+-------------------------------------------------------------+\n");
        printf(">>>>>>>>");
        scanf("%d",&choice);
        switch (choice)
        {
            case 0:head2=addbook(head2);break;
            case 1:head2=delbook(head2);break;
            case 2:rewritebook(head2);break;
            case 3:head1=creat();recharge(head1);storagereader(head1);break;
            case 4:choice=4;break;
            default : printf("没有对应的系统指令，请查证重输\n");break;
        }
    }
    storagebook(head2);
}

struct bookinf *addbook(struct bookinf *head)
{
    struct bookinf *b,*b3;
    printf("请输入要添加图书的信息\n");
    printf("书名 作者 出版社 出版时间 价格 图书编号 分类 是否在架 借阅次数:\n");
    if(head==NULL)
    {
        head=(struct bookinf*)malloc(LON);
        scanf("%s %s %s %s %d %d %s %d %d",head->name,head->author,head->pubcompany,head->pubdate,&head->price,&head->ISBN,head->category,&head->condition,&head->borrowednum);
        head->next=NULL;
        printf("添加成功！\n");
    }
    else
    {
        b3=head; /*如此处理可以省去free语句，也不用多输入数据以判断添加是否结束*/
        b=(struct bookinf*) malloc(LON);
        b->next=NULL;
        scanf("%s %s %s %s %d %d %s %d %d",
        b->name,b->author,b->pubcompany,b->pubdate,&b->price,
        &b->ISBN,b->category,&b->condition,&b->borrowednum);
        while(b3->next!=NULL)
        b3=b3->next;
        b3->next=b;
        printf("添加成功！\n");
    }
    return(head);/*因为有空链表的情况，头指针可能改变，所以需要返回值*/
}

struct bookinf *delbook(struct bookinf *head)
{
    int n;
    struct bookinf *b,*b3;
    printf("请输入要删除图书的ISBN\n");
    scanf("%d",&n);
    if(head->ISBN==n)
    head=head->next;
    else
    {
        b3=head;
        while(b3->ISBN!=n&&b3->next!=NULL)
        {
            b=b3;
            b3=b3->next;
        }
        if(b3->ISBN==n)
        {
            b->next=b3->next;
            printf("删除成功！\n");
        }
        else
        printf("无此图书\n");
    }
    return(head);/*因为存在头指针改变的情况，所以需要返回值*/
}

void rewritebook(struct bookinf *b)
{
    int n;
    char a[31],au[21],c[30],d[20];
    printf("请输入要修改图书的ISBN\n");
    scanf("%d",&n);
    while(b->ISBN!=n&&b->next!=NULL)
    b=b->next;
    if(b->ISBN==n)
    {
        printf("请输入要修改图书的全部信息\n");
        printf("书名 作者 出版社 出版时间 价格 图书编号 分类 是否在架 借阅次数:\n");
        scanf("%s %s %s %s %d %d %s %d %d",a,b,c,d,&b->price,&b->ISBN,b->category,&b->condition,&b->borrowednum);
        strcpy(b->name,a);
        strcpy(b->author,au);
        strcpy(b->pubcompany,c);
        strcpy(b->pubdate,d);
    }
    else
    printf("无此图书\n");
}

void recharge(struct readerinf *p)
{
    int n,m;
    printf("请输入要充值用户的ID\n");
    scanf("%d",&n);
    while(p->ID!=n&&p->next!=NULL)
    p=p->next;
    if(p->ID==n)
    {
        printf("请输入要充值数额\n");
        scanf("%d",&m);
        p->balance=p->balance+m;
        printf("充值成功！\n");
    }
    else
    printf("无此用户\n");
}

struct readerinf * loadthree()
{
    int i=0,j=1,n=0;
    char c;
    struct readerinf *p;
    head1=creat();
    p=head1;
    printf("返回上层请按4\n");
    printf("请输入用户ID\n");
    scanf("%d",&n);
    if(fh1==n)
    return(NULL);
    while(p->ID!=n&&p->next!=NULL)
    p=p->next;
    if(p->ID==n)
    {
        printf("请输入密码\n");
        while(n!=j)
        {
            n=0;
            for(j=0;p->secretnum[j]!='\0';)
            {
                c=getch();
                if(p->secretnum[j]==(c-20)*2)
                n++;
                j++;
            }
            if(n!=j)
            printf("您输入的密码有误\n");
        }
        return(p);
    }
    else
    {
        printf("用户不存在\n");
        return(NULL);
    }
}

void operation()
{
    int choice=0; /*p1为读者登录后对应的指针*/
    while(choice!=fh1)
    {
        printf("============================================================= |\n");
        printf("|                           图书管理系统                       |\n");
        printf("+-------------------------------------------------------------+\n");
        printf("| <1>                 借书请按1                                 \n");
        printf("| <2>                 续借请按2                                 \n");
        printf("| <3>                 还书请按3                                 \n");
        printf("| <4>                 返回请按4                                 \n");
        printf("| <5>                 查寻图书请按5                             \n");
        printf("| <6>                 修改读者信息请按6                          \n");
        printf("+-------------------------------------------------------------+\n");
        printf(">>>>>>>>");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:head2=begin();borrowbook(head2,p1);storagebook(head2);break;
            case 2:renewbook(p1);break;
            case 3:returnbook(p1);break;
            case 4:choice=4;break;
            case 5:head2=begin();checkbook(head2);storagebook(head2);break;
            case 6:rewritereader(p1);break;
            default : printf("没有对应的系统指令，请查证重输\n");break;
        }
    }
    storagereader(head1);/*如果参数为p1则会出错,head1在loadthree()中已经被赋值*/
}

struct bookinf *begin(void)
{
    struct bookinf *head;
    pb=fopen("book.txt","r+");
    if(pb==NULL)
    {
        printf("不能打开文件\n");
        exit(0);
    }
    if(pb==-1)
    head=NULL;
    else
    {
        b2=(struct bookinf*)malloc(LON);
        fscanf(pb,"%s %s %s %s %d %d %s %d %d",b2->name,b2->author,b2->pubcompany,b2->pubdate,&b2->price,&b2->ISBN,b2->category,&b2->condition,&b2->borrowednum);
        head=b2;
        while(!feof(pb))
        {
            b1=(struct bookinf*)malloc(LON);
            fscanf(pb,"%s %s %s %s %d %d %s %d %d",b1->name,b1->author,b1->pubcompany,b1->pubdate,&b1->price,&b1->ISBN,b1->category,&b1->condition,&b1->borrowednum);
            b2->next=b1;
            b2=b1;
        }
        b2->next=NULL;
        fclose(pb);
    }
    return(head);
}

void borrowbook(struct bookinf *b1,struct readerinf *p) /*借书*/
{
    struct bookinf *b;
    int n,m;
    struct tm *t;
    time_t tt;
    time(&tt);
    t=localtime(&tt);
    tt=mktime(t);
    b=b1;
    if(strcmp(p->type,"学生")==0)
    {
        if(p->bornum<10)
        {
            printf("请输入要借图书的ISBN\n");
            scanf("%d",&n);
            while(b->ISBN!=n&&b->next!=NULL)
            b=b->next;
            if(b->ISBN==n)
            {
                if(b->condition=1)
                {
                    b->condition=0;
                    b->borrowednum++;
                    m=p->bornum;
                    p->bornum++;
                    p->b[m].book=n;
                    p->b[m].tim=tt+2592000;
                    p->b[m].outday=t->tm_mday;
                    if(t->tm_mon+1==12)
                    {
                        p->b[m].outyear=(t->tm_year+1901);
                        p->b[m].outmonth=1;
                    }
                    else
                    {
                        p->b[m].outyear=(t->tm_year+1900);
                        p->b[m].outmonth=t->tm_mon+2;
                    }
                    printf("借阅成功！\n");
                }
                else
                printf("该图书已经被借\n");
            }
            else
            printf("无此图书\n");
        }
        else
        printf("您的借书书已达上限，不能再借\n");
    }
    else
    {
        if(p->bornum<30)
        {
            printf("请输入要借图书的ISBN\n");
            scanf("%d",&n);
            while(b->ISBN!=n&&b->next!=NULL)
            b=b->next;
            if(b->ISBN==n)
            {
                if(b->condition=1)
                {
                    b->condition=0;
                    b->borrowednum++;
                    m=p->bornum;
                    p->bornum++;
                    p->b[m].book=n;
                    p->b[m].outday=t->tm_mday;
                    p->b[m].tim=tt+2592000*5;
                    if(t->tm_mon+1>7)
                    {
                        p->b[m].outyear=t->tm_year+1901;
                        p->b[m].outmonth=(t->tm_mon-6);/*经过数学推导得到的公式*/
                    }
                    else
                    {
                        p->b[m].outyear=t->tm_year+1900;
                        p->b[m].outmonth=t->tm_mon+6;
                    }
                    printf("借阅成功！\n");
                }
                else
                printf("该图书已经被借\n");
            }
            else
            printf("无此图书\n");
        }
        else
        printf("您的借书书已达上限，不能再借\n");
    }
}

void renewbook(struct readerinf *p)
{
    int n,d;
    time_t tt;
    struct tm *t;
    struct bookinf *b;
    b=begin();
    time(&tt);
    t=localtime(&tt);
    tt=mktime(t);
    if(strcmp(p->type,"学生")==0)
    {
        printf("请输入要续借借图书的ISBN\n");
        scanf("%d",&n);
        for(d=0;p->b[d].book!=n&&d<p->bornum;d++);
        while(b->ISBN!=n&&b->next!=NULL)
        b=b->next;
        if(p->b[d].book==n)
        {
            if(b->condition==0)
            {
                b->condition=2;
                p->outdatenum--;
                if(p->b[d].outmonth==12)
                {
                    p->b[d].outyear++;
                    p->b[d].outmonth=1;
                }
                else
                p->b[d].outmonth++;
                p->b[d].tim=tt+2592000;
                printf("续借成功！\n");
            }
            else
            printf("已经续借过一次不能再借\n");
        }
        else
        printf("未借此图书\n");
    }
    else
    {
        printf("请输入要续借借图书的ISBN\n");
        scanf("%d",&n);
        for(d=0;p->b[d].book!=n&&d<p->bornum;d++);
        while(b->ISBN!=n&&b->next!=NULL)
        b=b->next;
        if(p->b[d].book==n)
        {
            if(b->condition==0)
            {
                b->condition=2;
                if(p->b[d].outmonth>7)
                {
                    p->b[d].outyear++;
                    p->b[d].outmonth-=7;/*经过数学推导得到的公式*/
                }
                else
                p->b[d].outmonth+=5;
                p->b[d].tim=tt+2592000*5;
                printf("续借成功！\n");
            }
            else
            printf("已经续借过一次不能再借\n");
        }
        else
        printf("未借此图书\n");
    }
}

void returnbook(struct readerinf *p)
{
    int n,d,m;
    struct tm *t;
    struct bookinf *b;
    time_t tt;
    b1=b=begin();
    time(&tt);
    t=localtime(&tt);
    printf("请输入要还图书的ISBN\n");/*因为有些书的数目不为一，防止出错*/
    scanf("%d",&n);
    for(d=0;p->b[d].book!=n&&d<p->bornum;d++);
    while(b->ISBN!=n&&b->next!=NULL)
    b=b->next;
    if(p->b[d].book==n)
    {
        b->condition=1; /*若满足上述条件，该书肯定存在*/
        p->bornum=p->bornum-1;
        if((t->tm_year+1900+(t->tm_mon+1)/12.0)==(p->b[d].outyear+(p->b[d].outmonth)/12.0)) /*调整超期图书数*/
        {
            if(p->b[d].outday<t->tm_mday)
            p->outdatenum--;
        }
        if((t->tm_year+1900+(t->tm_mon+1)/12.0)>(p->b[d].outyear+(p->b[d].outmonth)/12.0))
        p->outdatenum--;
        m=p->bornum;
        for(;d<m;d++) /*调整被借图书数组*/
        {
            p->b[d].book=p->b[d+1].book;
            p->b[d].outday=p->b[d+1].outday;
            p->b[d].outmonth=p->b[d+1].outmonth;
            p->b[d].outyear=p->b[d+1].outyear;
            p->b[d].tim=p->b[d+1].tim;
        }
        p->b[m].book=0;
        p->b[m].outday=0;
        p->b[m].outmonth=0;
        p->b[m].outyear=0;
        p->b[m].tim=0;
        printf("还书成功！\n");
    }
    else
    printf("未借此图书\n");
    storagebook(b1);
}

void checkbook(struct bookinf *b)
{
    char a[31],n=0;
    printf("请输入要查找图书的书名:");
    scanf("%s",a);
    while(b!=NULL)/*因为有某本书的数目大于1的情况*/
    {
        if(strcmp(b->name,a)==0)
        {
            printf("书名 作者 出版社 出版时间 价格 图书编号 图书分类 是否在架 借阅次数\n");
            printf("%s %s %s %s %d %d %s %d %d\n",b->name,b->author,b->pubcompany,b->pubdate,b->price,b->ISBN,b->category,b->condition,b->borrowednum);
            n=1;
        }
        b=b->next;
    }
    if(n==0)
    printf("无此图书\n");
}

void rewritereader(struct readerinf *p3)
{
    struct readerinf *p;
    char a[30],b[4],c[20],d[20],e[10];
    long int n;
    p=p3;
    printf("请输入所要修改的信息\n");
    printf("姓名 性别 出生年月 学院 密码 学号:\n");/*按实际情况读者只能修改一部分信息*/
    scanf("%s %s %s %s %s %s %d",a,b,c,d,e,&n);
    strcpy(p->name,a);
    strcpy(p->sex,b);
    strcpy(p->birthday,c);
    strcpy(p->college,d);
    strcpy(p->secretnum,e);
    p->ID=n;
}

void storagebook(struct bookinf *b)
{
    int n=1;
    pb=fopen("book.txt","w+");
    while(b!=NULL)
    {
        if(n!=1)
        fprintf(pb,"\n");
        fprintf(pb,"%s %s %s %s %d %d %s %d %d",b->name,b->author,b->pubcompany,b->pubdate,b->price,b->ISBN,b->category,b->condition,b->borrowednum);
        n++;
        b1=b;
        b=b->next;
        free(b1);
    }
    fclose(pb);
}

void fine()
{
    int i;
    struct readerinf *p,*p2;
    struct tm *t;
    time_t tt;
    time(&tt);
    t=localtime(&tt);
    p2=creat();
    p=p2;
    tt=mktime(t);
    while(p!=NULL)
    {
        for(i=0;i<p->bornum;i++)
        {
            if((t->tm_year+1900+(t->tm_mon+1)/12.0)==(p->b[i].outyear+(p->b[i].outmonth)/12.0))
            {
                if(t->tm_mday==p->b[i].outday)/*到期了*/
                {
                    p->outdatenum++;
                    p->b[i].tim=tt;
                }
                if(t->tm_mday>p->b[i].outday)/*超期了*/
                {
                    p->balance-=(tt-p->b[i].tim)/864000;
                    p->b[i].tim=tt;
                }
            }
            if((t->tm_year+1900+(t->tm_mon+1)/12.0)>(p->b[i].outyear+(p->b[i].outmonth)/12.0))/*超期了*/
            {
                p->balance-=(tt-p->b[i].tim)/864000;
                p->b[i].tim=tt;
            }
        };
        p=p->next;
    }
    storagereader(p2);
}

void statistic()
{
    int n=0;
    struct bookinf *b,*b1,*bhead;
    bhead=b=begin();
    while(b!=NULL)
    {
        if(b->borrowednum>n)
        {
            n=b->borrowednum;/*记录最受欢迎图书的被借次数和地址*/
            b1=b;
        }
        b=b->next;
    }
    printf("以下是最受喜欢的图书的信息:\n");
    printf("书名 作者 出版社 出版时间 价格 分类 借阅次数\n");
    printf("%s %s %s %s %d %s %d\n",b1->name,b1->author,b1->pubcompany,b1->pubdate,b1->price,b1->category,n);
    storagebook(bhead);
}
