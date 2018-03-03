# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
const int MAXN = 105; 
const int mod = 998244353;
int n, A[MAXN], B[MAXN], C[MAXN], D[MAXN], f[2][MAXN][MAXN][MAXN], g[2][MAXN][MAXN][MAXN], Ni = 828542813, now, cnt;


inline int read() {
    register int x = 0; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) ; 
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    if (ch != '.') return x; 
    for (; !isdigit(ch); ch = getchar()) ;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x;
}

struct data {
    int v, Sum; 
    inline bool operator < (const data &x) const {
        return v < x.v;
    }
} val[1005];

inline void upd(int &a, const int &b) {
    (a += b) %= mod; 
}

inline void DP(int f[][MAXN][MAXN][MAXN], int *A, int *C) {
    f[0][0][0][0] = 1; now = 1;
    for (int i = 1; i <= n; ++i) {
        memset(f[now], 0, sizeof f[now]);
        for (int j = 0; j < i; ++j)
            for (int k = 0; k <= j; ++k)
                for (int l = 0; l + j < i; ++l) {
                    int q = A[i], p = (1 - A[i] + mod) % mod, Q = C[i], P = (1 - C[i] + mod) % mod;
                    upd(f[now][j + 1][k][l], 1ll * q * P % mod * f[now ^ 1][j][k][l] % mod);
                    upd(f[now][j + 1][k + 1][l], 1ll * q * Q % mod * f[now ^ 1][j][k][l] % mod);
                    upd(f[now][j][k][l], 1ll * p * P % mod * f[now ^ 1][j][k][l] % mod);
                    upd(f[now][j][k][l + 1], 1ll * p * Q % mod * f[now ^ 1][j][k][l] % mod); 
                }    
        now ^= 1;
    }
}

inline void Read(int *a) {
    for (int i = 1; i <= n; ++i) a[i] = 1ll * read() * Ni % mod; 
}

inline int find(int x) {
    if (x < val[1].v) return 0;
    if (x > val[cnt].v) return val[cnt].Sum; 
    int l = 1, r = cnt, mid, Ans = 0;
    while (l <= r) {
        mid = l + r >> 1;
        if (x > val[mid].v) Ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return val[Ans].Sum; 
}

int main() {
    n = read(); 
    Read(A); Read(B), Read(C), Read(D);
    DP(f, A, C); DP(g, B, D); now ^= 1;
    int Ans = 0;
    for (int i1 = 0; i1 <= n; ++i1) {
        for (int i2 = 0; i2 <= n; ++i2) {
            cnt = 0;
            for (int j = 0; j <= i1; ++j)
                for (int k = 0; k + i1 <= n; ++k) if (j * (n - i1) > k * i1)
                    val[++cnt] = (data){j * (2 * n - i1 - i2) - k * (i1 + i2), f[now][i1][j][k]}; 
            std::sort(&val[1], &val[cnt + 1]);
            for (int i = 2; i <= cnt; ++i) (val[i].Sum += val[i - 1].Sum) %= mod;
            for (int j = 0; j <= i2; ++j)
                for (int k = 0; k + i2 <= n; ++k) if (j * (n - i2) > k * i2)
                    upd(Ans, 1ll * find(k * (i1 + i2) - j * (2 * n - i1 - i2)) * g[now][i2][j][k] % mod);
        }
    }
    printf("%d\n", Ans);
    return 0; 
}
