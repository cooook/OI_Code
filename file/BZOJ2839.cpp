#include <stdio.h>
const int mod = 1000000007,MAXN = 1000005;
typedef long long ll;
int n,k,i; ll fac[MAXN],inv[MAXN],now = 2,Ans;


template<typename _t>
inline _t read(){
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline ll C(int n,int m){
    if (n == m || !m) return 1;
    if (n < m) return 0;
    return fac[n] * inv[n-m] % mod * inv[m] % mod;
}

inline ll qpow(ll x,ll k){
    ll Ans = 1;
    for (; k; k >>= 1,x = x * x % mod) 
        if (k & 1) 
            Ans = Ans * x % mod;
    return Ans;
}

int main() {
    n = read<int>(); k = read<int>();
    for (fac[0] = 1,i = 1; i <= n; i++) fac[i] = fac[i-1] * i % mod;
    for (inv[n] = qpow(fac[n],mod - 2),i = n-1; i; i--) inv[i] = inv[i+1] * (i + 1) % mod; inv[0] = 1;
    for (int i = n - k; ~i; i--) {
        (Ans += ((i & 1)?-1:1) * C(n-k,i) * (now - 1 + mod) % mod) %= mod;
        now = now * now % mod;
    }
    if (Ans < 0) Ans += mod;
    (Ans *= C(n,k)) %= mod;
    printf("%lld\n",Ans);
    return 0;
}