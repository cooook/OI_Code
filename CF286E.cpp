# include <math.h> 
# include <stdio.h> 
# include <cstring> 
# include <iostream>
# define GG { puts("NO"); exit(0); }
const int maxn = 1 << 22;
const int MAXN = 1e6 + 5;
const double PI = acos(-1.); 
int n, m, N, rev[maxn], val[MAXN];
bool vis[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Complex {
    double x, r;
    Complex(double x = 0.0, double r = 0.0): x(x), r(r) {  }
    inline Complex operator + (const Complex &a) const { return Complex(x + a.x, r + a.r); }
    inline Complex operator - (const Complex &a) const { return Complex(x - a.x, r - a.r); }
    inline Complex operator * (const Complex &a) const { return Complex(x * a.x - r * a.r, x * a.r + r * a.x); }
}A[maxn], wn[maxn], ni[maxn];

inline void Init(int n) {
    for (N = 1; N < (n << 1); N <<= 1);
    for (int i = 0; i < N; ++i) 
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    for (int i = 0; i <= N; ++i)
        wn[i] = Complex( cos(2 * PI / N * i), sin(2 * PI / N * i)),
        ni[i] = Complex( cos(2 * PI / N * i), - sin(2 * PI / N * i));
}

inline void fft(Complex *f, int type, Complex *wn) {
    register int i, j, k, len; Complex t, *l, *r, *w; 
    for (i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    for (k = 2, len = N >> 1; k <= N; k <<= 1, len >>= 1)
        for (j = 0; j < N; j += k) {
            l = f + j, r = l + (k >> 1), w = wn;
            for (i = 0; i < (k >> 1); ++i, ++l, ++r, w += len)
                t = *r * *w, *r = *l - t, *l = *l + t;
        }
    if (type == -1) for (i = 0; i < N; ++i) f[i].x /= N;
}

int main() {
    n = read(), m = read(); Init(m + 1);
    for (int i = 1; i <= n; ++i) A[val[i] = read()] = Complex(1.0), vis[val[i]] = true;
    fft(A, 1, wn);
    for (int i = 0; i < N; ++i)
        A[i] = A[i] * A[i];
    fft(A, -1, ni);
    int cnt = n;
    for (int i = 2; i <= m; ++i) if (round(A[i].x)) {
        if (!vis[i]) GG
        vis[i] = false;
        -- cnt;
    }
    puts("YES");
    printf("%d\n", cnt);
    for (int i = 1; i <= n; ++i)
        if (vis[val[i]]) printf("%d ", val[i]);
    return 0; 
}
