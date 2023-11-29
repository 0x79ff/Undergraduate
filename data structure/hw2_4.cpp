#include <bits/stdc++.h>
using namespace std;
int n,m,ans;
int a[1000+10][1000+10];

const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

typedef struct{
    int x;
    int y;
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


void bfs(int xx,int yy)
{
    int is_border=true;
    LinkQueue Q;InitQueue(Q);
    Qelemtype e;
    if(xx>1 && xx<n && yy>1 && yy<m) is_border=false;
    e.x=xx;e.y=yy;
    EnQueue(Q,e);
    a[e.x][e.y]=0;
    for(;!Empty(Q);){
        Qelemtype pos;
        DeQueue(Q,pos);
        //cout<<pos.x<<' '<<pos.y<<endl;
        for(int i=0;i<4;i++)
        {
            int x1=pos.x+dx[i];
            int y1=pos.y+dy[i];
            //cout<<"x1"<<x1<<' '<<"y1"<<y1<<endl;
            if(x1>=1 && x1<=n && y1>=1 && y1<=m && a[x1][y1]==1){//没有超出区域 
                if(x1>1 && x1<n && y1>1 && y1<m) is_border=false;
                 e.x=x1;e.y=y1;
                 EnQueue(Q,e);
                 a[e.x][e.y]=0;
            }
        }
    }
    if(!is_border) ans++;

    Destroy(Q);
    return ;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
           scanf("%d",&(a[i][j]));
    
     for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]==0) continue;
            else bfs(i,j); 
        }
    }
    printf("%d",ans);
    return 0;
}