//Paste your code here
//NOTE: If you use java, your Main class must be named solution
#include <bits/stdc++.h>
using namespace std;
int n;
typedef int ElemType;

#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2        
 
typedef int Status;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
 
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;
 
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem) exit(LOVERFLOW);
    L.length=0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    ElemType *p, *q;
    if (i<1 || i>L.length+1)   
        return ERROR;
    
    if (L.length >= L.listsize) {
    ElemType *newbase;
    newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
    if (!newbase)
        return LOVERFLOW;
 
    L.elem = newbase;
    L.listsize += LISTINCREMENT;
    }
 
    q = &(L.elem[i-1]);  
 
    /* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
    for (p=&(L.elem[L.length-1]); p>=q; --p) *(p+1)=*(p);
 
    *q = e;
    L.length++;
    return OK;
}
 
Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    ElemType *p, *q;
    if (i<1 || i>L.length+1)   
        return ERROR;
 
    p = &(L.elem[i-1]);         //指向第i个元素
    e=*p;
    q = L.elem + L.length -1;
 
    for(++p;p <= q;++p) *(p-1)=*(p);
    --L.length;
    return OK;
}
 
 
Status myunique_Sq(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        for(int j=i+1;j<L.length;)
        {
            if(L.elem[i]==L.elem[j])
            {
                int e;
                ListDelete_Sq(L,j+1,e);
            }
            else
            {
                j++;
            }
        }
    }
    return OK;
}
 
int main()
{
    SqList L;
    InitList_Sq(L);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        ListInsert_Sq(L,L.length+1,tmp);
    }
    myunique_Sq(L);
    for(int i=0;i<L.length;i++)
    {
        printf("%d ",L.elem[i]);
    }
 
    return 0;
}
