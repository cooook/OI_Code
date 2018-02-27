# include <math.h> 
# include <stdio.h> 
# include <cstring> 
# include <iostream>
const int P = 31623;
const int MAXN = 1e5 + 5; 
const int maxn = 1 << 21;
const int mod = 1e9+7; 
const double PI = acos(-1.0);
typedef long long ll; 
ll n; int k, fac[MAXN], Inv[MAXN], f[MAXN], g[MAXN], N, rev[maxn];  


inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

struct Complex {
    double x, r;
    Complex():x(0), r(0) {  }
    Complex(double x, double r) : x(x), r(r) {  }
    inline Complex operator + (const Complex &a) const { return Complex(x + a.x, r + a.r); }
    inline Complex operator - (const Complex &a) const { return Complex(x - a.x, r - a.r); }
    inline Complex operator * (const Complex &a) const { return Complex(x * a.x - r * a.r, x * a.r + r * a.x); }
}A[maxn], B[maxn], C[maxn], D[maxn], wn[maxn], ni[maxn];

inline void Init(int n) {
    for (N = 1; N < (n << 1); N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    for (int i = 0; i <= N; ++i)
        wn[i] = Complex(cos(2 * PI / N * i), sin(2 * PI / N * i)), 
        ni[i] = Complex(cos(2 * PI / N * i), -sin(2 * PI / N * i));
}

inline void fft(Complex *f, int type, Complex *wn) {
    register Complex *l, *r, *w, t; register int i, j, k, len;
    for (i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    for (k = 2, len = N >> 1; k <= N; k <<= 1, len >>= 1) 
        for (j = 0; j < N; j += k) {
            l = f + j, r = l + (k >> 1), w = wn;
            for (i = 0; i < (k >> 1); ++i)
                t = *r * *w, *r = *l - t, *l = *l + t, ++l, ++r, w += len;
        }
    if (type == -1) for (i = 0; i < N; ++i) f[i].x /= N;
}

inline void FFT(int *a, int *b, int *Ans, int p) {
    for (int i = 0; i < N; ++i) A[i] = Complex(), B[i] = Complex(), C[i] = Complex(), D[i] = Complex();
    int tot = 1;
    for (int i = 0; i <= k; ++i) {
        A[i].x = (1ll * a[i] * fac[k - i] % mod) / P;
        B[i].x = (1ll * a[i] * fac[k - i] % mod) % P;
        C[i].x = (1ll * (1ll * b[i] * fac[k - i] % mod) * tot % mod) / P;
        D[i].x = (1ll * (1ll * b[i] * fac[k - i] % mod) * tot % mod) % P;
        tot = 1ll * tot * p % mod;
    }

    fft(A, 1, wn), fft(B, 1, wn), fft(C, 1, wn), fft(D, 1, wn);
    for (int i = 0; i < N; ++i) {
        register Complex Ai = A[i], Bi = B[i], Ci = C[i], Di = D[i];
        A[i] = Ai * Ci, B[i] = Ai * Di + Bi * Ci, C[i] = Bi * Di;
    }
    fft(A, -1, ni), fft(B, -1, ni), fft(C, -1, ni);
    for (int i = 0; i <= k; ++i) {
        Ans[i] = (((ll)round(A[i].x) % mod * P % mod * P % mod + 
        (ll)round(B[i].x) % mod * P % mod) % mod + (ll)round(C[i].x) % mod) % mod;
        Ans[i] = 1ll * Ans[i] * Inv[k] % mod * Inv[k - i] % mod; 
    }
}

inline int Cobm(int n, int m) {
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return 1ll * fac[n] * Inv[n - m] % mod * Inv[m] % mod;
} 

int main() {
    scanf("%lld%d", &n, &k);
    if (n > k) return puts("0"), 0; 
    fac[0] = 1; Inv[0] = 1;
    for (int i = 1; i <= k; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    Inv[k] = qpow(fac[k], mod - 2);
    for (int i = k - 1; i; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= k; ++i) g[i] = Cobm(k, i);  f[0] = 1; 
    Init(k + 1); 
    int t = 2; 
    for (; n; n >>= 1, FFT(g, g, g, t), t = 1ll * t * t % mod)
        if (n & 1) FFT(g, f, f, t);
    int Ans = 0;
    for (int i = 0; i <= k; ++i) (Ans += f[i]) %= mod;
    printf("%d\n", Ans);
    return 0;
}