# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
const int MAXN = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int first[MAXN], e = 1, size[MAXN], Ans, Judge, n, L, R, Num, f[MAXN], rt; 
bool vis[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(int &a, const int &b) {
    if (a < b) a = b;
}

struct node {
    node *ls, *rs; 
    int Mx;  
    node() { ls = rs = NULL; Mx = -inf; }
    inline void Maintain() {
        Mx = -inf;
        if (ls) gmax(Mx, ls -> Mx);
        if (rs) gmax(Mx, rs -> Mx);
    }
} *root;

inline void build(node *&o, int l, int r) {
    o = new node(); 
    if (l == r) return ;
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
}

inline void Update(node *o, int l, int r, int x, int val) {
    if (l == r) return gmax(o -> Mx, val), void();
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, val);
    else Update(o -> rs, mid + 1, r, x, val);
    o -> Maintain();
}

inline void Set(node *o, int l, int r, int x) {
    if (l == r) return o -> Mx = -inf, void();
    register int mid = l + r >> 1;
    if (x <= mid) Set(o -> ls, l, mid, x);
    else Set(o -> rs, mid + 1, r, x);
    o -> Maintain();
}

inline int Query(node *o, int l, int r, int x, int y) {
    if (x > y) return -inf;
    if (x == l && r == y) return o -> Mx;
    register int mid = l + r >> 1;
    if (y <= mid) return Query(o -> ls, l, mid, x, y);
    else if (x > mid) return Query(o -> rs, mid + 1, r, x, y);
    else return std::max(Query(o -> ls, l, mid, x, mid), Query(o -> rs, mid + 1, r, mid + 1, y));
}

struct edge {
    int u, v, w, next; 
} a[MAXN << 1];

inline void push(int u, int v, int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].next = first[u]; first[u] = e++;
}

inline void G_Size(int u, int fa) {
    size[u] = 1;
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa && !vis[a[i].v]) G_Size(a[i].v, u), size[u] += size[a[i].v];
}

inline void G_root(int u, int fa) {
    f[u] = 0;
    for (int i = first[u]; i; i = a[i].next) {
        if (a[i].v == fa || vis[a[i].v]) continue; 
        register int v = a[i].v;
        gmax(f[u], size[v]);
        G_root(v, u);
    }
    gmax(f[u], Num - f[u]);
    if (f[rt] > f[u]) rt = u; 
}

inline void dfs(int u, int fa, int deep, int Sum) {
    if (deep > R) return ;
    gmax(Ans, Query(root, 1, R, std::max(1, L - deep), R - deep) + Sum);
    if (deep >= L) gmax(Ans, Sum);
    for (int i = first[u]; i; i = a[i].next) 
        if (a[i].v != fa && !vis[a[i].v])
            dfs(a[i].v, u, deep + 1, Sum + ((a[i].w < Judge) ? -1 : 1));
}

inline void U(int u, int fa, int deep, int Sum) {
    if (deep > R) return ;
    Update(root, 1, R, deep, Sum);
    for (int i = first[u]; i; i = a[i].next) 
        if (a[i].v != fa && !vis[a[i].v])
            U(a[i].v, u, deep + 1, Sum + ((a[i].w < Judge) ? -1 : 1));
}

inline void Clear(int u, int fa, int deep) {
    if (deep > R) return ;
    Set(root, 1, R, deep);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa && !vis[a[i].v])
            Clear(a[i].v, u, deep + 1);
}

inline void Work(int u) {
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v]) dfs(a[i].v, u, 1, ((a[i].w < Judge) ? -1 : 1)), U(a[i].v, u, 1, ((a[i].w < Judge) ? -1 : 1));
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v]) Clear(a[i].v, u, 1);
}

inline void Div(int u) {
    vis[u] = true; Work(u); G_Size(u, 0); 
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (vis[v]) continue;
        Num = size[v]; rt = 0; G_root(v, 0); Div(rt);
    }
    vis[u] = false;
}

inline bool Check() {
    Ans = -inf, f[0] = inf; Num = n; rt = 0;
    G_Size(1, 0); G_root(1, 0); Div(rt);
    if (Ans >= 0) return true;
    return false;
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read(), L = read(), R = read();
    build(root, 1, R);
    int l = 0, r = 0, res = 0;
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read(), w = read();
        push(u, v, w), push(v, u, w);
        gmax(r, w);
    }
    while (l <= r) {
        Judge = l + r >> 1;
        if (Check()) res = Judge, l = Judge + 1;
        else r = Judge - 1;
    }
    printf("%d\n", res);
    return 0;
}