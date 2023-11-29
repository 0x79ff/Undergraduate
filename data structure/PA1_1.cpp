/*2153299 杨非凡*/

/*用顺序表实现*/
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

/*
将学生和课程放在一个结构体表示选课信息
*/
typedef struct
{
    Student stu;
    Course cou;
} Info;

/*顺序表相关操作*/
/*begin*/

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LOVERFLOW -2

typedef int Status;

#define LIST_INIT_SIZE 500
#define LISTINCREMENT 20

typedef Info ElemType;
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

/*线性表的初始化*/
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        exit(LOVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

/*线性表指定位置元素的加入*/
Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    ElemType *p, *q;
    if (i < 1 || i > L.length + 1)
        return ERROR;

    if (L.length >= L.listsize)
    {
        ElemType *newbase;
        newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return LOVERFLOW;

        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }

    q = &(L.elem[i - 1]);

    /* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
    for (p = &(L.elem[L.length - 1]); p >= q; --p)
    {
        memcpy(p + 1, p, sizeof(ElemType));
    }

    memcpy(q, &e, sizeof(ElemType));
    L.length++;
    return OK;
}

/*线性表指定位置元素删除*/
Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    ElemType *p, *q;
    if (i < 1 || i > L.length + 1)
        return ERROR;

    p = &(L.elem[i - 1]); //指向第i个元素
    e = *p;
    q = L.elem + L.length - 1;

    for (++p; p <= q; ++p)
    {
        memcpy((p - 1), p, sizeof(ElemType));
    }
    --L.length;
    return OK;
}

/*两个比较函数函数，被其它函数调用来对线性表中的元素进行筛选*/
int Compare_stu_no(ElemType e1, ElemType e2)
{
    return (!strcmp(e1.stu.no, e2.stu.no));
}

int Compare_cou_no(ElemType e1, ElemType e2)
{
    return (!strcmp(e1.cou.no, e2.cou.no));
}

/*线性表元素的查找*/
int ListLocate_Sq(SqList L, ElemType e, int compare(ElemType e1, ElemType e2))
{
    int pos = 0; //没找到则返回0
    for (int i = 1; i <= L.length; i++)
    {
        if (compare(L.elem[i - 1], e))
        { //表中找到了符合条件的元素
            pos = i;
            break;
        }
    }
    return pos;
}

/*线性表的遍历和输出*/
Status ListVisit_Sq(SqList L, ElemType e, int compare(ElemType e1, ElemType e2))
{
    if (compare == Compare_cou_no)
        printf("选这门课的学生如下:\n");
    if (compare == Compare_stu_no)
        printf("该学生选课如下:\n");
    int num = 1;
    for (int i = 1; i <= L.length; i++)
    {
        if (compare(L.elem[i - 1], e)) //表中找到了符合条件的元素
        {
            if (compare == Compare_cou_no) //找到了这门课的学生
                printf("%d.学号:%s,姓名:%s,性别:%s\n", num++, L.elem[i - 1].stu.no, L.elem[i - 1].stu.name, L.elem[i - 1].stu.gender);
            if (compare == Compare_stu_no) //找到了这个学生选的课
                printf("%d.课号:%s,课名:%s,学分:%d\n", num++, L.elem[i - 1].cou.no, L.elem[i - 1].cou.name, L.elem[i - 1].cou.credit);
        }
    }
    return OK;
}
/*end*/

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
    SqList stu_list; /*存储学生信息*/
    InitList_Sq(stu_list);
    SqList cou_list; /*存储课程信息*/
    InitList_Sq(cou_list);
    SqList course_selection; /*存储学生选课信息*/
    InitList_Sq(course_selection);

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
                ElemType tmp;
                scanf("%s %s", &tmp.stu.no, &tmp.stu.name); //输入学号和姓名
                //错误处理:性别只能输入男或女
                for (;;)
                {
                    int ret = scanf("%s", &tmp.stu.gender);
                    if (ret == 1 && (!strcmp(tmp.stu.gender, "男") || !strcmp(tmp.stu.gender, "女")))
                        break;
                    else
                    {
                        printf("性别只能为\"男\"或\"女\",请重新输入:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
                if (pos != 0)
                {
                    printf("该学号在学生列表中已经存在\n");
                }
                else
                {
                    ListInsert_Sq(stu_list, stu_list.length + 1, tmp);
                    printf("已添加该学生,学号:%s,姓名:%s,性别:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
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
                ElemType tmp;
                scanf("%s %s", &tmp.cou.no, &tmp.cou.name);
                //错误处理:学分输入只能为int型数字
                for (;;)
                {
                    int ret = scanf("%d", &tmp.cou.credit);
                    if (ret == 1)
                        break;
                    else
                    {
                        printf("学分只能为int型整数,请重新输入:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = ListLocate_Sq(stu_list, tmp, Compare_cou_no);
                if (pos != 0)
                {
                    printf("该课号在课程列表中已经存在\n");
                }
                else
                {
                    ListInsert_Sq(cou_list, cou_list.length + 1, tmp);
                    printf("已添加该课程,课号:%s,课名:%s,学分:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
                }
            }
            printf("成功加入%d个课程信息\n", num_cou);
        }

        else if (option == 3)
        { // 3.查找、删除学生记录

            printf("请输入要删除的学生的学号:");
            ElemType tmp;
            scanf("%s", &tmp.stu.no);
            int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            if (pos == 0)
            {
                printf("该学号在学生列表中无法找到\n");
            }
            else
            {
                //删除该学生的同时在所有包含该学生课程名单中删去他
                for(int i=0;i<course_selection.length;i++)
                {
                    if(!strcmp(course_selection.elem[i].stu.no,tmp.stu.no)){
                        ListDelete_Sq(course_selection, i+1, tmp);
                        i--;
                    }
                }
                ListDelete_Sq(stu_list, pos, tmp);
                printf("已删除该学生,学号:%s,姓名:%s,性别:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
            }
        }

        else if (option == 4)
        {//4.查找、插入学生记录
            ElemType tmp;
            printf("请输入要添加的学生的学号、姓名、性别(\"男\"或\"女\")\n");
            scanf("%s %s", &tmp.stu.no, &tmp.stu.name); //输入学号和姓名
            //错误处理:性别只能输入男或女
            for (;;)
            {
                int ret = scanf("%s", &tmp.stu.gender);
                if (ret == 1 && (!strcmp(tmp.stu.gender, "男") || !strcmp(tmp.stu.gender, "女")))
                    break;
                else
                {
                    printf("性别只能为\"男\"或\"女\",请重新输入:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            if (pos != 0)
            {
                printf("该学号在学生列表中已经存在\n");
            }
            else
            {
                ListInsert_Sq(stu_list, stu_list.length + 1, tmp);
                printf("已添加该学生,学号:%s,姓名:%s,性别:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
            }
        }

        else if (option == 5)
        {//5.查找、删除课程记录
            printf("请输入要删除的课程的课号:");
            ElemType tmp;
            scanf("%s", &tmp.cou.no);
            int pos = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
            if (pos == 0)
            {
                printf("该课号在课程列表中无法找到\n");
            }
            else
            {
                //删除该学生的同时在所有包含该学生课程名单中删去他
                for(int i=0;i<course_selection.length;i++)
                {
                    if(!strcmp(course_selection.elem[i].cou.no,tmp.cou.no)){
                        ListDelete_Sq(course_selection, i+1, tmp);
                        i--;
                    }
                }
                ListDelete_Sq(cou_list, pos, tmp);
                printf("已删除该课程,课号:%s,课名:%s,学分:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
            }
        }

        else if (option == 6)
        {//6.查找、插入课程记录
            ElemType tmp;
            printf("请输入要添加的课程的课号、课名、学分\n");
            scanf("%s %s", &tmp.cou.no, &tmp.cou.name);
            //错误处理:学分输入只能为int型数字
            for (;;)
            {
                int ret = scanf("%d", &tmp.cou.credit);
                if (ret == 1)
                    break;
                else
                {
                    printf("性别只能为\"男\"或\"女\",请重新输入:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
            if (pos != 0)
            {
                printf("该课号在课程列表中已经存在\n");
            }
            else
            {
                ListInsert_Sq(cou_list, cou_list.length + 1, tmp);
                printf("已添加该课程,课号:%s,课名:%s,学分:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
            }
        }
        else if (option == 7)
        { //7.输入学生选课信息
            ElemType tmp;
            printf("请依次输入选课学生的学号与该课程的课号:\n");
            scanf("%s %s", &tmp.stu.no, &tmp.cou.no);

            int pos_stu = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            int pos_cou = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
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
                memcpy(&tmp.stu, &stu_list.elem[pos_stu - 1].stu, sizeof(Student));
                memcpy(&tmp.cou, &cou_list.elem[pos_cou - 1].cou, sizeof(Course));
                ListInsert_Sq(course_selection, course_selection.length + 1, tmp);
                printf("已成功添加选课信息\n");
                printf("学生:学号:%s,姓名:%s,性别:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
                printf("课程:课号:%s,课名:%s,学分:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
            }
        }
        else if (option == 8)
        { //8.输出某门课程所有选课学生名单
            ElemType tmp;
            printf("请输入该课程的课号:\n");
            scanf("%s", &tmp.cou.no);
            int pos = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
            if (pos == 0)
            {
                printf("该课号在课程列表中不存在\n");
            }
            else
            {
                memcpy(&tmp.cou, &cou_list.elem[pos - 1].cou, sizeof(Course));
                printf("该课程:课号:%s,课名:%s,学分:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
                ListVisit_Sq(course_selection, tmp, Compare_cou_no);
            }
        }
        else if (option == 9)
        { //9.输出某位学生所有选课课程清单
            ElemType tmp;
            printf("请输入该学生的学号:\n");
            scanf("%s", &tmp.stu.no);
            int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            if (pos == 0)
            {
                printf("该学号在学生列表中不存在\n");
            }
            else
            {
                memcpy(&tmp.stu, &stu_list.elem[pos - 1].stu, sizeof(Student));
                printf("学生:学号:%s,姓名:%s,性别:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
                ListVisit_Sq(course_selection, tmp, Compare_stu_no);
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