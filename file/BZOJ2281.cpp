# include <stdio.h>
typedef long long ll;
const int mod = 1e9 + 7; 
int n, k, d, f[32][10005], fac[10005], Inv[10005];


inline int upd(int &a, const int &b) {
    a += b;
    if (a > mod) a -= mod;
    return a;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline int C(int n, int m) {
    if (!m || n == m) return 1;
    if (n < m) return 0;
    return 1ll * fac[n] * Inv[m] % mod * Inv[n - m] % mod;
}

int main() {
    scanf("%d%d%d", &n, &k, &d); ++ d;
    f[0][0] = 1; fac[0] = 1;
    for (int i = 1; i <= 10000; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    Inv[10000] = qpow(fac[10000], mod - 2);
    for (int i = 9999; i; i--) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= 15; i++)
        for (int j = 0, t = 1 << i - 1; j <= n - k; j++)
            for (int l = 0; j + d * t * l <= n - k && d * l <= k >> 1; l++)
                upd(f[i][j + d * t * l], 1ll * f[i - 1][j] * C(k >> 1, d * l) % mod);
    int Ans = 0;
    for (int i = 0; i <= n - k; ++i) upd(Ans, 1ll * f[15][i] * C(n - (k >> 1) - i, k >> 1) % mod);
    // n - k - i  (k >> 1) + 1
    // C(n + m - 1) (m - 1)
    // n - (k >> 1) - i
    printf("%d\n", (C(n, k) - Ans + mod) % mod);
    return 0;
}