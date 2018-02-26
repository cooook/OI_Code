# include <set>
# include <map>
# include <stack>
# include <queue>
# include <vector>
# include <time.h>
# include <bitset>
# include <string>
# include <iomanip>
# include <stdio.h>
# include <cstring>
# include <stdlib.h>
# include <iostream>
# include <algorithm>
const int MAXM = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int first[MAXM], e = 2, n, m, dir[21][21], id[21][21][2], S, T, cnt, dis[MAXM], pre[MAXM];
bool vis[MAXM];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-' ? f = -f : 0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, next, w, c;
}a[MAXM << 1];

inline void add(int u, int v, int w, int c) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].c = c;
    a[e].next = first[u]; first[u] = e++;
}

inline void push(int u, int v, int w, int c) {
    add(u, v, w, c), add(v, u, 0, -c);
}

inline int read_char() {
    char ch = getchar();
    while (ch != 'R' && ch != 'D' && ch != 'L' && ch != 'U') ch = getchar();
    if (ch == 'U') return 0;
    if (ch == 'D') return 1;
    if (ch == 'L') return 2;
    return 3;
}

inline bool bfs() {
    std::queue<int> Q;
    for (int i = 1; i <= cnt; i++) pre[i] = 0, dis[i] = 0x3f3f3f3f;
    dis[S] = 0; Q.push(S);
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

inline int SPFA() {
    int Ans = 0, tmp;
    while (bfs()) {
        tmp = inf;
        for (int i = pre[T]; i; i = pre[a[i].u]) tmp = std::min(tmp, a[i].w);
        for (int i = pre[T]; i; i = pre[a[i].u]) Ans += a[i].c * tmp, a[i].w -= tmp, a[i ^ 1].w += tmp;
    } return Ans;
}

int main() {
    n = read(), m = read(); S = ++ cnt; T = ++ cnt; 
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            dir[i][j] = read_char(), id[i][j][0] = ++ cnt, id[i][j][1] = ++ cnt;
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j) {
            push(S, id[i][j][0], 1, 0);
            push(id[i][j][1], T, 1, 0);
            for (register int k = 0; k < 4; ++k) {
                register int x = i + dx[k], y = j + dy[k];
                if (x == 0) x = n;
                if (y == 0) y = m;
                if (x == n + 1) x = 1; 
                if (y == m + 1) y = 1;
                if (k == dir[i][j]) push(id[i][j][0], id[x][y][1], 1, 0);
                else push(id[i][j][0], id[x][y][1], 1, 1);
            }
        }
    printf("%d\n", SPFA());
    return 0;
}