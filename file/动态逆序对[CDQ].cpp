#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 100005
#define int long long
int n,m,val[MAXN],cnt,Ans[MAXN],pos[MAXN];
bool vis[MAXN];


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

int tree[MAXN];
#define lowbit(x) ((x)&(-x))
inline void Update_mn(int x,int val){for(;x<=n;x+=lowbit(x)) tree[x] += val;}
inline void Update_mx(int x,int val){for(;x;x-=lowbit(x)) tree[x] += val;}
inline int Query_mx(int x){int Ans = 0;for(;x<=n;x+=lowbit(x)) Ans += tree[x];return Ans;}
inline int Query_mn(int x){int Ans = 0;for(;x;x-=lowbit(x)) Ans += tree[x];return Ans;}

struct Operation{
    int x,y,time;
    inline bool operator < (const Operation & a)const{return x < a.x;}
}a[MAXN],tmp[MAXN];

inline bool cmp(const Operation &a,const Operation &b) {
    return a.x > b.x;
}

//  三维偏序：
//  若 (i,j) == 1
//  --> live[i] == live[j] == 1 && ((i < j && a[i] > a[j]) || i>j && a[i]<a[j])
//  --> 考虑按i 排序？ 然后对a[i] 的处理可以用树状数组 

inline void CDQ(int l,int r){
    if(l == r) return;
    register int mid = l + r >> 1,L=l,R = mid + 1;
    for(int i = l;i<=r;i++) {
        if(a[i].time <= mid) Update_mx(a[i].y,1);
        if(a[i].time > mid) Ans[a[i].time] += Query_mx(a[i].y); 
    }
    for(int i = l;i<=r;i++) if(a[i].time <= mid) Update_mx(a[i].y,-1);
    for(int i = l;i<=r;i++) 
        if(a[i].time <= mid) tmp[L++] = a[i];
        else tmp[R++] = a[i];
    for(int i = l;i<=r;i++) a[i] = tmp[i];
    CDQ(l,mid);CDQ(mid+1,r);
}

inline void CDQ1(int l,int r){
    if(l == r) return;
    register int mid = l + r >> 1,L = l,R = mid + 1;
    for(int i = l;i<=r;i++)
        if(a[i].time <= mid) Update_mn(a[i].y,1);
        else Ans[a[i].time] += Query_mn(a[i].y);
    for(int i = l;i<=r;i++) if(a[i].time <= mid) Update_mn(a[i].y,-1);
    for(int i = l;i<=r;i++)
        if(a[i].time <= mid) tmp[L++] = a[i];
        else tmp[R++] = a[i];
    for(int i = l;i<=r;i++) a[i] = tmp[i];
    CDQ1(l,mid);CDQ1(mid+1,r);
}

signed main() {
    freopen("inverse.in","r",stdin);
    freopen("inverse.out","w",stdout);
    n = read<int>(); m = read<int>();
    for(int i = 1;i<=n;i++) {
        val[i] = read<int>();
        pos[val[i]] = i;
    }
    for(int i = 1;i<=m;i++) {
        a[n-m+i].y = read<int>();
        a[n-m+i].x = pos[a[n-m+i].y];
        a[n-m+i].time = n - i + 1;
        vis[a[n-m+i].y] = 1;
    }
    for(int i = 1;i<=n;i++) if(!vis[val[i]]) {
        a[++cnt].x = i;
        a[cnt].y = val[i];
        a[cnt].time = cnt;
    }
    std::sort(&a[1],&a[n+1]); CDQ(1,n); 
    std::sort(&a[1],&a[n+1],cmp);  CDQ1(1,n);
    for(int i = 1;i<=n;i++) Ans[i] += Ans[i-1];
    for(int i = n;i>n-m;i--) printf("%lld\n",Ans[i]);
    return 0;
}