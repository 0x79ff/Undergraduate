#include <bits/stdc++.h>
using namespace std;

int n;
int num_in_queue;

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

typedef int Qelemtype;
typedef struct QNode{
    Qelemtype data;
    struct QNode *prior;
    struct QNode *next;
}QNode,*DequePtr;

typedef struct{
    DequePtr front;
    DequePtr rear;
}LinkDeque;

Status InitDeque(LinkDeque &Q)
{
    Q.front = (DequePtr)malloc(sizeof(QNode));
    if(!Q.front) exit(LOVERFLOW);
    Q.rear = (DequePtr)malloc(sizeof(QNode));
    if(!Q.rear) exit(LOVERFLOW);
    Q.front->prior=NULL;
    Q.rear->next=NULL;
    Q.rear->prior=Q.front;Q.front->next=Q.rear;
    return OK;
}

Status Destroy(LinkDeque &Q)
{
    while(Q.front){
        Q.rear=Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

Status Print(LinkDeque Q)
{
    DequePtr p = Q.front->next;
    while(p!=Q.rear){
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}

int Empty(LinkDeque Q)
{
    if(Q.front->next==Q.rear) return TRUE;
    else return FALSE;
}

Status EnDeque_back(LinkDeque &Q,Qelemtype e)
{
    //插入新的队尾元素
    DequePtr s;
    s = (DequePtr)malloc(sizeof(QNode));
    if(!s) exit(LOVERFLOW);
    s->data = e;
    s->prior=Q.rear->prior; Q.rear->prior->next=s;
    s->next=Q.rear; Q.rear->prior=s;
    return OK;
}

Status EnDeque_front(LinkDeque &Q,Qelemtype e)
{
    //插入新的队头元素
    DequePtr s;
    s = (DequePtr)malloc(sizeof(QNode));
    if(!s) exit(LOVERFLOW);
    s->data = e;
    s->next=Q.front->next; Q.front->next->prior=s;
    s->prior=Q.front; Q.front->next=s;
    return OK;
}

Status DeDeque_front(LinkDeque &Q,Qelemtype &e)
{
    //删除队头元素，并用e返回
    if(Empty(Q)) return ERROR;
    DequePtr s;s=Q.front->next;
    e=s->data;
    Q.front->next=s->next;
    s->next->prior=Q.front;
    free(s);
    return OK;
}

Status DeDeque_back(LinkDeque &Q,Qelemtype &e)
{
     //删除队尾元素，并用e返回
    if(Empty(Q)) return ERROR;
    DequePtr s;s=Q.rear->prior;
    e=s->data;
    Q.rear->prior=s->prior;
    s->prior->next=Q.rear;
    free(s);
    return OK;
}

Status Get_front(LinkDeque Q,Qelemtype &e)
{
    if(Empty(Q)) return ERROR;
    e=Q.front->next->data;
    return OK;
}

Status Get_rear(LinkDeque Q,Qelemtype &e)
{
    if(Empty(Q)) return ERROR;
    e=Q.rear->prior->data;
    return OK;
}

int main()
{
    scanf("%d", &n);
    LinkDeque Q,D;
    InitDeque(Q);InitDeque(D);
    char operation[20];
    
    for (;;)
    {
        scanf("%s", operation);
        if (strcmp(operation, "dequeue") == 0){
            if (num_in_queue == 0) printf("Queue is Empty\n");
            else{
                Qelemtype e1;DeDeque_front(Q,e1);
                printf("%d\n",e1);
                Qelemtype e2;Get_front(D,e2);
                if(e1==e2) DeDeque_front(D,e2);
                num_in_queue--;
            }
        }
        else if (strcmp(operation, "enqueue") == 0){
             Qelemtype e;scanf("%d",&e);
            if (num_in_queue == n) printf("Queue is Full\n");
            else{
                EnDeque_back(Q,e);
                for(;;){
                     Qelemtype e1;Get_rear(D,e1);
                     if(Empty(D)||e1>=e){
                        EnDeque_back(D,e);
                        break;
                     } 
                     else DeDeque_back(D,e1);
                }
                num_in_queue++;
            }
        }
        else if (strcmp(operation, "max") == 0){
            if (num_in_queue == 0) printf("Queue is Empty\n");
            else{
                Qelemtype e;Get_front(D,e);
                printf("%d\n",e);
            }
        }
        else if (strcmp(operation, "quit") == 0){
            break;
        }
        else ;
    }
    Print(Q);
    return 0;
}
