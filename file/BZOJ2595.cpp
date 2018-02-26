# include <bits/stdc++.h>
# define int long long 
# define fi first
# define se second 
# define mk std::make_pair
# define ID(_, __) (_ * m + __)
typedef std::pair<int, int> pii;
const int MAXN = 105;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n, m, cnt, id[MAXN], map[MAXN], full, f[105][1 << 10];
bool vis[MAXN], mark[MAXN]; pii from[105][1 << 10];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0}; 
std::queue<int> Q;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void SPFA(int S) {
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop(); vis[u] = false;
        register int X = u / m, Y = u % m;
        for (int i = 0; i < 4; i++) {
            register int x = X + dx[i], y = Y + dy[i];
            if (x < 0 || y < 0 || x >= n || y >= m) continue;
            if (f[ID(x, y)][S] > f[ID(X, Y)][S] + map[ID(x, y)]) {
                f[ID(x, y)][S] = f[ID(X, Y)][S] + map[ID(x, y)]; from[ID(x, y)][S] = mk(ID(X, Y), S);
                if (!vis[ID(x, y)]) vis[ID(x, y)] = true, Q.push(ID(x, y));
            }
        }
    }
}

inline void dfs(int x, int S) {
    if (f[x][S] == inf) return;
    mark[x] = true;
    dfs(from[x][S].fi, from[x][S].se);
    if (from[x][S].fi == x) dfs(from[x][S].fi, S ^ from[x][S].se);
}

signed main() {
    memset(f, 0x3f, sizeof f);
    n = read(), m = read();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            map[ID(i ,j)] = read();
            if (!map[ID(i, j)]) id[++cnt] = ID(i, j);
        }
    full = 1 << cnt;
    for (int i = 0; i < n * m; i++)
        for (int j = 0; j < full; j++)
            from[i][j] = mk(n * m, full);
    for (int i = 1; i <= cnt; i++) f[id[i]][1 << i - 1] = 0;
    for (int S = 1; S < full; S++) {
        for (int i = 0; i < n * m; i++) {
            for (int j = S; j; (-- j) &= S) 
                if (f[i][S] > f[i][j] + f[i][S ^ j] - map[i])
                    f[i][S] = f[i][j] + f[i][S ^ j] - map[i], from[i][S] = mk(i, j);
            if (f[i][S] != inf) Q.push(i); 
        }
        SPFA(S);
    }
    int Ans = inf, pos;
    for (int i = 0; i < n * m; i++) 
        if (Ans > f[i][full - 1])
            Ans = f[i][full - 1], pos = i;
    printf("%lld\n", Ans);
    dfs(pos, full - 1);
    for (int i = 0; i < n; i++, puts(""))
        for (int j = 0; j < m; j++)
            if (!map[ID(i, j)]) putchar('x');
            else if (mark[ID(i, j)]) putchar('o');
            else putchar('_');
    return 0;
}