# include <stdio.h> 
# include <iostream>
const int MAXN = 1e5 + 5; 
const int maxn = 1 << 21;
const int mod = 1e9 + 7; 
long long n; int k; 
int fac[MAXN], Inv[MAXN], f[MAXN][2333]; 


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
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
    scanf("%lld%d", &n, &k);
    if (n > k) return puts("0"), 0;
    fac[0] = 1; Inv[0] = 1; 
    for (int i = 1; i <= k; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    Inv[k] = qpow(fac[k], mod - 2);
    for (int i = k - 1; ~i; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod;

    f[0][0] = 1; 

    for (int i = 1; i <= n; ++i)
        for (int j = i - 1; j <= k; ++j)
            for (int l = 1; l + j <= k; ++l)
                (f[i][l + j] += 1ll * f[i - 1][j] * C(k - j, l) % mod * (1ll << j) % mod) %= mod;
    
    // (k - j)! \ l! (k - j - l)! 
    // 2 ^ j
    
    int Ans = 0;
    for (int i = n; i <= k; ++i) (Ans += f[n][i]) %= mod;
    printf("%d\n", Ans);
    while (true);
    return 0;
}