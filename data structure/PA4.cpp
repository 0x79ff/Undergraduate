#include <bits/stdc++.h>
using namespace std;
//欧拉一笔画问题 无向图 邻接矩阵存储 dfs 起点为数字1

int n;
const int maxn = 100+10;
int g[maxn][maxn];
int degree[maxn];
int odd_degree_num,arc_num;

//图的建立
void Build()
{     
    //输入以及错误处理
    for (;;){
        printf("请输入图的顶点数目n (1<=n<=100)\n");
        int ret = scanf("%d", &n);
        if (ret == 1 && (n >= 1 && n <= 100)) break;
        else if (ret == 1 && (n < 1 || n > 100)) continue;
        else
            while (getchar() != '\n') ;
    }
    printf("请输入%d x %d的邻接矩阵来表示该图\n",n,n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&g[i][j]);
            if(g[i][j] == 1){
                degree[i]++;
                if(i<j) arc_num++;//避免一条边重复计算
            }
        }
    }
}

//判断能否一笔画 能则返回1 否则0
int judge()
{
    for(int i=1;i<=n;i++)
        if(degree[i]%2==1) 
            odd_degree_num++;
    if((degree[1]%2==1 && odd_degree_num == 2) || odd_degree_num == 0) return 1;
    return 0;
}

int ans[maxn];//用数组存储当前的结果
int len_ans;

//dfs 采用递归的方式实现
void dfs(int pos)
{
    //终止条件 所有边遍历一遍
    //此时输出的顶点的数目应该为图中边的数量+1
    if(len_ans == arc_num + 1){
        for(int i=0;i<len_ans;i++) printf("%d ",ans[i]);
        printf("\n");
    }
 
    //循环所有相连边 循环顺序决定了序列中顶点顺序递增
    for(int i=1;i<=n;i++){
        if(g[pos][i] == 1){
            g[pos][i] = g[i][pos] = 0;//递归 
            ans[len_ans++] = i;//更新状态
            dfs(i);
            g[pos][i] = g[i][pos] = 1;//回溯
            len_ans--;//更新状态
        }
    }
}

int main()
{
    Build();
    if(judge() == 0){
        printf("该图从顶点1开始不能一笔画!\n");
        return 0;
    }
    else{
        printf("该图从顶点1开始能够实现一笔画!\n");
        printf("所有一笔画序列如下(按照顶点递增顺序排列):\n");
        ans[len_ans++] = 1;
        dfs(1);//进行深度优先搜索
    }
    return 0;
}