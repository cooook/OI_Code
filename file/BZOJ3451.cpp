#include <bits/stdc++.h>
const int MAXN = 30005,maxn = 1 << 17;
const double pi = acos(-1.0);
int first[MAXN],e = 1,n,size[MAXN],f[MAXN],Num,root,g[MAXN],N,rev[MAXN],cnt[MAXN],len,Ans[MAXN],d[MAXN];
bool vis[MAXN]; 


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
    Complex(double _x = 0.0,double _r = 0.0){x = _x; r = _r;}
    inline Complex operator + (const Complex &a)const{return (Complex){x+a.x,r+a.r};}
    inline Complex operator - (const Complex &a)const{return (Complex){x-a.x,r-a.r};}
    inline Complex operator * (const Complex &a)const{return (Complex){x*a.x-r*a.r,x*a.r+r*a.x};}
}A[maxn],B[maxn],C[maxn];

inline void fft(Complex *a,int type){
    for (int i = 0; i < N; i++) if (i < rev[i]) std::swap(a[i],a[rev[i]]);
    Complex wn,w,t;
    for (int k = 2; k <= N; k <<= 1){
        wn = Complex(cos(2*pi/k),type*sin(2*pi/k));
        for (int i = 0; i < N; i += k){
            w = Complex(1.0,0.0);
            for (int j = 0; j < k >> 1; j++, w = w * wn)
                t = a[i + j + (k >> 1)] * w, a[i + j + (k >> 1)] = a[i + j] - t, a[i + j] = a[i + j] + t;
        }
    }
    if (type == -1) for (int i = 0; i < N; i++) a[i].x /= N;
}

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void G_size(int u,int fa){
    size[u] = 1;
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v] && a[i].v != fa)
            G_size(a[i].v,u), size[u] += size[a[i].v];
}

inline void G_root(int u,int fa){
    f[u] = 0;
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v] && a[i].v != fa)
            f[u] = std::max(f[u],size[a[i].v]),
            G_root(a[i].v,u);
    f[u] = std::max(f[u],Num - f[u]);
    if (f[u] < f[root]) root = u;
}

inline void dfs(int u,int fa){
    cnt[d[u]] ++; len = std::max(len,d[u] + 1);
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v] && a[i].v != fa) d[a[i].v] = d[u] + 1,dfs(a[i].v,u);
}

inline void Calc(int u,int type){
    len = 0; dfs(u,0);
    for (N = 1; N < (len << 1); N <<= 1);
    for (int i = 0; i < N; i++)
        if (i & 1) rev[i] = rev[i >> 1] >> 1 | (N >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    for (int i = 0; i < len; i++) A[i] = Complex(cnt[i],0.0), cnt[i] = 0;
    for (int i = len; i < N; i++) A[i] = Complex(0.0,0.0);
    fft(A,1);
    for (int i = 0; i < N; i++) A[i] = A[i] * A[i];
    fft(A,-1);
    for (int i = 0; i < len << 1 && i < n; i++)
        Ans[i+1] += round(A[i].x) * type;
}

inline void Div(int u){
    vis[u] = true; G_size(u,0); d[u] = 0; Calc(u,1);
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v]) d[a[i].v] = 1, Calc(a[i].v,-1);
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (vis[v]) continue;
        Num = size[v]; root = 0; G_root(v,0); Div(root);
    }
}

int main(){
    n = read<int>();
    for (int i = 1; i < n; i++){
        register int u = read<int>() + 1, v = read<int>() + 1;
        push(u,v), push(v,u);
    }
    f[0] = n; Num = n; G_size(1,0); G_root(1,0); Div(root);
    double res = 0.0;
    for (int i = 1; i <= n; i++) res += Ans[i] / 1.0 / i;
    printf("%.4f\n",res);
    return 0;
}
