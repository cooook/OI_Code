#include <bits/stdc++.h>
typedef long long ll;
const int mod = 1004535809, MAXN = 1 << 16;
int val[MAXN],rev[MAXN],n,m,x,s,id[MAXN],N,g;
ll A[MAXN],B[MAXN],C[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline ll qpow(ll x, ll k,int mod){
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

inline void Init(){
    g = 1;
    while (true){
        bool is = true;
        for (int i = 1; i <= m - 2; i++)
            if (qpow(g,i,m) == 1){is = false; break;}
        if (is) break;
        else ++ g;
    }
}

inline void fft(ll *a,int type){
    for (int i = 0; i < N; i++)
        if (i < rev[i]) std::swap(a[i],a[rev[i]]);
    ll w,wn,t;
    for (int k = 2; k <= N; k <<= 1){
        wn = qpow(3,type == 1?((mod-1)/k):((mod-1)-(mod-1)/k),mod);
        for (int i = 0; i < N; i += k){
            w = 1;
            for (int j = 0; j < k >> 1; j++, w = w * wn % mod)
                t = a[i + j + (k >> 1)] * w % mod, a[i + j + (k >> 1)] = (a[i + j] - t) % mod, a[i + j] = (a[i + j] + t) % mod;
        }
    }
    if (type == -1){
        ll ni = qpow(N,mod - 2,mod);
        for (int i = 0; i < N; i++) a[i] = a[i] * ni % mod;
    }
}

inline void FFT(ll *A){
    fft(A,1);
    for (int i = 0; i < N; i++) A[i] = A[i] * A[i] % mod;
    fft(A,-1);
    for (int i = m; i < m << 1; i++) (A[i - m] += A[i]) %= mod;
    for (int i = m; i < N; i++) A[i] = 0;
}

inline void FFT(ll *A,ll *C){
    fft(A,1); fft(C,1);
    for (int i = 0; i < N; i++) C[i] = A[i] * C[i] % mod;
    fft(C,-1); fft(A,-1);
    for (int i = m; i < m << 1; i++) (C[i - m] += C[i]) %= mod;
    for (int i = m; i < N; i++) C[i] = 0;
}

int main(){
    n = read<int>(), m = read<int>(), x = read<int>(), s = read<int>();
    for (int i = 1; i <= s; i++){
        val[i] = read<int>();
        if (val[i] == 0 && x == 0){
            printf("%lld\n",(qpow(s,n,mod)-qpow(s-1,n,mod)+mod)%mod);
            return 0;
        }
    }
    Init();
    for (int i = 0; i < m - 1; i++) id[qpow(g,i,m)] = i;
    for (int i = 1; i <= s; i++) 
        if (val[i]) A[id[val[i]]] = 1; 
    m --;
    for (N = 1; N < (m << 1); N <<= 1);
    for (int i = 0; i < N; i++)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    C[0] = 1;
    for (; n; n >>= 1, FFT(A))
        if (n & 1) FFT(A,C);
    printf("%lld\n",(C[id[x]] + mod) % mod);
    return 0;
}