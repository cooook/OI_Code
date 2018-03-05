# include <stdio.h>
# define int long long
typedef long long ll;
const int MAXN = 1e6 + 5;
const int mod = 1005060097;
const int Inv2 = 502530049;
int prime[MAXN], mu[MAXN], cnt;
bool _prime[MAXN];
ll n;


inline void Init() {
    static const int N = 1e6;
    mu[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
            _prime[i * prime[j]] = true;
            if (!(i % prime[j])) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
}

inline int G(int l, int r) {
    register int len = (r - l + 1) % mod, sum = (l + r) % mod;
    return sum * len % mod * Inv2 % mod;
}

inline int Get(int n, int g) {
    register int Ans = 0, last;
    for (int i = 1; i <= n; i = last + 1) {
        last = n / (n / i);
        (Ans += G(i, last) * g % mod * (n / i) % mod) %= mod;
    }
    return Ans;
}

signed main() {
    Init();
    scanf("%lld", &n);
    register int Ans = 0;
    for (int i = 1; i * i <= n; ++i)
        (Ans += mu[i] * Get(n / i / i, i) % mod) %= mod;
    (Ans -= G(1, n)) %= mod;
    (Ans += mod) %= mod;
    printf("%d\n", (Ans + mod) % mod);
    return 0;
}
