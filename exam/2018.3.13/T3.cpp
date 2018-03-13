# include <stdio.h> 
# include <iostream>
# define int long long 
const int MAXN = 1e5 + 5; 
const int mod = 1e5+3; 
int n, m, fac[MAXN], Inv[MAXN], f[5][2]; 


inline int qpow(int x, int k) {
    register int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans; 
}

inline int C(int n, int m) {
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return 1ll * fac[n] * Inv[m] % mod * Inv[n - m] % mod; 
}

inline void upd(int &x, const int &y) {
    (x += y) %= mod; 
}

signed main() {
    fac[0] = 1; Inv[0] = 1;
    for (int i = 1; i < mod; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    Inv[mod - 1] = qpow(fac[mod - 1], mod - 2);
    for (int i = mod - 2; i; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod;
    scanf("%lld%lld", &n, &m);
    if (((n + m) & 1) || (n < m)) return puts("0"), 0; 
    register int Ans = 0, N = n + m >> 1, M = n - m >> 1, A, B, __C, lim;
    f[0][0] = 1; 
    for (int i = 1; i <= 4; ++i) {
        A = N % mod, B = n % mod; __C = M % mod; 
        N /= mod; n /= mod; M /= mod; lim = std::min(__C, A);
        for (int opt = 0; opt <= 1; ++ opt) if (f[i - 1][opt]) 
            for (int j = 0; j <= lim; ++j) {
                register int last = B - j - opt;
                if (last < 0) last += mod, upd(f[i][1], 1ll * f[i - 1][opt] * C(A, j) % mod * C(last, A) % mod); 
                else upd(f[i][0], 1ll * f[i - 1][opt] * C(A, j) % mod * C(last, A) % mod);
            }
    }
    printf("%lld\n", f[4][0]);
    return 0; 
}

/**
 * 毛爷爷的组合数白做了...
 * 其实也没有, 这道题的思路真是太妙了.
 * 考试的时候一眼就看出来了50分的做法，然后开始化式子, 瞎tm化, 化出了题解最后的式子...
 * 然后发现不能搞, 甚至都乱搞上了生成函数, 但是还是没法搞...  
 * 正解的话就是和myy的组合数类似的做法, 因为mod的数很小, 就可以考虑类似数位DP的做法. 
 * 枚举每一位是多少, 但是只这样是不行的, 因为还有C(n - i, n + m / 2)这种东西, 当n%mod-i小于0的时候不一定为负, 可能模掉了,
 * 这时候我们可以向p进制下的前一位借一， 这样就可以dp来求解了!
**/