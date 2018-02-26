#pragma GCC optimize("O3")
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MAXN 100005
int first[MAXN],e = 1,n,m,f[MAXN],size[MAXN],g[MAXN][20];


template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return  x * f;
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w) {
    a[e].u = u; a[e].v = v;a[e].w = w; 
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int fa) {
    size[u] = 1; g[u][0] = 1;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue; dfs(v,u);
        size[u] += size[v];
        f[u] += f[v] + size[v] * a[i].w;
        for (int j = 0; j <= 15; j++) g[u][(j + a[i].w) & 15] += g[v][j];
    }
}

inline void dp(int u,int fa) {
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        int tmp[20];
        memset(tmp,0,sizeof tmp);
        for (int j = 0; j <= 15; j++) tmp[(((j + a[i].w)&15)+a[i].w)&15] += g[u][(j+a[i].w) & 15] - g[v][j];
        for (int j = 0; j <= 15; j++) g[v][j] += tmp[j];
        f[v] += f[u] - (f[v] + a[i].w * size[v]) + a[i].w * (n - size[v]);
        dp(v,u);
    }
}

int main() {
    n = read<int>(); m = read<int>();
    for (int i = 1; i < n; i++) {
        register int a = read<int>(),b = read<int>(),c = read<int>();
        push(a,b,c); push(b,a,c);
    }
    dfs(1,0); dp(1,0);
    for (int i = 1; i <= n; i++) {
        // for (int j = 0 ;j <= 15; j++) printf("%d i=%d j=%d\n",g[i][j],i,j);
        for (int j = 0; j <= 15; j++) f[i] -= j * g[i][j],f[i] += (j ^ m) * g[i][j];
        printf("%d\n",f[i] - m);
    }
    // getchar(); getchar();
    return 0;
}
