#include <stdio.h>
#define mod 1000000007
typedef long long ll;
int n; ll bit[100005],f[100005],fac[100005];
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1; char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline ll qpow(ll x,ll k) {
    ll Ans = 1;
    for (; k; k >>= 1,x = x * x % mod) if (k & 1) Ans = Ans * x % mod;
    return Ans;
}
 
int main() {
    n = read<int>(); fac[0] = 1; bit[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i-1] * i % mod, bit[i] = (bit[i-1] << 1) % mod;
    for (int i = 1; i <= n; i++) f[i] = (f[i-1] * i % mod + (bit[i-1] - 1 + mod) * fac[i-1] % mod) % mod; 
    printf("%lld\n",f[n] * qpow(fac[n],mod - 2) % mod);
    // getchar(); getchar();
    return 0;
}