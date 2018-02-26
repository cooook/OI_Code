#include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 1e7+5,N = 1e7,mod = 1e9+7;
int n,prime[MAXN/10],cnt,first[76544],e = 1;
bool _prime[MAXN]; ll phi[MAXN],Inv6,Inv2;


inline void Init(){
    phi[1] = 1;
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j] % mod;
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]] % mod;
        }
    }
    for (int i = 2; i <= N; i++) (phi[i] *= i) %= mod, (phi[i] += phi[i-1]) %= mod;
}

inline ll qpow(ll x,ll k){
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

inline ll S(ll n){
    return n * (n + 1) % mod * (2 * n + 1) % mod * Inv6 % mod;
}

inline ll S1(ll n){
    return n * (n + 1) % mod * Inv2 % mod;
}

struct edge{
    int u,next; ll v;
}a[MAXN/10];

inline void push(int u,ll v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u % 76543]; first[u % 76543] = e++;
}

inline ll Query(int n){
    if (n <= N) return phi[n];
    for (int i = first[n % 76543]; i; i = a[i].next)
        if (a[i].u == n) return a[i].v;
    ll Ans = S(n); int last;
    for (int i = 2; i <= n; i = last + 1){
        last = n / (n / i);
        Ans -= (S1(last) - S1(i-1)) * Query(n / i) % mod;
        Ans %= mod;
    }
    return push(n,Ans), Ans;
}

int main(){
    Init(); Inv2 = qpow(2,mod-2), Inv6 = qpow(6,mod-2);
    scanf("%d",&n);
    puts("1");
    printf("%lld\n",(Query(n) + mod) % mod);
    return 0;
}