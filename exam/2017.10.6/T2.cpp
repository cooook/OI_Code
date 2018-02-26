#pragma GCC optimize("O3")
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <time.h>
typedef long long ll;
const int MAXN = (int)(3e7)+5,N = (int)3e7;
int mu[MAXN],prime[MAXN/10],cnt,first[MAXN],e = 1;
bool _prime[MAXN]; ll n;
 
 
template<typename _t>
inline _t read(){
    _t x = 0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch == '-') f = -f;
    for(;isdigit(ch);ch=getchar()) x = x * 10 +(ch^48);
    return x*f;
}
 
struct edge{
    ll u;
    int next,val;
}a[MAXN/10];
 
inline void push(ll u,int val){
    int k = u % 76543;
    a[e].u = u;a[e].val = val;a[e].next = first[k];first[k] = e++;
}
 
inline void get_mu(){
    mu[1] = 1;
    for(int i = 2;i<=N;i++){
        if(!_prime[i]) prime[++cnt] = i,mu[i] = -1;
        for(int j = 1;j<=cnt&&prime[j]*i<=N;j++){
            _prime[i*prime[j]] = 1;
            if(i%prime[j] == 0) break;
            mu[i*prime[j]] = -mu[i];
        }
    }
    for(int i = 2;i<=N;i++) mu[i] += mu[i-1];
}
 
inline ll Query(ll p){
    if(p<=N) return mu[p];
    int Ans = 1; ll last;
    for (int i = first[p%76543];i;i=a[i].next) if (a[i].u == p) return a[i].val;
    for (ll i = 2;i<=p;i=last+1){
        last = p/(p/i);
        Ans -= (last-i+1) * Query(p/i);
    } push(p,Ans);
    return Ans;
}
 
inline ll S(ll a, ll b) {
    return Query(b) - Query(a - 1);
}
 
int main(){
    get_mu(); 
    n = read<ll>();
    ll kk = sqrt(n),last,Ans = 0;
    for (ll i = 1; i <= kk; i = last + 1) {
        last = sqrt(n/(n/(i*i)));
        Ans += S(i,last) * (n/(i*i));
    }
    printf("%lld\n",Ans);
}