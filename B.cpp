# pragma GCC optimize("O3")
# include <stdio.h> 
# include <cstring> 
# include <iostream> 
const int mod = 100000007;
int phi[2005], prime[2005], cnt, T, n, k, f[2005][2005], Sum[2005][2005];
bool _prime[2005]; 


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

inline void upd(int &x, const int &y) {
    x += y; if (x >= mod) x -= mod; 
}

inline void Init() {
    phi[1] = 1;
    for (int i = 2; i <= 2000; ++i) {
        if (!_prime[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && prime[j] * i <= 2000; ++j) {
            _prime[i * prime[j]] = true; 
            if (!(i % prime[j])) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1); 
        }
    }
}

inline int Calc(int n) {
    int Ans = 0, last = 0, qwq = std::min(k, n - 1);
    if (::n <= k) ++ Ans;
    for (int i = 0; i <= qwq; ++i)
        upd(Ans, Sum[n - i - 1][std::min(k - i, n - i - 1)]);
    return Ans; 
}

int main() {
    T = read();
    Init();
    while (T --) {
        n = read(), k = read(); 
        memset(f, 0, sizeof f); 
        f[0][0] = 1; Sum[0][0] = 1; 
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                upd(f[i][0], f[i - 1][j]);
                if (j != k) upd(f[i][j + 1], f[i - 1][j]);
            }
            Sum[i][0] = f[i][0]; 
            for (int j = 1; j <= k; ++j) Sum[i][j] = (Sum[i][j - 1] + f[i][j]) % mod; 
        }
        int Ans = 0;
        for (int i = 1; i * i <= n; ++i)
            if (!(n % i)) {
                (Ans += 1ll * Calc(i) * phi[n / i] % mod) %= mod;
                if (i * i != n) (Ans += 1ll * Calc(n / i) * phi[i] % mod) %= mod; 
            }
        printf("%d\n", 1ll * Ans * qpow(n, mod - 2) % mod);
    }
    return 0; 
}