# include <bits/stdc++.h> 
const int MAXN = 1005;
const int mod = 998244353; 
int n, k, p, q, h[MAXN][MAXN], g[MAXN][MAXN], f[MAXN << 1], pow_q[MAXN], pow_p[MAXN], a[MAXN << 1], b[MAXN << 1], wq[MAXN], F[MAXN << 1];


inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline void upd(int &a, const int &b) {
    (a += b) %= mod;
}

// g[i][j] = g[i + 1][k] * h[i][j-k];
// h[i][j] = g[i + 1][k] * h[i][j - k - 1]; 
int tmp[MAXN << 1];

inline void mul(int *a, int *b, int n) { 
    for (int i = 0; i <= (n << 1); ++i) tmp[i] = 0;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            upd(tmp[i + j], 1ll * a[i] * b[j] % mod);
    for (int i = 2 * n; i >= n; --i) {
        int beishu = 1ll * tmp[i] * qpow(wq[n], mod - 2) % mod;
        for (int j = 0; j <= n; ++j)
            tmp[i - n + j] = ((tmp[i - n + j] - 1ll * beishu * wq[j] % mod) % mod + mod) % mod;
    }
    for (int i = 0; i <= n; ++i) a[i] = tmp[i];
}

inline int Calc(int k) {
    if (!k) return qpow(p, n);
    memset(h, 0, sizeof h);
    memset(g, 0, sizeof g);
    memset(F, 0, sizeof F);
    memset(f, 0, sizeof f);
    g[k][1] = 1ll * pow_q[k] * p % mod; g[k][0] = 1;
    for (int i = k - 1; i; --i) {
        register int len = k / i;
        g[i][0] = h[i][0] = 1; 
        for (int j = 0; j <= len; ++j) {
            for (int l = j; l <= len; ++l)
                if (l) upd(g[i][l], 1ll * g[i + 1][l - j] * h[i][j] % mod); 
            for (int l = j + 1; l <= len; ++l)
                upd(h[i][l], 1ll * g[i + 1][l - j - 1] * h[i][j] % mod * pow_q[i] % mod * p % mod);
        }
    }
    f[0] = 1; 
    for (int i = 1; i <= (k + 1) << 1; ++i)
        for (int j = 0; j < i && j <= k; ++j)
            upd(f[i], 1ll * f[i - j - 1] * g[1][j] % mod * p % mod);

    if (n <= (k + 1) * 2) {
        int Ans = 0;
        for (int i = 0; i <= k && i <= n; ++i)
            upd(Ans, 1ll * f[n - i] * g[1][i] % mod);
        return Ans; 
    }

    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    memset(wq, 0, sizeof wq);


    int N = k + 1; wq[N] = 1;
    for (int i = 0; i < N; ++i) wq[i] = -(1ll * g[1][N - i - 1] * p % mod);

    a[1] = b[0] = 1;

    int K = n - k - 1;

    for (; K; K >>= 1, mul(a, a, N))
        if (K & 1) mul(b, a, N);
    
    for (int i = 1; i <= k + 1; ++i) // F[i] --> f[n - k - 1 + i];
        for (int j = 0; j <= k; ++j)
            upd(F[i], 1ll * b[j] * f[i + j] % mod);
        
    int Ans = 0;
    for (int i = 1; i <= k + 1; ++i)
        upd(Ans, 1ll * F[i] * g[1][k - i + 1] % mod);
    
    return Ans; 
}

int main() {
    int x, y;
    scanf("%d%d%d%d", &n, &k, &x, &y);
    q = 1ll * x * qpow(y, mod - 2) % mod; p = (1 - q + mod) % mod;
    pow_q[0] = pow_p[0] = 1;
    for (int i = 1; i <= k; ++i) 
        pow_q[i] = 1ll * pow_q[i - 1] * q % mod, 
        pow_p[i] = 1ll * pow_p[i - 1] * p % mod; 
    printf("%d\n", ((Calc(k) - Calc(k - 1)) % mod + mod) % mod);
    return 0; 
}