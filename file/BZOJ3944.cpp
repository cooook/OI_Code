#include <bits/stdc++.h>
// #define int long long 
typedef long long ll;
const int MAXN = 7e6+5,N = 7e6,Key = 76543;
int T,n,prime[MAXN/10],mu[MAXN],cnt;
bool _prime[MAXN]; ll phi[MAXN];


inline void Init(){
    mu[1] = 1; phi[1] = 1;
    for (int i = 2; i <= N; i++){
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= cnt && 1ll * prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = 1ll * phi[i] * prime[j];
                break;
            }
            mu[i * prime[j]] = - mu[i];
            phi[i * prime[j]] = 1ll * phi[i] * phi[prime[j]];
        }
    }
    for (int i = 2; i <= N; i++) mu[i] += mu[i-1], phi[i] += phi[i-1];
}

namespace Phi{
    int first[Key+1], e = 1;
    struct edge{
        int u,next; ll v;
    }a[MAXN/10];

    inline void New(int u,ll v){
        a[e].u = u; a[e].v = v;
        a[e].next = first[u % Key]; first[u % Key] = e++;
    }

    inline ll Qphi(int n){
        if (n <= N) return phi[n];
        for (int i = first[n % Key]; i; i = a[i].next)
            if (a[i].u == n) return a[i].v;
        ll Ans = ((ll)n + 1) * n / 2, last;
        for (ll i = 2; i <= n; i = last + 1){
            last = 1ll * n / (n / i);
            Ans -= Qphi(n/i) * (last - i + 1);
        } 
        New(n,Ans);
        return Ans;
    }
}

namespace Mu{
    int first[Key+1], e = 1;
    struct edge{
        int u,v,next;
    }a[MAXN/10];

    inline void New(int u,int v){
        a[e].u = u; a[e].v = v;
        a[e].next = first[u % Key]; first[u % Key] = e++;
    }

    inline int Qmu(int u){
        if (u <= N) return mu[u];
        for (int i = first[u % Key]; i; i = a[i].next)
            if (a[i].u == u) return a[i].v;
        int Ans = 1; ll last;
        for (ll i = 2; i <= u; i = last + 1){
            last = u / (u / i);
            Ans -= Qmu(u/i) * (last - i + 1);
        }
        New(u,Ans);
        return Ans;
    }
}

signed main(){
    Init();
    printf("%d\n", Mu::Qmu(1000000000));
    return 0;
}