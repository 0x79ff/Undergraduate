#include <bits/stdc++.h>
using namespace std;
 
typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    
 
 
typedef int Elemtype;
typedef struct CSNode{
    //Elemtype data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;
 
Status Initcstree(CSTree &t)
{
    t=(CSNode*)malloc(sizeof(CSNode));
    if(!t) exit(LOVERFLOW);
    t->firstchild = NULL;
    t->nextsibling = NULL;
    return OK;
} 
 
 
 
//栈的相关操作
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef CSTree Selemtype;
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
 
Status Gettop(Sqstack s,Selemtype &e)
{
    if(s.top==s.base) return ERROR;
    e=*(s.top - 1);
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
/////
 
 
int deep1 = 0;
int deep2 = 0;
 
void dfs(CSTree t,int num)
{
    deep2=max(deep2,num);
    if(t->firstchild) dfs(t->firstchild,num+1);
    if(t->nextsibling) dfs(t->nextsibling,num+1);
}
 
void Solution(string a,int i)
{
    //初始化
    deep1=0;
    deep2=0;
    Sqstack s; Initstack(s);
    CSTree t; Initcstree(t);
    Push(s,t);//根节点
    
    int dp=0;
    int last_u=0;
    CSTree tmptop=NULL;
    for(int i=0;i<a.length();i++){
        if(a[i]=='d'){
            //创建新节点，建立与双亲关系，入栈
            CSTree p;
            Initcstree(p);
            
            if(last_u == 0){
                Gettop(s,tmptop);
                tmptop->firstchild = p;
            }
            else{
                tmptop->nextsibling = p;
            }
            Push(s,p);
            last_u = 0;
 
            dp++;
            deep1=max(deep1,dp);
        }
        if(a[i]=='u'){
            //出栈
            Pop(s,tmptop);
            last_u = 1;
 
            dp--;
        }
    }
    dfs(t,0);
    printf("Tree %d: %d => %d\n\n",i,deep1,deep2);
}
 
int main()
{
    string a;
    for(int i=1;cin>>a;i++){
        if(a=="#") break;
        else Solution(a,i);
    }
    return 0;
}