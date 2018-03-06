# include <stdio.h> 
# include <cstring>
# include <iostream> 
const int MAXN = 1e5 + 5;
int T, n, m, k, prime[MAXN], cnt, mod;
bool _prime[MAXN];


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

inline void Init(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!_prime[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && prime[j] * i <= n; ++j) {
            _prime[i * prime[j]] = true;
            if (!(i % prime[j])) break; 
        }
    }
}

inline int phi(int x) {
    if (x == 1) return 1;
    int Ans = 1;
    for (int i = 1; prime[i] * prime[i] <= x && i <= cnt; ++i)
        if (x % prime[i] == 0) {
            Ans *= prime[i] - 1;
            x /= prime[i];
            while (x % prime[i] == 0) Ans *= prime[i], x /= prime[i];
        }
    if (x != 1) Ans *= x - 1;
    return Ans % mod; 
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    Init(100000);
    T = read(); 
    while (T --) {
        n = read(), mod = read();
        int Ans = 0;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i) continue; 
            (Ans += 1ll * qpow(n % mod, i - 1) * phi(n / i) % mod) %= mod; 
            if (i * i != n) (Ans += 1ll * qpow(n % mod, n / i - 1) * phi(i) % mod) %= mod; 
        }
        printf("%d\n", Ans);
    }
    return 0;
}