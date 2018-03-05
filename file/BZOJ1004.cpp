# include <bits/stdc++.h>
const int MAXN = 1005;
int sr, sb, sg, m, mod, n, pos[MAXN], size[MAXN], Sum[MAXN], f[105][105][105], cnt; 
bool vis[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans; 
}

inline void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true; 
    ++ size[cnt];
    dfs(pos[u]); 
}

inline void upd(int &x, const int &y) {
    x += y; if (x >= mod) x -= mod; 
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    sr = read(), sb = read(), sg = read(), m = read(), mod = read();
    n = sr + sb + sg;  int Ans = 0; 
    for (int TAT = 1; TAT <= m; ++TAT) {
        memset(size, 0, sizeof size); 
        memset(f, 0, sizeof f);
        cnt = 0;
        for (int i = 1; i <= n; ++i) pos[i] = read(), vis[i] = false;
        for (int i = 1; i <= n; ++i)    
            if (!vis[i]) ++ cnt, dfs(i);
        for (int i = 1; i <= n; ++i) Sum[i] = Sum[i - 1] + size[i];
        f[0][0][0] = 1;
        for (int i = 1; i <= cnt; ++i) 
            for (int j = 0; j <= Sum[i - 1] && j <= sr; ++j)
                for (int k = 0; k <= Sum[i - 1] && k <= sb; ++k) {
                    if (j + size[i] <= sr) upd(f[i][j + size[i]][k], f[i - 1][j][k]);
                    if (k + size[i] <= sb) upd(f[i][j][k + size[i]], f[i - 1][j][k]);
                    if (Sum[i - 1] - j - k + size[i] <= sg) upd(f[i][j][k], f[i - 1][j][k]);
                }
        upd(Ans, f[cnt][sr][sb]); 
    }
    memset(size, 0, sizeof size); 
    memset(f, 0, sizeof f);
    cnt = 0;
    for (int i = 1; i <= n; ++i) pos[i] = i, vis[i] = false;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) ++ cnt, dfs(i);
    for (int i = 1; i <= n; ++i) Sum[i] = Sum[i - 1] + size[i];
    f[0][0][0] = 1;
    for (int i = 1; i <= cnt; ++i) 
        for (int j = 0; j <= Sum[i - 1] && j <= sr; ++j)
            for (int k = 0; k <= Sum[i - 1] && k <= sb; ++k) {
                if (j + size[i] <= sr) upd(f[i][j + size[i]][k], f[i - 1][j][k]);
                if (k + size[i] <= sb) upd(f[i][j][k + size[i]], f[i - 1][j][k]);
                if (Sum[i - 1] - j - k + size[i] <= sg) upd(f[i][j][k], f[i - 1][j][k]);
            }
    upd(Ans, f[cnt][sr][sb]); 
    Ans = qpow(m + 1, mod - 2) * Ans % mod;
    printf("%d\n", Ans);
    return 0;
}