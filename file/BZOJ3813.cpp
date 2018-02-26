#include <bits/stdc++.h>
#define ls (o << 1)
#define rs (o << 1 | 1)
#define mk(x,y) std::make_pair(x,y)
#define fi first
#define se second
typedef long long ll;
typedef std::pair<ll,ll> pa;
const int mod = 19961993,MAXN = 100005;
int n,prime[65],cnt,pre[305];ll QWQ[MAXN<<2],sum[MAXN<<2],inv[305];
bool _prime[305];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline ll qpow(ll x,ll k) {
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

inline void init() {
    for (int i = 2; i <= 281; i++) {
        if (!_prime[i]) prime[++cnt] = i,pre[i] = cnt,inv[cnt] = qpow(i,mod - 2);
        for (int j = 1; j <= cnt && prime[j] * i <= 281; j++) {
            _prime[i*prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

inline void Maintain(int o) {
    QWQ[o] = QWQ[ls] | QWQ[rs];
    sum[o] = sum[ls] * sum[rs] % mod;
}

void build(int o,int l,int r) {
    if (l == r) return QWQ[o] = 1ll << pre[3],sum[o] = 3,void();
    register int mid = l + r >> 1;
    build(ls,l,mid); build(rs,mid+1,r);
    Maintain(o);
}

inline void Update(int o,int l,int r,int x,int val) {
    if (l == r) {
        sum[o] = val;
        QWQ[o] = 0;
        for (int i = 1; i <= 60; i++)
            if (val % prime[i] == 0)
                QWQ[o] |= 1ll << i;
        return;
    }
    register int mid = l + r >> 1;
    if (x <= mid) Update(ls,l,mid,x,val);
    else Update(rs,mid+1,r,x,val);
    Maintain(o);
}

inline pa Query(int o,int l,int r,int x,int y) {
    if (x <= l && r <= y) return mk(QWQ[o],sum[o]);
    register int mid = l + r >> 1; pa Ans; Ans.fi = 0;Ans.se = 1;
    if (x <= mid) {
        pa Q = Query(ls,l,mid,x,y);
        Ans.fi |= Q.fi;
        Ans.se = Ans.se * Q.se % mod;
    }
    if (mid < y) {
        pa Q = Query(rs,mid+1,r,x,y);
        Ans.fi |= Q.fi;
        Ans.se = Ans.se * Q.se % mod;
    }
    return Ans;
}

int main() {
    init();
    n = read<int>();
    build(1,1,100000);
    while (n --) {
        register int op = read<int>(),a = read<int>(),b = read<int>();
        if (!op) {
            pa Ans = Query(1,1,100000,a,b);
            ll res = 1;
            for (int i = 1; i <= 60; i++) 
                if (Ans.fi & (1ll << i)) res = res * (prime[i] - 1) % mod * inv[i] % mod;
            res = res * Ans.se % mod;
            printf("%lld\n",res);
        }
        else Update(1,1,100000,a,b);
    }
    return 0;
}