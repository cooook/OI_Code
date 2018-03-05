# include <bits/stdc++.h> 
const int mod = 1005060097;
const int maxn = 1 << 20; 
const int MAXN = 2e5 + 5; 
int n, m, Ans[MAXN], cnt[1 << 16], N, rev[maxn], Ni, wn[maxn], ni[maxn], A[maxn], B[maxn], Max; 
char data[MAXN], test[MAXN]; 
 
 
inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
}

inline int count(int x) {
    return cnt[x >> 16] + cnt[x & 65535]; 
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline void Init(int n) {
    for (N = 1; N < n; N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    wn[0] = 1; wn[1] = qpow(5, (mod - 1) / N);
    for (int i = 2; i <= N; ++i) wn[i] = 1ll * wn[i - 1] * wn[1] % mod;
    std::reverse_copy(wn, &wn[N + 1], ni);
}

inline void fft(int *f, int type, int *wn) {
    register int *l, *r, *w, len, i, j, k, t;
    for (i = 0; i < N; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    for (k = 2, len = N >> 1; k <= N; k <<= 1, len >>= 1)
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
 
int main() {
    scanf("%d%d", &m, &n); 
    scanf("%s%s", data, test);
    for (int i = 1; i < 1 << 16; ++i) cnt[i] = cnt[i - (i & (-i))] + 1;
    for (int i = n; i < n * 2; ++i) data[i] = data[i - n]; 
    std::reverse(data, &data[n << 1]);
    Init(n << 2); 
    for (int i = 0; i < n; ++i) A[i] = (test[i] == '1' ? (1) : -1);
    for (int i = 0; i < n << 1; ++i) B[i] = (data[i] == '1' ? (1) : -1);
    fft(A, 1, wn), fft(B, 1, wn);
    for (int i = 0; i < N; ++i)
        A[i] = 1ll * A[i] * B[i] % mod;
    fft(A, -1, ni);
    for (int i = n - 1; i <= n * 2 - 1; ++i)
        Ans[n * 2 - i - 1] = ((n + ((A[i] + mod) % mod)) % mod) >> 1;
    int full = (1 << m + 1) - 1, res = n + n + m + 1, pos, cnt, X1, X2, S;
    for (int i = 0; i <= full; ++i) {
        S = i; cnt = count(S), X2 = S >> m & 1; S ^= X2 << m;
        pos = (((X2 * 2 - 1) * S % n) + n) % n;
        gmin(res, cnt + n - Ans[pos]); 
        gmin(res, cnt + Ans[pos] + 1);
    }
    printf("%d\n", res);
    return 0;
}