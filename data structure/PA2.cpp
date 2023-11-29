/*2153299 杨非凡*/
/*运用栈模拟阶乘函数的调用过程
实验目的 ：
1 、掌握栈的结构和基本操作；
2 、理解函数调用的递归和回溯过程；
3、 运用栈消除递归调用。
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

/*Bigint相关操作开始*/
#define LIST_INIT_SIZE 10000
#define LISTINCREMENT 1000 
typedef int ElemType;
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}BigInt;

/*BIgint的初始化，初值赋为1*/
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


/*bigint的*=操作*/
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
 
 /*bigint的输出*/
Status Print_BigInt(BigInt p)
{
    for(int i=p.length-1;i>=0;i--)
    {
        printf("%d",p.elem[i]);
    }
    printf("\n");
    return OK;
}


/*栈的相关操作开始*/
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct{
    int n; //函数的输入参数
    BigInt *a;
    //int returnAddress; 函数的返回地址，栈消解递归中并不需要
}Data;
/*bigint相关操作结束*/

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

/*栈的相关操作结束*/


/*传统的阶乘函数*/
int Factorial(int n)
{
    if(n==1 || n==0) return 1;
    return n*Factorial(n-1);
}

/*栈消解递归求n阶乘，使用高精度*/
void Stack_resolution_recursion(int n,BigInt &result2)
{
    Sqstack s;
    Initstack(s);
    Selemtype e;
    e.n=n;
    e.a=&result2;
    //递归过程
    for(;;){
        if(e.n==0) break;
        Push(s,e);
        printf("递归过程: %d 入栈\n",e.n);
        --e.n;
    }
    //回溯过程
    for(;;){
        if(Empty(s)) break;
        else{
            Selemtype tmp;
            Pop(s,tmp);
            printf("回溯过程: %d 出栈\n",tmp.n);
            Mu_BigInt(*tmp.a,tmp.n);
        }
    }
    return ;
}

/*菜单函数*/
int menu()
{
    int n;
    while (1) {
		printf("本程序的作用是求n的阶乘  请输入n的值:\n");
		int ret = scanf("%d", &n);
        //错误处理
		if (ret == 1) break;//输入为int
		else {
            printf("输入只能为int类型,请重新输入\n");
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

    //使用传统递归函数求解
    printf("传统递归函数求解:\n");
    result1=Factorial(n);
    printf("结果为:%d\n",result1);
    printf("\n");

    //栈消解递归函数求解
    printf("栈消解递归函数求解:\n");
    Stack_resolution_recursion(n,result2);
    printf("结果为:");
    Print_BigInt(result2);
    printf("\n");

    
    return 0;
}