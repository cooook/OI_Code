#include <stdio.h>
#include <iostream>
const int MAXN = 10000005, N = 10000000;
int T,n,m,mu[MAXN],prime[MAXN],cnt;
bool _prime[MAXN]; long long f[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Init(){
    mu[1] = 1;
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1, f[i] = 1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[prime[j] * i] = true;
            if (i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                f[i * prime[j]] = mu[i];
                break;
            }
            f[i * prime[j]] = mu[i] - f[i];
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= N; i++) f[i] += f[i-1];
}

int main(){
    Init();
    T = read<int>();
    while (T --){
        n = read<int>(), m = read<int>();
        if (n > m) std::swap(n,m);
        int last; long long Ans = 0;
        for (int i = 1; i <= n; i = last + 1){
            last = std::min(n/(n/i),m/(m/i));
            Ans += (f[last] - f[i-1]) * (n / i) * (m / i);
        } printf("%lld\n",Ans);
    }
    return 0;
}