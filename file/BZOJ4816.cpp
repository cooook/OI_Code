#include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 1e6+5,N = 1e6,mod = 1e9+7;
int T,n,m,mu[MAXN],prime[MAXN],cnt; ll ni[MAXN],fib[MAXN],f[MAXN],Inv[MAXN],Sum[MAXN],Inv_Sum[MAXN];
bool _prime[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline ll qpow(ll x,ll k){
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

inline void Init(){
    fib[0] = 0; fib[1] = 1; mu[1] = 1;
    for (int i = 2; i <= N; i++) fib[i] = (fib[i-1] + fib[i-2]) % mod;
    for (int i = 1; i <= N; i++) Inv[i] = qpow(fib[i],mod - 2), f[i] = 1;
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) mu[i] = -1, prime[++cnt] = i;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = - mu[i];
        }
    }
    for (int i = 2; i <= N; i++) mu[i] += mu[i-1];
    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j += i)
            if (mu[j / i] == 1) (f[j] *= fib[i]) %= mod;
            else if (mu[j / i] == -1) (f[j] *= Inv[i]) %= mod;
    Sum[0] = 1;
    for (int i = 1; i <= N; i++) Sum[i] = Sum[i-1] * f[i] % mod;
    Inv_Sum[N] = qpow(Inv_Sum[N],mod - 2);
    for (int i = N - 1; i; i--) Inv_Sum[i] = Inv_Sum[i + 1] * f[i] % mod;
    Inv_Sum[0] = 1;
}

inline ll Query(int n,int m){
    ll Ans = 1; int last;
    if (n > m) std::swap(n,m);
    for (int i = 1; i <= n; i = last + 1){
        last = n / (n / i);
        (Ans *= qpow(Sum[last] * Inv_Sum[i-1],(n/i)*(m/i))) %= mod;
    } return Ans;
}

int main(){
    Init();
    T = read<int>();
    while(T--){
        n = read<int>(); m = read<int>();
        printf("%lld\n",Query(n,m));
    }
    return 0;
}