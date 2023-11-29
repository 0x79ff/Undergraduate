#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll T,m,n;
const int N =2000+50;
ll a[N],b[N],tmp[N];

struct node{
    int x,y,val;
    bool operator < (const node aa) const{
        return val > aa.val;
    }
};

void merge(ll *a,int first,int mid,int last)
{
    int *tmpa = new int[last-first+2];
    int i=first,j=mid+1,pos=1;
    while(i<=mid && j<=last){
        if(a[i]<=a[j]){
            tmpa[pos++]=a[i++];
        }
        else{
            tmpa[pos++]=a[j++];
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

void merge_sort(ll *a,int first,int last)
{
    if(first==last)
        return;
    int mid=(first+last)/2;
    merge_sort(a,first,mid);
    merge_sort(a,mid+1,last);
    merge(a,first,mid,last);
}

void output()
{
    for(int i=1;i<=n;i++){
        cout<<a[i]<<' ';
    }
    cout<<endl;
}

void update()
{
    priority_queue<node>q;
    for(int i=1;i<=n;i++){
        node p;
        p.x=i;p.y=1;p.val=a[i]+b[1];
        q.push(p);
    }
    for(int i=1;i<=n;i++){
        node p=q.top();
        tmp[i]=p.val;
        q.pop();
        p.y=p.y+1;
        p.val=a[p.x]+b[p.y];
        q.push(p);
    }
    for(int i=1;i<=n;i++){
        a[i]=tmp[i];
    }
}

void solve()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if (i == 1)
                cin >> a[j];
            else
                cin >> b[j];
        }
        if(i==1){
            merge_sort(a, 1, n);
        }
        else{
            merge_sort(b, 1, n);
            update();
        }
    }
    output();
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>T;
    while(T--){
        solve();
    }
    return 0;

}