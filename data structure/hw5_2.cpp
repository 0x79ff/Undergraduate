#include <bits/stdc++.h>
using namespace std;
//二叉排序树BST 能有相同元素

const int maxn = 1e3+50;
typedef int Belemtype;
typedef struct Bithrnode{
    Belemtype data;
    int num;
    struct Bithrnode *lchild,*rchild;
}Bithrnode,*Bithrtree;

void Init(Bithrtree &pos)
{
    pos->data = 0;
    pos->num = 0;
    pos->lchild = NULL;
    pos->rchild = NULL;
}

void insert_num(Bithrtree &pos,int x)
{
    if(pos == NULL){
        pos = (Bithrtree)malloc(sizeof(Bithrnode));
        if(!pos) exit(-1);
        Init(pos);
        pos->data = x;
        pos->num = 1;
        return ;
    }
    if (pos != NULL && pos->data == x)
    {
        (pos->num)++;
        return;
    }
    if (pos->data < x)
    {
        insert_num(pos->rchild, x);
    }
    if (pos->data > x)
    {
        insert_num(pos->lchild, x);
    }
}

void delete_num(Bithrtree &pos,int x)
{
    if(pos == NULL){
        printf("None\n");
        return ;
    }
    if(pos->data == x){
        //分类讨论
        if(pos->num > 1) (pos->num)--;
        else{
            if (pos->lchild == NULL && pos->rchild == NULL){ // 叶子节点
                Bithrtree q = pos;
                pos = NULL;
                free(q);
            }
            else if (pos->lchild == NULL && pos->rchild != NULL)
            {
                Bithrtree q = pos;
                pos = pos->rchild;
                free(q);
            }
            else if (pos->lchild != NULL && pos->rchild == NULL)
            {
                Bithrtree q = pos;
                pos = pos->lchild;
                free(q);
            }
            else
            { // 最复杂情况
                Bithrtree q = pos;
                Bithrtree s = pos->lchild;
                while (s->rchild)
                {
                    q = s;
                    s = s->rchild;
                }
                pos->data = s->data;
                pos->num = s->num;
                if (q != pos)
                    q->rchild = s->lchild;
                else
                    q->lchild = s->lchild;
                free(s);
            }
        }
    }
    else if(pos->data < x){
        delete_num(pos->rchild,x);
    }
    else{
        delete_num(pos->lchild,x);
    }
}

void count_num(Bithrtree pos,int x)
{
    //中序遍历
    if(pos == NULL){
        printf("0\n");
        return ;
    }
    if(pos->data == x){
        printf("%d\n",pos->num);
    }
    else if(pos->data < x){
        count_num(pos->rchild,x);
    }
    else{
        count_num(pos->lchild,x);
    }
}

void query_min(Bithrtree t)
{
    //中序遍历第一个值
    Bithrtree p = t;
    if(p==NULL){
        printf("-1\n");    
        return;
    }
    while(p->lchild) p=p->lchild;
    printf("%d\n",p->data);
}

void query_max(Bithrtree t)
{
    //中序遍历最后一个值
    Bithrtree p = t;
      if(p==NULL){
        printf("-1\n");    
        return;
    }
    while(p->rchild) p=p->rchild;
    printf("%d\n",p->data);
}


int intree;
Bithrtree pre;
void query_pre(Bithrtree pos,int x)
{
    if(pos->lchild) query_pre(pos->lchild,x);
    //中序遍历求x前面的即可
    if(pos->data >= x && intree == 0){
        intree = 1;
        if(pre == NULL) printf("None\n");
        else printf("%d\n",pre->data);
        return;
    }
    pre = pos;
    if(pos->rchild) query_pre(pos->rchild,x);
}

int main()
{
    Bithrtree t = NULL;
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int opt;scanf("%d",&opt);
        int x;
        if(opt != 4) scanf("%d",&x);
        if(opt == 1) insert_num(t,x);
        else if(opt == 2) delete_num(t,x);
        else if(opt == 3) count_num(t,x);
        else if(opt == 4) query_min(t);
        else if(opt == 5) {
            intree = 0;
            pre=NULL;
            query_pre(t,x);
            if(!intree) query_max(t);
        }

    }
    return 0;
}
