#include <stdio.h>
#include <iostream>
#define int long long 
const int MAXN = 200005;
int n,m,first[MAXN],e = 1,size[MAXN],Ans[MAXN],low[MAXN],dfn[MAXN],cnt;


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
}a[1000005];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void tarjan(int u) { 
    low[u] = dfn[u] = ++ cnt;
    size[u] = 1;
    register int mo_std_wxh = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u],low[v]);
            size[u] += size[v];
            if (low[v] < dfn[u]) continue;
            Ans[u] += mo_std_wxh * size[v] * 2;
            mo_std_wxh += size[v];
        }
        else low[u] = std::min(low[u],dfn[v]);
    }   
    Ans[u] += mo_std_wxh * (n - mo_std_wxh - 1) * 2;
}

signed main() {
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= m; i++) {
        register int u = read<int>(),v = read<int>();
        push(u,v); push(v,u);
    }
    tarjan(1);
    for (int i = 1; i <= n; i++)
        printf("%lld\n",Ans[i] + 2 * n - 2);
    // getchar(); getchar();
    return 0;
}