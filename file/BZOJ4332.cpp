# include <bits/stdc++.h> 
const double PI = acos(-1.0);
const int maxn = 1 << 22;
int M, mod, A, O, S, U, N, rev[maxn], f[maxn], g[maxn], mul[maxn], t[maxn];


struct Complex {
    double x, r;
    Complex(double x = 0.0, double r = 0.0) : x(x), r(r) {  }
    inline Complex operator + (const Complex &a) const { return Complex(x + a.x, r + a.r); }
    inline Complex operator - (const Complex &a) const { return Complex(x - a.x, r - a.r); }
    inline Complex operator * (const Complex &a) const { return Complex(x * a.x - r * a.r, x * a.r + r * a.x); }
}tmp1[maxn], tmp2[maxn];

inline void Init(int n) {
    for (N = 1; N <= (n << 1); N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
}

inline void fft(Complex *f, int type) {
    for (int i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    Complex wn, w, t; 
    for (int k = 2; k <= N; k <<= 1) {
        wn = Complex(cos(2 * PI / k), type * sin(2 * PI / k));
        for (int i = 0; i < N; i += k) {
            w = Complex(1.0);
            for (int j = 0; j < (k >> 1); ++j, w = w * wn)
                t = f[i + j + (k >> 1)] * w, f[i + j + (k >> 1)] = f[i + j] - t, f[i + j] = f[i + j] + t;
        }
    }
    if (type == -1) for (int i = 0; i < N; ++i) f[i].x /= N;
}

inline void FFT(int *a, int *b, int *c) {
    for (int i = 0; i < N; ++i) tmp1[i] = Complex(a[i]), tmp2[i] = Complex(b[i]);
    fft(tmp1, 1); fft(tmp2, 1);
    for (int i = 0; i < N; ++i) tmp1[i] = tmp1[i] * tmp2[i];
    fft(tmp1, -1);
    for (int i = 0; i <= M; ++i) c[i] = (long long)round(tmp1[i].x) % mod;
}

inline void Solve(int n) {
    if (n == 1) return ;
    Solve(n >> 1), FFT(f, g, t); FFT(g, g, g);
    for (int i = 0; i <= M; ++i) (f[i] += t[i]) %= mod; 
    if (n & 1) {
        FFT(g, mul, g);
        for (int i = 0; i <= M; ++i) (f[i] += g[i]) %= mod;     
    }
}

int main() {
    scanf("%d%d%d%d%d%d", &M, &mod, &A, &O, &S, &U); 
    for (int i = 1; i <= M; ++i) mul[i] = (1ll * O * i * i % mod + 1ll * S * i % mod + U) % mod, g[i] = f[i] = mul[i];
    Init(M), Solve(A);
    printf("%d\n", f[M]);
    return 0;
}