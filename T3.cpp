# include <stdio.h> 
# include <iostream> 
# define RG register 
const int MAXN = 3e4 + 5; 
int n, m, first[MAXN], e = 1, deep[MAXN], f[MAXN][18], son[MAXN], root[MAXN], cnt, Max; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; RG char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(register int &x, const register int &y) {
    if (x < y) x = y; 
}

struct node {
    int l, r, Sum; 
} tree[MAXN * 20]; 

inline void Insert(int &o, RG int old, RG int l, RG int r, RG int x) {
    o = ++ cnt; tree[o] = tree[old]; ++ tree[o].Sum;
    if (l == r) return;
    register int mid = l + r >> 1;
    if (x <= mid) Insert(tree[o].l, tree[old].l, l, mid, x);
    else Insert(tree[o].r, tree[old].r, mid + 1, r, x);
}

struct edge {
    int u, v, w, next;
} a[MAXN << 1];

inline void push(register int u, register int v, register int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].next = first[u]; first[u] = e++; 
}

inline void dfs(RG int u, RG int fa) {
    deep[u] = deep[fa] + 1; f[u][0] = fa; 
    for (int i = 1; i <= 17; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa) Insert(root[a[i].v], root[u], 1, Max, a[i].w), dfs(a[i].v, u);
}

inline int lca(RG int u, RG int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    register int t = deep[u] - deep[v];
    for (RG int i = 17; ~i; --i)
        if (t >> i & 1) u = f[u][i];
    if (u == v) return u;
    for (RG int i = 17; ~i; --i)
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];  
}

inline int Query(RG int u, RG int v, RG int fa, RG int kth) {
    RG int l = 1, r = Max, mid, left;
    while (l < r) {
        mid = l + r >> 1;
        left = tree[tree[u].l].Sum + tree[tree[v].l].Sum - 2 * tree[tree[fa].l].Sum;
        if (left >= kth) 
            u = tree[u].l, v = tree[v].l, fa = tree[fa].l, r = mid;
        else 
            kth -= left, u = tree[u].r, v = tree[v].r, fa = tree[fa].r, l = mid + 1;
    }
    return l; 
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("T3.in","r",stdin);
    // freopen("T3.out","w",stdout);
    n = read(); 
    for (RG int i = 1; i < n; ++i) {
        register int u = read(), v = read(), w = read();
        push(u, v, w), push(v, u, w); ++ son[u]; ++ son[v]; 
        gmax(Max, w);
    }
    dfs(1, 0);
    long long Ans = 0;
    register int i, j, K, len; 
    for (i = 1; i <= n; ++i)
        for (j = i + 1; j <= n; ++j) {
            K = lca(i, j), len = deep[i] + deep[j] - deep[K] * 2;
            if (len & 1) Ans += Query(root[i], root[j], root[K], len + 1 >> 1);
        }
    printf("%lld\n", Ans);
    // printf("%d\n", clock());
    // while (true); 
    return 0; 
}