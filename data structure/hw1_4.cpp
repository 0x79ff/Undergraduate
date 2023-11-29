#include <bits/stdc++.h>
using namespace std;
typedef int ElemType;
 
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2        
 
typedef int Status;
#define LIST_INIT_SIZE 1000
#define LISTINCREMENT 50 
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}BigInt;

Status InitList_BigInt(BigInt &L)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    
    if(!L.elem) exit(LOVERFLOW);
    memset(L.elem,0,LIST_INIT_SIZE);
    L.length=0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
 
Status Add_BigInt(BigInt &p,BigInt q)
{
    for(int i=0;i<max(p.length,q.length);i++)
    {
        if(i<min(p.length,q.length))
        {
            p.elem[i]+=q.elem[i];
        }
        if(i>=p.length && i<q.length)
        {
            p.elem[i]=q.elem[i];        
        }
        if(i>=q.length && i<p.length)
        {
            ;
        }
    }
    p.length=max(p.length,q.length);
    for(int i=0;i<p.length;i++)
    {
        if(i==p.length-1 && p.elem[i]>=10)
        {
            p.length++;
        }
        p.elem[i+1]+=(p.elem[i]/10);
        p.elem[i]%=10;
    }
    return OK;
}
 
Status Mu_BigInt(BigInt &p,int x)//相当于BigInt的*=
{
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
 
Status Print_BigInt(BigInt p)
{
    for(int i=p.length-1;i>=0;i--)
    {
        printf("%d",p.elem[i]);
    }
    printf("\n");
    return OK;
}
 
int main()
{
    int n,a;
    for(;scanf("%d %d",&n,&a)!=EOF;)
    {
        if(a==0)
        {
            printf("0\n");
            continue;
        }
        BigInt ans,A;
        InitList_BigInt(ans);
        InitList_BigInt(A);
        A.length=1;
        A.elem[0]=1;
        for(int i=1;i<=n;i++)
        {
            Mu_BigInt(A,a);
          
            BigInt A1;
            InitList_BigInt(A1);    
            Add_BigInt(A1,A);
            
            Mu_BigInt(A1,i);
            
            Add_BigInt(ans,A1);
        }
        Print_BigInt(ans);
    }
    
 
    return 0;
}