#include <bits/stdc++.h>
#define MAXN 200005
#define Min(x,y) ((x)<(y)?(x):(y))
int T,n,m,dfn[MAXN],low[MAXN],cnt,vis[MAXN],first[MAXN],e = 1;
bool Judge[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN << 2];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline bool Check(int fa) {
    if ((!dfn[n]) | (!dfn[1])) return false;
    if ((dfn[1] < dfn[fa] | dfn[1] > cnt) & (dfn[n] < dfn[fa] | dfn[n] > cnt)) return false;
    if ((dfn[1] >= dfn[fa] & dfn[1] <= cnt) & (dfn[n] >= dfn[fa] & dfn[n] <= cnt)) return false;
    return true;
}

void tarjan(int u){
    low[u] = dfn[u] = ++cnt;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (!dfn[v]) {
            tarjan(v),low[u] = Min(low[v],low[u]);
            if (dfn[u] <= low[v] && Check(v) && u != 1) Judge[u] = true;
        }
        else low[u] = Min(low[u],dfn[v]);
    }
}

int main() {
    T = read<int>();
    while (T --) {
        n = read<int>(); m = read<int>();
        memset(first,0,sizeof first);
        memset(low,0,sizeof low);
        memset(dfn,0,sizeof dfn);
        memset(Judge,0,sizeof Judge);
        memset(vis,0,sizeof vis);
        cnt = 0;e = 1;
        for (int i = 1,u,v; i <= m; i++) {
            u = read<int>(),v = read<int>();
            push(u,v); push(v,u);
        }
        int Ans = 0;
        tarjan(1);
        for (int i = 2; i < n; i++) Ans += Judge[i];
        printf("%d\n",Ans);
        for (int i = 2; i < n; i++)
            if (Judge[i]) printf("%d ",i);
        puts("");
    }
    return 0;
}