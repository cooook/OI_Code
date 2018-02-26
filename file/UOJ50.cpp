# include <stdio.h> 
# include <cstring> 
# include <iostream>
const int mod = 998244353;
const int maxn = 1 << 22; 
const int MAXN = 2e5 + 5;
int n, rev[maxn], N, f[maxn], g[maxn], h[maxn], fac[MAXN], Inv[MAXN], tmp1[maxn], tmp2[maxn];
char s[MAXN];


inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

inline int del(int a, int b) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}

inline int sum(int a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

inline void fft(int *f, int type) {
    for (int i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    int wn, w, t;
    for (int k = 2; k <= N; k <<= 1) {
        wn = qpow(3, type == 1 ? ((mod - 1) / k) : (mod - 1 - (mod - 1) / k));
        for (int i = 0; i < N; i += k) {
            w = 1;
            for (int j = 0; j < (k >> 1); ++j, w = 1ll * w * wn % mod)
                t = 1ll * f[i + j + (k >> 1)] * w % mod, 
                f[i + j + (k >> 1)] = del(f[i + j], t),
                f[i + j] = sum(f[i + j], t);
        }
    }
    if (type == -1) {
        int Ni = qpow(N, mod - 2);
        for (int i = 0; i < N; ++i) f[i] = 1ll * f[i] * Ni % mod; 
    }
}

inline void Init(int n) {
    for (N = 1; N < (n << 1); N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
}

inline void Solve(int l, int r) {
    if (l == r) return f[l] = 1ll * f[l] * Inv[l] % mod, void();
    register int mid = l + r >> 1;
    Solve(l, mid);
    Init(r - l + 1);
    memset(tmp1, 0, N << 2);
    memset(tmp2, 0, N << 2);
    for (int i = l; i <= mid; ++i) tmp1[i - l] = f[i];
    for (int i = 0; i <= r - l; ++i) 
        if (i < l) tmp2[i] = f[i] * 2 % mod;
        else if (i <= mid) tmp2[i] = f[i];
    fft(tmp1, 1), fft(tmp2, 1);
    for (int i = 0; i < N; ++i) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % mod;
    fft(tmp1, -1);
    for (int i = mid + 1; i <= r; ++i) add(h[i], tmp1[i - l]);
    memset(tmp1, 0, N << 2);
    memset(tmp2, 0, N << 2);
    for (int i = l; i <= mid; ++i) tmp1[i - l] = h[i];
    for (int i = 0; i <= r - l; ++i) tmp2[i] = g[i];
    fft(tmp1, 1), fft(tmp2, 1); 
    for (int i = 0; i < N; ++i) tmp1[i] = 1ll * tmp1[i] * tmp2[i] % mod; 
    fft(tmp1, -1);
    for (int i = mid + 1; i <= r; ++i) add(f[i], 1ll * tmp1[i - l - 1] * fac[i - 1] % mod);
    Solve(mid + 1, r);
}

int main() {
    scanf("%d%s", &n, s);
    fac[0] = 1; Inv[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    Inv[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod;
    for (int i = 0; s[i]; ++i)
        if (s[i] == '1') g[i] = 1ll * Inv[i] * Inv[2] % mod;
    f[1] = 1;
    Solve(1, n);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", 1ll * f[i] * fac[i] % mod);
    return 0;
}