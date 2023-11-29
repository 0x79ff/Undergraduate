/*2153299 ��Ƿ�*/

/*��˳���ʵ��*/
/*���뻷����g++ (tdm64-1) 10.3.0*/
/*�ַ�����GB2312*/
/*
Ҫ��
����Ϊһ��ӵ�нӽ�40000��ѧ����3000�ſγ̵Ĵ�ѧ������һ��ѡ��ϵͳ���������¹��ܣ�
(1) �ܹ���������ѧ����Ϣ��ѧ�ţ��������Ա�,...����
(2) �ܹ��������пγ���Ϣ���κţ�������ѧ��,...����
(3) �ܹ����ҡ����롢ɾ��ѧ����¼��
(4) �ܹ����ҡ����롢ɾ���γ̼�¼��
(5) �ܹ�����ѧ��ѡ����Ϣ�����������ѧ��a���κ�b�����ͱ�ʾѧ��aע���˿γ�b��
(6) �ܹ����ĳ�ſγ̵�����ѡ��ѧ��������������ѧ��������Ϣ��ѧ�š��������Ա𡣡�������
(7) �ܹ����ĳλѧ��������ѡ�ογ��嵥�������γ̵�������Ϣ���κš�������ѧ�֡���������
*/
#include <bits/stdc++.h>
using namespace std;

/*
ѧ���ṹ��
������ѧ�š��������Ա�
*/
typedef struct
{
    char no[20];
    char name[20];
    char gender[5];
} Student;
/*
�γ̽ṹ��
�������κš�������ѧ��
*/
typedef struct
{
    char no[20];
    char name[20];
    int credit;
} Course;

/*
��ѧ���Ϳγ̷���һ���ṹ���ʾѡ����Ϣ
*/
typedef struct
{
    Student stu;
    Course cou;
} Info;

/*˳�����ز���*/
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

/*���Ա�ĳ�ʼ��*/
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        exit(LOVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

/*���Ա�ָ��λ��Ԫ�صļ���*/
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

    /* �����һ����length����[length-1]�С���ʼ����i��Ԫ�����κ���һ�� */
    for (p = &(L.elem[L.length - 1]); p >= q; --p)
    {
        memcpy(p + 1, p, sizeof(ElemType));
    }

    memcpy(q, &e, sizeof(ElemType));
    L.length++;
    return OK;
}

/*���Ա�ָ��λ��Ԫ��ɾ��*/
Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    ElemType *p, *q;
    if (i < 1 || i > L.length + 1)
        return ERROR;

    p = &(L.elem[i - 1]); //ָ���i��Ԫ��
    e = *p;
    q = L.elem + L.length - 1;

    for (++p; p <= q; ++p)
    {
        memcpy((p - 1), p, sizeof(ElemType));
    }
    --L.length;
    return OK;
}

/*�����ȽϺ������������������������������Ա��е�Ԫ�ؽ���ɸѡ*/
int Compare_stu_no(ElemType e1, ElemType e2)
{
    return (!strcmp(e1.stu.no, e2.stu.no));
}

int Compare_cou_no(ElemType e1, ElemType e2)
{
    return (!strcmp(e1.cou.no, e2.cou.no));
}

/*���Ա�Ԫ�صĲ���*/
int ListLocate_Sq(SqList L, ElemType e, int compare(ElemType e1, ElemType e2))
{
    int pos = 0; //û�ҵ��򷵻�0
    for (int i = 1; i <= L.length; i++)
    {
        if (compare(L.elem[i - 1], e))
        { //�����ҵ��˷���������Ԫ��
            pos = i;
            break;
        }
    }
    return pos;
}

/*���Ա�ı��������*/
Status ListVisit_Sq(SqList L, ElemType e, int compare(ElemType e1, ElemType e2))
{
    if (compare == Compare_cou_no)
        printf("ѡ���ſε�ѧ������:\n");
    if (compare == Compare_stu_no)
        printf("��ѧ��ѡ������:\n");
    int num = 1;
    for (int i = 1; i <= L.length; i++)
    {
        if (compare(L.elem[i - 1], e)) //�����ҵ��˷���������Ԫ��
        {
            if (compare == Compare_cou_no) //�ҵ������ſε�ѧ��
                printf("%d.ѧ��:%s,����:%s,�Ա�:%s\n", num++, L.elem[i - 1].stu.no, L.elem[i - 1].stu.name, L.elem[i - 1].stu.gender);
            if (compare == Compare_stu_no) //�ҵ������ѧ��ѡ�Ŀ�
                printf("%d.�κ�:%s,����:%s,ѧ��:%d\n", num++, L.elem[i - 1].cou.no, L.elem[i - 1].cou.name, L.elem[i - 1].cou.credit);
        }
    }
    return OK;
}
/*end*/

/*
��������menu
���ܣ��˵��������������������Ϣ������ѡ����ظ�main
*/
int menu()
{
    int option;
    while (1)
    {
        printf("\n");
        printf("--------------------------------\n");
        printf("1.��������ѧ����Ϣ(ѧ��,����,�Ա�)\n");
        printf("2.�������пγ���Ϣ(�κ�,����,ѧ��)\n");
        printf("3.���ҡ�ɾ��ѧ����¼\n");
        printf("4.���ҡ�����ѧ����¼\n");
        printf("5.���ҡ�ɾ���γ̼�¼\n");
        printf("6.���ҡ�����γ̼�¼\n");
        printf("7.����ѧ��ѡ����Ϣ\n");
        printf("8.���ĳ�ſγ�����ѡ��ѧ������\n");
        printf("9.���ĳλѧ������ѡ�ογ��嵥\n");
        printf("0.�˳�\n");
        printf("--------------------------------\n");
        printf("������ѡ��[0-9]:");
        int ret = scanf("%d", &option);
        //������
        if (ret == 1 && (option >= 0 && option <= 9)) //����Ϊint�ҷ�Χ��ȷ
            break;
        else if (ret == 1 && (option < 0 || option > 9)) //��Χ����
            continue;
        else //���벻Ϊint
        {
            while (getchar() != '\n')
                ;
        }
    }
    return option;
}



int main()
{
    /*�������Ա�*/
    SqList stu_list; /*�洢ѧ����Ϣ*/
    InitList_Sq(stu_list);
    SqList cou_list; /*�洢�γ���Ϣ*/
    InitList_Sq(cou_list);
    SqList course_selection; /*�洢ѧ��ѡ����Ϣ*/
    InitList_Sq(course_selection);

    for (;;)
    {
        int option = menu();
        printf("\n");
        if (option == 0)
            break;
        if (option == 1)
        { // 1.��������ѧ����Ϣ(ѧ��,����,�Ա�)
            int num_stu;
            for (;;)
            {
                printf("������Ҫ�����ѧ������:");
                int ret = scanf("%d", &num_stu);
                if (ret == 1)
                    break;
                else
                {
                    printf("ѧ������ֻ��Ϊint������,����������:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            for (int i = 1; i <= num_stu; i++)
            {
                printf("�������%d��ѧ����ѧ�š��������Ա�(\"��\"��\"Ů\")\n", i);
                ElemType tmp;
                scanf("%s %s", &tmp.stu.no, &tmp.stu.name); //����ѧ�ź�����
                //������:�Ա�ֻ�������л�Ů
                for (;;)
                {
                    int ret = scanf("%s", &tmp.stu.gender);
                    if (ret == 1 && (!strcmp(tmp.stu.gender, "��") || !strcmp(tmp.stu.gender, "Ů")))
                        break;
                    else
                    {
                        printf("�Ա�ֻ��Ϊ\"��\"��\"Ů\",����������:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
                if (pos != 0)
                {
                    printf("��ѧ����ѧ���б����Ѿ�����\n");
                }
                else
                {
                    ListInsert_Sq(stu_list, stu_list.length + 1, tmp);
                    printf("����Ӹ�ѧ��,ѧ��:%s,����:%s,�Ա�:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
                }
            }
            printf("�ɹ�����%d��ѧ����Ϣ\n", num_stu);
        }
        else if (option == 2)
        { // 2.�������пγ���Ϣ(�κ�,����,ѧ��)
            int num_cou;
            for (;;)
            {
                printf("������Ҫ����Ŀγ�����:");
                int ret = scanf("%d", &num_cou);
                if (ret == 1)
                    break;
                else
                {
                    printf("�γ�����ֻ��Ϊint������,����������:\n");
                    while (getchar() != '\n')
                        ;
                }
            }
            for (int i = 1; i <= num_cou; i++)
            {
                printf("�������%d���γ̵Ŀκš�������ѧ��\n", i);
                ElemType tmp;
                scanf("%s %s", &tmp.cou.no, &tmp.cou.name);
                //������:ѧ������ֻ��Ϊint������
                for (;;)
                {
                    int ret = scanf("%d", &tmp.cou.credit);
                    if (ret == 1)
                        break;
                    else
                    {
                        printf("ѧ��ֻ��Ϊint������,����������:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = ListLocate_Sq(stu_list, tmp, Compare_cou_no);
                if (pos != 0)
                {
                    printf("�ÿκ��ڿγ��б����Ѿ�����\n");
                }
                else
                {
                    ListInsert_Sq(cou_list, cou_list.length + 1, tmp);
                    printf("����Ӹÿγ�,�κ�:%s,����:%s,ѧ��:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
                }
            }
            printf("�ɹ�����%d���γ���Ϣ\n", num_cou);
        }

        else if (option == 3)
        { // 3.���ҡ�ɾ��ѧ����¼

            printf("������Ҫɾ����ѧ����ѧ��:");
            ElemType tmp;
            scanf("%s", &tmp.stu.no);
            int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            if (pos == 0)
            {
                printf("��ѧ����ѧ���б����޷��ҵ�\n");
            }
            else
            {
                //ɾ����ѧ����ͬʱ�����а�����ѧ���γ�������ɾȥ��
                for(int i=0;i<course_selection.length;i++)
                {
                    if(!strcmp(course_selection.elem[i].stu.no,tmp.stu.no)){
                        ListDelete_Sq(course_selection, i+1, tmp);
                        i--;
                    }
                }
                ListDelete_Sq(stu_list, pos, tmp);
                printf("��ɾ����ѧ��,ѧ��:%s,����:%s,�Ա�:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
            }
        }

        else if (option == 4)
        {//4.���ҡ�����ѧ����¼
            ElemType tmp;
            printf("������Ҫ��ӵ�ѧ����ѧ�š��������Ա�(\"��\"��\"Ů\")\n");
            scanf("%s %s", &tmp.stu.no, &tmp.stu.name); //����ѧ�ź�����
            //������:�Ա�ֻ�������л�Ů
            for (;;)
            {
                int ret = scanf("%s", &tmp.stu.gender);
                if (ret == 1 && (!strcmp(tmp.stu.gender, "��") || !strcmp(tmp.stu.gender, "Ů")))
                    break;
                else
                {
                    printf("�Ա�ֻ��Ϊ\"��\"��\"Ů\",����������:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            if (pos != 0)
            {
                printf("��ѧ����ѧ���б����Ѿ�����\n");
            }
            else
            {
                ListInsert_Sq(stu_list, stu_list.length + 1, tmp);
                printf("����Ӹ�ѧ��,ѧ��:%s,����:%s,�Ա�:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
            }
        }

        else if (option == 5)
        {//5.���ҡ�ɾ���γ̼�¼
            printf("������Ҫɾ���Ŀγ̵Ŀκ�:");
            ElemType tmp;
            scanf("%s", &tmp.cou.no);
            int pos = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
            if (pos == 0)
            {
                printf("�ÿκ��ڿγ��б����޷��ҵ�\n");
            }
            else
            {
                //ɾ����ѧ����ͬʱ�����а�����ѧ���γ�������ɾȥ��
                for(int i=0;i<course_selection.length;i++)
                {
                    if(!strcmp(course_selection.elem[i].cou.no,tmp.cou.no)){
                        ListDelete_Sq(course_selection, i+1, tmp);
                        i--;
                    }
                }
                ListDelete_Sq(cou_list, pos, tmp);
                printf("��ɾ���ÿγ�,�κ�:%s,����:%s,ѧ��:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
            }
        }

        else if (option == 6)
        {//6.���ҡ�����γ̼�¼
            ElemType tmp;
            printf("������Ҫ��ӵĿγ̵Ŀκš�������ѧ��\n");
            scanf("%s %s", &tmp.cou.no, &tmp.cou.name);
            //������:ѧ������ֻ��Ϊint������
            for (;;)
            {
                int ret = scanf("%d", &tmp.cou.credit);
                if (ret == 1)
                    break;
                else
                {
                    printf("�Ա�ֻ��Ϊ\"��\"��\"Ů\",����������:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
            if (pos != 0)
            {
                printf("�ÿκ��ڿγ��б����Ѿ�����\n");
            }
            else
            {
                ListInsert_Sq(cou_list, cou_list.length + 1, tmp);
                printf("����Ӹÿγ�,�κ�:%s,����:%s,ѧ��:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
            }
        }
        else if (option == 7)
        { //7.����ѧ��ѡ����Ϣ
            ElemType tmp;
            printf("����������ѡ��ѧ����ѧ����ÿγ̵Ŀκ�:\n");
            scanf("%s %s", &tmp.stu.no, &tmp.cou.no);

            int pos_stu = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            int pos_cou = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
            if (pos_stu == 0)
            {
                printf("��ѧ����ѧ���б��в�����!\n");
            }
            if (pos_cou == 0)
            {
                printf("�ÿκ��ڿγ��б��в�����!\n");
            }
            if (pos_stu != 0 && pos_cou != 0)
            {
                memcpy(&tmp.stu, &stu_list.elem[pos_stu - 1].stu, sizeof(Student));
                memcpy(&tmp.cou, &cou_list.elem[pos_cou - 1].cou, sizeof(Course));
                ListInsert_Sq(course_selection, course_selection.length + 1, tmp);
                printf("�ѳɹ����ѡ����Ϣ\n");
                printf("ѧ��:ѧ��:%s,����:%s,�Ա�:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
                printf("�γ�:�κ�:%s,����:%s,ѧ��:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
            }
        }
        else if (option == 8)
        { //8.���ĳ�ſγ�����ѡ��ѧ������
            ElemType tmp;
            printf("������ÿγ̵Ŀκ�:\n");
            scanf("%s", &tmp.cou.no);
            int pos = ListLocate_Sq(cou_list, tmp, Compare_cou_no);
            if (pos == 0)
            {
                printf("�ÿκ��ڿγ��б��в�����\n");
            }
            else
            {
                memcpy(&tmp.cou, &cou_list.elem[pos - 1].cou, sizeof(Course));
                printf("�ÿγ�:�κ�:%s,����:%s,ѧ��:%d\n", tmp.cou.no, tmp.cou.name, tmp.cou.credit);
                ListVisit_Sq(course_selection, tmp, Compare_cou_no);
            }
        }
        else if (option == 9)
        { //9.���ĳλѧ������ѡ�ογ��嵥
            ElemType tmp;
            printf("�������ѧ����ѧ��:\n");
            scanf("%s", &tmp.stu.no);
            int pos = ListLocate_Sq(stu_list, tmp, Compare_stu_no);
            if (pos == 0)
            {
                printf("��ѧ����ѧ���б��в�����\n");
            }
            else
            {
                memcpy(&tmp.stu, &stu_list.elem[pos - 1].stu, sizeof(Student));
                printf("ѧ��:ѧ��:%s,����:%s,�Ա�:%s\n", tmp.stu.no, tmp.stu.name, tmp.stu.gender);
                ListVisit_Sq(course_selection, tmp, Compare_stu_no);
            }
        }
        else
            ;
    }
    return 0;
}
/*
�Բ�����
һ��
1
3
2153299 yff 1 Ů
2151769 lbw ��
2152513 xbw ��

2
2
1 �߳� a 3
2 ���ݽṹ���㷨 3
3 �����ѧ 2

3
2111111
2153299

4
2151769 lbw ��
2153299 yff 1 Ů

5
4
1

6
2 ���ݽṹ���㷨 3
1 �߳� a 3

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

����
1
3
1 1 ��
2 2 ��
3 3 Ů

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