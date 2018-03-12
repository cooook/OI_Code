# include <bits/stdc++.h> 
# define RG register
typedef long long ll; 
const int MAXN = 105; 
const int mod = 1e9 + 7; 
int n, m, vis[MAXN][MAXN], Ans[MAXN], tmp[MAXN]; 
ll a[MAXN][MAXN];  


template <typename __Type>
inline void Swap(__Type &x, __Type &y) {
    register __Type t = x; x = y; y = t;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans; 
}
 
inline ll Gauss(int n) {
    RG ll Ans = 1;
    for (RG int i = 1; i <= n; ++i)
        for (RG int j = 1; j <= n; ++j)
            a[i][j] = (a[i][j] + mod) % mod;
    for (RG int i = 1; i <= n; ++i) {
        RG int Ni = qpow(a[i][i], mod - 2);
        for (RG  int j = i + 1; j <= n; ++j) 
            if (a[i][j]) {
                RG int Now = 1ll * a[i][j] * Ni % mod;
                for (int k = i; k <= n; ++k)
                    a[j][k] = (a[j][k] - 1ll * a[i][k] * Now % mod + mod) % mod;  
            }
        (Ans *= a[i][i]) %= mod;
    }
    return (Ans + mod) % mod;
}

inline void Add(int x, int y, int val) {
    a[x][x] += val; a[y][y] += val; a[x][y] -= val; a[y][x] -= val; 
}

int main() {
    RG int i, x;
    scanf("%d%d", &n, &m);
    for (i = 2; i <= n; ++i) scanf("%d", &x), vis[x + 1][i] = vis[i][x + 1] = 1; 
    for (int X = 1; X <= n; ++X) {
        memset(a, 0, sizeof a);
        memset(tmp, 0, sizeof tmp);
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                Add(i, j, vis[i][j] ? 1 : X);
        RG int QAQ = Gauss(n - 1), ni; tmp[0] = 1;
        for (int Y = 1, k = 0; Y <= n; ++Y, ++k) {
            if (X == Y) continue;
            ni = qpow((X - Y + mod) % mod, mod - 2);
            for (int i = k; ~i; --i) {
                (tmp[i + 1] += 1ll * tmp[i] * ni % mod) %= mod;
                tmp[i] = (1ll * tmp[i] * (mod - Y) % mod) * ni % mod; 
            }
        }
        for (int i = 0; i <= n; ++i) (Ans[i] += 1ll * QAQ * tmp[i] % mod) %= mod;
    }
    RG int res = 0;
    for (int i = 0; i <= m; ++i) (res += Ans[i]) %= mod; 
    printf("%d\n", res);
    return 0; 
}