#include <stdio.h>
#include <iostream>
#define MAXN 100005
typedef long long ll;
ll n,m,mod,fac[MAXN],inv[MAXN];
 
 
template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline ll qpow(ll x,ll k) {
    ll Ans = 1;
    for (; k; k >>= 1,x = x * x % mod) if (k&1) Ans = Ans * x % mod;
    return Ans;
}
 
inline ll C(int n,int m) {
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return fac[n] * inv[n-m] % mod * inv[m] % mod;
}
 
inline ll lucas(int n,int m) {
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return lucas(n/mod,m/mod) * C(n%mod,m%mod) % mod;
}
 
int main() {
    n = read<ll>(); m = read<ll>(); mod = read<ll>();
    fac[0] = 1;
    for (int i = 1; i < mod; i++) fac[i] = fac[i-1] * i % mod;
    inv[mod - 1] = qpow(fac[mod - 1],mod - 2);
    for (int i = mod - 2; i >= 1; i--) inv[i] = inv[i+1] * (i+1) % mod;
    inv[0] = 1;
    printf("%lld\n",lucas(n,m));
    // getchar(); getchar();
    return 0;
}