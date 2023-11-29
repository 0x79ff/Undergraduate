#include <bits/stdc++.h>
using namespace std;
//邻接矩阵，最小生成树

const int maxn = 100+10;

int m,n;//边，顶点
int g[maxn][maxn];//邻接矩阵

void build_gragh()
{
    scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
            scanf("%d",&g[i][j]);
        }
	}
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d %d",&x,&y);
        g[x][y] = g[y][x] =0;
    }
}

void Prim()
{
    int ans = 0;
    struct{
        int adjvex;
        int lowcost;//为-1表示在u中
    }closedge[maxn];
    //init
    for(int i=1;i<=n;i++)
        if(i!=1) closedge[i]={1,g[1][i]};
    closedge[1].lowcost = -1;

    //merge n-1
    for(int i=1;i<=n-1;i++){
        int k;
        int mindis = 2000;
        for(int j=1;j<=n;j++){
            if(closedge[j].lowcost!=-1 && closedge[j].lowcost<mindis){
                mindis = closedge[j].lowcost;
                k = j;
            }
        }
        //update
        ans+=closedge[k].lowcost;
        for(int j=1;j<=n;j++){
            if(g[j][k]<closedge[j].lowcost){
                closedge[j].lowcost = g[j][k];
            }
        }
        closedge[k].lowcost = -1;
        
    }
    printf("%d",ans);
}

int main()
{
	build_gragh();
    Prim();
    return 0;
}