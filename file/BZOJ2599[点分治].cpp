#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#define MAXN 200005ul
#define MAXM 1000005ul
#define inf 0x3f3f3f3f
int f[MAXN],mn[MAXM],size[MAXN],dis[MAXN],root,first[MAXN],Ans = inf,num,e = 1,n,k;
bool vis[MAXN];


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct edge{
    int u,v,w,next;
}a[MAXN<<1];

inline void push(int u,int v,int w){
    a[e].u = u;a[e].v = v;a[e].w = w;
    a[e].next = first[u];  first[u] = e++;
}

inline void G_root(int u,int fa){
    size[u] = 1;f[u] = 0;
    for(int i = first[u];i;i = a[i].next) {
        register int v = a[i].v;
        if(vis[v] || v == fa) continue;
        G_root(v,u);
        size[u] += size[v];
        f[u] = std::max(f[u],size[v]);
    }
    f[u] = std::max(f[u],num - f[u]);
    if(f[u] < f[root]) root = u;
}

inline void U(int u,int fa,int QWQ){
    if(dis[u] <= k)
        Ans = std::min(Ans,mn[k - dis[u]] + QWQ);
    for(int i = first[u];i;i=a[i].next)
        if(!vis[a[i].v] && a[i].v != fa)dis[a[i].v] = dis[u] + a[i].w, U(a[i].v,u,QWQ+1);
}

inline void A(int u,int fa,int QWQ){
    if(dis[u] <= k) 
        mn[dis[u]] = std::min(mn[dis[u]],QWQ);
    for(int i = first[u];i;i=a[i].next)
        if(!vis[a[i].v] && a[i].v != fa) A(a[i].v,u,QWQ+1);
}

inline void erase(int u,int fa){
    if(dis[u] <= k) mn[dis[u]] = inf;
    for(int i = first[u];i;i = a[i].next) 
        if(!vis[a[i].v] && a[i].v != fa) erase(a[i].v,u);
}

inline void Calc(int u){
    dis[u] = 0;
    for(int i = first[u];i;i = a[i].next)
        if(!vis[a[i].v]) dis[a[i].v] = a[i].w,U(a[i].v,u,1),A(a[i].v,u,1);
    for(int i = first[u];i;i = a[i].next) 
        if(!vis[a[i].v]) erase(a[i].v,u);
    return;
}

inline void dfs(int u){
    vis[u] = 1; mn[0] = 0; Calc(u);
    for(int i = first[u];i;i = a[i].next) {
        register int v = a[i].v;
        if(vis[v]) continue;
        num = size[u]; root = 0;
        G_root(a[i].v,0); 
        dfs(root);
    }
}

int main(){
    n = read<int>(); k = read<int>();
    for(int i = 1;i<n;i++) {
        int u = read<int>() + 1 ,v = read<int>() + 1,w = read<int>();
        push(u,v,w); push(v,u,w);
    }
    memset(mn,0x3f,sizeof mn); mn[0] = 0; num = n;
    root = 0;f[0] = inf; G_root(1,0); dfs(root);
    printf("%d\n",Ans == inf?-1:Ans);
    return 0;
}