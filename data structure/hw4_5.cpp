#include <bits/stdc++.h>
using namespace std;
//关键路径 aov网络 事件在顶点

//stack begin
typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

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

Status Clear(Sqstack &s)
{
    s.top=s.base;
    return OK;
}
//end


const int maxn = 100+10;
int ve[maxn],vl[maxn];//最早开始时间 最迟发生时间
int in_degree[maxn];

typedef struct node		
{
	int adjvex;			//该边指向的结点位置
	struct node* nextarc;	//指向下一条边
	//int info;
}ArcNode;

//建立顶点表
typedef struct
{
	int time;
	ArcNode *firstarc;
}VNode,AdjList[maxn];

//建立连接表
typedef struct
{
	AdjList vertices;//邻接表的顶点存放数组
	int vexnum,arcnum;
}ALGragh;

ALGragh g;
    
void build_gragh()
{
    scanf("%d",&g.vexnum);
    for(int i=1;i<=g.vexnum;i++){
        int c;scanf("%d %d",&g.vertices[i].time,&c);
        in_degree[i] = c;
        for(int j=1;j <= c;j++){
            int b;scanf("%d", &b);
            //有向图 头插 b——>i
            ArcNode *s = (ArcNode *)malloc(sizeof(ArcNode));
            s->adjvex = i;
            s->nextarc = g.vertices[b].firstarc;
            g.vertices[b].firstarc = s;
            // end
        }
	}
}

void Aov_criticalpath()
{
    //有向图 关键路径
    //top排序
    Sqstack s,t;Initstack(s);Initstack(t);
    for(int i=1;i<=g.vexnum;i++)
        if(in_degree[i] == 0) Push(s,i);
    int max_time = 0;
    while(!Empty(s)){
        int j;Pop(s,j);Push(t,j);
        ArcNode *p = g.vertices[j].firstarc;
        for (; p; p = p->nextarc)
        {
            int k = p->adjvex;
            if( --in_degree[k] == 0) Push(s,k);
            if(ve[j] + g.vertices[j].time > ve[k]){
                ve[k] = ve[j] + g.vertices[j].time;
                max_time = max(max_time,ve[k]+g.vertices[k].time);
            }
        }
    }
    

    for(int i=1;i<=g.vexnum;i++){
        vl[i] = max_time;
        ve[i] += g.vertices[i].time;
    }
    
    while(!Empty(t)){
        int j;Pop(t,j);
        ArcNode *p = g.vertices[j].firstarc;
        for (; p; p = p->nextarc)
        {
            int k = p->adjvex;
            if(vl[k] - g.vertices[k].time < vl[j])
                vl[j] = vl[k] - g.vertices[k].time;
        }
    }
    
}

void print_ans()
{
    for(int i=1;i<=g.vexnum;i++){
        printf("%d %d\n",ve[i],(ve[i]==vl[i]?1:0));
    }
}

int main()
{
    build_gragh();
    Aov_criticalpath();
    print_ans();
    return 0;
}