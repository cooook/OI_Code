# include <stdio.h>
# include <cstring>
# include <iostream>
# include <algorithm>
const int maxn = 1 << 21; 
const int mod = 998244353; 
int n, k, wn[maxn], ni[maxn], N, rev[maxn], Max, f[maxn], a[maxn], b[maxn], c[maxn], wq[maxn];


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline void Pre(int n) { // Init_wn ; 
    for (Max = 1; Max < (n << 1); Max <<= 1) ;
    wn[0] = 1; wn[1] = qpow(3, (mod - 1) / Max);
    for (int i = 2; i <= Max; ++i) wn[i] = 1ll * wn[i - 1] * wn[1] % mod;
    std::reverse_copy(wn, &wn[Max + 1], ni);
}

inline void Init(int n) {
    for (N = 1; N < n; N <<= 1);
    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    Max = N; 
    wn[0] = 1; wn[1] = qpow(3, (mod - 1) / N);
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

inline void Mul(int *a, int *b, int *c, int n, int m)  { // a * b => c deg(a) = n, deg(b) = m
    static int tmp1[maxn], tmp2[maxn];
    Init(n + m); 
    for (int i = 0; i < n; ++i) tmp1[i] = a[i];
    for (int i = 0; i < m; ++i) tmp2[i] = b[i];
    for (int i = n; i < N; ++i) tmp1[i] = 0;
    for (int i = m; i < N; ++i) tmp2[i] = 0; 
    fft(tmp1, 1, wn), fft(tmp2, 1, wn);
    for (int i = 0; i < N; ++i) c[i] = 1ll * tmp1[i] * tmp2[i] % mod;
    fft(c, -1, ni);
}

inline void Mod(int *a, int *b, int *c, int n, int m) { // a % b => c deg(a) = n, deg(b) = m
    static int tmp1[maxn], tmp2[maxn], tmp3[maxn]; 
    std::reverse_copy(a, a + n, tmp1);
    std::reverse_copy(b, b + m, tmp2);
    memcpy(c, a, n << 2);
    Get_Inv(tmp2, tmp3, n - m + 1);
    Mul(tmp1, tmp3, tmp2, n - m + 1, n - m + 1);
    std::reverse(tmp2, tmp2 + n - m + 1);
    std::fill(&tmp2[n - m + 1], &tmp2[n + 1], 0);
    Mul(tmp2, b, tmp1, n - m + 1, m);
    for (int i = 0; i < m; ++i) c[i] = (c[i] - tmp1[i] + mod) % mod;/*, printf("c[%d] = %d\n", i, c[i]);*/ 
    for (int i = m; i <= n; ++i) c[i] = 0; // 只能保证前m项是对的.  
}

int main() {
    n = read(), k = read(); 

    for (int i = 1; i <= k; ++i) a[i] = (mod - read() % mod); a[0] = 1; 
    Get_Inv(a, f, k * 2 + 1); // 预处理前2 * k 项. 

    if (n <= k * 2) return printf("%d\n", (f[n] + mod) % mod), 0; 

    
    wq[k] = 1;
    for (int i = 0; i < k; ++i) wq[i] = a[k - i];

    static int tmp[maxn]; 
    
    b[0] = c[1] = 1;
    int power = n - k, Ans = 0;

    Mod(c, wq, c, k + 1, k + 1);
    
    while (power) {
        if (power & 1) {
            Mul(b, c, tmp, k, k);
            for (int i = k << 1; i < N; ++i) tmp[i] = 0; 
            Mod(tmp, wq, b, k << 1, k + 1);
        }
        Mul(c, c, tmp, k, k);
        for (int i = k << 1; i < N; ++i) tmp[i] = 0;
        Mod(tmp, wq, c, k << 1, k + 1);
        power >>= 1;
    }

    for (int i = 0; i < k; ++i)
        (Ans += 1ll * f[k + i] * b[i] % mod) %= mod;
    printf("%d\n", Ans);
    return 0;
}