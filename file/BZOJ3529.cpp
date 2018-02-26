#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>

typedef unsigned int ll;
const int MAXN = 1e5+5,N = 1e5,full = 2147483647;

int Q,id[MAXN],prime[MAXN],mu[MAXN],cnt;
ll f[MAXN],g[MAXN],Ans[MAXN],s[MAXN];
bool _prime[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Query{
    int n,m,a,id;
    inline bool operator < (const Query &x)const{
        return a < x.a;
    }
}a[MAXN];

inline bool cmp(const int &x,const int &y){
    return f[x] == f[y]?x < y:f[x] < f[y];
}

template <typename _t>
class BIT{
    private:
        _t tree[MAXN];
    public:
        BIT(){memset(tree,0,sizeof tree);}
        inline void Update(int x,int val){for (; x <= N; x += x & (-x)) tree[x] += val;}
        inline _t Sum(int x){_t Ans = 0; for (; x; x -= x & (-x)) Ans += tree[x]; return Ans;}
};
BIT<ll> T;

inline void Init(){
    mu[1] = 1; id[1] = 1; f[1] = 1;
    for (int i = 2; i <= N; i++){
        id[i] = i;
        if (!_prime[i]) prime[++cnt] = i, f[i] = i + 1, g[i] = i + 1, s[i] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++){
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                s[i * prime[j]] = s[i] * prime[j];
                g[i * prime[j]] = g[i] + s[i * prime[j]];
                f[i * prime[j]] = f[i] / g[i] * g[i * prime[j]];
                break;
            }
            mu[i * prime[j]] = - mu[i];
            s[i * prime[j]] = prime[j];
            g[i * prime[j]] = prime[j] + 1;
            f[i * prime[j]] = f[i] * g[i * prime[j]];
        }
    }
    std::sort(&id[1],&id[N+1],cmp);
}

inline void Update(int x){
    for (int i = x; i <= N; i += x) 
        T.Update(i,f[x] * mu[i/x]);
}

inline ll Query(int n,int m){
    if (n > m) std::swap(n,m);
    int last; ll Ans = 0;
    for (int i = 1; i <= n; i = last + 1){
        last = std::min(n/(n/i),m/(m/i));
        Ans += (T.Sum(last) - T.Sum(i - 1)) * (m / i) * (n / i);
    } return Ans & full;
}

int main(){
    Init();
    Q = read<int>();
    for (int i = 1; i <= Q; i++) 
        a[i].n = read<int>(),a[i].m = read<int>(),
        a[i].a = read<int>(), a[i].id = i;
    std::sort(&a[1],&a[Q+1]);
    int top = 1;
    for (int i = 1; i <= Q; i++){
        while (a[i].a >= f[id[top]] && top <= N) Update(id[top++]);
        Ans[a[i].id] = Query(a[i].n,a[i].m);
    }
    for (int i = 1; i <= Q; i++) printf("%d\n",Ans[i]);
    return 0;
}