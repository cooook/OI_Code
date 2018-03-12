# include <map> 
# include <stdio.h> 
# include <cstring> 
const int mod = 1e9 + 7;
int n, k, Ans, fa[85]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v; 
} E[85]; 

struct matrix {
    int a[8][8]; 
    matrix() { memset(a, 0, sizeof a); }
    inline bool operator == (const matrix &x) const {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (a[i][j] != x.a[i][j])
                    return false; 
        return true; 
    }
    inline bool operator < (const matrix &x) const {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (a[i][j] != x.a[i][j])
                    return a[i][j] < x.a[i][j];
        return false; 
    }
    inline void Print() {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                printf("%d%c", a[i][j], " \n"[j == n]);
    }
}q;

inline int qpow(int x, int k) {
    register int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans; 
}

std::map<matrix, bool> ma; 

bool vis[8]; 

inline void Mark(int x, matrix q) {
    if (vis[x]) return ;
    vis[x] = true; 
    for (int i = 1; i <= n; ++i)
        if (q.a[x][i]) Mark(i, q); 
}

inline void dfs(int cnt, matrix now) {
    if (cnt == k + 1) return; 
    matrix tmp;
    register int u, v; 
    tmp = now; 
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (!tmp.a[u][v]) continue;
            tmp.a[u][v] = tmp.a[v][u] = 0;
            for (int j = 1; j <= n; ++j) {
                memset(vis, 0, sizeof vis); 
                Mark(j, tmp);
                for (int k = 1; k <= n; ++k)
                    if (!vis[k]) {
                        tmp.a[j][k] = tmp.a[k][j] = 1;
                        if (!ma.count(tmp)) ++ Ans, ma[tmp] = true;
                        dfs(cnt + 1, tmp);
                        tmp.a[j][k] = tmp.a[k][j] = 0; 
                    }
            }        
            tmp.a[u][v] = tmp.a[v][u] = 1; 
        }
    }
}

inline void Work1() {
    Ans = 1; 
    ma[q] = true;
    dfs(1, q);
    printf("%d\n", Ans);
}

int main() {
    freopen("tree1.in","r",stdin);
    // freopen("T2.out","w",stdout);
    n = read(), k = read(); 
    for (int i = 2; i <= n; ++i) {
        register int x = read() + 1;
        q.a[x][i] = q.a[i][x] = 1; 
        E[i - 1].u = x, E[i - 1].v = i; 
    }
    if (k == n - 1) printf("%d\n", qpow(n, n - 2));
    else if (n <= 7) Work1(); 
    else puts("0");
    while (true); 
    return 0; 
}