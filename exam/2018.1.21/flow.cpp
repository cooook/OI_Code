# include <bits/stdc++.h> 
const int inf = 0x3f3f3f3f;
const int MAX_NODE = 1e6 + 5;
const int MAX_EDGE = 2e6 + 5;
int n, m, first[MAX_NODE], e = 2, d[MAX_NODE], S, T;
char s[55][55];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};


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

inline int id(int x, int y) {
    return (x - 1) * m + y;
}

inline bool bfs() {
    std::queue<int> Q;
    Q.push(S);
    memset(d, -1, sizeof d);
    d[S] = 1;
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
    register int Ans = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v, w = a[i].w;
        if (d[v] == d[u] + 1 && w) {
            w = dfs(v, std::min(cap, a[i].w));
            Ans += w; cap -= w;
            a[i].w -= w; a[i ^ 1].w += w;
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

inline int Dir(char c) {
    if (c == 'A') return 0;
    if (c == 'V') return 1;
    if (c == '<') return 2;
    if (c == '>') return 3;
    return -1;
}

inline int gmax(int &x, const int &y) {
    if (x < y) x = y;
    return x; 
}

inline bool In(int x, int y) {
    return x >= 1 && y >= 1 && x <= n && y <= m; 
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
        for (int j = 1; s[i][j]; ++j) {
            if (isdigit(s[i][j])) s[i][j] -= '0';  
            push(id(i, j), id(i, j) + n * m, inf);
        }
    }
    int Ans = 0; T = n * m * 2 + 1; 
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int d;
            if (~(d = Dir(s[i][j]))) {
                bool is = d < 2;
                int mx = 0;
                for (int x = i, y = j; In(x, y); x += dx[d], y += dy[d]) 
                    if (s[x][y] <= 9) gmax(mx, s[x][y]);
                if (is) push(S, id(i, j), inf);
                else push(id(i, j) + n * m, T, inf);
                Ans += mx;
                for (int x = i, y = j; In(x + dx[d], y + dy[d]); x += dx[d], y += dy[d])
                    if (is) push(id(x, y), id(x + dx[d], y + dy[d]), mx - (s[x][y] <= 9 ? s[x][y] : 0));
                    else push(id(x + dx[d], y + dy[d]) + n * m, id(x, y) + n * m, mx - (s[x][y] <= 9 ? s[x][y] : 0));
            }
        }
    printf("%d\n", Ans - dinic());
    return 0;
}