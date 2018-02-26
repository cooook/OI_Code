#include <stdio.h>
#include <iostream>
#include <algorithm>
const int MAXN = 200005;
int n,m,first[MAXN],e = 1,pre[MAXN],g[MAXN],size[MAXN],root,Num;
bool vis[MAXN],col[MAXN];
int num[MAXN],Sum[MAXN],Up_Sum[MAXN],Dis[MAXN][18],f[MAXN][18],deep[MAXN],Use[MAXN],father[20];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w){
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int fa){
    for (int i = 1; i <= 17; i++) f[u][i] = f[f[u][i-1]][i-1], Dis[u][i] = Dis[f[u][i-1]][i-1] + Dis[u][i-1];
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (v == fa) continue;
        f[v][0] = u; Dis[v][0] = a[i].w; deep[v] = deep[u] + 1;
        dfs(v,u);
    }
}

inline int dis(int u,int v){
    if (deep[u] < deep[v]) std::swap(u,v);
    int t = deep[u] - deep[v], Ans = 0;
    for (int i = 17; ~i; i--)
        if (t >> i & 1)
            Ans += Dis[u][i], u = f[u][i];
    if (u == v) return Ans;
    for (int i = 17; ~i; i--)
        if (f[u][i] != f[v][i])
            Ans += Dis[u][i] + Dis[v][i],
            u = f[u][i], v = f[v][i];
    return Ans + Dis[u][0] + Dis[v][0];
}

inline void G_size(int u,int fa){
    size[u] = 1;
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (vis[v] || v == fa) continue;
        G_size(v,u);
        size[u] += size[v];
    }
}

inline void G_root(int u,int fa){
    g[u] = 0;
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (v == fa || vis[v]) continue;
        g[u] = std::max(g[u],size[v]);
        G_root(v,u);
    }
    g[u] = std::max(g[u],Num - g[u]);
    if (g[u] < g[root]) root = u;
}

inline void Div(int u){
    vis[u] = true;
    G_size(u,0);
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v])
            Num = size[a[i].v], root = 0, G_root(a[i].v,0), pre[root] = u, Div(root);
}

inline void White(int x){
    for (int u = x; u; u = pre[u])
        -- num[u], Sum[u] -= dis(u,x), Up_Sum[u] -= dis(pre[u],x);
}

inline void Black(int x){
    for (int u = x; u; u = pre[u])
        ++ num[u], Sum[u] += dis(u,x), Up_Sum[u] += dis(pre[u],x);
}

inline int Query(int x){
    int Ans = 0;
    for (int u = x; u; u = pre[u]){
        Ans += Sum[u];
        if (pre[u]) Ans += -Up_Sum[u] + (num[pre[u]] - num[u]) * dis(pre[u],x);
    }
    return Ans;
}

int main(){
    freopen("zjoi15_tree1.in","r",stdin);
    // freopen("A_Tree.in","r",stdin);
    // freopen("A_Tree.out","w",stdout);
    n = read<int>(), m = read<int>();
    for (int i = 1; i < n; i++){
        int u = read<int>(),v = read<int>(),w = read<int>();
        push(u,v,w), push(v,u,w);
    } dfs(1,0);
    g[0] = n; Num = n; G_size(1,0); root = 0; G_root(1,0); Div(root);
    for (int i = 1; i <= n; i++) printf("pre[%d]=%d\n",i,pre[i]);
    int x;
    return 0;
}