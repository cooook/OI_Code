#include <bits/stdc++.h>
#define int long long 
#define fi first
#define se second
#define mk std::make_pair
typedef std::pair<int,int> pii;
const int MAXN = 1e5+5;
int n,Q,first[MAXN],e = 1,pre[MAXN],Sum[MAXN],Up_Sum[MAXN],num[MAXN],f[MAXN],bin[21],Log[MAXN << 1];
int deep[MAXN],Num,g[MAXN],root,size[MAXN],Top_Sum[MAXN],dfn[MAXN],idx;  bool vis[MAXN];
std::vector<pii> G[MAXN]; int st[MAXN<<1][21];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,w,next;
}a[MAXN<<1];

inline void push(int u,int v,int w){
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u){
    st[dfn[u] = ++ idx][0] = deep[u];
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != f[u]){
            deep[a[i].v] = deep[u] + a[i].w;
            f[a[i].v] = u;
            dfs(a[i].v);
		    st[++idx][0] = deep[u];
        }
}

inline int lca(int u,int v){
    int x = dfn[u], y = dfn[v];
    if (x > y) std::swap(x,y);
    int len = Log[y - x + 1];
    return std::min(st[x][len],st[y-bin[len]+1][len]);
}

inline void build_st(){
    Log[1] = 0; bin[0] = 1;
    for (int i = 2; i <= idx; i++) Log[i] = Log[i >> 1] + 1;
    for (int i = 1; i <= 20; i++) bin[i] = bin[i-1] << 1;
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + bin[j] - 1 <= idx; i++)
            st[i][j] = std::min(st[i][j-1],st[i+bin[j-1]][j-1]);
}

inline int dis(int u,int v){
    return deep[u] + deep[v] - 2 * lca(u,v);
}

inline void G_size(int u,int fa){
    size[u] = 1;
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa && !vis[a[i].v]) G_size(a[i].v,u), size[u] += size[a[i].v];
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
            Num = size[a[i].v], root = 0, G_root(a[i].v,0), G[u].push_back(mk(root,a[i].v)), pre[root] = u, Div(root);
}

inline int Query(int x){
    int Ans = 0;
    for (int u = x; u; u = pre[u]){
        Ans += Sum[u];
        if (pre[u]) Ans += -Up_Sum[u] + (num[pre[u]] - num[u]) * dis(x,pre[u]);
    }
    return Ans;
}

inline void Change(int x,int val){
    for (int u = x; u; u = pre[u])
        num[u] += val, Sum[u] += val * dis(x,u), Up_Sum[u] += val * dis(x,pre[u]);
}

inline int G_Ans(int u){
    int Ans = Query(u);
    for (std::vector<pii>::iterator it = G[u].begin(); it != G[u].end(); ++it)
        if (Ans > Query(it -> se)) return G_Ans(it -> fi);
    return Ans;
}

signed main(){
    int rt;
    n = read<int>(), Q = read<int>();
    for (int i = 1; i < n; i++){
        int u = read<int>(),v = read<int>(),w = read<int>();
        push(u,v,w), push(v,u,w);
    } dfs(1); build_st(); G_size(1,0); Num = n; g[0] = n; G_root(1,0); rt = root; Div(root); 
    while (Q--){
        int x = read<int>(),y = read<int>();
        Change(x,y);
        printf("%lld\n",G_Ans(rt));
    }
    return 0;
}
