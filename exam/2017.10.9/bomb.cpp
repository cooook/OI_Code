#include <stdio.h>
#include <cstring>
#include <math.h>
#include <iostream>
#define MAXN 1000005
int n,m,first[MAXN],e = 1,st[MAXN],top,low[MAXN],dfn[MAXN],cnt,size[MAXN],scc,f[MAXN],belong[MAXN],Ans;
bool vis[MAXN],used[MAXN];


template<typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void tarjan(int u) {
    dfn[u] = low[u] = ++ cnt;
    st[++top] = u; vis[u] = true;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (!dfn[v]) tarjan(v),low[u] = std::min(low[v],low[u]);
        else if (vis[v]) low[u] = std::min(low[u],dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int v;scc ++;
        do {
            v = st[top--];
            ++ size[scc];
            vis[v] = false;
            belong[v] = scc;
        } while (u != v);
    }
}

inline void dfs(int u) {
    if (used[u]) return;
    used[u] = true;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v; dfs(v);
        f[u] = std::max(f[u],f[v]); // f[v] have add sum[v];
    }
    f[u] += size[u];
}

int main () {
    freopen("bomb.in","r",stdin);
    freopen("bomb.out","w",stdout);
    n = read<int>(); m = read<int>();

    for (int i = 1; i <= m; i++) {
        register int u = read<int>(),v = read<int>();
        push(u,v);
    }

    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);

    memset(first,0,sizeof first);

    int tmp = e - 1;

    for (int i = 1; i <= tmp; i++)
        if (belong[a[i].u] != belong[a[i].v])
            push(belong[a[i].u],belong[a[i].v]);

    int Ans = 0;

    for (int i = 1; i <= scc; i++) dfs(i),Ans = std::max(Ans,f[i]);

    printf("%d\n",Ans);

    return 0;
}