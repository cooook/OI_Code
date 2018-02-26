# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
const int maxn = 1 << 22;
const int mod = 1004535809;
int n, a[maxn], b[maxn], c[maxn], tmp[maxn], rev[maxn], N, Inv[maxn], fac[maxn]; 


inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
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
                f[i + j + (k >> 1)] = (f[i + j] - t + mod) % mod,
                f[i + j] = (f[i + j] + t) % mod;
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

inline void Get_Inv(int *A, int *B, int n) {
    if (n == 1) return B[0] = qpow(A[0], mod - 2), void();
    Get_Inv(A, B, n + 1 >> 1); Init(n);
    for (int i = 0; i < n; ++i) tmp[i] = A[i];
    for (int i = n; i < N; ++i) tmp[i] = 0;
    fft(tmp, 1), fft(B, 1);
    for (int i = 0; i < N; ++i) B[i] = 1ll * B[i] * ((2 - 1ll * B[i] * tmp[i] % mod + mod) % mod) % mod;
    fft(B, -1); for (int i = n; i < N; ++i) B[i] = 0;
}

int main() {
    scanf("%d", &n);
    Inv[0] = 1; fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    Inv[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod;
    for (int i = 0; i <= n; ++i) a[i] = (i < 2) ? (1) : (1ll * qpow(2, 1ll * i * (i - 1) / 2 % (mod - 1)) * Inv[i] % mod);
    for (int i = 0; i < n; ++i) b[i] = 1ll * (i + 1) * a[i + 1] % mod; 
    Get_Inv(a, c, n); Init(n); 
    fft(c, 1), fft(b, 1);
    for (int i = 0; i < N; ++i) c[i] = 1ll * c[i] * b[i] % mod;
    fft(c, -1);
    printf("%d\n", 1ll * c[n - 1] * fac[n - 1] % mod);
    return 0;
}