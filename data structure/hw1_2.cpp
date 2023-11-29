//Paste your code here
//NOTE: If you use java, your Main class must be named solution
#include <bits/stdc++.h>
using namespace std;
 
typedef struct student {
    char   no[40];
    char  name[40];
    } ElemType;
 
 
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2        
 
typedef int Status;
 
#define LIST_INIT_SIZE 10000
#define LISTINCREMENT 10
 
 
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;
 
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem) exit(LOVERFLOW);
    L.length=0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
 
 
Status ListInsert_Sq(SqList &L, int i, ElemType e)
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
 
Status ListDelete_Sq(SqList &L, int i, ElemType *e)
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
 
 
Status compare_no(ElemType e1, ElemType e2)
{
     return (strcmp(e1.no,e2.no)==0);
}
 
Status compare_name(ElemType e1, ElemType e2)
{
    return (strcmp(e1.name,e2.name)==0);
}
 
 
Status VisitElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType e1, ElemType e2))
{
    ElemType *p = L.elem;
    int       i = 1;
 
    while(i<=L.length && (*compare)(*p++, e)==FALSE)
        i++;
        
    if(i<=L.length) printf("%d %s %s\n",i,L.elem[i-1].no,L.elem[i-1].name);
    else printf("-1\n");
    
    return OK;    //找到返回i，否则返回0
}
 
 
 
int main()
{
    SqList L;
    InitList_Sq(L);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        ElemType tmp_stu;
        scanf("%s %s",tmp_stu.no,tmp_stu.name);
        ListInsert_Sq(L,L.length+1,tmp_stu);
    }
 
    char in_cmd[20];
    for(;;)
    {
        scanf("%s",in_cmd);
        if(strcmp(in_cmd,"insert")==0)
        {
            int pos;
            ElemType tmp_stu;
            scanf("%d %s %s",&pos,tmp_stu.no,tmp_stu.name);
            if(ListInsert_Sq(L,pos,tmp_stu)==OK) printf("0\n");
            else printf("-1\n");
        }
        if(strcmp(in_cmd,"remove")==0)
        {
            int pos;
            ElemType tmp_stu;
            scanf("%d",&pos);
            if(ListDelete_Sq(L,pos,&tmp_stu)==OK) printf("0\n");
            else printf("-1\n");
        }
 
        if(strcmp(in_cmd,"check")==0)
        {
            char info[20];
            ElemType tmp_stu;
            scanf("%s",info);
            if(strcmp(info,"name")==0)
            {
                scanf("%s",tmp_stu.name);
                VisitElem_Sq(L,tmp_stu,compare_name);
            }
            if(strcmp(info,"no")==0)
            {
                scanf("%s",tmp_stu.no);
                VisitElem_Sq(L,tmp_stu,compare_no);        
            }
        }
        if(strcmp(in_cmd,"end")==0)
        {
            printf("%d",L.length);
            break;
        }
    }
 
    return 0;
}
