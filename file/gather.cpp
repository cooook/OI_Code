#include <bits/stdc++.h>
#define MAXN 100005
#define int long long 
int n,size[MAXN],f[MAXN],tot,first[MAXN],e = 1,Ans;


template<typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,w,next;
}a[MAXN<<1];

inline void push(int u,int v,int w) {
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int fa) {
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v,u); size[u] += size[v];
        f[u] += size[v] * a[i].w + f[v];
    }
}

inline void dp(int u,int fa) {
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        f[v] += f[u] - f[v] + (tot - size[v]) * a[i].w - size[v] * a[i].w;
        dp(v,u);
    }
}

signed main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) size[i] = read<int>(),tot += size[i];
    for (int i = 1; i < n; i++) {
        register int a = read<int>(),b = read<int>(),c = read<int>();
        push(a,b,c); push(b,a,c);
    }
    dfs(1,0); dp(1,0); Ans = 0x3f3f3f3f3f3f3f3fll;
    for (int i = 1; i <= n; i++) Ans = std::min(Ans,f[i]);
    printf("%lld\n",Ans);
    // getchar(); getchar();
    return 0;
}