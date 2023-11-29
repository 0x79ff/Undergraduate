#include <bits/stdc++.h>
using namespace std;

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

const int maxn=10100+10;
typedef char Qelemtype;
typedef struct {
    Qelemtype data;
    int lchild=-1;
    int rchild=-1;
}BinaryTree;
BinaryTree t1[4*maxn],t2[4*maxn];
int root1,root2;
int maxdeep1,maxdeep2;
int is_not_root[maxn];

Status InitBiTree(BinaryTree *t,int &root)
{
    //输入创建二叉树
    int n;scanf("%d",&n);
    memset(is_not_root,0,sizeof(is_not_root));//is_root用来寻找根节点
    
    for(int i=0;i<n;i++){
        char input0[10],input1[10],input2[10];
        scanf("%s %s %s",input0,input1,input2);
        t[i].data=input0[0];
        if(input1[0]!='-'){
            t[i].lchild=atoi(input1);
            is_not_root[t[i].lchild]=1;
        }
        if(input2[0]!='-'){
            t[i].rchild=atoi(input2);
            is_not_root[t[i].rchild]=1;
        }
    }
    for(int i=0;i<n;i++){
        if(is_not_root[i]==0){
            root=i;
            break;
        }
    }
    return OK;    
}

int check(int pos1,int pos2)
{
    //递归判断二叉树是否同构
    if(t1[pos1].data!=t2[pos2].data) return FALSE;//当前节点值不相同
    int childnum1=(t1[pos1].lchild!=-1)+(t1[pos1].rchild!=-1);//孩子的数目
    int childnum2=(t2[pos2].lchild!=-1)+(t2[pos2].rchild!=-1); 
    if(childnum1==0 && childnum2==0) return TRUE;//结束标志
    if(childnum1!=childnum2) return FALSE;
    //继续向下搜索，深度要增加
    if(childnum1==1)//1种可能
        return check((t1[pos1].lchild==-1?t1[pos1].rchild:t1[pos1].lchild),(t2[pos2].lchild==-1?t2[pos2].rchild:t2[pos2].lchild));
    else//4种可能
        return (check(t1[pos1].lchild,t2[pos2].lchild) && check(t1[pos1].rchild,t2[pos2].rchild))
        || (check(t1[pos1].rchild,t2[pos2].lchild) && check(t1[pos1].lchild,t2[pos2].rchild));
}

void solve_maxdeep(BinaryTree *t,int pos,int dp,int &maxdeep)
{
    if(t[pos].lchild!=-1) solve_maxdeep(t,t[pos].lchild,dp+1,maxdeep);    
    if(t[pos].rchild!=-1) solve_maxdeep(t,t[pos].rchild,dp+1,maxdeep);
    if(t[pos].lchild==-1 && t[pos].rchild==-1){
        if(dp>maxdeep) maxdeep=dp;
    }
}

int main()
{
    InitBiTree(t1,root1);
    InitBiTree(t2,root2);
    if(check(root1,root2)) printf("Yes\n");
    else printf("No\n");

    solve_maxdeep(t1,root1,1,maxdeep1);
    solve_maxdeep(t2,root2,1,maxdeep2);
    printf("%d\n",maxdeep1);
    printf("%d\n",maxdeep2);
    return 0;
}
