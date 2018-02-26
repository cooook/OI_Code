# include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 1e6 + 5;
const int N = 1e6;
const int Key = 76543;
const double PI = acos(-1.0);
int L, R, prime[MAXN], cnt, mu[MAXN];
bool _prime[MAXN]; ll phi[MAXN];


inline void Init() {
    phi[1] = 1; mu[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!_prime[i]) prime[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            mu[i * prime[j]] = -mu[i];
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 2; i <= N; i++) phi[i] += phi[i - 1], mu[i] += mu[i-1];
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

int main() {
    Init();
    scanf("%d%d", &L, &R);
    printf("%.2f\n", (Mu::Qmu(R + 1) - Mu::Qmu(L) + Phi::Qphi(R + 1) - Phi::Qphi(L)) / 2.0);
    return 0;
}