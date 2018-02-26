#include <stdio.h>
#include <iostream>
const int mod = 998244353, g = 3, MAXN = 100005, maxn = 1 << 18;
typedef long long ll;
int n,N,rev[maxn]; ll Inv[MAXN],bin[MAXN],fac[MAXN],A[maxn],B[maxn],C[maxn];  


inline ll qpow(ll x, ll k){
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

inline void fft(ll *f,int type){
    for (int i = 0; i < N; i++) if (i > rev[i]) std::swap(f[i],f[rev[i]]);
    ll u,w,wn;
    for (int k = 2; k <= N; k <<= 1){
        wn = qpow(g,type == 1?(mod-1)/k:mod-1-(mod-1)/k), w = 1;
        for (int i = 0; i < N; i += k, w = 1)
            for (int j = 0; j < k >> 1; j++, w = w * wn % mod)
                u = f[i + j + (k >> 1)] * w % mod, f[i + j + (k >> 1)] = (f[i + j] - u) % mod, f[i + j] = (f[i + j] + u) % mod;
    }
    if (type == -1){
        int ni = qpow(N, mod - 2);
        for (int i = 0; i < N; i++) f[i] = f[i] * ni % mod;
    }
}

inline void FFT(ll *A,ll *B){
    for (int i = 0; i < N; i++)
        if (i & 1) rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    fft(A,1); fft(B,1);
    for (int i = 0; i < N; i++) C[i] = A[i] * B[i] % mod;
    fft(C,-1);
}

int main(){
    scanf("%d",&n); N = 1;
    while (N < ((n + 1) << 1)) N <<= 1;
    bin[0] = 1; fac[0] = 1;

    for (int i = 1; i <= n; i++) bin[i] = bin[i-1] * 2 % mod, fac[i] = fac[i - 1] * i % mod;
    Inv[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i; i--) Inv[i] = Inv[i + 1] * (i + 1) % mod;
    
    Inv[0] = 1; B[0] = 1; B[1] = n + 1;

    for (int i = 0; i <= n; i++) A[i] = (i & 1)?-Inv[i]:Inv[i];
    for (int i = 2; i <= n; i++) B[i] = (qpow(i,n+1) - 1) * (qpow(i-1,mod-2)) % mod * Inv[i] % mod;

    FFT(A,B);
    
    ll Ans = 0;
    for (int i = 0; i <= n; i++)
        (Ans += C[i] * bin[i] % mod * fac[i] % mod) %= mod;
    printf("%lld\n",(Ans+mod)%mod);
    
    return 0;
}