#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAXN 100005
#define P 6323
#define fi first
#define se second
typedef std::pair<int,unsigned long long> pa;
typedef unsigned long long ull;
int root,n,m,q,size[MAXN],first[MAXN],e = 1,T; 
ull f[MAXN],Tree[MAXN],Now[MAXN];
int have_fa[MAXN],Ans[MAXN]; pa now[MAXN];
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
struct edge{
    int u,v,next;
}a[MAXN<<1];
 
inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}
 
inline void Tree_Hash(int u) {
    size[u] = 1;
    for (int i = first[u]; i; i = a[i].next) Tree_Hash(a[i].v),size[u] += size[a[i].v];
    f[u] = size[u];
    int cnt = 0;
    for (int i = first[u]; i; i = a[i].next) now[++cnt] = (pa){size[a[i].v],f[a[i].v]};
    std::sort(&now[1],&now[cnt+1]);
    for (int i = 1; i <= cnt; i++) f[u] = f[u] * P + now[i].se;
}
 
int main() {
    n = read<int>(); m = read<int>(); q = read<int>();
    for (int i = 1; i <= n; i++)  {
        for (int j = 1; j <= m; j++) first[j] = 0,f[j] = 0;
        e = 1; T ++;
        for (int j = 1; j < m; j++) {
            register int u = read<int>(),v = read<int>();
            push(u,v),have_fa[v] = T;
        }
        for (int j = 1; j <= m; j++) if (have_fa[j] != T) root = j;
        Tree_Hash(root);
        Tree[i] = f[root];
        Now[i] = Tree[i];
    }  
    std::sort(&Now[1],&Now[n+1]);
    int sz = std::unique(&Now[1],&Now[n+1]) - Now - 1; 
    for (int i = 1; i <= n; i++) Ans[std::lower_bound(&Now[1],&Now[sz+1],Tree[i]) - Now]++;
    while (q --) {
        for (int i = 1; i <= m; i++) f[i] = first[i] = 0;
        e = 1; T ++;
        for (int i = 1; i < m; i++) {
            register int u = read<int>(),v = read<int>();
            push(u,v),have_fa[v] = T;
        }
        for (int i = 1; i <= m; i++) if (have_fa[i] != T) root = i;
        Tree_Hash(root);
        int p = std::lower_bound(&Now[1],&Now[sz+1],f[root]) - Now;
        if (Now[p] != f[root]) printf("0\n");
        else printf("%d\n",Ans[p]);
    }
    return 0;
}