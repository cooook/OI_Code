# include <bits/stdc++.h>
const int MAXN = 200005;
int n, first[MAXN], e = 1, ls[MAXN], rs[MAXN], d[MAXN], size[MAXN], root[MAXN];
long long tag[MAXN], val[MAXN], L; 


inline long long read() {
    long long x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'? f = -f : 0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u, v, next; long long w;
} a[MAXN];

inline void push(int u, int v, long long w) {
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

inline void Add(int u,long long v) {
    tag[u] += v; val[u] += v;
}

inline void Push_down(int x) {
    if (!tag[x]) return;
    if (ls[x]) Add(ls[x], tag[x]);
    if (rs[x]) Add(rs[x], tag[x]);
    tag[x] = 0;
}

inline int merge(int x,int y) {
    if (!x || !y) return x | y;
    Push_down(x); Push_down(y);
    if (val[x] < val[y]) std::swap(x, y);
    rs[x] = merge(rs[x], y);
    if (d[ls[x]] < d[rs[x]]) std::swap(ls[x], rs[x]);
    d[x] = d[rs[x]] + 1;
    return x;
}

inline void dfs(int u) {
    size[u] = 1; root[u] = u;
    for (int i = first[u]; i; i = a[i].next) {
        dfs(a[i].v); Add(root[a[i].v], a[i].w);
        root[u] = merge(root[u], root[a[i].v]);
        size[u] += size[a[i].v];
    }
    while (val[root[u]] > L) root[u] = merge(ls[root[u]], rs[root[u]]), -- size[u];
}

int main() {
    n = read(); L = read(); d[0] = -1;
    for (int i = 2; i <= n; i++) {
        register int u = read(); long long w = read();
        push(u, i, w);
    } dfs(1);
    for (int i = 1; i <= n; i++) printf("%d\n", size[i]);
    return 0;
}