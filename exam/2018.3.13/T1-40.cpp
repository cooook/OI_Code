# include <bits/stdc++.h>
const int MAXN = 2e5 + 5; 
int n, val[MAXN], f[3005][3005], Hash[MAXN], cnt, first[MAXN], e = 1; 
 
 
char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline void gmax(int &x, const int &y) {
    if (x < y) x = y;
}
 
struct edge {
    int u, v, next;
} a[MAXN << 1];
 
inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}
 
inline void dfs(int u, int fa) {
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v, u);
        for (int j = 1; j <= cnt; ++j)
            f[u][j] += f[v][j];
    }
    ++ f[u][val[u]];
    for (int i = val[u] - 1; i; --i)
        gmax(f[u][i], f[u][i + 1]);
}
 
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) Hash[i] = val[i] = read();
    std::sort(&Hash[1], &Hash[n + 1]);
    cnt = std::unique(&Hash[1], &Hash[n + 1]) - Hash - 1;
    for (int i = 1; i <= n; ++i) val[i] = std::lower_bound(&Hash[1], &Hash[cnt + 1], val[i]) - Hash;
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        push(u, v), push(v, u); 
    }
    dfs(1, 0);
    printf("%d\n", n - f[1][1]);
    return 0;
}
// 另一种暴力DP...