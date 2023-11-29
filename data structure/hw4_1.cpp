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

typedef int Qelemtype;
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

const int maxn = 1e4+100;
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
	for(int i=0;i<g.vexnum;i++){
		g.vertices[i].firstarc = NULL;
		g.vertices[i].data = i;
	}
    for(int i=1;i<=g.arcnum;i++){
        int a,b;
        scanf("%d %d",&a,&b);    
		//无向图 尾插法 begin
		ArcNode *s1 =(ArcNode*)malloc(sizeof(ArcNode));
		s1->adjvex = b;
		s1->nextarc = NULL;
		
		ArcNode *p = g.vertices[a].firstarc;
		if(p == NULL) g.vertices[a].firstarc = s1;
		else {
			while (p->nextarc)
			{
				p = p->nextarc;
			}
			p->nextarc = s1;
		}

        ArcNode *s2 =(ArcNode*)malloc(sizeof(ArcNode));
		s2->adjvex = a;
		s2->nextarc = NULL;
		
		p = g.vertices[b].firstarc;
		if(p == NULL) g.vertices[b].firstarc = s2;
		else {
			while (p->nextarc)
			{
				p = p->nextarc;
			}
			p->nextarc = s2;
		}
		//end
    }
}

void dfs(int pos)
{
	ArcNode *p = g.vertices[pos].firstarc;
	for (;p;p = p->nextarc)
    {
		int x=p->adjvex;
		if(vis[x]==0){
			vis[x] = 1;
		    printf(" %d",p->adjvex);
			dfs(x);
		}
	}
}

void print_gragh()
{
	
	for(int i=0;i<g.vexnum;i++){
		if(vis[i]==0){
			vis[i]=1;
			printf("{%d",i);
			dfs(i);
			printf("}");
		}
	}
	printf("\n");
	
	memset(vis,0,sizeof(vis));
	//bfs
	LinkQueue Q;InitQueue(Q);
	for(int i=0;i<g.vexnum;i++){
		if(vis[i]==0){
			vis[i]=1;
			EnQueue(Q,i);
			printf("{%d",i);
			for(;!Empty(Q);){
				int pos;
				DeQueue(Q,pos);
				ArcNode *p = g.vertices[pos].firstarc;
				for (; p; p = p->nextarc)
				{
					int x = p->adjvex;
					if (vis[x] == 0)
					{
						vis[x] = 1;
						printf(" %d", p->adjvex);
						EnQueue(Q,x);
					}
				}
			}
			printf("}");
		}
	}
	
}

int main()
{
	build_gragh();
	print_gragh();
    return 0;
}