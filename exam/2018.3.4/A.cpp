# include <bits/stdc++.h>
const int mod = 1005060097;
const int maxn = 1 << 22; 
int n, m, A[maxn], B[maxn], tmp[maxn], wn[maxn], ni[maxn], N, rev[maxn], Max;


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline void Pre(int n) {
    for (Max = 1; Max < (n << 1); Max <<= 1) ;
    wn[0] = 1; wn[1] = qpow(5, (mod - 1) / Max);
    for (int i = 2; i <= Max; ++i) wn[i] = 1ll * wn[i - 1] * wn[1] % mod;
    std::reverse_copy(wn, &wn[Max + 1], ni);
}

inline void Init(int n) {
    for (N = 1; N < n; N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    Max = N; 
    wn[0] = 1; wn[1] = qpow(5, (mod - 1) / N);
    for (int i = 2; i <= N; ++i) wn[i] = 1ll * wn[i - 1] * wn[1] % mod;
    std::reverse_copy(wn, &wn[N + 1], ni);
}

inline void fft(int *f, int type, int *wn) {
    register int *l, *r, *w, len, i, j, k, t;
    for (i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    for (k = 2, len = Max >> 1; k <= N; k <<= 1, len >>= 1)
        for (i = 0; i < N; i += k)  {
            l = f + i, r = l + (k >> 1), w = wn;
            for (j = 0; j < (k >> 1); ++j, ++l, ++r, w += len)
                t = 1ll * *r * *w % mod, *r = (*l - t + mod) % mod, *l = (*l + t) % mod; 
        }
    if (type == -1) {
        int Ni = qpow(N, mod - 2);
        for (i = 0; i < N; ++i) f[i] = 1ll * f[i] * Ni % mod; 
    }
}

inline void Get_Inv(int *a, int *b, int n) {
    static int tmp[maxn]; 
    if (n == 1) return b[0] = qpow(a[0], mod - 2), void();
    Get_Inv(a, b, n + 1 >> 1); Init(n << 1);
    for (int i = 0; i < n; ++i) tmp[i] = a[i];
    for (int i = n; i < N; ++i) tmp[i] = 0, b[i] = 0;
    fft(tmp, 1, wn); fft(b, 1, wn);
    for (int i = 0; i < N; ++i) b[i] = 1ll * b[i] * (2 - (1ll * b[i] * tmp[i] % mod) + mod) % mod; 
    fft(b, -1, ni); for (int i = n; i < N; ++i) b[i] = 0; 
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) -- A[read()];   
    A[0] = 1;
    Get_Inv(A, B, n + 1);
    printf("%d\n", (B[n] + mod) % mod);
    // while (true);
    return 0;
}