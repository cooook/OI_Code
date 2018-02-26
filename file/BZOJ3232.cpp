# include <stdio.h> 
# include <cstring>
# include <queue> 
const int MAXN = 55;
const int inf = 0x3f3f3f3f;
const int MAXM = 1e6+5;
const double eps = 1e-6;
int n, m, val[MAXN][MAXN], l[MAXN][MAXN], h[MAXN][MAXN], first[MAXM], e = 2, d[MAXM], S, T, id[MAXN][MAXN], cnt;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
 
 
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'? f = -f : 0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
struct edge {
    int u, v, next; double w;
}a[MAXM << 1];
 
inline void add(int u, int v, double w) {
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}
 
inline void push(int u, int v, double w) {
    add(u, v, w), add(v, u, 0);
}
 
inline bool bfs() {
    std::queue<int> Q;
    memset(d, -1, sizeof d);
    Q.push(S);
    d[S] = 1;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next)
            if (d[a[i].v] == -1 && a[i].w > eps) 
                d[a[i].v] = d[u] + 1, Q.push(a[i].v);
    }
    return d[T] != -1;
}
 
inline double dfs(int u, double cap) {
    if (u == T || cap < eps) return cap;
    double Ans = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v; register double w = a[i].w;
        if (d[v] == d[u] + 1 && w > eps) {
            w = dfs(v, std::min(w, cap));
            Ans += w;
            cap -= w;
            a[i].w -= w;
            a[i ^ 1].w += w;
            if (cap < eps) break;
        }
    }
    if (Ans < eps) d[u] = -1;
    return Ans;
}
 
inline double dinic() {
    double Ans = 0;
    while (bfs()) Ans += dfs(S, inf);
    return Ans;
}
 
inline bool Judge(double mid) {
    memset(first, 0, sizeof first); e = 2;
    double Ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            push(S, id[i][j], val[i][j]);
            Ans += val[i][j];
            for (int k = 0; k < 4; k++) {
                int x = dx[k] + i, y = dy[k] + j; double p;
                if (k == 0) p = l[i][j] * mid; 
                if (k == 1) p = l[i+1][j] * mid;
                if (k == 2) p = h[i][j] * mid;
                if (k == 3) p = h[i][j+1] * mid;
                if (x == 0 || y == 0 || x > n || y > m) push(id[i][j], T, p);
                else push(id[i][j], id[x][y], p);
            }
        }
    return Ans - dinic() > eps;
}
 
int main() {
    n = read(), m = read();
    S = ++ cnt; T = ++ cnt;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            val[i][j] = read(), id[i][j] = ++ cnt;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= m; j++)
            l[i][j] = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m + 1; j++)
            h[i][j] = read();
    double l = 0.0, r = 1e4, mid;
    while (l + 1e-4 < r) {
        mid = (l + r) / 2;
        if (Judge(mid)) l = mid;
        else r = mid;
    } printf("%.3f\n", mid);
    return 0;
}