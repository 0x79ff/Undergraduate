#include <bits/stdc++.h>
using namespace std;
 
//线性表，顺序实现
typedef struct Poker {
    char   type[10];
    char   num[5];
    } ElemType;
 
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2        
 
typedef int Status;
 
#define LIST_INIT_SIZE 400
#define LISTINCREMENT 10
 
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;
 
 
Status InitList_Poker(SqList &L)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem) exit(LOVERFLOW);
    L.length=0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
 
 
Status ListInsert_Poker(SqList &L, int i, ElemType e)
{
    ElemType *p, *q;
    if (i<1 || i>L.length+1)  //合理位置是1-length+1
        return ERROR;
    
    if (L.length >= L.listsize) {
    ElemType *newbase;
    newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
    if (!newbase)
        return LOVERFLOW;
 
    L.elem = newbase;
    L.listsize += LISTINCREMENT;
    }
 
    q = &(L.elem[i-1]);  
 
    /* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
    for (p=&(L.elem[L.length-1]); p>=q; --p)
    {
        memcpy(p+1, p, sizeof(ElemType));
    }
 
    memcpy(q, &e, sizeof(ElemType));
    L.length++;
    return OK;
}
 
 
Status ListDelete_Poker(SqList &L, int i, ElemType *e)
{
    ElemType *p, *q;
    if (i<1 || i>L.length)   
        return ERROR;
 
    p = &(L.elem[i-1]);         //指向第i个元素
    memcpy(e, p, sizeof(ElemType));
 
    q = L.elem + L.length -1;
 
    for(++p;p <= q;++p)
    {
        memcpy((p-1), p, sizeof(ElemType));
    }
    --L.length;
    return OK;
}
 
Status ListRevert_Poker(SqList &L)
{
    ElemType t;
    for(int i=0;i<L.length/2;i++)
    {
        memcpy(&t, L.elem+i, sizeof(ElemType));
        memcpy(L.elem+i,L.elem+L.length-i-1,sizeof(ElemType));
        memcpy(L.elem+L.length-i-1,&t,sizeof(ElemType));
    }
    return OK;
}
 
 
Status Print_Poker(SqList L)
{
    if(L.length==0)
    {
        printf("NULL\n");
    }
    else
    {
        for(int i=0;i<L.length;i++)
        {
            printf("%s %s\n",L.elem[i].type,L.elem[i].num);
        }
    }
    return OK;
}
 
 
bool lessorequal_Poker(char *cmp1,char *cmp2)
{
    int num1,num2;
    if(cmp1[0]=='1' && cmp1[1]=='0') num1=10;
    else if(cmp1[0]=='A') num1=1;
    else if(cmp1[0]>='2' && cmp1[0] <= '9') num1=cmp1[0]-'0';
    else if(cmp1[0]=='J') num1=11;
    else if(cmp1[0]=='Q') num1=12;
    else if(cmp1[0]=='K') num1=13;
    else ;
 
    if(cmp2[0]=='1' && cmp2[1]=='0') num2=10;
    else if(cmp2[0]=='A') num2=1;
    else if(cmp2[0]>='2' && cmp2[0] <= '9') num2=cmp2[0]-'0';
    else if(cmp2[0]=='J') num2=11;
    else if(cmp2[0]=='Q') num2=12;
    else if(cmp2[0]=='K') num2=13;
    else ;
 
    return num1<=num2;
}
 
 
Status ListExtract_Poker(SqList &L,char *target_type)
{
    SqList La,Lb,Lc;
    InitList_Poker(La);
    InitList_Poker(Lb);
    
    for(int i=1;i<=L.length;i++)
    {
        if(strcmp(L.elem[i-1].type,target_type)==0)
        {
            int j;
            for(j=1;j<=La.length;j++)
            {
                if(lessorequal_Poker(L.elem[i-1].num,La.elem[j-1].num))
                {
                    break;
                }
            }
            ListInsert_Poker(La,j,L.elem[i-1]);
        }
        else
        {
            ListInsert_Poker(Lb,Lb.length+1,L.elem[i-1]);
        }    
    }
 
    for(int i=1;i<=L.length;i++)
    {
        if(i<=La.length)
        {
            memcpy(L.elem+i-1,La.elem+i-1,sizeof(ElemType));
        }
        else
        {
            memcpy(L.elem+i-1,Lb.elem+i-La.length-1,sizeof(ElemType));
        }
    }
    
    return OK;
}
 
 
 
 
int main()
{
    SqList L;
    InitList_Poker(L);
 
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        //cout<<i<<':'<<endl;
        char t[10];
        scanf("%s",t);
        
        if(strcmp(t,"Append")==0)
        {
            ElemType add;
            scanf("%s %s",add.type,add.num);
            ListInsert_Poker(L,L.length+1,add);
        }
 
        if(strcmp(t,"Pop")==0)
        {
            if(L.length==0)
            {
                printf("NULL\n");
            }
            else
            {
                ElemType de;
                ListDelete_Poker(L,1,&de);
                printf("%s %s\n",de.type,de.num);
            }
        }
 
        if(strcmp(t,"Revert")==0)
        {
            ListRevert_Poker(L);
        }
 
        if(strcmp(t,"Extract")==0)
        {
            char target_type[10];
            scanf("%s",target_type);
            ListExtract_Poker(L,target_type);
        }
        
        //Print_Poker(L);
    }
    Print_Poker(L);
 
    return 0;
}
