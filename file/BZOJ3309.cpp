#include <stdio.h>
#include <iostream>
typedef long long ll;
const int MAXN = 1e7+5,N = 1e7;


int T,n,m,prime[MAXN/10],cnt;
bool _prime[MAXN]; ll f[MAXN],size[MAXN],mul[MAXN];

template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Init(){
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) prime[++cnt] = i, mul[i] = i, size[i] = 1, f[i] = 1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0){
                mul[i * prime[j]] = mul[i] * prime[j];
                size[i * prime[j]] = size[i] + 1;
                register int tmp = i / mul[i];
                if (tmp == 1) f[i * prime[j]] = 1;
                else f[i * prime[j]] = (size[i * prime[j]] == size[tmp]?-f[tmp]:0);
                break;
            }
            mul[i * prime[j]] = prime[j];
            size[i * prime[j]] = 1;
            f[i * prime[j]] = size[i] == 1?-f[i]:0;
        }
    }
    for (int i = 2; i <= N; i++) f[i] += f[i-1];
}

inline ll Query(int n,int m){
    if (n > m) std::swap(n,m);
    int last; ll Ans = 0;
    for (int i = 1; i <= n; i = last + 1){
        last = std::min(n/(n/i),m/(m/i));
        Ans += (f[last] - f[i - 1]) * (n / i) * (m / i);
    } return Ans;
}

int main(){
    Init();
    T = read<int>();
    while (T --){
        n = read<int>(), m = read<int>();
        printf("%lld\n",Query(n,m));
    }
    return 0;
}