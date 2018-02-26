#include <bits/stdc++.h>
const int MAXN = 500005;
int n,m,s,t,dis[MAXN],first[MAXN],e = 1;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next,w;
}a[MAXN<<2];

inline void push(int u,int v,int w) {
    a[e].u = u; a[e].v = v;a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

int low[MAXN],dfn[MAXN],idx,st[MAXN],top,val[MAXN],belong[MAXN],bcc;
bool vis[MAXN];

inline void tarjan(int u,int fa) {
    low[u] = dfn[u] = ++ idx; vis[u] = true; st[++top] = u;
    for (int i = first[u]; i; i = a[i].next) 
        if (a[i].v == fa) continue;
        else if (!dfn[a[i].v]) tarjan(a[i].v,u),low[u] = std::min(low[u],low[a[i].v]);
        else if (vis[a[i].v]) low[u] = std::min(low[u],dfn[a[i].v]);
    if (low[u] == dfn[u]) {
        bcc++; register int v;
        do {
            v = st[top--];
            vis[v] = false;
            belong[v] = bcc;
        } while (u != v);
    }
}

inline void dfs(int u,int fa,int val) {
    val += ::val[u];
    if (u == belong[t]) return dis[belong[t]] = std::max(val,dis[belong[t]]),void();
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v,u,a[i].w + val);
    }
}

int main() {
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= m; i++) {
        register int u = read<int>(),v = read<int>(),w = read<int>();
        push(u,v,w); push(v,u,w);
    }
    s = read<int>(); t = read<int>();
    tarjan(1,0);
    int tot = e - 1;
    memset(first,0,sizeof first);
    for (int i = 1; i <= tot; i += 2)
        if (belong[a[i].u] != belong[a[i].v])
            push(belong[a[i].u],belong[a[i].v],a[i].w),push(belong[a[i].v],belong[a[i].u],a[i].w);
        else val[belong[a[i].u]] += a[i].w;
    if (belong[s] == belong[t]) {
        if (val[belong[s]] > 0) puts("YES");
        else puts("NO");
        return 0;
    }
    dfs(belong[s],0,0);
    if (dis[belong[t]] > 0) puts("YES");
    else puts("NO");
    // getchar(); getchar();
    return 0;
}