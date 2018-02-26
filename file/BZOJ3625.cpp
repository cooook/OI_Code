# include <bits/stdc++.h> 
const int mod = 998244353;
const int maxn = 1 << 22;
int N, rev[maxn], a[maxn], b[maxn], c[maxn], tmp[maxn], Inv2, n, m; 


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
    int w, wn, t;
    for (int k = 2; k <= N; k <<= 1) {
        wn = qpow(3, type == 1 ? ((mod - 1) / k) : (mod - 1 - (mod - 1) / k));
        for (int j = 0; j < N; j += k) {
            w = 1;
            for (int i = 0; i < (k >> 1); ++i, w = 1ll * w * wn % mod)
                t = 1ll * f[i + j + (k >> 1)] * w % mod, f[i + j + (k >> 1)] = (f[i + j] - t + mod) % mod, f[i + j] = (f[i + j] + t) % mod;
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

inline void Get_Inv(int *a, int *b, int n) {
    if (n == 1) return b[0] = qpow(a[0], mod - 2), void();
    Get_Inv(a, b, n + 1 >> 1); Init(n);
    for (int i = 0; i < n; ++i) tmp[i] = a[i];
	for (int i = n; i < N; i++) tmp[i] = 0;
    fft(tmp, 1), fft(b, 1);
    for (int i = 0; i < N; ++i) b[i] = 1ll * b[i] * ((2 - 1ll * tmp[i] * b[i] % mod + mod) % mod) % mod;
    fft(b, -1); for (int i = n; i < N; i++) b[i] = 0;
}

inline void Get_Sqrt(int *a, int *b, int n) {
    if (n == 1) return b[0] = 1, void();
    Get_Sqrt(a, b, n + 1 >> 1); 
    memset(c, 0, sizeof (int) * n * 2); Get_Inv(b, c, n);
    for (int i = 0; i < n; ++i) tmp[i] = a[i];
    for (int i = n; i < N; ++i) tmp[i] = 0;
    fft(tmp, 1), fft(b, 1), fft(c, 1);
    for (int i = 0; i < N; ++i) 
        b[i] = 1ll * (tmp[i] + 1ll * b[i] * b[i] % mod) % mod * c[i] % mod * Inv2 % mod;
    fft(b, -1); for (int i = n; i < N; ++i) b[i] = 0;
}

int main() {
    n = read(), m = read(); Inv2 = qpow(2, mod - 2);
    for (int i = 1; i <= n; ++i) a[read()] = mod - 4; a[0] = 1;
    Get_Sqrt(a, b, m + 1); (b[0] += 1) %= mod; memset(a, 0, sizeof a);
    Get_Inv(b, a, m + 1); 
    for (int i = 1; i <= m; ++i)
        printf("%d\n", 2ll * a[i] % mod);
    return 0;
}