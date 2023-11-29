/*一元多项式相加相乘*/
#include <bits/stdc++.h>
using namespace std;
 
typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2        
 
typedef struct{
    int coef;
    int expn;
}term,ElemType;
 
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
 
typedef LinkList polynomial;
 
Status CreatePolyn(polynomial &L,int num)
{
    L=(LinkList)malloc(sizeof(LNode));
    if(!L) return ERROR;
    L->next = NULL;
    for(int i=1;i<=num;i++)
    {
        ElemType t;
        scanf("%d %d",&t.coef,&t.expn);
        LinkList pos=L;
        LinkList s;
        s=(LinkList)malloc(sizeof(LNode));
        if(!s) return ERROR;
        s->data=t;
        
        for(;pos->next;pos=pos->next)
        {
            if((pos->next)->data.expn>t.expn) break;
        }
        
        s->next=pos->next;
        pos->next=s;
    }
    return OK;
}
 
Status AddPolyn(polynomial &pa,polynomial &pb,polynomial &result)
{
    polynomial p1,p2;
    CreatePolyn(result,0);
    LinkList pos=result;
    p1=pa->next;
    p2=pb->next;
    
    for(;p1 && p2;)
    {
        /*建立新的节点*/
        LinkList s;
        s=(LinkList)malloc(sizeof(LNode));
        if(!s) return ERROR;
 
        if(p1->data.expn<p2->data.expn){
            s->data=p1->data;
            pos->next=s;
            pos=pos->next;
            p1=p1->next;
        }
        else if(p1->data.expn>p2->data.expn)
        {
            s->data=p2->data;
            pos->next=s;
            pos=pos->next;
            p2=p2->next;
        }
        else
        {
            if(p1->data.coef+p2->data.coef!=0)
            {
              s->data.expn=p1->data.expn;
              s->data.coef=p1->data.coef+p2->data.coef;
              pos->next=s;
              pos=pos->next;
            }
            else
                free(s);
            p1=p1->next;
            p2=p2->next;
        }
    }
    
    if(p1 || p2)
    {
        if(p1)
        {
            for(;p1;)
            {
                LinkList s;
                s=(LinkList)malloc(sizeof(LNode));
                if(!s) return ERROR;
                s->data=p1->data;
                pos->next=s;
                pos=pos->next;
                p1=p1->next;
            }
        }
        if(p2)
        {
            for(;p2;)
            {
                LinkList s;
                s=(LinkList)malloc(sizeof(LNode));
                if(!s) return ERROR;
                s->data=p2->data;
                pos->next=s;
                pos=pos->next;
                p2=p2->next;
            }
        }
    }
    return OK;
}
 
 
Status MultiplyPolyn(polynomial pa,polynomial pb,polynomial &result)
{
    polynomial p1,p2,p3;
    CreatePolyn(p3,0);
    CreatePolyn(result,0);
    LinkList pos=result;
    p1=pa->next;
    p2=pb->next;
 
    for(;p1;)
    {    
        pos=result;
        p2=pb->next;
        for(;p2;)
        {
            ElemType t;
            t.coef=p1->data.coef*p2->data.coef;
            t.expn=p1->data.expn+p2->data.expn;
            for(;pos->next;pos=pos->next)
            { 
               if((pos->next)->data.expn>t.expn)
               {
                  LinkList s;
                  s=(LinkList)malloc(sizeof(LNode));
                  if(!s) return ERROR;
                  s->data=t;
                  s->next=pos->next;
                   pos->next=s;
                  break;
               }
               if((pos->next)->data.expn==t.expn)
               { 
                    (pos->next)->data.coef+=t.coef;
                    break;
               }
            }
            if(!(pos->next))
            {
                LinkList s;
                s=(LinkList)malloc(sizeof(LNode));
                if(!s) return ERROR;
                s->data=t;
                s->next=pos->next;
                 pos->next=s;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
 
 
    //除去为0的节点
    pos=result;
    for(;pos->next;pos=pos->next)
    {
        if((pos->next)->data.coef==0)
        {
            pos->next=(pos->next)->next;
        }
    }
    
    return OK;
}
 
Status PrintPolyn(polynomial p)
{
    polynomial pos=p->next;
    for(;pos;pos=pos->next)
    {    
        printf("%d %d ",pos->data.coef,pos->data.expn);
    }
    printf("\n");
    return OK;
}
 
int main()
{
    int n,m,r;
    polynomial p,q;
    scanf("%d",&m);
    CreatePolyn(p,m);
    
    scanf("%d",&n);
    CreatePolyn(q,n);
    scanf("%d",&r);
    if(r==0)
    {
        polynomial result=NULL;
        AddPolyn(p,q,result);
        PrintPolyn(result);
    }
    if(r==1)
    {
        polynomial result=NULL;
        MultiplyPolyn(p,q,result);
        PrintPolyn(result);
    }
    if(r==2)
    {
        polynomial result1=NULL,result2=NULL;
        AddPolyn(p,q,result1);
        PrintPolyn(result1);
        MultiplyPolyn(p,q,result2);
        PrintPolyn(result2);
    }
 
    return 0;
}