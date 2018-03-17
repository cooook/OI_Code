# include <queue> 
# include <stdio.h> 
# include <cstring> 
# include <iostream>
# define int long long 
const int MAXN = 105; 
const int inf = 0x3f3f3f3f3f3f3f3fll; 
int first[MAXN], e = 2, n, m, d[MAXN];
 
 
inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
struct edge {
    int u, v, w, next; 
}a[5005];
 
inline void push(int u, int v, int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].next = first[u]; first[u] = e++;
}
 
inline bool bfs() {
    std::queue<int> Q;
    memset(d, 0, sizeof d);
    Q.push(1); d[1] = 1;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        if (u == n) return true; 
        for (int i = first[u]; i; i = a[i].next) 
            if (!d[a[i].v] && a[i].w)
                d[a[i].v] = d[u] + 1, Q.push(a[i].v);
    }
    return false; 
}
 
inline int dfs(int u, int cap) {
    if (u == n || !cap) return cap;
    register int Ans = 0, v, w;
    for (int i = first[u]; i; i = a[i].next) {
        v = a[i].v, w = a[i].w;
        if (d[v] == d[u] + 1 && w) {
            w = dfs(v, std::min(w, cap));
            Ans += w; a[i].w -= w; cap -= w;
            a[i ^ 1].w += w;
            if (!cap) break;
        }
    }
    if (!Ans) d[u] = 0;
    return Ans; 
}
 
inline int dinic() {
    int Ans = 0;
    while (bfs()) Ans += dfs(1, inf);
    return Ans; 
}
 
signed main() {
    // freopen("T1.in","r",stdin);
    // freopen("T1.out","w",stdout);
    n = read(); m = read();  
    for (int i = 1; i <= m; ++i) {
        register int u = read(), v = read(), w = read();
        push(u, v, w), push(v, u, inf); 
    }
    int Ans = dinic();
    printf("%lld\n", Ans >= inf ? -1 : Ans);
    // while (true); 
    return 0; 
}