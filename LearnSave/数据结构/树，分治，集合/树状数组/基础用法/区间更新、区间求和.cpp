//
// Created by awake on 2026/2/4.
//https://www.luogu.com.cn/problem/P3372
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n,m;
int a[N];int b[N];
int lowbit(int x){
    return x&-x;
}
void add(int *s ,int x,int k){
    while(x<=n){
        s[x]+=k;
        x+=lowbit(x);
    }
}
int query(int *s,int x){
    int t=0;
    while(x){
        t+=s[x];
        x-=lowbit(x);
    }
    return t;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;cin>>k;
        add(a,i,k);add(a,i+1,-k);
        add(b,i,k*(i-1));add(b,i+1,-k*i);
    }
    while(m--){
        char op;int x,y,k;
        cin>>op;
        cin>>x>>y;
        if(op=='Q'){
            k=query(a,y)*y-query(b,y)-(query(a,x-1)*(x-1)-query(b,x-1));
            cout<<k<<"\n";
        }else{
            cin>>k;
            add(a,x,k);add(a,y+1,-k);
            add(b,x,k*(x-1));add(b,y+1,-k*y);
        }
    }
    return 0;
}