# include <stdio.h> 
# include <cstring> 
# include <iostream>
const int MAXN = 2e5 + 5; 
const int mod = 1005060097;
const int G = 5;
const int maxn = 1 << 20;
int n, m, last, cnt, Mx[MAXN], fa[MAXN], trans[MAXN][26], size[MAXN], t[MAXN], w[MAXN];
char s[MAXN]; int A[maxn], Ans[maxn], rev[maxn], N, ni, Wn[maxn], IWn[maxn];


inline void Extend(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1; ++ size[np];
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
            fa[nq] = fa[q]; fa[q] = fa[np] = nq;
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    }
    last = np;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod; 
    return Ans;
}

inline void Swap(int &x, int &y) {
    x ^= y; y ^= x; x ^= y;
}

inline void fft(int *f, int type, int *wn) {
    for (int i = 0; i < N; ++i) if (rev[i] < i) Swap(f[i], f[rev[i]]);
    register int t; 
    for (int k = 2; k <= N; k <<= 1) 
        for (int i = 0; i < N; i += k) 
            for (int j = 0; j < k >> 1; ++j)
                t = 1ll * f[i + j + (k >> 1)] * wn[N / k * j] % mod,
                f[i + j + (k >> 1)] = (f[i + j] - t + mod) % mod,
                f[i + j] = (f[i + j] + t) % mod;
    if (type == -1)
        for (int i = 0; i < N; ++i) f[i] = 1ll * f[i] * ni % mod;
}

int main() {
    scanf("%d%d", &n, &m);

    int i; 
    
    
    for (N = 1; N < (m + 1 << 1); N <<= 1);
    for (i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    ni = qpow(N, mod - 2);

    int tmp = qpow(G, (mod - 1) / N);

    Wn[0] = IWn[0] = 1;

    for (int i = 1; i < N; ++i) {
        Wn[i] = 1ll * Wn[i - 1] * tmp % mod;
        IWn[i] = qpow(Wn[i], mod - 2);
    }

    scanf("%s", s + 1); 
    last = ++ cnt; 
    for (i = 1; s[i]; ++i) Extend(s[i] - 'a'); 
    

    for (i = 1; i <= cnt; ++i) ++ w[Mx[i]];
    for (i = 1; s[i]; ++i) w[i] += w[i-1];
    for (i = cnt; i; --i) t[w[Mx[i]] --] = i;
    for (i = cnt; i; --i) {
        size[fa[t[i]]] += size[t[i]];
        if (size[t[i]] <= m) 
            (A[size[t[i]]] += 1ll * (Mx[t[i]] - Mx[fa[t[i]]]) * size[t[i]] % mod) %= mod;
    }

    Ans[0] = 1;
    while (n) {

        if (n & 1) {
            fft(Ans, 1, Wn), fft(A, 1, Wn);
            for (i = 0; i < N; ++i)
                Ans[i] = 1ll * Ans[i] * A[i] % mod;

            fft(Ans, -1, IWn); fft(A, -1, IWn);
        }

        n >>= 1;
        fft(A, 1, Wn);

        for (i = 0; i < N; ++i)
            A[i] = 1ll * A[i] * A[i] % mod;

        fft(A, -1, IWn);
        
        for (int i = m + 1; i < N; ++i) A[i] = 0, Ans[i] = 0;
    }
    
    printf("%d\n", Ans[m]);
    return 0;
}