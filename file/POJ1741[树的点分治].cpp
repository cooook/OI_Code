#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MAXN 10005
int first[MAXN],e = 1,n,m,root,Ans,S,size[MAXN],d[MAXN],deep[MAXN],f[MAXN],cnt;
bool vis[MAXN];


template<typename _t>
inline _t read(){
    _t x = 0,f = 1;
    char ch = getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch == '-') f = -f;
    for(;isdigit(ch);ch=getchar()) x = x * 10 + (ch^48);
    return x*f;
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w){
    a[e].u = u;a[e].v = v;a[e].w = w;
    a[e].next = first[u];first[u] = e++;
}

inline void G_root(int u,int fa){
    size[u] = 1; f[u] = 0;
    for(int i = first[u];i;i=a[i].next) {
        register int v = a[i].v;
        if(!vis[v] && v != fa) {
            G_root(v,u);
            size[u] += size[v];
            f[u] = std::max(f[u],size[v]);
        }
    }
    f[u] = std::max(f[u],S - f[u]);
    if(f[u] < f[root]) root = u;
}

inline void G_deep(int u,int fa){
    d[++cnt] = deep[u];
    for(int i = first[u];i;i=a[i].next)
        if(!vis[a[i].v] && a[i].v != fa)
            deep[a[i].v] = deep[u] + a[i].w,G_deep(a[i].v,u);
}

inline int G_Ans(int u){
    cnt = 0;G_deep(u,0); int Ans = 0;
    std::sort(&d[1],&d[cnt + 1]); 
    for(int l = 1,r = cnt;l<r;) 
        if(d[l] + d[r] <= m) Ans += r - l, l ++; 
        else r --;
    return Ans;
}

inline void dfs(int u){
    deep[u] = 0;vis[u] = 1; Ans += G_Ans(u); 
    for(int i = first[u];i;i=a[i].next)  
        if(!vis[a[i].v]) deep[a[i].v] = a[i].w,Ans -= G_Ans(a[i].v),
                S = size[u],root = 0,G_root(a[i].v,0),dfs(root);
}

int main(){
    freopen("poj1741_tree.in","r",stdin);
    freopen("poj1741_tree.out","w",stdout);
    while(scanf("%d%d",&n,&m) && (n || m)){
        memset(first,0,sizeof first); 
        memset(vis,0,sizeof vis);
        Ans = 0,e = 1;
        for(int i = 1;i<n;i++) {
            register int u = read<int>(),v = read<int>(),w = read<int>();
            push(u,v,w); push(v,u,w);
        } f[0] = 0x7fffffff;  S = n;
        root = 0; G_root(1,0); 
        dfs(root);
        printf("%d\n",Ans);
    }
    return 0;
}