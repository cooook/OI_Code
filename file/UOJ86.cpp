# include <stdio.h> 
# include <cstring> 
# include <iostream>
typedef long long ll; 


# ifdef ONLINE_JUDGE
__int128_t n, l, r;
# define Type __int128
# else
ll n, l, r;
# define Type ll
# endif 

const int MAXN = 3e4 + 5;
const int maxn = 1 << 20;
const int mod = 998244353; 
int p, T[105], cnt, tot, digit[105], fac[MAXN], Inv[MAXN], pre[MAXN], power[MAXN];
int N, rev[maxn], w[maxn], Ans[MAXN], Len, f[maxn], g[maxn], tmp1[maxn], tmp2[maxn], tmp3[maxn];



template <typename _t>
inline _t read() {
    register _t x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int qpow(int x, int k, const int &mod) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans;
}

inline int C(int n, int m) {
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return 1ll * fac[n] * Inv[m] % p * Inv[n - m] % p;
}

inline void Get() {
    int g = 1; register bool _Is; 
    while (true) {
        _Is = true;
        for (int i = 1; i < p - 1; ++i)
            if (qpow(g, i, p) == 1) { _Is = false; break; }
        if (_Is) break;
        else ++ g; 
    }
    int tmp = 1; pre[tmp] = 0; power[0] = 1;
    for (int i = 1; i < p - 1; ++i) power[i] = power[i - 1] * g % p, pre[power[i]] = i;
}

inline void fft(int *f, int type) {
    for (int i = 0; i < N; ++i) if (rev[i] < i) std::swap(f[i], f[rev[i]]);
    register int t;
    for (int k = 2; k <= N; k <<= 1) 
        for (int j = 0; j < N; j += k)
            for (int i = 0; i < (k >> 1); ++i) 
                t = 1ll * f[i + j +(k >> 1)] * w[type == 1 ? (N / k * i) : (N - N / k * i)] % mod, 
                f[i + j + (k >> 1)] = (f[i + j] - t + mod) % mod,
                f[i + j] = (f[i + j] + t) % mod;
    if (type == -1) { 
        int ni = qpow(N, mod - 2, mod);
        for (int i = 0; i < N; ++i) f[i] = 1ll * f[i] * ni % mod;
    }
}

inline void Init(int n) {
    for (N = 1; N < (n << 1); N <<= 1) ;

    for (int i = 0; i < N; ++i)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    
    w[0] = 1; w[1] = qpow(3, (mod - 1) / N, mod);
    for (int i = 2; i <= N; ++i) w[i] = 1ll * w[i - 1] * w[1] % mod;
}

inline int get_bit(Type x) {
    int cc = 0;
    while (x) ++ cc, x /= p;
    return cc;
}

inline void Init() {
    Get(); 

    Type QAQ = n; while (QAQ) T[++tot] = QAQ % p, QAQ /= p;
    
    fac[0] = 1; Inv[0] = 1; Len = get_bit(r); Len = std::max(Len, tot);
    
    for (int i = 1; i < p; ++i) fac[i] = fac[i - 1] * i % p; 
    
    Inv[p - 1] = qpow(fac[p - 1], p - 2, p);

    for (int i = p - 2; i; --i) Inv[i] = Inv[i + 1] * (i + 1) % p;

    Init(p);
}

inline void Dp(Type n, int val) {
    if (n < 0) return ;
    int last, t;
    for (int i = 1; i < N; ++i) f[i] = 0, g[i] = 0;
    f[0] = 1; g[0] = 1;
    memset(digit, 0, sizeof digit);
    cnt = 0; 
    while (n) digit[++cnt] = n % p, n /= p;
    for (int i = 1; i <= Len; ++i) {
        for (int j = 0; j < N; ++j) tmp1[j] = tmp2[j] = 0;
        last = 0;
        for (int j = T[i]; j < p; ++j) {
            t = pre[C(j, T[i])];
            ++ tmp1[t];
            if (j < digit[i]) ++ tmp2[t];
            else if (j == digit[i]) last = t;
        }
        if (digit[i] < T[i]) for (int i = 0; i < N; ++i) f[i] = 0;
        else {
            for (int j = 0; j < N; ++j) tmp3[j] = 0;
            for (int j = 0; j < N; ++j) (tmp3[(j + last) % (p - 1)] += f[j]) %= mod;
            memcpy(f, tmp3, N << 2);
        }
        fft(tmp1, 1), fft(tmp2, 1), fft(g, 1);
        for (int j = 0; j < N; ++j)
            tmp1[j] = 1ll * tmp1[j] * g[j] % mod, tmp2[j] = 1ll * tmp2[j] * g[j] % mod;
        fft(tmp1, -1), fft(tmp2, -1);
        memset(g, 0, N << 2);
        for (int j = 0; j < N; ++j) (g[j % (p - 1)] += tmp1[j]) %= mod, (f[j % (p - 1)] += tmp2[j]) %= mod;
    }
    for (int i = 0; i < p - 1; ++i)
        (Ans[power[i]] += f[i] * val) %= mod;
}

int main() {
    p = read<int>(), n = read<Type>();
    l = read<Type>() - 1, r = read<Type>();
    Ans[0] = (r - l) % mod;
    Init();

    Dp(r, 1); 
    Dp(l, -1);
    for (int i = 1; i <= p - 1; ++i) (Ans[0] -= ((Ans[i] += mod) %= mod)) %= mod;
    (Ans[0] += mod) %= mod;
    for (int i = 0; i <= p - 1; ++i) printf("%d\n", Ans[i]);
    return 0;
}