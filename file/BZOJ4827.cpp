# include <bits/stdc++.h> 
# define int long long 
const int maxn = 1 << 22;
const int MAXN = 50005;
const double PI = acos(-1.0);
int n, m, val1[MAXN], val2[MAXN], t[maxn];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Complex {
    double x, r;
    Complex(double x = 0.0, double r = 0.0) : x(x), r(r) {  }
    inline Complex operator + (const Complex &a) const { return Complex(x + a.x, r + a.r); }
    inline Complex operator - (const Complex &a) const { return Complex(x - a.x, r - a.r); }
    inline Complex operator * (const Complex &a) const { return Complex(x * a.x - r * a.r, x * a.r + r * a.x); }
}A[maxn], B[maxn];
int N, rev[maxn];

inline void Init(int n) {
    for (N = 1; N < n; N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
}

inline void fft(Complex *f, int type) {
    for (int i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    Complex wn, w, t;
    for (int k = 2; k <= N; k <<= 1) {
        wn = Complex(cos(2 * PI / k), type * sin(2 * PI / k));
        for (int j = 0; j < N; j += k) {
            w = Complex(1.0, 0.0);
            for (int i = 0; i < (k >> 1); ++i, w = w * wn)
                t = f[i + j + (k >> 1)] * w, f[i + j + (k >> 1)] = f[i + j] - t, f[i + j] = f[i + j] + t;
        }
    }
    if (type == -1) for (int i = 0; i < N; ++i) f[i].x /= N, f[i].r /= N;
}

inline void gmin(int &x, const int &y) {
    if (x > y) x = y;
}

int Sumx, Sumy, Ans, Totalx, Totaly; 

signed main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) val1[i] = read(), Sumx += val1[i], Totalx += val1[i] * val1[i];
    for (int i = 1; i <= n; ++i) val2[i] = read(), Sumy += val2[i], Totaly += val2[i] * val2[i];
    Init(n * 3);
    for (int i = 1; i <= n; ++i) A[n - i] = Complex(val1[i]);
    for (int i = 1; i <= n << 1; ++i) {
        if (i <= n) B[i - 1] = Complex(val2[i]);
        else B[i - 1] = Complex(val2[i - n]);
    } 
    fft(A, 1); fft(B, 1);
    for (int i = 0; i < N; ++i) A[i] = A[i] * B[i];
    fft(A, -1); 
    for (int i = 0; i < N; ++i) t[i] = round(A[i].x);
    Ans = 0x3f3f3f3f;
    for (int i = n - 1; i <= n - 1 << 1; ++i)
        for (int j = -m; j <= m; ++j)
            gmin(Ans, -2 * t[i] + Totalx + Totaly + 2 * Sumx * j + j * j * n - 2 * j * Sumy);
    printf("%lld\n", Ans);
    return 0;
}