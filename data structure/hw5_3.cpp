#include <bits/stdc++.h>
using namespace std;
int n,m;
const int M = 10000+100;
bool vis[M];

//生成大于等于p的最小素数m
int prime_M(int p)
{
    int i;
    for(i=p;;i++){
        int prime = 1;
        for(int j =2;j<=sqrt(i);j++){//枚举，判断是否为素数
            if(i%j == 0){
                prime = 0;
                break;
            }
        }
        if(prime && i > 1) break;
    }
    return i;
}

//哈希函数 根据字符串返回函数值
void hkey(string a)
{
    int key = 0;
    //计算哈希函数的值key
    for(int i=0;i<a.size();i++){
        key = (37*key)%m;
        key = (key+a[i])%m;   
    }
    if(vis[key] == 0){
        vis[key] = 1;
        printf("%d ",key);
        return;
    }
    //平方检测冲突
    for(int i=1;i<=m;i++)
    {
        int key2;
        if(i%2==1)
            key2 = ( key + ((i+1)/2) * ((i+1)/2) ) % m;
        else
            key2 = ( key - ((i+1)/2) * ((i+1)/2) ) % m;
        if(key2<0)
            key2 += m;

        if(vis[key2] == 0){
            vis[key2] = 1;
            printf("%d ",key2);
            return;
        }
    }
    printf("- ");

}

void input()
{
    for(int i=1;i<=n;i++){
        string a;
        cin>>a;
        hkey(a);
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    m = prime_M(m);
    input();
    return 0;
}
