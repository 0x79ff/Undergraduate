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

typedef char Selemtype;
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

int check(Sqstack &s,string a,string b)
{
    int i=0,j=0;
    for(;j<b.length();)
    {
        if(!Empty(s)) 
        {
            Selemtype e;
            Gettop(s,e);
            if(e==b[j])
            {
                Pop(s,e);
                j++;
                continue;
            }
        }
        if(i>=a.length()) return FALSE;
        for(;i<a.length();)
        {
            if(a[i]==b[j])
            {
                i++;
                j++;
                break;
            }
            else
            {
                Push(s,a[i]);
                i++;
            }
        }
    }
    return TRUE;
}



int main()
{
    Sqstack s;
    Initstack(s);
    string a,b;
    cin>>a;
    for(;cin>>b;)
    {
        Clear(s);
        if(check(s,a,b)) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}