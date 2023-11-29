/*2153299 杨非凡*/

/*用链表实现*/
/*编译环境：g++ (tdm64-1) 10.3.0*/
/*字符集：GB2312*/
/*
要求：
请你为一所拥有接近40000名学生和3000门课程的大学，生成一个选课系统，具有如下功能：
(1) 能够输入所有学生信息（学号，姓名，性别,...）；
(2) 能够输入所有课程信息（课号，课名，学分,...）；
(3) 能够查找、插入、删除学生记录；
(4) 能够查找、插入、删除课程记录；
(5) 能够输入学生选课信息，例如给定（学号a，课号b），就表示学生a注册了课程b；
(6) 能够输出某门课程的所有选课学生的名单，包含学生所有信息（学号、姓名、性别。。。）；
(7) 能够输出某位学生的所有选课课程清单，包含课程的所有信息（课号、课名、学分。。。）；
*/
#include <bits/stdc++.h>
using namespace std;

/*
将学生和课程放在一个结构体表示选课信息
*/

/*链表相关操作*/
/*begin*/

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LOVERFLOW -2
typedef int Status;

/*
学生结构体
包括：学号、姓名、性别
*/
typedef struct
{
    char no[20];
    char name[20];
    char gender[5];
} Student;
/*
课程结构体
包括：课号、课名、学分
*/
typedef struct
{
    char no[20];
    char name[20];
    int credit;
} Course;

/*结构体声明*/
struct STU_Node;
struct COU_Node;

typedef struct STU_Node{
    Student data;
    struct STU_Node *next;
    COU_Node* cous;
}STU_Node,*STU_LIST;

typedef struct COU_Node{
    Course data;
    struct COU_Node *next;
    STU_Node* stus;
}COU_Node,*COU_LIST;

Status Init_STU_LIST(STU_LIST &L)
{
    L = (STU_Node *)malloc(sizeof(STU_Node));
    if (!L) exit(LOVERFLOW);
    L->next=NULL;
    L->cous = (COU_Node *)malloc(sizeof(COU_Node));
    if (!L->cous) exit(LOVERFLOW);
    L->cous->next=NULL;
    return OK;
}

Status Init_COU_LIST(COU_LIST &L)
{
    L = (COU_Node *)malloc(sizeof(COU_Node));
    if (!L) exit(LOVERFLOW);
    L->next=NULL;
    L->stus = (STU_Node *)malloc(sizeof(STU_Node));
    if (!L->stus) exit(LOVERFLOW);
    L->stus->next=NULL;
    return OK;
}


/*线性表指定位置元素的加入*/
Status Insert_STU_LIST(STU_LIST &L, int i, Student e)
{
    STU_LIST p = L;
    int pos=0;
    
    for(;p && pos < i-1;){
        p=p->next;
        ++pos;
    }

    if(!p && pos > i - 1) return ERROR;

    STU_LIST s;
    Init_STU_LIST(s);
    s->data=e; s->next = p->next;
    p->next = s;
    return OK;
}

Status Insert_COU_LIST(COU_LIST &L, int i, Course e)
{
    COU_LIST p = L;
    int pos=0;
    
    for(;p && pos < i-1;){
        p=p->next;
        ++pos;
    }

    if(!p && pos > i - 1) return ERROR;

    COU_LIST s;
    Init_COU_LIST(s);
    s->data=e; s->next = p->next;
    p->next = s;
    return OK;
}



/*线性表指定位置元素删除*/
Status Delete_STU_LIST(STU_LIST &L, int i, Student &e)
{
    STU_LIST p = L;
    int pos=0;
    
    for(;p->next && pos < i-1;){
        p=p->next;
        ++pos;
    }

    if(!(p->next) && pos > i - 1) return ERROR;
    
    STU_LIST q = (STU_LIST)malloc(sizeof(STU_Node));
    q=p->next;p->next=q->next;
    e=q->data; free(q);
    return OK;
}

Status Delete_COU_LIST(COU_LIST &L, int i, Course &e)
{
    COU_LIST p = L;
    int pos=0;
    
    for(;p->next && pos < i-1;){
        p=p->next;
        ++pos;
    }

    if(!(p->next) && pos > i - 1) return ERROR;
    
    COU_LIST q = (COU_LIST)malloc(sizeof(COU_Node));
    q=p->next;p->next=q->next;
    e=q->data; free(q);
    return OK;
}

/*两个比较函数函数，被其它函数调用来对线性表中的元素进行筛选*/
int Compare_STU_LIST(Student e1, Student e2)
{
    return (!strcmp(e1.no, e2.no));
}

int Compare_COU_LIST(Course e1, Course e2)
{
    return (!strcmp(e1.no, e2.no));
}

/*线性表元素的查找*/
int Locate_STU_LIST(STU_LIST L, Student e, int compare(Student e1, Student e2))
{
    STU_LIST p = L;
    int pos = 1;
    for(;p->next;++pos,p=p->next){
        if(compare(e,p->next->data)){
            return pos;
        }
    }
    return 0;
}

int Locate_COU_LIST(COU_LIST L, Course e, int compare(Course e1, Course e2))
{
    COU_LIST p = L;
    int pos = 1;
    for(;p->next;++pos,p=p->next){
        if(compare(e,p->next->data)){
            return pos;
        }
    }
    return 0;
}

/*
函数名：menu
功能：菜单函数，用来输出交互信息，输入选项并返回给main
*/
int menu()
{
    int option;
    while (1)
    {
        printf("\n");
        printf("--------------------------------\n");
        printf("1.输入所有学生信息(学号,姓名,性别)\n");
        printf("2.输入所有课程信息(课号,课名,学分)\n");
        printf("3.查找、删除学生记录\n");
        printf("4.查找、插入学生记录\n");
        printf("5.查找、删除课程记录\n");
        printf("6.查找、插入课程记录\n");
        printf("7.输入学生选课信息\n");
        printf("8.输出某门课程所有选课学生名单\n");
        printf("9.输出某位学生所有选课课程清单\n");
        printf("0.退出\n");
        printf("--------------------------------\n");
        printf("请输入选项[0-9]:");
        int ret = scanf("%d", &option);
        //错误处理
        if (ret == 1 && (option >= 0 && option <= 9)) //输入为int且范围正确
            break;
        else if (ret == 1 && (option < 0 || option > 9)) //范围不对
            continue;
        else //输入不为int
        {
            while (getchar() != '\n')
                ;
        }
    }
    return option;
}


int main()
{
    /*三个线性表*/
    STU_LIST stu_list; /*存储学生信息*/
    Init_STU_LIST(stu_list);
    COU_LIST cou_list; /*存储课程信息*/
    Init_COU_LIST(cou_list);

    for (;;)
    {
        int option = menu();
        printf("\n");
        if (option == 0)
            break;
        if (option == 1)
        { // 1.输入所有学生信息(学号,姓名,性别)
            int num_stu;
            for (;;)
            {
                printf("请输入要输入的学生数量:");
                int ret = scanf("%d", &num_stu);
                if (ret == 1)
                    break;
                else
                {
                    printf("学生数量只能为int型整数,请重新输入:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            for (int i = 1; i <= num_stu; i++)
            {
                printf("请输入第%d个学生的学号、姓名、性别(\"男\"或\"女\")\n", i);
                Student tmp;
                scanf("%s %s", &tmp.no, &tmp.name); //输入学号和姓名
                //错误处理:性别只能输入男或女
                for (;;)
                {
                    int ret = scanf("%s", &tmp.gender);
                    if (ret == 1 && (!strcmp(tmp.gender, "男") || !strcmp(tmp.gender, "女")))
                        break;
                    else
                    {
                        printf("性别只能为\"男\"或\"女\",请重新输入:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
                if (pos != 0)
                {
                    printf("该学号在学生列表中已经存在\n");
                }
                else
                {
                    Insert_STU_LIST(stu_list, 0, tmp);
                    printf("已添加该学生,学号:%s,姓名:%s,性别:%s\n", tmp.no, tmp.name, tmp.gender);
                }
            }
            printf("成功加入%d个学生信息\n", num_stu);
        }
        else if (option == 2)
        { // 2.输入所有课程信息(课号,课名,学分)
            int num_cou;
            for (;;)
            {
                printf("请输入要输入的课程数量:");
                int ret = scanf("%d", &num_cou);
                if (ret == 1)
                    break;
                else
                {
                    printf("课程数量只能为int型整数,请重新输入:\n");
                    while (getchar() != '\n')
                        ;
                }
            }
            for (int i = 1; i <= num_cou; i++)
            {
                printf("请输入第%d个课程的课号、课名、学分\n", i);
                Course tmp;
                scanf("%s %s", &tmp.no, &tmp.name);
                //错误处理:学分输入只能为int型数字
                for (;;)
                {
                    int ret = scanf("%d", &tmp.credit);
                    if (ret == 1)
                        break;
                    else
                    {
                        printf("学分只能为int型整数,请重新输入:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
                if (pos != 0)
                {
                    printf("该课号在课程列表中已经存在\n");
                }
                else
                {
                    Insert_COU_LIST(cou_list, 0, tmp);
                    printf("已添加该课程,课号:%s,课名:%s,学分:%d\n", tmp.no, tmp.name, tmp.credit);
                }
            }
            printf("成功加入%d个课程信息\n", num_cou);
        }

        else if (option == 3)
        { // 3.查找、删除学生记录
            Student tmp;
            printf("请输入要删除的学生的学号:");
            scanf("%s", &tmp.no);
            int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
            if (pos == 0)
            {
                printf("该学号在学生列表中无法找到\n");
            }
            else
            {
                COU_LIST p=cou_list;
                for(;p->next;p=p->next){
                    int pos_this_stu=Locate_STU_LIST(p->next->stus,tmp,Compare_STU_LIST);
                    if(pos_this_stu!=0) Delete_STU_LIST(p->next->stus,pos_this_stu,tmp);
                }
                Delete_STU_LIST(stu_list, pos, tmp);
                printf("已删除该学生,学号:%s,姓名:%s,性别:%s\n", tmp.no, tmp.name, tmp.gender);
            }
        }

        else if (option == 4)
        {//4.查找、插入学生记录
            Student tmp;
            printf("请输入要添加的学生的学号、姓名、性别(\"男\"或\"女\")\n");
            scanf("%s %s", &tmp.no, &tmp.name); //输入学号和姓名
            //错误处理:性别只能输入男或女
            for (;;)
            {
                int ret = scanf("%s", &tmp.gender);
                if (ret == 1 && (!strcmp(tmp.gender, "男") || !strcmp(tmp.gender, "女")))
                    break;
                else
                {
                    printf("性别只能为\"男\"或\"女\",请重新输入:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
            if (pos != 0)
            {
                printf("该学号在学生列表中已经存在\n");
            }
            else
            {
                Insert_STU_LIST(stu_list, 0, tmp);
                printf("已添加该学生,学号:%s,姓名:%s,性别:%s\n", tmp.no, tmp.name, tmp.gender);
            }
        }

        else if (option == 5)
        {//5.查找、删除课程记录
            Course tmp;
            printf("请输入要删除的课程的课号:");
            scanf("%s", &tmp.no);
            int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
            if (pos == 0)
            {
                printf("该课号在课程列表中无法找到\n");
            }
            else
            {
                //先把该课程从它所有学生的选课列表中移除，再删除该课程
                STU_LIST p=stu_list;
                for(;p->next;p=p->next){
                    int pos_this_cou=Locate_COU_LIST(p->next->cous,tmp,Compare_COU_LIST);
                    if(pos_this_cou!=0) Delete_COU_LIST(p->next->cous,pos_this_cou,tmp);
                }
                
                Delete_COU_LIST(cou_list, pos, tmp);
                printf("已删除该课程,课号:%s,课名:%s,学分:%d\n", tmp.no, tmp.name, tmp.credit);
            }
        }

        else if (option == 6)
        {//6.查找、插入课程记录
            Course tmp;
            printf("请输入要添加的课程的课号、课名、学分\n");
            scanf("%s %s", &tmp.no, &tmp.name);
            //错误处理:学分输入只能为int型数字
            for (;;)
            {
                int ret = scanf("%d", &tmp.credit);
                if (ret == 1)
                    break;
                else
                {
                    printf("性别只能为\"男\"或\"女\",请重新输入:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
            if (pos != 0)
            {
                printf("该课号在课程列表中已经存在\n");
            }
            else
            {
                Insert_COU_LIST(cou_list, -0, tmp);
                printf("已添加该课程,课号:%s,课名:%s,学分:%d\n", tmp.no, tmp.name, tmp.credit);
            }
        }
        else if (option == 7)
        { //7.输入学生选课信息
            Student tmpstu;
            Course tmpcou;
            printf("请依次输入选课学生的学号与该课程的课号:\n");
            scanf("%s %s", &tmpstu.no, &tmpcou.no);
            int pos_stu = Locate_STU_LIST(stu_list, tmpstu, Compare_STU_LIST);
            int pos_cou = Locate_COU_LIST(cou_list, tmpcou, Compare_COU_LIST);
            if (pos_stu == 0)
            {
                printf("该学号在学生列表中不存在!\n");
            }
            if (pos_cou == 0)
            {
                printf("该课号在课程列表中不存在!\n");
            }
            if (pos_stu != 0 && pos_cou != 0)
            {
                STU_LIST p_stu=stu_list;
                for(int i=1;i<=pos_stu;i++) p_stu=p_stu->next;
                COU_LIST p_cou=cou_list;
                for(int i=1;i<=pos_cou;i++) p_cou=p_cou->next;
                memcpy(&tmpstu,&(p_stu->data),sizeof(Student));
                memcpy(&tmpcou,&(p_cou->data),sizeof(Course));
                //维护学生中的课程链表和课程中的学生链表
                Insert_COU_LIST(p_stu->cous,0,p_cou->data);
                Insert_STU_LIST(p_cou->stus,0,p_stu->data);

                printf("已成功添加选课信息\n");
                printf("学生:学号:%s,姓名:%s,性别:%s\n", tmpstu.no, tmpstu.name, tmpstu.gender);
                printf("课程:课号:%s,课名:%s,学分:%d\n", tmpcou.no, tmpcou.name, tmpcou.credit);
            }
        }
        else if (option == 8)
        { //8.输出某门课程所有选课学生名单
            Course tmp;
            printf("请输入该课程的课号:\n");
            scanf("%s", &tmp.no);
            int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
            if (pos == 0)
            {
                printf("该课号在课程列表中不存在\n");
            }
            else
            {
                COU_LIST p_cou=cou_list;
                for(int i=1;i<=pos;i++) p_cou=p_cou->next;
                memcpy(&tmp,&(p_cou->data),sizeof(Course));
                printf("该课程: 课号:%s  课名:%s  学分:%d\n", tmp.no, tmp.name, tmp.credit);
                STU_LIST p=p_cou->stus;
                for(int count=1;p->next;p=p->next){
                     printf("%d.学号:%s  姓名:%s  性别:%s\n",
                      count++, p->next->data.no, p->next->data.name, p->next->data.gender);
                }
            }
        }
        else if (option == 9)
        { //9.输出某位学生所有选课课程清单
            Student tmp;
            printf("请输入该学生的学号:\n");
            scanf("%s", &tmp.no);
            int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
            if (pos == 0)
            {
                printf("该学号在学生列表中不存在\n");
            }
            else
            {
                STU_LIST p_stu=stu_list;
                for(int i=1;i<=pos;i++) p_stu=p_stu->next;
                memcpy(&tmp,&(p_stu->data),sizeof(Course));
                printf("该学生: 学号:%s  名字:%s  性别:%s\n", tmp.no, tmp.name, tmp.gender);
                COU_LIST p=p_stu->cous;
                for(int count=1;p->next;p=p->next){
                     printf("%d.课号:%s  课名:%s  学分:%d\n",
                      count++, p->next->data.no, p->next->data.name, p->next->data.credit);
                }
            }
        }
        else
            ;
    }
    return 0;
}
/*
自测数据
一、
1
3
2153299 yff 1 女
2151769 lbw 男
2152513 xbw 男

2
2
1 高程 a 3
2 数据结构与算法 3
3 组合数学 2

3
2111111
2153299

4
2151769 lbw 男
2153299 yff 1 女

5
4
1

6
2 数据结构与算法 3
1 高程 a 3

7
2153299 1
2153299 2
2153299 5
2151769 2
2151769 3
2152513 3
2152513 1

8
1

9
2153299

二、
1
3
1 1 男
2 2 男
3 3 女

2
3
1 1 1
2 2 2
3 3 3

7
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3

3
1

5
1

8
2

9
2

*/