# include <bits/stdc++.h>
const int MAXN = 1e5 + 5;
typedef long long ll; 
int n, m, l[MAXN], first[MAXN], e = 1, key[MAXN], ls[MAXN], rs[MAXN], d[MAXN], fa[MAXN], size[MAXN]; ll Ans, Sum[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u, v, next;
}a[MAXN];

inline void push(int u,int v){
    a[e] = {u, v, first[u]}; first[u] = e++;
}

inline int merge(int x,int y) {
    if (!x || !y) return x | y;
    if (key[x] < key[y]) std::swap(x, y);
    rs[x] = merge(rs[x], y);
    if (d[ls[x]] < d[rs[x]]) std::swap(ls[x], rs[x]);
    d[x] = d[rs[x]] + 1;
    return x;
}

inline void dfs(int u) {
    Sum[u] = key[u]; fa[u] = u; size[u] = 1;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        dfs(v);
        size[u] += size[a[i].v];
        Sum[u] += Sum[a[i].v];
        fa[u] = merge(fa[u], fa[a[i].v]);
    }
    while (Sum[u] > m) Sum[u] -= key[fa[u]], fa[u] = merge(ls[fa[u]], rs[fa[u]]), -- size[u];
    Ans = std::max(Ans, 1ll * size[u] * l[u]);
}

int main() {
    n = read(), m = read(); d[0] = -1;
    for (int i = 1; i <= n; i++) {
        push(read(), i);
        key[i] = read(), l[i] = read();
    }  dfs(1);
    printf("%lld\n", Ans);
    return 0;
}