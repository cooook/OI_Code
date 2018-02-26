# include <bits/stdc++.h>
const int inf = 0x3f3f3f3f, MAXN = 1e6+5;
int n, m, d[MAXN], first[MAXN], e = 2, S, T, D, map[50][50], id[50][50][2], cnt; 
char s[50][50];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u, v, w, next; 
}a[2000000]; 

inline void push(int u, int v, int w) {
    a[e] = (edge){u, v, w, first[u]}; first[u] = e++;
    a[e] = (edge){v, u, 0, first[v]}; first[v] = e++;
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
            if (a[i].w && d[a[i].v] == -1)
                d[a[i].v] = d[u] + 1, Q.push(a[i].v);
    } return false;
}

inline int dfs(int u, int cap) {
    if (u == T || !cap) return cap;
    int Ans = 0, w;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (d[v] == d[u] + 1 && a[i].w) {
            w = dfs(v, std::min(cap, a[i].w));
            Ans += w;
            a[i].w -= w;
            a[i ^ 1].w += w;
            cap -= w;
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

inline bool dis(int a, int b, int c, int d) {
    return abs(a - c) + abs(b - d) <= D;
}

inline void Link(int x, int y) {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (dis(i, j, x, y) && map[i][j]) {
                if (x == i && y == j) continue;
                push(id[x][y][1], id[i][j][0], inf);
            }
}

inline int read_char() {
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar());
    return ch - '0';
}

int main() {
    n = read(), m = read(), D = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            map[i][j] = read_char(); id[i][j][0] = ++ cnt; id[i][j][1] = ++ cnt;
            if (map[i][j]) push(id[i][j][0], id[i][j][1], map[i][j]);
        }
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (map[i][j]) Link(i, j);
    int Ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] == 'L') push(S, id[i][j][0], 1), ++ Ans;
    T = ++ cnt;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (std::min(std::min(i, n - i + 1), std::min(j, m - j + 1)) <= D && map[i][j])
                push(id[i][j][1], T, inf);
    printf("%d\n", Ans - dinic());
    return 0;
}