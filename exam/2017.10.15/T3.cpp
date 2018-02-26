#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const int mod = 1000000007;
int fac[200005],inv[200005],n,m,k,f[3005];
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline ll C(int n,int m) {
    if (!m || n == m) return 1;
    if (n < m) return 0;
    return fac[n] * inv[n-m] % mod * inv[m] % mod;
}
 
struct Point {
    int d[2];
    inline bool operator < (const Point &x) const{
        return d[0] == x.d[0] ? d[1] < x.d[1]: d[0] < x.d[0];
    }
    inline int& operator [] (const int &x){return d[x];}
    inline void in(){
        d[0] = read<int>();
        d[1] = read<int>();
    }
}pt[3005];
 
inline ll qpow(ll x,ll k) {
    ll Ans = 1;
    for (; k; k >>= 1,x = x * x % mod) 
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}
 
signed main() {
    n = read<int>(); m = read<int>(); k = read<int>();
    fac[0] = 1;
    for (int i = 1; i <= n+m; i++) fac[i] = fac[i-1] * i % mod;
    inv[n+m] = qpow(fac[n+m],mod-2);
    for (int i = n+m-1; i >= 1; i--) inv[i] = inv[i+1] * (i+1) % mod;
    inv[0] = 1;
    for (int i = 1; i <= k; i++) pt[i].in();
    std::sort(&pt[1],&pt[k+1]);
    for (int i = 1; i <= k; i++) {
        f[i] = C(pt[i][0]+pt[i][1],pt[i][0]);
        for (int j = 1; j < i; j++) {
            if (pt[j][1] <= pt[i][1]) (f[i] -= C(pt[i][1] - pt[j][1] + 
                pt[i][0] - pt[j][0],pt[i][1] - pt[j][1]) * f[j] % mod - mod) %= mod;
        }
    }
    ll Ans = C(n+m,n);
    for (int i = 1; i <= k; i++) Ans = (Ans - C(n-pt[i][0]+m-pt[i][1],n-pt[i][0]) * f[i] % mod + mod) % mod;
    printf("%lld\n",Ans);
    return 0;
}