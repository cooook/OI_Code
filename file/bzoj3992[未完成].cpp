#include <stdio.h>
const int mod = 1004535809,G = 3,maxn = 1<<22;
int g,m,n,x,s,id[8005];


template<typename _t>
inline _t read(){
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline ll qpow(ll x,ll k,ll mod){
    ll Ans = 1;
    for (; k; k >>= 1,x = x * x % mod)
        if (k & 1) 
            Ans = Ans * x % mod;
    return Ans;
}

inline void G_g(int m){
    g = 1;
    while (true){
        bool flag = 0;
        for (int i = 1; i <= m-2; i++)
            if (qpow(g,i,m) == 1) {flag = 1;break;}
        if (!flag) return;
        else g ++;
    }
}

inline void fnt(ll *a,int type) {
    for (int i = 0; i < N; i++) if (i < rev[i]) std::swap(a[i],a[rev[i]]);  ll w,wn,t;
    for (int k = 2; k <= N; k<<=1) {
        wn = qpow(G,type == 1?(mod - 1) / k : mod - 1 - (mod - 1) / k,mod),w = 1;
        for (int i = 0; i < N; i += k,w = 1)
            for (int j = 0; j < k >> 1; j++,w = w * wn % mod)
                t = a[i+j+(k>>1)] * w % mod,a[i+j+(k>>1)] = (a[i+j] - t) % mod,a[i+j] = (a[i+j] + t) % mod;
    }
    if (type == -1) {
        ll inv = qpow(N,mod - 2,mod);
        for (int i = 0; i < N; i++) a[i] = a[i] * inv % mod;
    }
}

struct dss{
    ll a[maxn];
    dss(){
        memset(a,0,sizeof a);
    }

    inline ll& operator [] (const int & x){
        return a[x];
    }
}A;

inline dss operator * (const dss &a,const dss &b){
    dss Ans;
    fnt(a.a,1); fnt(b.a,1)
    fnt();
}

inline dss operator ^ (const dss & a,int k) {
    dss Ans; Ans[0] = 1;
    for (; k; k >>= 1,a = a * a)
        if (k & 1)
            Ans = Ans * a;
    return Ans;
}

int main(){
    n = read<int>(); m = read<int>();
    x = read<int>(); s = read<int>();
    G_g(m); ll tmp = 1;
    for (N = 1; N <= (m-1) << 1; N <<= 1);
    for (int i = 0; i < m - 1; i++) id[tmp] = i,tmp = tmp * g % m;
    for (int i = 1; i <= s; i++) {
        register int w = read<int>();
        if (w == 0) continue;
        A[id[w]] = 1;
    }
    A = A ^ n;
    printf("%lld\n",A[id[x]]);
    return 0;
}