# include <bits/stdc++.h>
const int maxn = 1 << 22;
const double PI = acos(-1.0);
int n, m, t, x, rev[maxn], N, dis[105][105];
double f[105][40005], g[105][40005], p[105][40005];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {int u, v, w;}a[105];
struct Complex {
    double x, r;
    Complex(double _ = 0.0, double __ = 0.0) {x = _; r = __;}
    inline Complex operator + (const Complex &a) const {return (Complex){x + a.x, r + a.r};}
    inline Complex operator - (const Complex &a) const {return (Complex){x - a.x, r - a.r};}
    inline Complex operator * (const Complex &a) const {return (Complex){x * a.x - r * a.r, x * a.r + r * a.x};}
}A[maxn], B[maxn];

inline void fft(Complex *f, int type) {
    for (int i = 0; i < N; i++) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    Complex wn, w, t;
    for (int k = 2; k <= N; k <<= 1) {
        wn = Complex(cos(2 * PI / k), type * sin(2 * PI / k));
        for (int i = 0; i < N; i += k) {
            w = Complex(1);
            for (int j = 0; j < k >> 1; j++, w = w * wn)
                t = f[i + j + (k >> 1)] * w, f[i + j + (k >> 1)] = f[i + j] - t, f[i + j] = f[i + j] + t;
        }
    }
    if (!~type) for (int i = 0; i < N; i++) f[i].x /= N;
}

template <typename _t>
inline void gmin(_t &x, const _t &y) {
    if (x > y) x = y;
}

inline void Solve(int e, int l, int r) {
    register int mid = l + r >> 1;
    for (int i = 0; i < N; i++) A[i] = B[i] = Complex();
    for (int i = mid + 1; i <= r; i++) A[r - i] = Complex(f[a[e].v][i]);
    for (int i = 1; i <= r - l + 1; i++) B[i] = Complex(p[e][i]);
    fft(A, 1); fft(B, 1);
    for (int i = 0; i < N; i++) A[i] = A[i] * B[i];
    fft(A, -1);
    for (int i = l; i <= mid; i++) g[e][i] += A[r - i].x;
}

inline void Init(int len) {
    for (N = 1; N <= len; N <<= 1);
    for (int i = 0; i < N; i++)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
}

inline void CDQ(int l, int r) {
    if (l == r) {
        for (int i = 1; i < n; i++) f[i][l] = 1e16;
        for (int i = 1; i <= m; i++) gmin(f[a[i].u][l], g[i][l] + a[i].w);
        return;
    }
    register int mid = l + r >> 1, len = r - l + r - mid;
    CDQ(mid + 1, r); Init(len); 
    for (int i = 1; i <= m; i++) Solve(i, l, r);
    CDQ(l, mid);
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    memset(dis, 0x3f, sizeof dis);
    n = read(), m = read(), t = read(), x = read();
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int i = 1; i <= m; i++) {
        register int u = read(), v = read(), w = read();
        for (int j = 1; j <= t; j++) p[i][j] = read() / 100000.0;
        a[i] = (edge){u, v, w}; dis[u][v] = w;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                gmin(dis[i][j], dis[i][k] + dis[k][j]);
    for (int i = 1; i <= t; i++) f[n][i] = 0;
    for (int i = 1; i <= n; i++) for (int j = t + 1; j <= t << 1; j++) f[i][j] = dis[i][n] + x;
    Init((t << 1) + t);
    for (int i = 1; i <= m; i++) Solve(i, 0, t << 1);
    CDQ(0, t);
    printf("%.10f\n", f[1][0]);
    return 0;
}