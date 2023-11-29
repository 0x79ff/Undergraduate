#include <bits/stdc++.h>
using namespace std;
//两次拓扑排序 判断环

//stack
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
//stack end

const int maxk = 400+10;
int m,n,k;
int in_degree1[maxk],in_degree2[maxk];
int pos1[maxk],pos2[maxk];
int ans[maxk][maxk];

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
}VNode,AdjList[maxk];

//建立连接表
typedef struct
{
	AdjList vertices;//邻接表的顶点存放数组
	int vexnum,arcnum;
}ALGragh;

ALGragh g1,g2;
    
void build_gragh()
{
    scanf("%d %d %d",&k,&n,&m);
    g1.vexnum = k;g1.arcnum = n;
    g2.vexnum = k;g2.arcnum = m;
    
    for(int i=1;i<=g1.vexnum;i++){
		g1.vertices[i].firstarc = NULL;
		g1.vertices[i].data = i;
	}
    for(int i=1;i<=g1.arcnum;i++){
        int a,b;
        scanf("%d %d",&a,&b);    
		//无向图 头插 维护入度begin
        in_degree1[b]++;
		ArcNode *s =(ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = b;
        s->nextarc = g1.vertices[a].firstarc;
        g1.vertices[a].firstarc = s;
		//end
    }

    for(int i=1;i<=g2.vexnum;i++){
		g2.vertices[i].firstarc = NULL;
		g2.vertices[i].data = i;
	}
    for(int i=1;i<=g2.arcnum;i++){
        int a,b;
        scanf("%d %d",&a,&b);    
		//无向图 头插 维护入度 begin
        in_degree2[b]++;
		ArcNode *s =(ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = b;
        s->nextarc = g2.vertices[a].firstarc;
        g2.vertices[a].firstarc = s;
		//end
    }

}

int topplogicalsort(ALGragh g,int *pos,int *in_degree)
{
    Sqstack s;Initstack(s);
    for(int i=1;i<=g.vexnum;i++)
        if(!in_degree[i]) Push(s,i);
    int count = 0;
    for(;!Empty(s);){
        int t;Pop(s,t);
        count++;
        pos[t]=count;
        ArcNode *p = g.vertices[t].firstarc;
        for (; p; p = p->nextarc)
        {
            int x = p->adjvex;
            in_degree[x]--;
            if(in_degree[x]==0) Push(s,x);
        }
    }
    Clear(s);
    if(count < g.vexnum) return FALSE;
    return TRUE;
}

void print_ans()
{
    for(int i=1;i<=k;i++)
        ans[pos1[i]][pos2[i]] = i;
    
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++){
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    build_gragh();
    if(topplogicalsort(g1,pos1,in_degree1)==FALSE){
        printf("-1");
        return 0;
    }
    if(topplogicalsort(g2,pos2,in_degree2)==FALSE){
        printf("-1");
        return 0;
    }
    print_ans();
    return 0;
}