# include <queue> 
# include <stdio.h> 
# include <cstring>
const int MAX_EDGE = 2e6 + 5;
const int MAX_NODE = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int n, m, first[MAX_NODE], dis[MAX_NODE], val[MAX_NODE], flow[MAX_NODE], pre[MAX_NODE], e = 2;
bool vis[MAX_NODE];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u, v, w, c, next;
} a[MAX_EDGE];

inline void push(int u, int v, int w, int c) {
    a[e] = (edge){u, v, w, c, first[u]}; first[u] = e++;
    a[e] = (edge){v, u, 0, -c, first[v]}; first[v] = e++;
}

inline bool bfs(int S, int T) {
    std::queue<int> Q; Q.push(S);
    for (int i = 0; i <= n * 2 + 5; i++) dis[i] = inf;
    dis[S] = 0;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop(); vis[u] = false;
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v;
            if (dis[v] > dis[u] + a[i].c && a[i].w) {
                dis[v] = dis[u] + a[i].c; pre[v] = i;
                if (!vis[v]) Q.push(v), vis[v] = true;
            }
        }
    }
    return dis[T] != inf;
}

inline int SPFA(int S, int T) {
    int Ans = 0, tmp;
    while (bfs(S, T)) {
        tmp = inf;
        for (int i = pre[T]; i; i = pre[a[i].u]) tmp = std::min(tmp, a[i].w);
        for (int i = pre[T]; i; i = pre[a[i].u]) a[i].w -= tmp, a[i ^ 1].w += tmp;
        Ans += tmp * dis[T];
    }
    return Ans;
}

int main() {
    n = read(); m = read();
    for (int i = 1, w; i <= n; i++) w = read(), flow[i << 1] -= w, flow[i << 1 | 1] += w;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            int x = read();
            if (x != -1)
                push(i << 1 | 1, j << 1, inf, x);
        }
    int s = 1, t = n * 2 + 2, S = 0, T = t + 1, ss = T + 1;
    for (int i = 1; i <= n; i++) push(s, i << 1, inf, 0), push(i << 1 | 1, t, inf, 0);
    for (int i = 2; i <= (n << 1 | 1); i++) 
        if (flow[i] < 0) push(i, T, -flow[i], 0);
        else if (flow[i] > 0) push(S, i, flow[i], 0);
    push(ss, s, m, 0);
    push(t, ss, inf, 0);
    printf("%d\n", SPFA(S, T));
    return 0;
}