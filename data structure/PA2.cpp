/*2153299 ��Ƿ�*/
/*����ջģ��׳˺����ĵ��ù���
ʵ��Ŀ�� ��
1 ������ջ�Ľṹ�ͻ���������
2 ����⺯�����õĵݹ�ͻ��ݹ��̣�
3�� ����ջ�����ݹ���á�
*/
#include <bits/stdc++.h>
using namespace std;

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

/*Bigint��ز�����ʼ*/
#define LIST_INIT_SIZE 10000
#define LISTINCREMENT 1000 
typedef int ElemType;
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}BigInt;

/*BIgint�ĳ�ʼ������ֵ��Ϊ1*/
Status InitList_BigInt(BigInt &L)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem) exit(LOVERFLOW);
    memset(L.elem,0,LIST_INIT_SIZE);
    L.elem[0]=1;
    L.length=1;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}


/*bigint��*=����*/
Status Mu_BigInt(BigInt &p,int x)
{
    if(p.length+20>p.listsize){
         ElemType *newbase;
         newbase = (ElemType *)realloc(p.elem, (p.listsize+LISTINCREMENT)*sizeof(ElemType));
         if(!newbase) exit(LOVERFLOW);
          p.elem = newbase;
          p.listsize += LISTINCREMENT;
    }
    for(int i=0;i<p.length;i++)
    {
        p.elem[i]*=x;
    }
    for(int i=0;i<p.length;i++)
    {
        if(i==p.length-1 && p.elem[i]>=10) 
        {
            p.length++;
            p.elem[i+1]=(p.elem[i]/10);
            p.elem[i]%=10;
        }
        else
        {
        p.elem[i+1]+=(p.elem[i]/10);
        p.elem[i]%=10;
        }
    }
    return OK;
}
 
 /*bigint�����*/
Status Print_BigInt(BigInt p)
{
    for(int i=p.length-1;i>=0;i--)
    {
        printf("%d",p.elem[i]);
    }
    printf("\n");
    return OK;
}


/*ջ����ز�����ʼ*/
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct{
    int n; //�������������
    BigInt *a;
    //int returnAddress; �����ķ��ص�ַ��ջ����ݹ��в�����Ҫ
}Data;
/*bigint��ز�������*/

typedef Data Selemtype;
typedef struct{
    Selemtype *base;
    Selemtype *top;
    int stacksize;
}Sqstack;

Status Initstack(Sqstack &s)
{
    s.base=(Selemtype*)malloc(STACK_INIT_SIZE*sizeof(Selemtype));
    if(!s.base) exit(LOVERFLOW);
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
    return OK;
}

Status Pop(Sqstack &s,Selemtype &e)
{
    if(s.top==s.base) return ERROR;
    e=*--s.top;
    return OK;
}

Status Push(Sqstack &s,Selemtype e)
{
    if(s.top-s.base>=s.stacksize){
        s.base=(Selemtype *)realloc(s.base,(s.stacksize+STACKINCREMENT)*sizeof(Selemtype));
        if(!s.base) exit(LOVERFLOW);
        s.top=s.base+s.stacksize;
        s.stacksize+=STACKINCREMENT;
    }
    *s.top++=e;
    return OK;
}

int Empty(Sqstack s)
{
    if(s.top==s.base) return TRUE;
    else return FALSE;
}

/*ջ����ز�������*/


/*��ͳ�Ľ׳˺���*/
int Factorial(int n)
{
    if(n==1 || n==0) return 1;
    return n*Factorial(n-1);
}

/*ջ����ݹ���n�׳ˣ�ʹ�ø߾���*/
void Stack_resolution_recursion(int n,BigInt &result2)
{
    Sqstack s;
    Initstack(s);
    Selemtype e;
    e.n=n;
    e.a=&result2;
    //�ݹ����
    for(;;){
        if(e.n==0) break;
        Push(s,e);
        printf("�ݹ����: %d ��ջ\n",e.n);
        --e.n;
    }
    //���ݹ���
    for(;;){
        if(Empty(s)) break;
        else{
            Selemtype tmp;
            Pop(s,tmp);
            printf("���ݹ���: %d ��ջ\n",tmp.n);
            Mu_BigInt(*tmp.a,tmp.n);
        }
    }
    return ;
}

/*�˵�����*/
int menu()
{
    int n;
    while (1) {
		printf("���������������n�Ľ׳�  ������n��ֵ:\n");
		int ret = scanf("%d", &n);
        //������
		if (ret == 1) break;//����Ϊint
		else {
            printf("����ֻ��Ϊint����,����������\n");
			while (getchar() != '\n') ;
		}
	} 
    return n;
}

int main()
{
    int n=menu();
    int result1;
    BigInt result2;
    InitList_BigInt(result2);

    //ʹ�ô�ͳ�ݹ麯�����
    printf("��ͳ�ݹ麯�����:\n");
    result1=Factorial(n);
    printf("���Ϊ:%d\n",result1);
    printf("\n");

    //ջ����ݹ麯�����
    printf("ջ����ݹ麯�����:\n");
    Stack_resolution_recursion(n,result2);
    printf("���Ϊ:");
    Print_BigInt(result2);
    printf("\n");

    
    return 0;
}