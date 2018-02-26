#pragma GCC optimize("O3")
#include <bits/stdc++.h>
typedef long long ll;
const int mod = 100000009,MAXN = 10000005,N = 10000000;
int T,n,m,prime[MAXN],cnt;
bool _prime[MAXN]; ll Sum[MAXN],g[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Init(){
    g[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!_prime[i]) prime[++cnt] = i, g[i] = (i - 1ll * i * i) % mod;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++) {
            _prime[i*prime[j]] = true;
            if (i % prime[j] == 0){
                g[i * prime[j]] = g[i] * prime[j] % mod;
                break;
            }
            g[i * prime[j]] = g[i] * g[prime[j]] % mod;
        }
    }
    for (int i = 1;i <= N; i++) Sum[i] = (Sum[i-1] + g[i]) % mod;
}

inline ll f(int x){
    return 1ll * (x + 1) * x / 2 % mod;
}

inline ll Query(int n,int m){
    if (n > m) std::swap(n,m);
    int last; ll Ans = 0;
    for (int i = 1; i <= n; i = last + 1){
        last = std::min(n/(n/i),m/(m/i));
        Ans += (Sum[last] - Sum[i-1]) * f(n/i) % mod * f(m/i) % mod;
        Ans %= mod; 
    } return (Ans + mod) % mod;
}

int main(){
    Init();
    T = read<int>();
    while (T--){
        n = read<int>(), m = read<int>();
        printf("%lld\n",Query(n,m));
    }
    return 0;
}