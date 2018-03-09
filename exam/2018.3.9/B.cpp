# include <bits/stdc++.h>
# define int long long 
typedef long long ll;  
const int MAXN = 1e5 + 5;
int n, pos[MAXN], a[MAXN], m, k, val[MAXN], Ans[MAXN], id[MAXN], size, Num[MAXN]; 
bool vis[MAXN];
 
 
char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline void dfs(int u) {
    if (vis[u]) return ;
    vis[u] = true;
    Num[size++] = u;  
    dfs(id[u]);
}
 
signed main() {
    n = read();
    for (int i = 1; i <= n; ++i) pos[i] = read(); 
    for (int i = 1; i < n; ++i) val[i] = pos[i + 1] - pos[i], id[i] = i; 
    m = read(), k = read();
    for (int i = 1; i <= m; ++i) {
        register int v = read();
        std::swap(id[v - 1], id[v]);
    }
    for (int i = 1; i < n; ++i)
        if (!vis[i]) {
            size = 0;
            dfs(i); 
            for (int j = 0; j < size; ++j)
                id[Num[j]] = Num[(j + k) % size]; 
        }
    register ll Ans = pos[1];
    for (int i = 1; i <= n; ++i) {
        printf("%lld\n", Ans);
        Ans += val[id[i]]; 
    }
    // while (true); 
    return 0;
}