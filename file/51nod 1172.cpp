# include <math.h> 
# include <stdio.h> 
# include <iostream>
const int mod = 1e9 + 7;
const int P = 31623;
const int maxn = 1 << 20; 
const int MAXN = 1e5 + 5;
const double PI = acos(-1.0); 
typedef long long ll; 
int n, k, val[MAXN], Inv[MAXN], Ans[maxn], N, rev[maxn]; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Complex {
    double x, r;
    Complex(double x = 0.0, double r = 0.0): x(x), r(r) {  } 
    inline Complex operator + (const Complex &a) const { return Complex(x + a.x, r + a.r); }
    inline Complex operator - (const Complex &a) const { return Complex(x - a.x, r - a.r); }
    inline Complex operator * (const Complex &a) const { return Complex(x * a.x - r * a.r, x * a.r + r * a.x); }
}A[maxn], B[maxn], C[maxn], D[maxn];

Complex wn[maxn], Inv_wn[maxn];

inline void fft(Complex *f, int type, Complex *wn) {
    for (int i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    Complex t;
    for (int k = 2; k <= N; k <<= 1) 
        for (int i = 0; i < N; i += k)
            for (int j = 0; j < (k >> 1); ++j)
                t = f[i + j + (k >> 1)] * wn[N / k * j], f[i + j + (k >> 1)] = f[i + j] - t, f[i + j] = f[i + j] + t; 
    if (type == -1) for (int i = 0; i < N; ++i) f[i].x /= N, f[i].r /= N; 
}

inline void Init(int n) {
    for (N = 1; N < (n << 1); N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    for (int i = 0; i <= N; ++i)
        wn[i] = Complex(cos(2 * PI / N * i), sin(2 * PI / N * i)), 
        Inv_wn[i] = Complex(cos(2 * PI / N * i), -sin(2 * PI / N * i));
}

int main() {
    n = read(), k = read();
    Init(n); 
    for (int i = 1; i <= n; ++i) val[i] = read();
    Inv[1] = 1;
    for (int i = 2; i <= n; ++i) Inv[i] = 1ll * (mod - mod / i) * Inv[mod % i] % mod; 
    int Com = 1;
    for (int i = 1; i <= n; ++i) {
        A[i] = Complex(Com / P); B[i] = Complex(Com % P); 
        Com = 1ll * Com * (i + k - 1) % mod * Inv[i] % mod;
    } 
    for (int i = 1; i <= n; ++i) 
        C[i] = Complex(val[i] / P), D[i] = Complex(val[i] % P);
    fft(A, 1, wn), fft(B, 1, wn), fft(C, 1, wn), fft(D, 1, wn);
    Complex a, b, c, d;
    for (int i = 0; i < N; ++i) {
        a = A[i], b = B[i], c = C[i], d = D[i]; 
        A[i] = a * c, B[i] = a * d + b * c, C[i] = b * d;
    }
    fft(A, -1, Inv_wn), fft(B, -1, Inv_wn), fft(C, -1, Inv_wn);
    for (int i = 0; i < N; ++i)
        Ans[i] = (((ll)round(A[i].x) % mod * P % mod * P % mod + (ll)round(B[i].x) % mod * P % mod) % mod + (ll)round(C[i].x) % mod) % mod;
    for (int i = 2; i <= n + 1; ++i)
        printf("%d\n", Ans[i]);
    // while (true);
    return 0;
}


/*
 
    51nod 1565 
    51nod 1172 
*/ 
