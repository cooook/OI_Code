# include <queue> 
# include <stdio.h>
# include <cstring> 
# include <math.h> 
const int MAX_NODE = 1e6 + 5;
const int MAX_EDGE = 2e6 + 5;
const int inf = 0x3f3f3f3f;
int n, first[MAX_NODE], e = 2, dis[MAX_NODE], flow[MAX_NODE], pre[MAX_NODE];
bool vis[MAX_NODE];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-' ? f = -f : 0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, w, c, next; 
} a[MAX_EDGE];

inline void push(int u, int v, int w, int c) {
    a[e] = (edge){u, v, w, c, first[u]}; first[u] = e++;
    a[e] = (edge){v, u, 0, -c, first[v]}; first[v] = e++;
}

inline bool bfs(int S, int T) {
    for (int i = 0; i <= n * 2 + 5; i++) dis[i] = inf;
    std::queue<int> Q; Q.push(S);
    dis[S] = 0;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop(); vis[u] = false;
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

inline int Min_Cost(int S, int T) {
    int Ans = 0, tmp;
    while (bfs(S, T)) {
        tmp = inf;
        for (int i = pre[T]; i; i = pre[a[i].u]) tmp = std::min(tmp, a[i].w);
        for (int i = pre[T]; i; i = pre[a[i].u]) a[i].w -= tmp, a[i ^ 1].w += tmp; 
        Ans += tmp * dis[T];
    } return Ans;
}

int main() {
    n = read(); 
    int t = n + 1, S = 0, T = t + 1, Ans = 0; 
    for (int i = 1; i <= n; i++) {
        register int num = read();
        for (int j = 1; j <= num; j++) {
            register int v = read(), w = read();
            push(i, v, inf, w);
            flow[i] --; flow[v] ++;
            Ans += w;
        }
        push(i, t, inf, 0);
    }
    push(t, 1, inf, 0);
    for (int i = 1; i <= n; i++)
        if (flow[i] > 0) push(S, i, flow[i], 0);
        else if (flow[i] < 0) push(i, T, -flow[i], 0);
    printf("%d\n", Ans + Min_Cost(S, T));
    return 0;
}
