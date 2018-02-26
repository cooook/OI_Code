#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define MAXN 200005
#define MAXM 500000
int n,m,first[MAXN],e = 1;
int prime[MAXM+5],mu[MAXM+5],cnt;
bool _prime[MAXM+5],vis[MAXN]; long long Ans,sum[MAXM+5];


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct edge{
    int v,next;
}a[MAXM<<6];

inline void push(int u, int v){
    a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void Mu_table(){
    mu[1] = 1;
    for (int i = 2;i<=MAXM;i++) {
        if (!_prime[i]) prime[++cnt] = i,mu[i] = -1;
        for (int j = 1;j<=cnt && prime[j] * i <= MAXM;j++) {
            _prime[i*prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i*prime[j]] = - mu[i];
        }
    }
}

int main(){
    Mu_table();
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= n; i++) {
        int val = read<int>();
        for (int j = 1; j * j <= val; j++) {
            if (val % j) continue;
            push(i,j);
            if (val / j != j) push(i,val/j);
        }
    }
    while (m --){
        register int x = read<int>();
        if (vis[x])
            for (int i = first[x]; i; i = a[i].next) sum[a[i].v] --,Ans -= sum[a[i].v] * mu[a[i].v];
        else for (int i = first[x]; i; i = a[i].next) Ans += sum[a[i].v] * mu[a[i].v], sum[a[i].v] ++;
        vis[x] ^= 1;printf("%lld\n",Ans);
    }
    return 0;
}