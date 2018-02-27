# include <bits/stdc++.h> 
const int MAXN = 2e5 + 5;
const int maxn = 1 << 21; 
const int mod = 998244353; 
char s[MAXN], t[MAXN]; 
int Q, N, rev[maxn], f[205][MAXN], A[maxn], B[maxn], wn[maxn], Ni, ni[maxn], len = 10000, bl[MAXN], n, m, cnt[1 << 16];
unsigned int cnt1[MAXN], cnt2[MAXN];


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS ++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void read(char s[]) {
    int cnt = 0; char c = getc;
    for (; c != '0' && c != '1'; c = getc) ;
    for (; c == '0' || c == '1'; c = getc) s[++cnt] = c;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)   
        if (k & 1) Ans = 1ll * x * Ans % mod;
    return Ans;
}

inline void Init(int n) {
    for (N = 1; N < n; N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    wn[0] = 1; wn[1] = qpow(3, (mod - 1) / N);
    for (int i = 2; i <= N; ++i) wn[i] = 1ll * wn[i - 1] * wn[1] % mod;
    std::reverse_copy(wn, &wn[N + 1], ni);
    Ni = qpow(N, mod - 2);
}

inline void fft(int *f, int type, int *wn) {
    register int i, j, k, *l, *r, *w, len, t; 
    for (i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    for (k = 2, len = N >> 1; k <= N; k <<= 1, len >>= 1) 
        for (j = 0; j < N; j += k) {
            l = f + j, r = l + (k >> 1), w = wn; 
            for (i = 0; i < (k >> 1); ++i, ++l, ++ r, w += len)
                t = 1ll * *r * *w % mod, *r = (*l - t + mod) % mod, *l = (*l + t) % mod;
        }
    if (type == -1) for (i = 0; i < N; ++i) f[i] = 1ll * f[i] * Ni % mod;
}

inline int count(unsigned int x) {
    return cnt[x >> 16] + cnt[x & 65535];
}

inline void Query(int l, int r, int Len) {
    int Ans = 0, last = l + bl[r] * len - r + 1;
    for (int i = bl[r] + 1; i < bl[r + Len - 1]; ++i) Ans += f[i][last], last += len;
    int st = r, end = std::min(bl[r] * len, r + Len - 1);
    for (; st + 31 <= end; st += 32) Ans += count(cnt1[l + st - r] ^ cnt2[st]);
    for (; st <= end; ++st) Ans += s[l + st - r] ^ t[st]; 
    if (st > r + Len - 1) return printf("%d\n", Ans), void();
    st = (bl[r + Len - 1] - 1) * len + 1, end = r + Len - 1; 
    for (; st + 31 <= end; st += 32) Ans += count(cnt1[l + st - r] ^ cnt2[st]);
    for (; st <= end; ++st) Ans += s[l + st - r] ^ t[st]; 
    printf("%d\n", Ans);
}

int main() {
    for (int i = 1; i < 1 << 16; ++i) cnt[i] = cnt[i - ((i)&(-i))] + 1;

    read(s), read(t);
    n = strlen(s + 1), m = strlen(t + 1);
    for (int i = 1; i <= m; ++i) bl[i] = (i - 1) / len + 1;
    Init(n + len + 2);
    int last = 0;
    for (int i = 1; i <= n; ++i) A[i] = (mod - 1 + ((s[n - i + 1] == '1') << 1)) % mod;
    fft(A, 1, wn);

    for (int i = 0; i * len < m; ++i) {
        register int block = std::min(len, m - i * len), end = std::min(m, (i + 1) * len);
        memset(B, 0, N << 2);
        for (int j = i * len + 1; j <= end; ++j) B[j - i * len] = (mod - 1 + ((t[j] == '1') << 1)) % mod;
        fft(B, 1, wn);
        for (int j = 0; j < N; ++j) B[j] = 1ll * B[j] * A[j] % mod;
        fft(B, -1, ni);
        for (int j = 1; j <= n + 1; ++j)
            f[i + 1][n - j + 2] = ((block - B[j] + mod) % mod) >> 1;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 32; ++j)
            if (s[i + j] == '1') cnt1[i] |= 1ll << j;

    for (int i = 1; i <= m; ++i)
        for (int j = 0; j < 32; ++j)
            if (t[i + j] == '1') cnt2[i] |= 1ll << j;

    Q = read();
    register int l, r, Len, Ans, i;
    while (Q --) {
        l = read() + 1, r = read() + 1, Len = read();
        Query(l, r, Len);
    }
    return 0;
}