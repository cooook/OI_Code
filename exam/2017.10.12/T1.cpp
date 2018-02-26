#include <bits/stdc++.h>
#define mod 20100403
#define MAXN 1000005
typedef long long ll;
ll fac[MAXN<<1],inv[MAXN<<1]; int n,m;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline ll qpow(ll x,ll k) {
    ll Ans = 1;
    for (; k; k >>= 1,x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

inline ll C(ll n, ll m) {
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return fac[n] * inv[n-m] % mod * inv[m] % mod;
}

int main() {
    n = read<int>(); m = read<int>();
    fac[0] = 1;
    for (int i = 1; i <= n + m; i++) fac[i] = fac[i-1] * i % mod;
    inv[n+m] = qpow(fac[n+m],mod - 2);
    for (int i = n + m - 1; i; i--) inv[i] = inv[i+1] * (i+1) % mod;
    inv[0] = 1;
    printf("%lld\n",(C(n+m,m) - C(n+m,m-1) + mod)%mod);
    // getchar(); getchar();
    // C(n+m,n) - C(n+m,n-1);
    return 0;
}
