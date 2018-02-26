#include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 1e7+5,N = 1e7,mod = 1e9+7;
int n,k,l,r,prime[MAXN/10],cnt,mu[MAXN];
bool _prime[MAXN];


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
    for (int i = 2; i <= N; i++) mu[i] += mu[i-1];
}

int first[76544],e = 1;
struct edge{int u,v,next;}a[MAXN/10];
inline void push(int u,int v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u % 76543], first[u % 76543] = e++;
}

inline int Query(int n){
    if (n <= N) return mu[n];
    for (int i = first[n % 76543]; i; i = a[i].next)
        if (a[i].u == n) return a[i].v;
    int Ans = 1,last; 
    for (int i = 2; i <= n; i = last + 1){
        last = n / (n / i);
        Ans -= (last - i + 1) * Query(n / i);
    }
    return push(n,Ans), Ans;
}

int main(){
    Init();
    scanf("%d%d%d%d",&n,&k,&l,&r); -- l;
    ll Ans = 0; int last; l /= k; r /= k;
    for (int i = 1; i <= r; i = last + 1){
        last = std::min(r/(r/i),(l/i)?l/(l/i):r);
        Ans += (Query(last) - Query(i - 1)) * qpow(r / i - l / i,n) % mod;
        Ans %= mod;
    } printf("%lld\n",(Ans + mod) % mod);
    return 0;
}