#include <bits/stdc++.h>

typedef long long ll;

const int MAXN = 1e5+5,MAXM = 1e9+5,N = 5e6,mod = 1e9+7;
int n,m,prime[N/10],cnt,fuc[N+5]; ll phi[N+5];
bool _prime[N+5]; 
std::map<int,ll> ma[100005];


inline void Init(){
    phi[1] = 1;
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) prime[++cnt] = i, phi[i] = i - 1, fuc[i] = i;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0){
                fuc[i * prime[j]] = fuc[i];
                phi[i * prime[j]] = 1ll * phi[i] * prime[j] % mod;
                break;
            }
            fuc[i * prime[j]] = fuc[i] * prime[j];
            phi[i * prime[j]] = 1ll * phi[i] * phi[prime[j]] % mod;
        }
    }
    for (int i = 2; i <= N; i++) (phi[i] += phi[i-1]) %= mod;
}

int first[76544],e = 1;
struct edge{int u,next; ll v;}a[N/10];
inline void push(int u,ll v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u % 76543], first[u % 76543] = e++;
}

inline ll Query(int n){
    if (n <= N) return phi[n];
    for (int i = first[n % 76543]; i; i = a[i].next)    
        if (a[i].u == n) return a[i].v;
    ll Ans = 1ll * n * (n + 1) / 2,last;
    for (int i = 2; i <= n; i = last + 1){
        last = n / (n / i);
        Ans -= (last - i + 1) * Query(n / i) % mod;
        Ans %= mod;
    }
    return push(n,Ans), Ans;
}

inline ll Query(int n,int m){
    if (!m) return 0;
    if (m == 1) return phi[n] - phi[n-1];
    if (n == 1) return Query(m);
    if (ma[n][m]) return ma[n][m];
    if (fuc[n] != n) return ma[n][m] = n / fuc[n] * Query(n/(n/fuc[n]),m) % mod; 
    ll Ans = 0;
    for (int i = 1; i * i <= n; i++)
        if (n % i == 0){
            Ans += (phi[n/i] - phi[n/i-1]) * Query(i,m/i) % mod; Ans %= mod;
            if (i * i != n) Ans += (phi[i] - phi[i-1]) * Query(n/i,m/(n/i)) % mod, Ans %= mod;
        }
    return ma[n][m] = Ans;
}

int main(){
    Init();
    scanf("%d%d",&n,&m);
    ll Ans = 0;
    for (int i = 1; i <= n; i++)
        (Ans += Query(i,m)) %= mod;
    printf("%lld\n",(Ans + mod) % mod);
    return 0;
}