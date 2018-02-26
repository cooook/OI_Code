# pragma GCC optimize("O3")
# include <stdio.h>
const int MAXN = 100005, mod = 10007;
int T, n, c, lim[MAXN], mu[MAXN], C[MAXN][21], f[MAXN][21], g[21][MAXN][21], prime[MAXN], cnt, mn;
bool _prime[MAXN]; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Init() {
    static const int N = 100000;
    mu[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
            _prime[i * prime[j]] = true;
            if (!(i % prime[j])) break;
            mu[i * prime[j]] = - mu[i];
        }
    }
    C[0][0] = 1;
    for (int i = 1; i <= N; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= 20; ++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
    }
    for (int c = 2; c <= 20; ++c)
        for (int d = 1; d <= N; ++d)
            for (int k = d; k <= N; k += d)
                (f[k][c] += C[d - 1][c - 2] * mu[k / d] % mod) %= mod;
    for (int c = 2; c <= 20; ++c)
        for (int d = 1; d <= N; ++d)
            for (int Mul = 1, j = 0; j <= 11; j++, (Mul = Mul * d % mod))
                g[c][d][j] = (g[c][d-1][j] + f[d][c] * Mul % mod) % mod;
}

inline int gmin(int &a, const int b) {
    if (a > b) a = b;
    return a;
} 

int Mul[MAXN]; 

inline void Work() {
    int last, Ans = 0, Mi, Mul1, Mul2;
    for (int i = 1; i <= mn; i = last + 1) {
        last = mn;
        for (int j = 1; j <= n; ++j) gmin(last, lim[j] / (lim[j] / i));
        Mul[0] = 1; 
        for (int j = 1; j <= n; ++j) {
            Mi = lim[j] / i % mod;
            Mul1 = Mi * (lim[j] + 1) % mod, Mul2 = -Mi * (Mi + 1) / 2 % mod;
            Mul[j] = Mul[j - 1] * Mul2 % mod;
            for (int k = j - 1; k >= 0; k--) Mul[k] = (Mul[k] * Mul1 % mod + (k?Mul[k-1] * Mul2 % mod:0)) % mod;
        }
        for (int j = 0; j <= n; ++j) (Ans += (Mul[j] * (g[c][last][j] - g[c][i-1][j] + mod) % mod) % mod) %= mod;
    }
    printf("%d\n", (Ans + mod) % mod);
}

int main() {
    Init();
    T = read(); 
    while (T --) {
        n = read(); c = read();  mn = MAXN; 
        for (int i = 1; i <= n; ++i) lim[i] = read() - 1, gmin(mn, lim[i]);
        Work(); 
    }
    return 0;
}