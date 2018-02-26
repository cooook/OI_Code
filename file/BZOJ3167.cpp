#include <stdio.h>
#include <cstring>
#include <iostream>
typedef long long ll;
const int mod = 1e9+7,MAXN = 1005;
int T,first[MAXN],e = 1,n,size[MAXN];
ll f[MAXN][MAXN],Sum[MAXN],g[MAXN],C[MAXN][MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline bool read_char() {
    char ch = getchar();
    for (; ch != '<' && ch != '>'; ch = getchar());
    return ch != '<';
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w) {
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

void dp(int u,int fa) {
    size[u] = 1; f[u][1] = 1;
    for (int i = first[u],v; i; i = a[i].next) {
        v = a[i].v;
        if (v == fa) continue;
        dp(v,u);
        for (int j = 1; j <= size[u] + size[v]; j++) g[j] = 0;
        if (a[i].w) {
            for (int j = 1; (j << 1) <= size[u]; j++) std::swap(f[u][j],f[u][size[u]-j+1]);
            for (int j = 1; (j << 1) <= size[v]; j++) std::swap(f[v][j],f[v][size[v]-j+1]);
        }
        Sum[0] = 0;
        for (int j = 1; j <= size[v]; j++) Sum[j] = (Sum[j-1] + f[v][j]) % mod;
        for (int j = 1; j <= size[u]; j++)
            for (int k = j + 1; k <= j + size[v]; k++)
                (g[k] += f[u][j] * Sum[k-j] % mod * C[j-1][k-j] % mod * C[size[u]-j][size[v]-k+j] % mod) %= mod;
        size[u] += size[v];
        for (int j = 1; j <= size[u]; j++) f[u][j] = g[j];
        if (a[i].w)  for (int j = 1; (j << 1) <= size[u]; j++) std::swap(f[u][j],f[u][size[u]-j+1]);
    }
}

int main() {
    for (int i = 0; i <= 1000; i++) C[i][0] = C[0][i] = 1;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j <= 1000; j++)
            C[i][j] = (C[i-1][j] + C[i][j-1]) % mod;
    T = read<int>();
    while (T--){
        memset(first,0,sizeof first); e = 1;
        memset(f,0,sizeof f); 
        memset(size,0,sizeof size);
        n = read<int>();
        for (int i = 1,u,v,w; i < n; i++) {
            u = read<int>() + 1,w = read_char(),v = read<int>() + 1;
            push(u,v,w),push(v,u,w^1);
        }
        dp(1,0);
        int Ans = 0;
        for (int i = 1; i <= n; i++) Ans = (Ans + f[1][i]) % mod;
        printf("%d\n",Ans);
    }
    return 0;
}