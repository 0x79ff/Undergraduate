#include <bits/stdc++.h>
using namespace std;

typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2    

#define STACK_INIT_SIZE 1000
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


//顺序为（ ） | & ！ #
const char priority[10][10]={ {'<', '=', '<', '<', '<', '>'},
                              {' ', '>', '>', '>', '>', '>'},
                              {'<', '>', '>', '<', '<', '>'},
                              {'<', '>', '>', '>', '<', '>'},
                              {'<', '>', '>', '>', '<', '>'},
                              {'<', ' ', '<', '<', '<', '='}};

int Mapping(char cc)
{
    if(cc=='(') return 0;
    if(cc==')') return 1;
    if(cc=='|') return 2;
    if(cc=='&') return 3;
    if(cc=='!') return 4; 
    if(cc=='#') return 5;
    return -1;
}

char Judge_priority(char c1,char c2)
{
    return priority[Mapping(c1)][Mapping(c2)];
}                             


int Is_PTR(char ch)
{
    if(ch=='V' || ch=='F') return TRUE;
    else return FALSE;
}


char solution(string &a,Sqstack &sPTR,Sqstack &sPND)
{
    a='#'+a+'#';
   // cout<<a<<endl;
    for(int i=0;i<a.length();i++)
    {
        /*for(int j=0;j<=i;j++) cout<<a[j];
        cout<<endl;
        cout<<a<<endl;*/
        if(Is_PTR(a[i]))  Push(sPTR,a[i]);
        else{
               if(a[i]==' ') continue;
               if(Empty(sPND)){
                Push(sPND,a[i]);
                continue;
               } 
               Selemtype e;Gettop(sPND,e);
                //cout<<e<<' '<<Judge_priority(e,a[i])<<' '<<a[i]<<endl;
               if(Judge_priority(e,a[i])=='<')  Push(sPND,a[i]);//优先级大先进栈
               
               else if(Judge_priority(e,a[i])=='=') Pop(sPND,e);//优先级相等消去

               else if(Judge_priority(e,a[i])=='>') //优先级小进行内部运算
               {
                 Pop(sPND,e);
                 if(e=='!'){
                    Selemtype e1;Pop(sPTR,e1);
                    if(e1=='V') Push(sPTR,'F');
                    if(e1=='F') Push(sPTR,'V');
                 }
                 if(e=='|'){
                    Selemtype e1,e2;Pop(sPTR,e1);Pop(sPTR,e2);
                    if(e1=='F' && e2=='F') Push(sPTR,'F');
                    else Push(sPTR,'V'); 
                 }
                 if(e=='&'){
                    Selemtype e1,e2;Pop(sPTR,e1);Pop(sPTR,e2);
                    if(e1=='V' && e2=='V') Push(sPTR,'V');
                    else Push(sPTR,'F'); 
                 }
                 i--;
               }
               
        }
       /*for(int i=0;i<sPND.top-sPND.base;i++)
        {
            printf("%c",sPND.base[i]);
        }
        printf("\n");
        for(int i=0;i<sPTR.top-sPTR.base;i++)
        {
            printf("%c",sPTR.base[i]);
        }
        printf("\n");*/
    }
    Selemtype eresult;Pop(sPTR,eresult);
    return eresult;
}


int main()
{
    Sqstack sPTR,sPND;//运算数，运算符号
    Initstack(sPTR);
    Initstack(sPND);
    int A=0;
    string a;
    for(;getline(cin,a);)
    {
        A++;
        Clear(sPTR);
        Clear(sPND);
        printf("Expression %d: %c\n",A,solution(a,sPTR,sPND));
    }
    return 0;
}