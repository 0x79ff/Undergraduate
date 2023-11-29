#include <bits/stdc++.h>
using namespace std;

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

Status Gettop(Sqstack s,Selemtype &e)
{
    if(s.top==s.base) return ERROR;
    e=*(s.top - 1);
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

int main()
{
    Sqstack s;
    Initstack(s);
    string a;
    cin>>a;
    
    //记录各个数值
    int max_len=0,max_start=0,left=-1;
    for(int i=0;i<a.length();i++)
    {
        if(a[i]=='(') Push(s,i);
        
        if(a[i]==')'){
            if(Empty(s)) {
                left=i;
                continue;
            }

            Selemtype e;
            Pop(s, e);
            if (Empty(s)){
                if(i-left>max_len){
                    max_len = i-left;
                    max_start = left+1;
                }
            }
            else{
                Selemtype e2;
                Gettop(s, e2);
                if (i - e2 > max_len){
                    max_len = i - e2;
                    max_start = e2 + 1;
                }
            }
        }
    }
    printf("%d %d",max_len,max_start);
    return 0;
}