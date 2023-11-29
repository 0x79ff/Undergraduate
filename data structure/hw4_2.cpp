#include <bits/stdc++.h>
using namespace std;
//邻接表，尾插法

//栈和队列

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    
//


typedef struct{
    int pos;
    int dp;
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

Status Destroy(LinkQueue &Q)
{
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
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
//

const int maxn = 2e3+10;
int vis[maxn];

typedef struct node		
{
	int adjvex;			//该边指向的结点位置
	struct node* nextarc;	//指向下一条边
	//int info;
}ArcNode;

//建立顶点表
typedef struct
{
	int data;
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
    scanf("%d %d",&g.vexnum,&g.arcnum);
	for(int i=1;i<=g.vexnum;i++){
		g.vertices[i].firstarc = NULL;
		g.vertices[i].data = i;
	}
    for(int i=1;i<=g.arcnum;i++){
        int a,b;
        scanf("%d %d",&a,&b);    
		//无向图 头插 begin
		ArcNode *s1 =(ArcNode*)malloc(sizeof(ArcNode));
		s1->adjvex = b;
        s1->nextarc = g.vertices[a].firstarc;
        g.vertices[a].firstarc = s1;
		
        ArcNode *s2 =(ArcNode*)malloc(sizeof(ArcNode));
		s2->adjvex = a;
		s2->nextarc = g.vertices[b].firstarc;
        g.vertices[b].firstarc = s2;
		//end
    }
}


//bfs
int bfs(int x)
{
    int ret = 0;

    memset(vis,0,sizeof(vis));
	LinkQueue Q;InitQueue(Q);
    vis[x]=1;
    EnQueue(Q,{x,0});
    ret++;
    
    int dp = 1;
    for (;!Empty(Q);)
    {
        Point t;
        DeQueue(Q, t);
        if(t.dp < 6){
            ArcNode *p = g.vertices[t.pos].firstarc;
            for (; p; p = p->nextarc)
            {
                int x = p->adjvex;
                if (vis[x] == 0)
                {
                    vis[x] = 1;
                    EnQueue(Q, {x,t.dp+1});
                    ret++;
                }
            }
        }
    }
    return ret;
}


int main()
{
	build_gragh();
	for(int i=1;i<=g.vexnum;i++){
        printf("%d: %.2f%%\n",i,(bfs(i)+0.0)*100/g.vexnum);
    }
    return 0;
}