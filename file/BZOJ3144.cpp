# include <stdio.h> 
# include <cstring>
# include <queue>
# define S 0 
const int MAXN = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int first[MAXN], e = 2, n, m, r, id[45][45][45], cnt, d, val[45][45][45], T, Dis[MAXN];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
 
 
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-' ? f = -f : 0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
} 
 
struct edge{
    int u, v, w, next; 
}a[MAXN << 1];
 
inline void push(int u, int v, int w) {
    a[e] = (edge){u, v, w, first[u]}; first[u] = e++;
    a[e] = (edge){v, u, 0, first[v]}; first[v] = e++;
}
 
inline bool bfs() {
    memset(Dis, -1, sizeof Dis);
    std::queue<int> Q;
    Q.push(S);
    Dis[S] = 1;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next)
            if (Dis[a[i].v] == -1 && a[i].w)
                Dis[a[i].v] = Dis[u] + 1, Q.push(a[i].v);
    }
    return Dis[T] != -1;
}
 
inline int dfs(int u, int cap) {
    if (u == T || !cap) return cap;
    int Ans = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v, w = a[i].w;
        if (Dis[v] == Dis[u] + 1 && w) {
            w = dfs(v, std::min(cap, w));
            cap -= w;
            Ans += w;
            a[i].w -= w;
            a[i ^ 1].w += w;
            if (!cap) break;
        }
    }
    if (!Ans) Dis[u] = -1;
    return Ans;
}
 
inline int dinic() {
    int Ans = 0;
    while (bfs()) Ans += dfs(S, inf);
    return Ans; 
}
 
int main() {
    n = read(); m = read(); r = read(); d = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= r; k++)
                id[i][j][k] = ++ cnt;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                val[j][k][i] = read();
    T = ++ cnt;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= r; k++) {
                if (k == r) push(id[i][j][k], T, inf), push(id[i][j][k - 1], id[i][j][k], val[i][j][k]);
                else if (k == 1) push(S, id[i][j][k], val[i][j][k]);
                else push(id[i][j][k-1], id[i][j][k], val[i][j][k]);
                if (k <= d) continue;
                for (int op = 0; op < 4; op++) {
                    int x = i + dx[op], y = j + dy[op];
                    if (x < 1 || y < 1 || x > n || y > m) continue;
                    push(id[i][j][k], id[x][y][k-d], inf);
                }
            }
    printf("%d\n", dinic());
    return 0;
}
﻿