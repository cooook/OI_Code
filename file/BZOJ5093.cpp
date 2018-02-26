// write by Cooook . 
# include <bits/stdc++.h> 
# define int long long 
const int mod = 998244353;
const int maxn = 1 << 22;
const int MAXN = 2e5 + 5;
const int G = 3;
typedef long long ll;
int n, k, N, rev[maxn];
ll A[maxn], B[maxn], fac[MAXN], Inv[MAXN];


inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline void fft(ll *f, int type) {
    for (int i = 0; i < N; ++i)
        if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    ll wn, w, t;
    for (int k = 2; k <= N; k <<= 1) {
        wn = qpow(G, type == 1 ? ((mod - 1) / k) : (mod - 1 - (mod - 1) / k));
        for (int i = 0; i < N; i += k) {
            w = 1;
            for (int j = 0; j < (k >> 1); ++j, w = w * wn % mod)
                t = f[i + j + (k >> 1)] * w % mod, f[i + j + (k >> 1)] = (f[i + j] - t + mod) % mod, f[i + j] = (f[i + j] + t) % mod; 
        } 
    }
    if (type == -1) {
        ll Ni = qpow(N, mod - 2);
        for (int i = 0; i < N; ++i) f[i] = f[i] * Ni % mod;
    }
}

signed main() {
    scanf("%lld%lld", &n, &k);
    fac[0] = 1; Inv[0] = 1;
    for (int i = 1; i <= k; ++i) fac[i] = fac[i - 1] * i % mod;
    Inv[k] = qpow(fac[k], mod - 2);
    for (int i = k - 1; i > 0; --i) Inv[i] = Inv[i + 1] * (i + 1) % mod;
    for (N = 1; N < (k + 1 << 1); N <<= 1) ;
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    for (int i = 0; i <= k; ++i) 
        A[i] = (((i & 1) ? -1 : 1) * Inv[i] + mod) % mod, B[i] = qpow(i, k) * Inv[i] % mod;
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < N; ++i) A[i] = A[i] * B[i] % mod;
    fft(A, -1);
    ll Ans = 0, Sum = 1;
    for (int i = 0; i <= k; ++i) {
        if (!Sum) break;
        (Ans += A[i] * Sum % mod * qpow(2, n - i - 1) % mod) %= mod;
        Sum = Sum * (n - i - 1) % mod;
    }
    (Ans *= n) %= mod;
    Ans *= qpow(2, 1ll * (n - 1) * (n - 2) / 2);
    printf("%lld\n", (Ans + mod) % mod);
    return 0;
}