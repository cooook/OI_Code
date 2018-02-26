# include <bits/stdc++.h>  
const int MAX_NODE = 1e6 + 5;
const int MAX_EDGE = 2e6 + 5;
const int MAXN = 1005;
const int inf = 0x3f3f3f3f;
int n, m, e = 2, first[MAX_NODE], w[MAXN], val[MAXN], S, T, d[MAX_NODE];
std::vector<int> G[MAXN];


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS ++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
}

inline void gmax(int &a, const int &b) {
    if (a < b) a = b;
}

struct edge {
    int u, v, w, next; 
} a[MAX_EDGE]; 

inline void add(int u, int v, int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; 
    a[e].next = first[u]; first[u] = e++;
}

inline void push(int u, int v, int w) {
    add(u, v, w), add(v, u, 0);
}

inline bool cmp(int a, int b) {
    return w[a] > w[b];
}

inline bool bfs() {
    std::queue<int> Q;
    memset(d, -1, sizeof d);
    d[0] = 1; Q.push(S);
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        if (u == T) return true;
        for (int i = first[u]; i; i = a[i].next)
            if (d[a[i].v] == -1 && a[i].w)
                d[a[i].v] = d[u] + 1, Q.push(a[i].v);
    }
    return false; 
}

inline int dfs(int u, int cap) {
    if (u == T || !cap) return cap;
    int Ans = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v, w = a[i].w;
        if (d[v] == d[u] + 1 && w) {
            w = dfs(v, std::min(cap, w));
            a[i].w -= w; a[i ^ 1].w += w;
            Ans += w; cap -= w;
            if (!cap) break;
        }
    }
    if (!Ans) d[u] = -1;
    return Ans;
}

inline int Work() {
    int Ans = 0;
    while (bfs()) Ans += dfs(S, inf);
    return Ans;
}

int main() {
    n = read(); m = read();
    for (int i = 1; i <= n; ++i) w[i] = read();
    for (int i = 1; i <= n; ++i) val[i] = read();
    for (int i = 1; i <= m; ++i) {
        register int u = read(), v = read();
        G[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i)
        std::sort(G[i].begin(), G[i].end(), cmp);
    int cnt = n;
    for (int i = 1; i <= n; ++i) {
        if (!G[i].size()) continue;
        ++ cnt; int id = cnt;
        push(S, cnt, w[G[i][0]]);
        for (int j = 1; j <= G[i].size(); ++j) {
            ++ cnt; 
            if (j != 1) push(cnt, cnt - 1, inf);
            if (j == G[i].size()) push(id, cnt, w[G[i][G[i].size() - 1]]);
            else push(id, cnt, w[G[i][j - 1]] - w[G[i][j]]);
            push(cnt, G[i][j - 1], inf);
        }
    }
    T = ++ cnt;
    for (int i = 1; i <= n; ++i) push(i, T, val[i]);
    printf("%d\n", Work());
    return 0;
}