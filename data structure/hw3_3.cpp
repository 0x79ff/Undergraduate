//表达式树
#include <bits/stdc++.h>
using namespace std;

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

//优先级判断
//顺序为 + - * / ( ) #
const char priority[10][10]={ {'>', '>', '<', '<', '<', '>', '>'},
                              {'>', '>', '<', '<', '<', '>', '>'},
                              {'>', '>', '>', '>', '<', '>', '>'},
                              {'>', '>', '>', '>', '<', '>', '>'},
                              {'<', '<', '<', '<', '<', '=', ' '},
                              {'>', '>', '>', '>', ' ', '>', '>'},
                              {'<', '<', '<', '<', '<', ' ', '='}};

int Mapping(char cc)
{
    if(cc=='+') return 0;
    if(cc=='-') return 1;
    if(cc=='*') return 2;
    if(cc=='/') return 3;
    if(cc=='(') return 4; 
    if(cc==')') return 5;
    if(cc=='#') return 6;
    return -1;
}

//c1是栈顶的，c2是刚入栈的
char Judge_priority(char c1,char c2)
{
    return priority[Mapping(c1)][Mapping(c2)];
}                             


const int maxn=50+10;

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
//

//
typedef struct{
    int pos;
    int dp;
    int tpos;
    char ch;
}Point;

typedef Point Qelemtype;
typedef struct QNode{
    Qelemtype data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front) exit(LOVERFLOW);
    Q.front->next=NULL;
    return OK;
}

Status EnQueue(LinkQueue &Q,Qelemtype e)
{
    //插入新的队尾元素
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(LOVERFLOW);
    p->data = e; p->next = NULL;
    Q.rear->next=p;
    Q.rear = p;
    return OK;
}

Status DeQueue(LinkQueue &Q,Qelemtype &e)
{
    //删除队头元素，并用e返回
    if(Q.front==Q.rear) return ERROR;
    QueuePtr p;p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p) Q.rear=Q.front;//防止尾结点被释放
    free(p);
    return OK;
}

int Empty(LinkQueue Q)
{
    if(Q.front==Q.rear) return TRUE;
    else return FALSE;
}
////////////


typedef char Belemtype;
typedef struct {
    Belemtype data='\0';
    int lchild=-1;
    int rchild=-1;
}BinaryTree;

Status BuildBiTree(string &a,BinaryTree *t,int &root)
{
    a='#'+a+'#';
    Sqstack sPTR,sPND;//运算数，运算符号
    Initstack(sPTR);
    Initstack(sPND);
    int pos=0;
    for(int i=0;i<a.length();i++) t[pos++].data = a[i];
    for(int i=0;i<a.length();i++)
    {
        if(a[i]>='a' && a[i]<='z')  Push(sPTR,i);
        else{
               if(Empty(sPND)){
                Push(sPND,i);
                continue;
               } 
               Selemtype e;Gettop(sPND,e);

               if(Judge_priority(t[e].data,a[i])=='<')  Push(sPND,i);//优先级大先进栈

               else if(Judge_priority(t[e].data,a[i])=='=') Pop(sPND,e);//优先级相等消去

               else if(Judge_priority(t[e].data,a[i])=='>') //优先级小进行内部运算
               {
                 Pop(sPND,e);
                 int lc,rc;
                 Pop(sPTR,rc);
                 Pop(sPTR,lc);
                 t[e].lchild = lc;
                 t[e].rchild = rc;
                 //入栈，补充运算数栈，同时更新根节点
                 root = e;
                 Push(sPTR,e);
                 i--;
               }
        }
    }
    return OK;
}


void solve_maxdeep(BinaryTree *t,int pos,int dp,int &maxdeep)
{
    if(t[pos].lchild!=-1) solve_maxdeep(t,t[pos].lchild,dp+1,maxdeep);    
    if(t[pos].rchild!=-1) solve_maxdeep(t,t[pos].rchild,dp+1,maxdeep);
    if(t[pos].lchild==-1 && t[pos].rchild==-1){
        if(dp>maxdeep) maxdeep=dp;
    }
}

Status PrintBiTree(BinaryTree *t,int root)
{
    //先求树的深度
    int maxdeep=0;
    solve_maxdeep(t,root,1,maxdeep);
    
    //之后用队列bfs搜索输出
    LinkQueue q1,q2;
    InitQueue(q1);InitQueue(q2);
    //根入队列
    Qelemtype p;
    p.pos=pow(2,maxdeep-1);
    p.dp=1;
    p.tpos=root;
    p.ch=t[root].data;

    EnQueue(q1,p);
    int pre_deep = 1;
    int pre_pos = 0;
    while(!Empty(q1)){
        DeQueue(q1,p);
        if(p.dp!=pre_deep){
            //清零，上一行结束
            pre_pos=0;
            printf("\n");

            //输出所有斜杠
            int pre_pos2=0;
            if(!Empty(q2)){
                while(!Empty(q2)){
                    Qelemtype tmp;
                    DeQueue(q2,tmp);
                    for(int j=1;j<=tmp.pos-pre_pos2-1;j++) printf(" ");
                    printf("%c",tmp.ch);
                    pre_pos2=tmp.pos; 
                }
                printf("\n");
            }
        }
        pre_deep = p.dp;

        for(int j=1;j<=p.pos-pre_pos-1;j++) printf(" ");
        printf("%c",p.ch);
        pre_pos=p.pos; 
                
        if(t[p.tpos].lchild!=-1){
            Qelemtype tmp;
            tmp.pos=p.pos-1;
            tmp.ch='/';
            EnQueue(q2,tmp);
            tmp.pos=p.pos - pow(2,maxdeep - p.dp - 1);
            tmp.dp = p.dp+1;
            tmp.tpos = t[p.tpos].lchild;
            tmp.ch = t[t[p.tpos].lchild].data;
            EnQueue(q1,tmp);
        }
        if(t[p.tpos].rchild!=-1){
            Qelemtype tmp;
            tmp.pos=p.pos+1;
            tmp.ch='\\';
            EnQueue(q2,tmp);
            tmp.pos=p.pos + pow(2,maxdeep - p.dp - 1);
            tmp.dp=p.dp+1;
            tmp.tpos = t[p.tpos].rchild; 
            tmp.ch=t[t[p.tpos].rchild].data;
            EnQueue(q1,tmp);
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


int Calculation(BinaryTree *t,int *b,int pos)
{
    //是运算符就要先分别算左右,字母直接返回结果
    if(!(t[pos].data>='a' && t[pos].data<='z')){
        if(t[pos].data == '+') return Calculation(t,b,t[pos].lchild) + Calculation(t,b,t[pos].rchild);
        if(t[pos].data == '-') return Calculation(t,b,t[pos].lchild) - Calculation(t,b,t[pos].rchild);
        if(t[pos].data == '*') return Calculation(t,b,t[pos].lchild) * Calculation(t,b,t[pos].rchild); 
        if(t[pos].data == '/') return Calculation(t,b,t[pos].lchild) / Calculation(t,b,t[pos].rchild);  
    }
    else return b[t[pos].data-'a'];
    return -1;
}

int main()
{
    BinaryTree t[maxn];
    int root;
    //读入数据
    string a;
    cin>>a;
    int b[50]={ 0 };
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){
        char tmp_ch[5];
        int tmp_num;
        scanf("%s %d",tmp_ch,&tmp_num);
        b[tmp_ch[0]-'a']=tmp_num;
    }
    BuildBiTree(a,t,root);
    //输出后缀表达式
    PostOrderTraverse(t,root);
    printf("\n");
    //画树 
    PrintBiTree(t,root);
    printf("\n");
    //求值，还是中序遍历加栈
    printf("%d",Calculation(t,b,root));
    return 0;
}