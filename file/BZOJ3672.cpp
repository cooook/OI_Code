#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long 
typedef long long ll;
const int MAXN = 200005;
int n,first[MAXN],e = 1,f[MAXN],root,size[MAXN],dis[MAXN],que[MAXN],now_size,cnt,fa[MAXN];
ll limit[MAXN],p[MAXN],q[MAXN],dp[MAXN]; bool vis[MAXN];


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct edge{
    int u,v,next;ll w;
}a[MAXN<<1];

inline void push(int u,int v,ll w){
    a[e].u=u;a[e].v=v;a[e].w=w;
    a[e].next=first[u];first[u]=e++;
}

struct QWQ{
    int id,val;
    inline bool operator < (const QWQ & a)const{return val > a.val;}
}Q[MAXN];

inline void G_root(int u,int &root){
    f[u] = 0,size[u] = 1;
    for(int i = first[u];i;i = a[i].next) if(!vis[a[i].v]) {
        G_root(a[i].v,root); 
        size[u] += size[a[i].v];
        f[u] = std::max(size[a[i].v],f[u]);
    }
    f[u] = std::max(f[u],now_size - size[u]);
    if(f[u] < f[root] && size[u] > 1) root = u;
}

inline void __dfs__(int u){
    size[u] = 1;
    for(int i = first[u];i;i = a[i].next) 
        dis[a[i].v] = dis[u] + a[i].w,
        __dfs__(a[i].v),size[u] += size[a[i].v];
}

inline void dfs(int u){
    Q[++cnt].id = u;Q[cnt].val = dis[u] - limit[u];
    for(int i = first[u];i;i = a[i].next) if(!vis[a[i].v]) dfs(a[i].v);
}

inline ll Calc(int x,int y){
    return dp[y] + (dis[x] - dis[y]) * p[x] + q[x];
}

inline double K(int u,int v) {
    return (dp[u] - dp[v])/1.0/(dis[u] - dis[v]);
}

inline void CDQ(int u,int Size){ 
    if(Size == 1) return;
    int root = 0,now,top = 0;
    now_size = Size; G_root(u,root);
    for(int i = first[root];i;i = a[i].next) vis[a[i].v] = 1;
    CDQ(u,Size - size[root] + 1); cnt = 0;
    for(int i = first[root];i;i = a[i].next) dfs(a[i].v);
    std::sort(&Q[1],&Q[cnt+1]);  now = root;
    for(int i = 1;i<=cnt;i++) {
        while(now != fa[u] && dis[Q[i].id] - limit[Q[i].id] <= dis[now]) {
            while(top > 1 && K(que[top],now) >= K(que[top-1],que[top])) top --;
            que[++top] = now;  
            now = fa[now];
        }
        if(top > 0) {
            int l = 1,r = top,mid,pos = 1;
            while(l<=r) {
                mid=(l+r)>>1; if(mid==top) { pos=top; break; }
                if(K(que[mid],que[mid+1]) >= p[Q[i].id]) l=mid+1,pos=mid+1;
                else r=mid-1;
            }
            dp[Q[i].id] = std::min(dp[Q[i].id],Calc(Q[i].id,que[pos]));
        }
    }
    for(int i = first[root];i;i = a[i].next) CDQ(a[i].v,size[a[i].v]);
}

signed main(){
    n = read<int>(); read<int>();
    for(int i = 2;i<=n;i++) {
        fa[i] = read<int>();
        register ll w = read<ll>(); push(fa[i],i,w);
        p[i] = read<ll>();q[i] = read<ll>();limit[i] = read<ll>(); 
    }
    for(int i = 2;i<=n;i++) dp[i] = (ll)1e17;
    f[0] = n + 1; __dfs__(1); CDQ(1,size[1]);
    for(int i = 2;i<=n;i++) printf("%lld\n",dp[i]);
    return 0;
}

//  f[i]=min{f[j]-dis[j]*p[i]}+dis[i]*p[i]+q[i]
//  斜率优化：
//  --> j<k j 优于 k
//  --> f[j] - dis[j]*p[i] < f[k] - dis[k]*p[i]
//  --> f[j] - f[k] < p[i] * (dis[j] - dis[k])
//  --> (f[j] - f[k]) / (dis[j] - dis[k]) < p[i];
//  --> 二分斜率
//  --> 
//  --> this problem use CDQ.