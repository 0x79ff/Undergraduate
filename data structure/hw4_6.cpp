#include <bits/stdc++.h>
using namespace std;
//dijstar 

const int maxn = 1e3+10;
int h,r;
int vis[maxn],dis[maxn][maxn];

typedef struct node		
{
	int adjvex;			//该边指向的结点位置
	struct node* nextarc;	//指向下一条边
	int dis;
}ArcNode;

//建立顶点表
typedef struct
{
	int grass;
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
        g.vertices[i].grass = 0;
	}
    
    for(int i=1;i<=g.arcnum;i++){
        int x,y,w;
        scanf("%d %d %d",&x,&y,&w);    
		//无向图 头插 begin
		ArcNode *s1 =(ArcNode*)malloc(sizeof(ArcNode));
		s1->adjvex = y;
        s1->dis = w;
        s1->nextarc = g.vertices[x].firstarc;
        g.vertices[x].firstarc = s1;
		
        ArcNode *s2 =(ArcNode*)malloc(sizeof(ArcNode));
		s2->adjvex = x;
        s2->dis = w;
		s2->nextarc = g.vertices[y].firstarc;
        g.vertices[y].firstarc = s2;
		//end
    }

    scanf("%d %d",&h,&r);
    for(int i=1;i<=h;i++){
        int x;scanf("%d",&x);
        g.vertices[x].grass = 1;//此处有草
    }
}

struct distant{
  int id,id_dis;
  distant(int x,int y)
  {
    id=x,id_dis=y;
  }
};

//复杂度为mlogm的dijkstra算法 优先队列优化
bool operator<(const distant &x,const distant &y)
{
  return x.id_dis > y.id_dis;
}
priority_queue <distant> q;

void Dijstra()
{
    memset(dis,0x3f,sizeof(dis));
    for (int i = 1; i <= g.vexnum; i++)
    {
        memset(vis, 0, sizeof(vis));
        dis[i][i] = 0;
        q.push(distant(i, 0));
        while (!q.empty())
        {
            int q1 = q.top().id;
            q.pop();
            if (vis[q1])
                continue;
            vis[q1] = true;
            //遍历顶点所连的边
            ArcNode *p = g.vertices[q1].firstarc;
            for (; p; p = p->nextarc)
            {
                if (dis[i][p->adjvex] > dis[i][q1] + p->dis)
                {
                    dis[i][p->adjvex] = dis[i][q1] + p->dis;
                    q.push(distant(p->adjvex, dis[i][p->adjvex]));
                }
            }
        }
    }
}

void search()
{
    for(int i=1;i<=r;i++){
        int sta,end;scanf("%d %d",&sta,&end);
        int ans = 0x3fffffff;
        for (int i = 1; i <= g.vexnum; i++)
        {
            if (g.vertices[i].grass == 1)//有草 更新最小值
                ans = min(dis[sta][i] + dis[i][end],ans);
        }
        printf("%d\n",ans);
    }
}

int main()
{
    build_gragh();
    Dijstra();
    search();
    return 0;
}