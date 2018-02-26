# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
const int mod = 950009857;
const int maxn = 1 << 22;
int n, k, a[maxn], b[maxn], c[maxn], tmp[maxn], rev[maxn], N;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

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
        wn = qpow(7, type == 1 ? ((mod - 1) / k) : (mod - 1 - (mod - 1) / k));
        for (int i = 0; i < N; i += k) {
            w = 1;
            for (int j = 0; j < (k >> 1); ++j, w = 1ll * w * wn % mod)
                t = 1ll * f[i + j + (k >> 1)] * w % mod,
                f[i + j + (k >> 1)] = (f[i + j] - t + mod) % mod,
                f[i + j] = (f[i + j] + t) % mod;
        }
    }
    if (type == -1) {
        int ni = qpow(N, mod - 2);
        for (int i = 0; i < N; ++i) f[i] = 1ll * f[i] * ni % mod;
    }
}

inline void Init(int n) {
    for (N = 1; N < (n << 1); N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
}

inline void Get_Inv(int *a, int *b, int n) {
    if (n == 1) return b[0] = qpow(a[0], mod - 2), void();
    Get_Inv(a, b, n + 1 >> 1); Init(n);
    for (int i = 0; i < n; ++i) tmp[i] = a[i];
    for (int i = n; i < N; ++i) tmp[i] = 0;
    fft(tmp, 1), fft(b, 1);
    for (int i = 0; i < N; ++i) b[i] = (1ll * b[i] * ((2 - 1ll * tmp[i] * b[i] % mod + mod) % mod)) % mod; 
    fft(b, -1); for (int i = n; i < N; ++i) b[i] = 0;
}

int main() {
    n = read(), k = read();
    for (int i = 1; i <= k; ++i) a[read() - 1] = mod - 1; a[0] = 1;
    Get_Inv(a, b, n); Init(n);
    c[0] = 1, k = n;
    while (k) {
        if (k & 1) {
            fft(b, 1), fft(c, 1);
            for (int i = 0; i < N; ++i) c[i] = 1ll * c[i] * b[i] % mod;
            fft(b, -1), fft(c, -1);
            for (int i = n; i < N; ++i) c[i] = 0;
        }
        fft(b, 1);
        for (int i = 0; i < N; ++i) b[i] = 1ll * b[i] * b[i] % mod;
        fft(b, -1);
        for (int i = n; i < N; ++i) b[i] = 0;
        k >>= 1;
    }
    printf("%d\n", 1ll * c[n - 1] * qpow(n, mod - 2) % mod);
    return 0;
}