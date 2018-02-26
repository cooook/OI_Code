#include <bits/stdc++.h>
typedef long long ll;
const int mod = 1e9+7, MAXN = 5e5+5,N = 5e5;
int n,m,prime[MAXN],cnt,mu[MAXN];
bool _prime[MAXN]; ll Sum1[MAXN],Sum2[MAXN],g[MAXN];
 
 
inline ll qpow(ll x,ll k){
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}
 
inline void Init(){
    mu[1] = 1;
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = - mu[i];
        }
    }
}
 
inline ll Calc(int n,int m){
    for (int d = 1; d <= m; d++){
        (g[d] *= d) %= mod;
        Sum1[d] = (Sum1[d-1] + mu[d] * g[d] * g[d] % mod) % mod;
        Sum2[d] = (Sum2[d-1] + g[d]) % mod;
    }
    ll Ans = 0; int last;
    for (int i = 1; i <= n; i = last + 1){
        last = std::min(n/(n/i),m/(m/i));
        Ans += (Sum1[last] - Sum1[i - 1]) * Sum2[n/i] % mod * Sum2[m/i] % mod;
        Ans %= mod;
    } 
    return Ans;
}
 
int main(){
    Init();
    scanf("%d%d",&n,&m);
    if (n > m) std::swap(n,m);
    ll Ans = 0;
    for (int i = 1; i <= m; i++) g[i] = 1;
    for (int i = 1; i <= n; i++) (Ans += qpow(i,i) * Calc(n/i,m/i) % mod) %= mod;
    printf("%lld\n",(Ans + mod) % mod);
    return 0;
}