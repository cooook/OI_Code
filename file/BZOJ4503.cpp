#include <bits/stdc++.h>
const int MAXN = 1e5+5,maxn = 1 << 20;
const double PI = 3.1415926535897932384;
char S[MAXN],T[MAXN]; int rev[maxn],cnt,N,pos[MAXN]; double Ans[maxn];


struct Complex{
    double x,r;
    Complex(double _x = 0, double _r = 0){x = _x; r = _r;}
    inline Complex operator + (const Complex &a)const{return (Complex){x+a.x,r+a.r};}
    inline Complex operator - (const Complex &a)const{return (Complex){x-a.x,r-a.r};}
    inline Complex operator * (const Complex &a)const{return (Complex){x*a.x-r*a.r,x*a.r+r*a.x};}
}A1[maxn],B1[maxn],A2[maxn],B2[maxn],A3[maxn],B3[maxn];

inline void fft(Complex *f,int type){
    for (int i = 0; i < N; i++) if (rev[i] < i) std::swap(f[i],f[rev[i]]);
    Complex w,wn,t;
    for (int k = 2; k <= N; k <<= 1){
        wn = (Complex){cos(2*PI/k),type*sin(2*PI/k)};
        for (int i = 0; i < N; i += k){
            w = (Complex){1,0};
            for (int j = 0; j < k >> 1; j++, w = w * wn)
                t = f[i + j + (k >> 1)] * w, f[i + j + (k >> 1)] = f[i + j] - t, f[i + j] = f[i + j] + t;
        }
    }
    if (type == -1) for (int i = 0; i < N; i++) f[i].x /= N;
}

inline void FFT(Complex *a,Complex *b,int type){
    fft(a,1); fft(b,1);
    for (int i = 0; i < N; i++) a[i] = a[i] * b[i];
    fft(a,-1);
    for (int i = 0; i < N; i++) Ans[i] += a[i].x * type;
}

int main(){
    scanf("%s%s",S,T);
    int len1 = strlen(S),len2 = strlen(T);
    std::reverse(&T[0],&T[len2]);
    for (N = 1; N < (len1 << 2); N <<= 1);
    for (int i = 0; i < N; i++) 
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    for (int i = 0; i < len1; i++){
        int s = S[i], t = T[i];
        if (T[i] == '?') t = 0;
        A1[i] = (Complex){1.0 * s * s * s,0};
        B3[i] = (Complex){1.0 * t * t * t,0};
        A2[i] = (Complex){1.0 * s * s,0};
        B2[i] = (Complex){1.0 * t * t,0};
        A3[i] = (Complex){1.0 * s,0};
        B1[i] = (Complex){1.0 * t,0};
    }
    FFT(A1,B1,1); FFT(A2,B2,-2); FFT(A3,B3,1);
    for (int i = len2 - 1; i < len1; i++)
        if (int(Ans[i]+0.1) == 0) pos[++cnt] = i - len2 + 1;
    printf("%d\n",cnt);
    for (int i = 1; i <= cnt; i++) printf("%d\n",pos[i]);
    return 0;
}