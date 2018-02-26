# include <bits/stdc++.h> 
const int MAXN = 2e5 + 5;
const int maxn = 1 << 20; 
const double PI = acos(-1.0);
int n, m, k, N, rev[maxn], Sum[MAXN][4];  char s[MAXN], t[MAXN];
bool S[MAXN][4]; 


struct Complex {
    double x, r;
    Complex() : x(0), r(0) {  }
    Complex(const double &x, const double &r) : x(x), r(r) {  }
    inline Complex operator + (const Complex &a) const { return Complex(x + a.x, r + a.r); }
    inline Complex operator - (const Complex &a) const { return Complex(x - a.x, r - a.r); }
    inline Complex operator * (const Complex &a) const { return Complex(x * a.x - r * a.r, x * a.r + r * a.x); }
}A[maxn], B[maxn], wn[maxn], Inv[maxn], C[maxn];

inline void Init(int n) {
    for (N = 1; N < n; N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    for (int i = 0; i <= N; ++i)
        wn[i] = Complex( cos(2 * PI / N * i), sin(2 * PI / N * i)),
        Inv[i] = Complex( cos(2 * PI / N * i), - sin(2 * PI / N * i));
}

inline void fft(Complex *f, int type, Complex *wn) {
    register int i, j, k, Len; 
    register Complex t, *l, *r, *w;
    for (i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    for (k = 2, Len = N >> 1; k <= N; k <<= 1, Len >>= 1) 
        for (j = 0; j < N; j += k) {
            l = f + j, r = f + j + (k >> 1), w = wn;
            for (i = 0; i < (k >> 1); ++i) 
                t = *r * *w, *r = *l - t, *l = *l + t, ++l, ++r, w += Len;
        }
    if (type == -1) for (int i = 0; i < N; ++i) f[i].x /= N;
}

inline int Get(char c) {
    if (c == 'A') return 0;
    else if (c == 'T') return 1;
    else if (c == 'C') return 2;
    else return 3;
} 

inline void Work(char *s, int n, bool S[][4]) {
    memset(Sum[0], 0, 16);
    register int id; 
    for (int i = 1; s[i]; ++i) {
        id = Get(s[i]);
        for (int j = 0; j <= 3; ++j) {
            Sum[i][j] = Sum[i - 1][j] + (id == j); 
            S[i][j] |= (Sum[i][j] - Sum[i >= k + 1 ? i - k - 1 : 0][j] > 0);
        }
    }
    memset(Sum[n + 1], 0, 16); 
    for (int i = n; i; --i) {
        id = Get(s[i]); 
        for (int j = 0; j <= 3; ++j) {
            Sum[i][j] = Sum[i + 1][j] + (id == j); 
            S[i][j] |= (Sum[i][j] - Sum[i + k + 1 <= n ? i + k + 1 : n + 1][j] > 0);
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", s + 1, t + 1); 
    std::reverse(&t[1], &t[m + 1]); 

    Work(s, n, S);

    Init(n + m + 2);

    for (int j = 0; j <= 3; ++j) {
        for (int i = 0; i <= n; ++i) A[i] = Complex(S[i][j], 0.0);
        for (int i = 1; i <= m; ++i) B[i] = Complex(Get(t[i]) == j, 0.0);
        B[0] = Complex(); 
        for (int i = n + 1; i < N; ++i) A[i] = Complex();
        for (int i = m + 1; i < N; ++i) B[i] = Complex();
        fft(A, 1, wn), fft(B, 1, wn);
        for (int i = 0; i < N; ++i)
            C[i] = C[i] + A[i] * B[i];
    }

    fft(C, -1, Inv); 

    int Ans = 0;
    for (int i = m + 1; i <= n + m; ++i)
        Ans += (int)(C[i].x + 0.5) == m;
    printf("%d\n", Ans);
    // while (true);
    return 0;
}
