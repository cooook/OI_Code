# include <bits/stdc++.h> 
# define int long long 
const int MAXN = 1e6 + 5;
int val[MAXN], pos[MAXN], id[MAXN], n, Sum[MAXN], mn[MAXN], size[MAXN], cnt;  
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
    mn[cnt] = std::min(mn[cnt], val[u]);
    Sum[cnt] += val[u];  ++ size[cnt]; 
    dfs(pos[u]); 
}

signed main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    memset(mn, 0x3f, sizeof mn);
    n = read(); 
    int Mn = 0x3f3f3f3f; 
    for (int i = 1; i <= n; ++i) val[i] = read(), Mn = std::min(Mn, val[i]);
    for (int i = 1; i <= n; ++i) id[i] = read();
    for (int i = 1; i <= n; ++i) pos[id[i]] = read();
    int Ans = 0; 
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) {
            ++ cnt, dfs(i); 
            Ans += Sum[cnt];
            Ans += std::min((size[cnt] - 2) * mn[cnt], (size[cnt] + 1) * Mn + mn[cnt]); 
        }
    printf("%lld\n", Ans);
    // while (true); 
    return 0; 
}

// 1 4 5 3 6 2 
// 5 3 2 4 6 1

// 3 4 5 1 6 2
// 5 4 3 1 6 2
// 5 4 2 1 6 3
// 5 4 2 3 6 1
// 5 3 2 4 6 1

