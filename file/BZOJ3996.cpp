# include <stdio.h>
# include <iostream>
# include <cstring>
# include <queue>
const int MAXN = 505;
const int MAXM = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int A[MAXN][MAXN], B[MAXN], n, first[MAXM], e = 2, S, T, d[MAXM], id[MAXN][MAXN], cnt, Ans; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u, v, w, next;
} a[MAXM << 1];

inline void push(int u, int v, int w) {
    e[a] = (edge){u, v, w, u[first]}; u[first] = e++;
    e[a] = (edge){v, u, 0, v[first]}; v[first] = e++;
}

inline bool bfs() {
    memset(d, -1, sizeof d);
    std::queue<int> Q;
    Q.push(S);
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
        if (w && d[v] == d[u] + 1) {
            w = dfs(v, std::min(w, cap));
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

int main() {
    n = read(); cnt = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            A[i][j] = read(), id[i][j] = ++ cnt, Ans += A[i][j], 
            push(S, cnt, A[i][j]), push(cnt, i, inf), push(cnt, j, inf); 
    T = ++ cnt;
    for (int i = 1; i <= n; i++) B[i] = read(), push(i, T, B[i]);
    printf("%d\n", Ans - dinic());
    return 0;
}