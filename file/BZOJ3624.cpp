#include <stdio.h>
#include <algorithm>
#define MAXN 100005
#define GG {puts("no solution");getchar(); getchar();return 0;}
int n,m,k,fa[MAXN],cnt,top; bool vis[MAXN];


template<typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,id;
    inline bool operator < (const edge &a)const{
        return id > a.id;
    }
}a[MAXN],out[MAXN];

inline int find(int x) {
    return x == fa[x]?x:fa[x] = find(fa[x]);
}

inline void Link(int x,int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    fa[x] = y;
}

int main() {
    n = read<int>(); m = read<int>(); k = read<int>();
    if (k > n - 1) GG
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        register int u = read<int>(),v = read<int>(),id = read<int>();
        a[i] = (edge){u,v,id};
    }
    std::sort(&a[1],&a[m+1]);
    for (int i = 1; i <= m; i++) if (find(a[i].u) != find(a[i].v)) {
        Link(a[i].u,a[i].v); cnt ++;
        if (!a[i].id) vis[i] = true;
        if (cnt == n - 1) break;
    }
    if (cnt != n - 1) GG
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) if (vis[i] && top < k) Link(a[i].u,a[i].v),out[++top] = a[i];
    if (top < k)
        for (int i = 1; i <= m; i++) 
            if (!vis[i] && top < k && a[i].id == 0 && find(a[i].u) != find(a[i].v)) 
                Link(a[i].u,a[i].v),out[++top] = a[i];
    if (top < k) GG
    cnt = top;
    for (int i = 1; i <= m; i++) {
        if (find(a[i].u) != find(a[i].v) && a[i].id) {
            Link(a[i].u,a[i].v);
            cnt ++;
            out[++top] = a[i];
            if (cnt == n - 1) break;
        }
    }
    if (cnt != n - 1) GG
    for (int i = 1; i <= top; i++) printf("%d %d %d\n",out[i].u,out[i].v,out[i].id);
    // getchar(); getchar();
    return 0;
}