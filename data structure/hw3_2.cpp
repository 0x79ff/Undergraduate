#include <bits/stdc++.h>
using namespace std;

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

const int maxn=83+10;

//栈的相关操作
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Selemtype;
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
////////////

//树的操作
typedef char Belemtype;
typedef struct {
    Belemtype data='\0';
    int lchild=-1;
    int rchild=-1;
}BinaryTree;


Status BuildBiTree(BinaryTree *t)
{
    //中序遍历，通过栈创建二叉树
    Sqstack s;
    Initstack(s);
    int n;scanf("%d",&n);
    int pos=0;
    Selemtype p1=0;
    int last_pop=0;
    for(int i=0;i<2*n;i++)
    {
        char a[10];scanf("%s",a);
        if(strcmp(a,"push")==0){
            pos++;
            char tmp[5];scanf("%s",tmp);
            t[pos].data=tmp[0];
            if(pos!=1){//排除根结点
                if(!last_pop) {
                Gettop(s,p1);
                t[p1].lchild=pos;//上一个节点的左结点
                }
                else{
                    t[p1].rchild=pos;
                }
            }
            Push(s,pos);
            last_pop=0;
        }
        else{
            Pop(s,p1);
            last_pop=1;
        }
    }
        
    return OK;
}

Status PostOrderTraverse(BinaryTree *t,int pos)
{
    //后序遍历输出二叉树
    if(t[pos].data!='\0'){
        if(t[pos].lchild!=-1) PostOrderTraverse(t,t[pos].lchild);
        if(t[pos].rchild!=-1) PostOrderTraverse(t,t[pos].rchild);
        printf("%c",t[pos].data);
    }
    return OK;
}


int main()
{
    BinaryTree t[maxn];
    BuildBiTree(t);
    PostOrderTraverse(t,1);       
    return 0;
}