#include <bits/stdc++.h>
using namespace std;

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

//树的操作
typedef enum{Link,ThRead} Pointertag;
typedef char Belemtype;
typedef struct Bithrnode{
    Belemtype data;
    Pointertag ltag,rtag;
    struct Bithrnode *lchild,*rchild;
}Bithrnode,*Bithrtree;


/*按照先序序列创建二叉树*/
Status CreateBithrtree(Bithrtree &t)
{
    char ch;scanf("%c",&ch);
    //if(ch=='\r' || ch == '\n') return;
    if(ch =='#') t=NULL;
    else{
        t=(Bithrnode*)malloc(sizeof(Bithrnode));
        t->ltag=Link;
        t->rtag=Link;
        t->lchild=NULL;
        t->rchild=NULL;
        if(!t) exit(LOVERFLOW);
        t->data = ch;
        CreateBithrtree(t->lchild);
        CreateBithrtree(t->rchild);
    }
    return OK;
}

Bithrtree pre;
Status InThReading(Bithrtree p)
{
    if(p){
        InThReading(p->lchild);
        if(!(p->lchild)){
            p->ltag = ThRead;
            p->lchild = pre;
        }
        if(!(pre->rchild)){
            pre->rtag = ThRead;
            pre->rchild = p;
        }
        pre=p;
        InThReading(p->rchild);
    }
    return OK;
}

/*中序遍历二叉树，将其线索化的过程*/
Status InOrderThReading(Bithrtree &thrt,Bithrtree t)
{
    thrt=(Bithrnode *)malloc(sizeof(Bithrnode));
    if(!thrt) exit(LOVERFLOW);
    thrt->ltag=Link;
    thrt->rtag=ThRead;
    thrt->rchild=thrt;
    
    if(!t) thrt->lchild=thrt;
    else{
        thrt->lchild=t;
        pre=thrt;
        InThReading(t);
        pre->rchild = thrt;
        pre->rtag = ThRead;
        thrt->rchild = pre;
    }
    return OK;
}

Status Output1(Belemtype e)
{
    printf("%c",e);
    return OK;
}

Status InOrderTraverse_Thr(Bithrtree t,Status (*Visit)(Belemtype e))
{
    Bithrtree p;
    p=t->lchild;
    for(;p!=t;){
        while(p->ltag==Link) p=p->lchild;
        if(!Visit(p->data)) return ERROR;
        while(p->rtag == ThRead && p->rchild!=t){
            p=p->rchild;
            if(!Visit(p->data)) return ERROR;
        }
        p=p->rchild;
    }
    return OK;
}


Status Output2(Bithrtree t)
{
    char tmp[5];scanf("%s",tmp);
    int count=0;
    Bithrnode *p,*q=NULL;//q为p前一个结点
    p=t->lchild;
    while(p!=t){
        while(p->ltag==Link) p=p->lchild;
        //输出
        if(p->data==tmp[0]){
            count++;
            //后继
            Bithrnode *r=p;
            if(r->rchild == t) printf("succ is NULL\n");
            else if(r->rtag == ThRead) printf("succ is %c%d\n",r->rchild->data,r->rchild->rtag);
            else{
                r=r->rchild;
                while(r->ltag==Link) r=r->lchild;
                printf("succ is %c%d\n",r->data,r->rtag);
            }
            //前驱
            if(q==NULL) printf("prev is NULL\n");
            else printf("prev is %c%d\n",q->data,q->ltag);
        }
        q=p;
        while(p->rtag == ThRead && p->rchild!=t){
            p=p->rchild;
            //输出
            if(p->data==tmp[0]){
               count++;
               //后继
               Bithrnode *r=p;
               if(r->rchild == t) printf("succ is NULL\n");
               else if(r->rtag == ThRead) printf("succ is %c%d\n",r->rchild->data,r->rchild->rtag);
               else{
                   r=r->rchild;
                   while(r->ltag==Link) r=r->lchild;
                   printf("succ is %c%d\n",r->data,r->rtag);
                   }
                //前驱
                if(q==NULL) printf("prev is NULL\n");
                else printf("prev is %c%d\n",q->data,q->ltag);
            }
            q=p;
        }
        p=p->rchild;
    }
    if(count==0) printf("Not found\n");
    return OK;
}


int main()
{
    Bithrtree t=NULL;
    Bithrtree thrt=NULL;
    CreateBithrtree(t);
    InOrderThReading(thrt,t);
    InOrderTraverse_Thr(thrt,Output1);
    printf("\n");
    Output2(thrt);
    

    return 0;
}