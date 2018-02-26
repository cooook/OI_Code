# include <map> 
# include <stdio.h> 
# include <iostream> 
const int mod = 998244353;
const int MAXN = 1e5 + 5;
const int N = 1e5;
int n, m, prime[MAXN], mu[MAXN], phi[MAXN], cnt, Sum[MAXN];
bool _prime[MAXN]; 
std::map<int, int> mt[MAXN];


inline void Init() {
    mu[1] = phi[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
            _prime[i * prime[j]] = true;
            if (!(i % prime[j])) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= N; ++i) Sum[i] = Sum[i - 1] + phi[i] * mu[i];
}

inline int T(int n, int m) {
    if (n == 1) return Sum[m];
    if (mt[n].count(m)) return mt[n][m];
    int Ans = 0;
    for (int i = 1; i <= m; ++i)
        (Ans += mu[i * n] * phi[i * n]) %= mod;
    return mt[n][m] = Ans;
}

inline int S(int n, int m) {
    if (n == 1) return Sum[m]; 
    if (m == 1) return phi[n];
    int Ans = 0;
    for (int i = 1; i * i <= n; ++i)
        if (n % i == 0) {
            (Ans += 1ll * phi[n / i] * T(i, m / i) % mod) %= mod;
            if (i * i != n) (Ans += 1ll * phi[i] * T(n / i, m / (n / i)) % mod) %= mod;
        }
    return Ans;
}

int main() {
    Init();
    scanf("%d%d", &n, &m);
    if (n > m) std::swap(n, m);
    int Ans = 0;
    for (int i = 1; i <= n; ++i)
        if (mu[i]) (Ans += mu[i] * S(i, m)) %= mod;
    printf("%d\n", (Ans + mod) % mod);
    return 0;
}