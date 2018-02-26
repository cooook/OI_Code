#include <bits/stdc++.h>
typedef long long ll;
const int mod = 1e9+7,MAXN = 5000005,N = 5000000;
int T,k,n,m,prime[MAXN],cnt; ll f[MAXN];
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
    for (; k; k >>= 1, (x *= x) %= mod)
        if (k & 1) (Ans *= x) %= mod;
    return Ans;
}

inline void Init(){
    f[1] = 1;
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) prime[++cnt] = i, f[i] = qpow(i,k) - 1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0){
                f[i * prime[j]] = f[i] * qpow(prime[j],k) % mod;
                break;
            }
            f[i * prime[j]] = f[i] * f[prime[j]] % mod;
        }
    }
    for (int i = 2; i <= N; i++) (f[i] += f[i-1]) %= mod;
}

// 13103231160

inline ll Query(int n,int m){
    if (n > m) std::swap(n,m);
    int last; ll Ans = 0;
    for (int i = 1; i <= n; i = last + 1){
        last = std::min(n/(n/i),m/(m/i));
        (Ans += (f[last] - f[i-1]) * (n/i) % mod * (m/i) % mod) %= mod;
    } return (Ans + mod) % mod;
}

int main(){
    T = read<int>(); k = read<int>();
    Init();
    while (T--){
        n = read<int>(), m = read<int>();
        printf("%lld\n",Query(n,m));
    }
    return 0;
}