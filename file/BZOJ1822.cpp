# include <stdio.h>
# include <queue> 
# include <cstring>
# define int long long 
const int MAXN = 20005;
const int inf = 0x3f3f3f3f;
int n, m, k, r[MAXN], t[MAXN], S, T, first[MAXN], e = 2, d[MAXN], Cap[MAXN * 10], cnt, T_first[MAXN];


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-' ? f = -f : 0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int sqr(int x) {
    return x * x;
}

struct edge {
    int u, v, w, next;
}a[MAXN * 10];

inline void push(int u, int v, int w) {
    a[e] = (edge){u, v, w, first[u]}; Cap[e] = w; first[u] = e++;
    a[e] = (edge){v, u, 0, first[v]}; Cap[e] = 0; first[v] = e++;
}

inline bool bfs() {
    std::queue<int> Q;
    Q.push(0); 
    memset(d, -1, sizeof d); 
    d[0] = 1;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        if (u == n + m + 1) return true;
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v;
            if (d[v] == -1 && a[i].w) d[v] = d[u] + 1, Q.push(v);
        }
    }
    return false;
}

inline int dfs(int u, int cap) {
    if (u == n + m + 1 || !cap) return cap;
    int Ans = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v, w = a[i].w;
        if (d[v] == d[u] + 1 && w) {
            w = dfs(v, std::min(cap, w));
            a[i].w -= w;
            a[i ^ 1].w += w;
            Ans += w;
            cap -= w;
            if (!cap) break;
        }
    }
    if (!Ans) d[u] = -1;
    return Ans;
}

inline int dinic() {
    int Ans = 0;
    while (bfs()) Ans += dfs(0, inf);
    return Ans;
}

struct Point {
    int d[3]; 
    inline int& operator [] (const int & x) {return d[x];}
    inline Point operator + (const Point & a) const {return (Point){d[0] + a.d[0], d[1] + a.d[1]};}
    inline Point operator - (const Point & a) const {return (Point){d[0] - a.d[0], d[1] - a.d[1]};}
    inline int operator * (const Point & x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
}pt[MAXN], C[MAXN], tree[MAXN];

inline int dis(Point a, Point b) {
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
}

inline bool Judge(int Time) {
    e = cnt + 1; memcpy(first, T_first, sizeof first);
    for (int i = 2; i <= cnt; i++) a[i].w = Cap[i];
    for (int i = 1; i <= n; i++) push(0, i, 1 + Time / t[i]);
    for (int i = 1; i <= m; i++) push(n + i, n + m + 1, 1);
    if (dinic() == m) return true;
    return false; 
}

signed main() {
    n = read(), m = read(), k = read();
    for (int i = 1; i <= n; i++) pt[i][0] = read(), pt[i][1] = read(), pt[i][2] = read(), pt[i][2] *= pt[i][2], t[i] = read();
    for (int i = 1; i <= m; i++) C[i][0] = read(), C[i][1] = read();
    for (int i = 1; i <= k; i++) tree[i][0] = read(), tree[i][1] = read(), tree[i][2] = read(), tree[i][2] *= tree[i][2];
    int l = 0, r = 0x7fffffff, Ans = -1;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) {
            if (dis(pt[i], C[j]) > pt[i][2]) continue;
            bool flag = true;
            for (int o = 1; o <= k; o++)
                if (sqr((pt[i] - tree[o]) * (C[j] - tree[o])) < dis(pt[i], C[j]) * tree[o][2]) {flag = false; break;}
            if (flag) push(i, n + j, 1);
        }
    memcpy(T_first, first, sizeof first);
    cnt = e - 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (Judge(mid)) Ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%lld\n", Ans);
    return 0;
}