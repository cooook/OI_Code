# include <bits/stdc++.h>
 
 
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
const int inf = 0x3f3f3f3f;
 
int first[1000000], e = 2, d[1000000], T, S, belong[1000000], scc, top, st[1000000], dfn[1000000], low[1000000], n, m, idx;
bool vis[1000000]; 
 
struct edge {
    int u, v, w, next; 
}a[2000005];
 
inline void add(int u, int v, int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; 
    a[e].next = first[u]; first[u] = e++;
} 
 
inline void push(int u, int v, int w) {
    add(u, v, w); add(v, u, 0);
}
 
inline bool bfs() {
    std::queue<int> Q;
    Q.push(S);
    memset(d, -1, sizeof d);
    d[S] = 1;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next) 
            if (d[a[i].v] == -1 && a[i].w)
                d[a[i].v] = d[u] + 1, Q.push(a[i].v);
    }
    return d[T] != -1;
} 
 
inline int dfs(int u, int cap) {
    if (u == T || !cap) return cap;
    int Ans = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v, w = a[i].w;
        if (d[v] == d[u] + 1 && a[i].w) {
            w = dfs(v, std::min(cap, w));
            Ans += w;
            cap -= w;
            a[i].w -= w;
            a[i ^ 1].w += w;
            if (!cap) break;
        }
    }
    if (!Ans) d[u] = -1;
    return Ans;
}
 
inline int dinic() {
    int Ans = 0;
    while (bfs()) Ans += dfs(S, inf);
    return Ans;
}
 
inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
}
 
inline void tarjan(int u) {
    vis[u] = true; dfn[u] = low[u] = ++ idx; st[++top] = u;
    for (int i = first[u]; i; i = a[i].next) {
        if (a[i].w == 0) continue;
        if (!dfn[a[i].v]) tarjan(a[i].v), gmin(low[u], low[a[i].v]);
        else if (vis[a[i].v]) gmin(low[u], dfn[a[i].v]);
    }
    if (dfn[u] == low[u]) {
        scc ++; int v;
        do {
            v = st[top--];
            vis[v] = false;
            belong[v] = scc;
        } while (u != v);
    }
}
 
int main() {
    n = read(), m = read(), S = read(), T = read();
    for (int i = 1; i <= m; i++) {
        register int u = read(), v = read(), w = read();
        push(u, v, w);
    } dinic();
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
    for (int i = 2; i < e; i += 2) {
        if (a[i].w) {puts("0 0"); continue;}
        if (belong[a[i].u] != belong[a[i].v]) putchar('1');
        else putchar('0');
        if (belong[a[i].u] == belong[S] && belong[a[i].v] == belong[T]) puts(" 1");
        else puts(" 0");
    }
    return 0;
}