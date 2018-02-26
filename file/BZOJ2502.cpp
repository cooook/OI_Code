# include <stdio.h> 
# include <queue>
# include <cstring> 
const int MAX_EDGE = 2e6 + 5;
const int MAX_NODE = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int first[MAX_NODE], e = 2, n, flow[MAX_NODE], _leaf[MAX_NODE], _root[MAX_NODE], d[MAX_NODE];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, w, next; 
} a[MAX_EDGE];

inline void add(int u, int v, int w) {
    a[e] = (edge){u, v, w, first[u]}; first[u] = e++;
    a[e] = (edge){v, u, 0, first[v]}; first[v] = e++;
}

inline void push(int u, int v, int w, int low) {
    add(u, v, w - low);
    flow[u] -= low; flow[v] += low;
}

inline bool bfs(int S, int T) {
    for (int i = 0; i <= n + 3; i++) d[i] = -1;
    d[S] = 1; 
    std::queue<int> Q; 
    Q.push(S);
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next)
            if (d[a[i].v] == -1 && a[i].w)
                d[a[i].v] = d[u] + 1, Q.push(a[i].v);
    }
    return d[T] != -1;
}

inline int dfs(int u, int T, int cap) {
    if (u == T || !cap) return cap;
    int Ans = 0, v, w;
    for (int i = first[u]; i; i = a[i].next) {
        v = a[i].v, w = a[i].w;
        if (d[v] == d[u] + 1 && w) {
            w = dfs(v, T, std::min(cap, w));
            cap -= w; Ans += w;
            a[i].w -= w; a[i ^ 1].w += w;
            if (!cap) break;
        }
    }
    if (!Ans) d[u] = -1;
    return Ans;
}

inline int dinic(int S, int T) {
    int Ans = 0;
    while (bfs(S, T)) Ans += dfs(S, T, inf);
    return Ans;
}

inline int Work() {
    int s = n + 1, t = n + 2, S = 0, T = n + 3;
    for (int i = 1; i <= n; i++) 
        if (!_root[i]) add(s, i, inf);
        else if (!_leaf[i]) add(i, t, inf); 
    add(t, s, inf);
    int tmp = e - 1;
    for (int i = 1; i <= n; i++)
        if (flow[i] > 0) add(S, i, flow[i]);
        else if (flow[i] < 0) add(i, T, -flow[i]);
    dinic(S, T);
    int Ans = a[tmp].w; a[tmp].w = a[tmp ^ 1].w = 0;
    for (int i = first[S]; i; i = a[i].next) a[i].w = a[i ^ 1].w = 0;
    for (int i = first[T]; i; i = a[i].next) a[i].w = a[i ^ 1].w = 0;
    return Ans - dinic(t, s);
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        int m = read();
        if (m) _leaf[i] = true; 
        for (int j = 1; j <= m; j++){
            int x = read();
            _root[x] = true;
            push(i, x, inf, 1);
        }
    }
    printf("%d\n", Work());
    return 0;
}