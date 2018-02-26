#include <bits/stdc++.h>
const int MAXN = 1 << 18;
const double pi = acos(-1.0);
int n,rev[MAXN],N,val;


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Complex{
    double x,r;
    inline Complex operator + (const Complex &a)const{return (Complex){x + a.x, r + a.r};}
    inline Complex operator - (const Complex &a)const{return (Complex){x - a.x, r - a.r};}
    inline Complex operator * (const int &a)const{return (Complex){x * a, r * a};}
    inline Complex operator * (const Complex &a)const{return (Complex){x * a.x - r * a.r,x * a.r + r * a.x};}
    friend Complex operator / (const Complex &a,const int &x){return (Complex){a.x/x,a.r/x};}
}A[MAXN],B[MAXN],C[MAXN],Ans[MAXN];

inline void fft(Complex *a,int type){
    for (int i = 0; i < N; i++) 
        if (rev[i] < i) std::swap(a[i],a[rev[i]]);
    Complex wn, w, t;
    for (int k = 2; k <= N; k <<= 1){
        wn = (Complex){cos(2*pi/k),type*sin(2*pi/k)};
        for (int i = 0; i < N; i += k){
            w = (Complex){1.0,0.0};
            for (int j = 0; j < k >> 1; j++, w = w * wn)
                t = a[i + j + (k >> 1)] * w, a[i + j + (k >> 1)] = a[i + j] - t, 
                a[i + j] = a[i + j] + t;
        }
    }
    if (type == -1) for (int i = 0; i < N; i++) a[i] = a[i] / N;
}

int main(){
    n = read<int>();
    for (int i = 1; i <= n; i++){
        val = read<int>();
        A[val].x += 1;
        B[val << 1].x += 1;
        C[val * 3].x += 1;
    }
    for (N = 1; N < (val * 6); N <<= 1);
    for (int i = 0; i < N; i++) 
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    fft(A,1), fft(B,1), fft(C,1);
    for (int i = 0; i < N; i++) Ans[i] = A[i] + (A[i] * A[i] - B[i]) / 2 + (A[i] * A[i] * A[i] - A[i] * B[i] * 3 + C[i] * 2) / 6;
    fft(Ans,-1);
    for (int i = 0; i <= val * 3; i++)
        if ((int)round(Ans[i].x)) printf("%d %d\n",i,(int)round(Ans[i].x));
    return 0;
}