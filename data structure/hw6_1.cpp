#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4+100;
int n,a[maxn],ans;

void merge(int *a,int first,int mid,int last)
{
    int *tmpa = new int[last-first+2];
    int i=first,j=mid+1,pos=1;
    while(i<=mid && j<=last){
        if(a[i]<=a[j]){
            tmpa[pos++]=a[i++];
        }
        else{
            tmpa[pos++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid){
        tmpa[pos++]=a[i++];
    }
    while(j<=last){
        tmpa[pos++]=a[j++];
    }
    for(int i=first;i<=last;i++){
        a[i]=tmpa[i-first+1];
    }
    delete []tmpa;
    tmpa=NULL;
}


void merge_sort(int *a,int first,int last)
{
    if(first==last)
        return;
    int mid=(first+last)/2;
    merge_sort(a,first,mid);
    merge_sort(a,mid+1,last);
    merge(a,first,mid,last);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    for(;;){
        cin>>n;
        if(n==0) break;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        ans=0;
        merge_sort(a,1,n);
        cout<<ans<<endl;
    }


    return 0;
}
