#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#define MAXN 100005
int n,m,T,first[MAXN],e = 1,in[MAXN],out[MAXN],cnt,f[MAXN][20],deep[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

#define lowbit(x) ((x)&(-x))
int tree[MAXN<<1];
inline void Update(int x,int val) {
    for (; x <= cnt; x += lowbit(x)) tree[x] += val;
}

inline int Query(int x) {
    int Ans = 0;
    for (; x; x -= lowbit(x)) Ans += tree[x];
    return Ans;
}

struct Query{
    int u,v,lca;
    inline bool operator < (const Query &x) const{
        return deep[lca] > deep[x.lca];
    }
}Q[MAXN];

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

void dfs(int u,int fa) {
    in[u] = ++ cnt;
    f[u][0] = fa; deep[u] = deep[fa] + 1;
    for (int i = 1; i <= 18; i++) f[u][i] = f[f[u][i-1]][i-1];
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v,u);
    }
    out[u] = ++ cnt;
}

inline int Lca(int u,int v) {
    if (deep[u] < deep[v]) std::swap(u,v);
    int t = deep[u] - deep[v];
    for (int i = 18; ~i; i--)
        if (t & (1 << i)) u = f[u][i];
    for (int i = 18; ~i; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i],v = f[v][i];
    return u == v?u:f[u][0]; 
}

int main() {
    T = read<int>();
    while (T --) {
        memset(first,0,sizeof first); e = 1;
        memset(in,0,sizeof in); cnt = 0;
        memset(out,0,sizeof out);
        memset(tree,0,sizeof tree);
        memset(f,0,sizeof f);
        memset(deep,0,sizeof deep);
        n = read<int>();  m = read<int>();
        for (int i = 1; i < n; i++) {
            register int u = read<int>(),v = read<int>();
            push(u,v); push(v,u);
        } dfs(1,0);
        for (int i = 1; i <= m; i++) Q[i].u = read<int>(),Q[i].v = read<int>(),Q[i].lca = Lca(Q[i].u,Q[i].v);
        std::sort(&Q[1],&Q[m+1]); int Ans = 0;
        for (int i = 1; i <= m; i++) {
            if (Query(in[Q[i].u]) - Query(in[Q[i].lca]) + Query(in[Q[i].v]) - Query(in[Q[i].lca] - 1)) continue;
            Ans ++; Update(in[Q[i].lca],1); Update(out[Q[i].lca],-1);
        }
        printf("%d\n",Ans);
    }
    return 0;
}
