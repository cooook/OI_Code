# include <queue> 
# include <stdio.h> 
# include <cstring>
const int MAX_EDGE = 2e6 + 5;
const int MAX_NODE = 1e6 + 5;
const int MAXN = 155;
const int inf = 0x3f3f3f3f;
int first[MAX_NODE], e = 2, in[MAX_NODE], dis[MAX_NODE], pre[MAX_NODE], n, m, k, S, T, f[MAXN][MAXN]; 
bool vis[MAX_NODE];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &x, const int &y) {
    if (x > y) x = y;
}

struct edge {
    int u, v, w, c, next;
} a[MAX_EDGE];

inline void add(int u, int v, int w, int c) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].c = c;
    a[e].next = first[u]; first[u] = e++;
}

inline void push(int u, int v, int w, int c) {
    add(u, v, w, c); add(v, u, 0, -c);
}

inline int bfs(int S, int T) {
    std::queue<int> Q;
    for (int i = 0; i <= T; i++) dis[i] = inf;
    dis[S] = 0; Q.push(S);
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        vis[u] = false;
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v;
            if (dis[v] > dis[u] + a[i].c && a[i].w) {
                dis[v] = dis[u] + a[i].c; pre[v] = i;
                if (!vis[v]) vis[v] = true, Q.push(v);
            }
        }
    }
    return dis[T] != inf;
}

inline int Solve(int S, int T) {
    int Ans = 0, tmp;
    while (bfs(S, T)) {
        tmp = inf;
        for (int i = pre[T]; i; i = pre[a[i].u]) gmin(tmp, a[i].w);
        for (int i = pre[T]; i; i = pre[a[i].u]) a[i].w -= tmp, a[i ^ 1].w += tmp;
        Ans += dis[T] * tmp;
    }
    return Ans;
}

int main() {
    n = read(), m = read(), k = read(); S = n * 2 + 1, T = S + 1; 
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            f[i][j] = inf;
    for (int i = 1; i <= m; i++) {
        register int u = read(), v = read(), c = read();
        f[u][v] = f[v][u] = std::min(f[u][v], c);
    }
    for (int i = 0; i <= n; i++) f[i][i] = 0;
    for (int k = 0; k <= n; k++)
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                if (k <= i || k <= j)
                    f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
    push(S, 0, k, 0);

    for (int i = 1; i <= n; i++)
        push(S, i, 1, 0), push(i + n, T, 1, 0);
    
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            push(i, j + n, 1, f[i][j]);
    
    printf("%d\n", Solve(S, T));
    return 0;
}

/*
不是非常懂
*/