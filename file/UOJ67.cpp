#include <stdio.h>
#include <iostream>
const int MAXN = 100005;
int low[MAXN],dfn[MAXN],cnt,n,m,du[MAXN],first[MAXN],e = 1,vis[MAXN];
bool cut[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
} a[MAXN<<1];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

void tarjan(int u) {
    low[u] = dfn[u] = ++ cnt;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (!dfn[v]) tarjan(v),low[u] = std::min(low[u],low[v]),vis[u] += low[v] >= dfn[u];
        else low[u] = std::min(low[u],dfn[v]);
    }
    if ((u == 1 && vis[u] >= 2) | (u != 1 && vis[u] >= 1)) cut[u] = true; 
}

int main() {
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= m; i++) {
        register int u = read<int>(),v = read<int>();
        push(u,v); push(v,u);
        du[u] ++; du[v] ++;
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    int Ans = 0;
    for (int i = 1; i <= n; i++) if (!cut[i]) {
        if (m - du[i] == n - 2) Ans ++;
        else cut[i] = true;
    }
    printf("%d\n",Ans);
    for (int i = 1; i <= n; i++)
        if (!cut[i]) printf("%d ",i);
    return 0;
}