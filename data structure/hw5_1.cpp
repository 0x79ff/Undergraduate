#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3+50;
int m,n;
int nums[maxn],queries[maxn],ans[maxn];

void input()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&nums[i]);
    for(int i=1;i<=m;i++) scanf("%d",&queries[i]);
}

void mysort()
{
    //直接冒泡排序
    for(int i=1;i<=n;i++){
        for(int j=n;j>=i+1;j--){//把最小的换到i处
            if(nums[j-1] > nums[j]){
                int t = nums[j-1];
                nums[j-1] = nums[j];
                nums[j] = t;
            }
        }
    }
}

void output()
{
    for(int i=1;i<=m;i++){
        int sum = 0;
        for(int j=1;j<=n;j++){
            sum += nums[j];
            if(sum > queries[i]){
                ans[i] = j-1;
                break; 
            }
            else if(j==n)
                ans[i] = n;
        }
    }
    for(int i=1;i<=m;i++) printf("%d ",ans[i]);
}

int main()
{
    input();
    mysort();
    output();
    return 0;
}