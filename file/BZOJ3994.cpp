#include <stdio.h>
#include <iostream>
typedef long long ll;
const int MAXN = 50005,N = 50000;
int T,n,m,prime[MAXN],mu[MAXN],cnt;
ll d[MAXN];
bool _prime[MAXN];


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
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= N; i++){
        int last; mu[i] += mu[i-1];
        for (int j = 1; j <= i; j = last + 1){
            last = i / (i / j);
            d[i] += (last - j + 1) * (i / j);    
        }
    }
}

inline ll Query(int n,int m){
    int last; ll Ans = 0;
    for (int i = 1; i <= n; i = last + 1){
        last = std::min(n/(n/i),m/(m/i));
        Ans += (mu[last] - mu[i-1]) * d[n/i] * d[m/i];
    } return Ans;
}

int main(){
    Init();
    T = read<int>();
    while (T --){
        n = read<int>(), m = read<int>();
        if (n > m) std::swap(n,m);
        printf("%lld\n",Query(n,m));
    }
    return 0;
}