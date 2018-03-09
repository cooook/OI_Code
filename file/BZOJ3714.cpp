# include <stdio.h> 
# include <iostream>
# include <algorithm> 
const int MAXN = 2005; 
int n, cnt, fa[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, w; 
    inline bool operator < (const edge &a) const {
        return w < a.w; 
    }
} a[MAXN * MAXN]; 

inline int find(register int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]); 
}

int main() {
    n = read(); 
    register int i, j, tot = 0, u, v; 
    register long long Ans = 0; 
    for (i = 1; i <= n; ++i)
        for (j = i; j <= n; ++j)
            a[++cnt].u = i - 1, a[cnt].v = j, a[cnt].w = read(); 
    std::sort(&a[1], &a[cnt + 1]);
    for (i = 1; i <= n; ++i) fa[i] = i; 
    for (i = 1; i <= cnt; ++i) {
        u = find(a[i].u), v = find(a[i].v);
        if (u != v) fa[u] = v, Ans += a[i].w, ++ tot;
        if (tot == n) break;
    }
    printf("%lld\n", Ans);
    return 0; 
}
/*
    没有想到的点：
    如果知道每个点的前缀和即可知道每个点.  
    此前缀和是针对0而言而不是1.  
    知道[1,j-1]和[j,i]即可知道[1,i].
    就相当于j-1,和i之间有了联系.
    最后只需要让n+1个点(包括0)都有联系就可以知道答案了.
*/