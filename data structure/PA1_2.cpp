/*2153299 ��Ƿ�*/

/*������ʵ��*/
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
��ѧ���Ϳγ̷���һ���ṹ���ʾѡ����Ϣ
*/

/*������ز���*/
/*begin*/

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LOVERFLOW -2
typedef int Status;

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

/*�ṹ������*/
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


/*���Ա�ָ��λ��Ԫ�صļ���*/
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



/*���Ա�ָ��λ��Ԫ��ɾ��*/
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

/*�����ȽϺ������������������������������Ա��е�Ԫ�ؽ���ɸѡ*/
int Compare_STU_LIST(Student e1, Student e2)
{
    return (!strcmp(e1.no, e2.no));
}

int Compare_COU_LIST(Course e1, Course e2)
{
    return (!strcmp(e1.no, e2.no));
}

/*���Ա�Ԫ�صĲ���*/
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
    STU_LIST stu_list; /*�洢ѧ����Ϣ*/
    Init_STU_LIST(stu_list);
    COU_LIST cou_list; /*�洢�γ���Ϣ*/
    Init_COU_LIST(cou_list);

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
                Student tmp;
                scanf("%s %s", &tmp.no, &tmp.name); //����ѧ�ź�����
                //������:�Ա�ֻ�������л�Ů
                for (;;)
                {
                    int ret = scanf("%s", &tmp.gender);
                    if (ret == 1 && (!strcmp(tmp.gender, "��") || !strcmp(tmp.gender, "Ů")))
                        break;
                    else
                    {
                        printf("�Ա�ֻ��Ϊ\"��\"��\"Ů\",����������:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
                if (pos != 0)
                {
                    printf("��ѧ����ѧ���б����Ѿ�����\n");
                }
                else
                {
                    Insert_STU_LIST(stu_list, 0, tmp);
                    printf("����Ӹ�ѧ��,ѧ��:%s,����:%s,�Ա�:%s\n", tmp.no, tmp.name, tmp.gender);
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
                Course tmp;
                scanf("%s %s", &tmp.no, &tmp.name);
                //������:ѧ������ֻ��Ϊint������
                for (;;)
                {
                    int ret = scanf("%d", &tmp.credit);
                    if (ret == 1)
                        break;
                    else
                    {
                        printf("ѧ��ֻ��Ϊint������,����������:\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
                if (pos != 0)
                {
                    printf("�ÿκ��ڿγ��б����Ѿ�����\n");
                }
                else
                {
                    Insert_COU_LIST(cou_list, 0, tmp);
                    printf("����Ӹÿγ�,�κ�:%s,����:%s,ѧ��:%d\n", tmp.no, tmp.name, tmp.credit);
                }
            }
            printf("�ɹ�����%d���γ���Ϣ\n", num_cou);
        }

        else if (option == 3)
        { // 3.���ҡ�ɾ��ѧ����¼
            Student tmp;
            printf("������Ҫɾ����ѧ����ѧ��:");
            scanf("%s", &tmp.no);
            int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
            if (pos == 0)
            {
                printf("��ѧ����ѧ���б����޷��ҵ�\n");
            }
            else
            {
                COU_LIST p=cou_list;
                for(;p->next;p=p->next){
                    int pos_this_stu=Locate_STU_LIST(p->next->stus,tmp,Compare_STU_LIST);
                    if(pos_this_stu!=0) Delete_STU_LIST(p->next->stus,pos_this_stu,tmp);
                }
                Delete_STU_LIST(stu_list, pos, tmp);
                printf("��ɾ����ѧ��,ѧ��:%s,����:%s,�Ա�:%s\n", tmp.no, tmp.name, tmp.gender);
            }
        }

        else if (option == 4)
        {//4.���ҡ�����ѧ����¼
            Student tmp;
            printf("������Ҫ��ӵ�ѧ����ѧ�š��������Ա�(\"��\"��\"Ů\")\n");
            scanf("%s %s", &tmp.no, &tmp.name); //����ѧ�ź�����
            //������:�Ա�ֻ�������л�Ů
            for (;;)
            {
                int ret = scanf("%s", &tmp.gender);
                if (ret == 1 && (!strcmp(tmp.gender, "��") || !strcmp(tmp.gender, "Ů")))
                    break;
                else
                {
                    printf("�Ա�ֻ��Ϊ\"��\"��\"Ů\",����������:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
            if (pos != 0)
            {
                printf("��ѧ����ѧ���б����Ѿ�����\n");
            }
            else
            {
                Insert_STU_LIST(stu_list, 0, tmp);
                printf("����Ӹ�ѧ��,ѧ��:%s,����:%s,�Ա�:%s\n", tmp.no, tmp.name, tmp.gender);
            }
        }

        else if (option == 5)
        {//5.���ҡ�ɾ���γ̼�¼
            Course tmp;
            printf("������Ҫɾ���Ŀγ̵Ŀκ�:");
            scanf("%s", &tmp.no);
            int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
            if (pos == 0)
            {
                printf("�ÿκ��ڿγ��б����޷��ҵ�\n");
            }
            else
            {
                //�ȰѸÿγ̴�������ѧ����ѡ���б����Ƴ�����ɾ���ÿγ�
                STU_LIST p=stu_list;
                for(;p->next;p=p->next){
                    int pos_this_cou=Locate_COU_LIST(p->next->cous,tmp,Compare_COU_LIST);
                    if(pos_this_cou!=0) Delete_COU_LIST(p->next->cous,pos_this_cou,tmp);
                }
                
                Delete_COU_LIST(cou_list, pos, tmp);
                printf("��ɾ���ÿγ�,�κ�:%s,����:%s,ѧ��:%d\n", tmp.no, tmp.name, tmp.credit);
            }
        }

        else if (option == 6)
        {//6.���ҡ�����γ̼�¼
            Course tmp;
            printf("������Ҫ��ӵĿγ̵Ŀκš�������ѧ��\n");
            scanf("%s %s", &tmp.no, &tmp.name);
            //������:ѧ������ֻ��Ϊint������
            for (;;)
            {
                int ret = scanf("%d", &tmp.credit);
                if (ret == 1)
                    break;
                else
                {
                    printf("�Ա�ֻ��Ϊ\"��\"��\"Ů\",����������:\n");
                    while (getchar() != '\n')
                        ;
                }
            }

            int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
            if (pos != 0)
            {
                printf("�ÿκ��ڿγ��б����Ѿ�����\n");
            }
            else
            {
                Insert_COU_LIST(cou_list, -0, tmp);
                printf("����Ӹÿγ�,�κ�:%s,����:%s,ѧ��:%d\n", tmp.no, tmp.name, tmp.credit);
            }
        }
        else if (option == 7)
        { //7.����ѧ��ѡ����Ϣ
            Student tmpstu;
            Course tmpcou;
            printf("����������ѡ��ѧ����ѧ����ÿγ̵Ŀκ�:\n");
            scanf("%s %s", &tmpstu.no, &tmpcou.no);
            int pos_stu = Locate_STU_LIST(stu_list, tmpstu, Compare_STU_LIST);
            int pos_cou = Locate_COU_LIST(cou_list, tmpcou, Compare_COU_LIST);
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
                STU_LIST p_stu=stu_list;
                for(int i=1;i<=pos_stu;i++) p_stu=p_stu->next;
                COU_LIST p_cou=cou_list;
                for(int i=1;i<=pos_cou;i++) p_cou=p_cou->next;
                memcpy(&tmpstu,&(p_stu->data),sizeof(Student));
                memcpy(&tmpcou,&(p_cou->data),sizeof(Course));
                //ά��ѧ���еĿγ�����Ϳγ��е�ѧ������
                Insert_COU_LIST(p_stu->cous,0,p_cou->data);
                Insert_STU_LIST(p_cou->stus,0,p_stu->data);

                printf("�ѳɹ����ѡ����Ϣ\n");
                printf("ѧ��:ѧ��:%s,����:%s,�Ա�:%s\n", tmpstu.no, tmpstu.name, tmpstu.gender);
                printf("�γ�:�κ�:%s,����:%s,ѧ��:%d\n", tmpcou.no, tmpcou.name, tmpcou.credit);
            }
        }
        else if (option == 8)
        { //8.���ĳ�ſγ�����ѡ��ѧ������
            Course tmp;
            printf("������ÿγ̵Ŀκ�:\n");
            scanf("%s", &tmp.no);
            int pos = Locate_COU_LIST(cou_list, tmp, Compare_COU_LIST);
            if (pos == 0)
            {
                printf("�ÿκ��ڿγ��б��в�����\n");
            }
            else
            {
                COU_LIST p_cou=cou_list;
                for(int i=1;i<=pos;i++) p_cou=p_cou->next;
                memcpy(&tmp,&(p_cou->data),sizeof(Course));
                printf("�ÿγ�: �κ�:%s  ����:%s  ѧ��:%d\n", tmp.no, tmp.name, tmp.credit);
                STU_LIST p=p_cou->stus;
                for(int count=1;p->next;p=p->next){
                     printf("%d.ѧ��:%s  ����:%s  �Ա�:%s\n",
                      count++, p->next->data.no, p->next->data.name, p->next->data.gender);
                }
            }
        }
        else if (option == 9)
        { //9.���ĳλѧ������ѡ�ογ��嵥
            Student tmp;
            printf("�������ѧ����ѧ��:\n");
            scanf("%s", &tmp.no);
            int pos = Locate_STU_LIST(stu_list, tmp, Compare_STU_LIST);
            if (pos == 0)
            {
                printf("��ѧ����ѧ���б��в�����\n");
            }
            else
            {
                STU_LIST p_stu=stu_list;
                for(int i=1;i<=pos;i++) p_stu=p_stu->next;
                memcpy(&tmp,&(p_stu->data),sizeof(Course));
                printf("��ѧ��: ѧ��:%s  ����:%s  �Ա�:%s\n", tmp.no, tmp.name, tmp.gender);
                COU_LIST p=p_stu->cous;
                for(int count=1;p->next;p=p->next){
                     printf("%d.�κ�:%s  ����:%s  ѧ��:%d\n",
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