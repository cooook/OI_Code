# include <bits/stdc++.h> 
typedef long long ll; 
const int MAXN = 2e5 + 5; 
int n, m, val[MAXN], dfn[MAXN], pre[MAXN], idx, size[MAXN], son[MAXN], deep[MAXN], fa[MAXN], top[MAXN], last[MAXN], first[MAXN], e = 1;
ll f[MAXN][2], g[MAXN][2]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int max(const int &x, const int &y) {
    return x > y ? x : y;
}

inline ll max(const ll &a, const ll &b) {
    return a > b ? a : b;
}

inline void gmax(int &a, const int &b) {
    if (a < b) a = b;
}

inline void gmax(ll &a, const ll &b) {
    if (a < b) a = b;
}

struct Option {
    int opt, x, y; 
} w[MAXN];

struct edge {
    int u, v, next; 
} a[MAXN];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

struct node {
    node *ls, *rs;
    ll mx[2][2];
    int l, r; 
    node() { ls = rs = NULL; memset(mx, 0xef, sizeof mx); }
    node(int l, int r): l(l), r(r) { ls = rs = NULL; memset(mx, 0xef, sizeof mx); }
    inline void Maintain() {
        if (l == r) return; 
        memset(mx, 0xef, sizeof mx);
        gmax(mx[0][1], ls -> mx[0][1] + rs -> mx[0][1]);
        gmax(mx[0][1], ls -> mx[0][0] + rs -> mx[1][1]);
        gmax(mx[0][1], ls -> mx[0][0] + rs -> mx[0][1]);
        gmax(mx[1][0], ls -> mx[1][0] + rs -> mx[1][0]);
        gmax(mx[1][0], ls -> mx[1][1] + rs -> mx[0][0]);
        gmax(mx[1][0], ls -> mx[1][0] + rs -> mx[0][0]);
        gmax(mx[0][0], ls -> mx[0][1] + rs -> mx[0][0]);
        gmax(mx[0][0], ls -> mx[0][0] + rs -> mx[1][0]);
        gmax(mx[0][0], ls -> mx[0][0] + rs -> mx[0][0]);
        gmax(mx[1][1], ls -> mx[1][0] + rs -> mx[1][1]);
        gmax(mx[1][1], ls -> mx[1][1] + rs -> mx[0][1]);
        gmax(mx[1][1], ls -> mx[1][0] + rs -> mx[0][1]); 
    }
    inline void* operator new (size_t);
}*root, *C, *mempool;

inline void* node::operator new (size_t) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
    return C++;
} 

inline void build(node *&o, int l, int r) {
    o = new node(l, r);
    if (l == r) return o -> mx[0][0] = f[pre[l]][0], o -> mx[1][1] = f[pre[l]][1], void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid), build(o -> rs, mid + 1, r);
    o -> Maintain();  
}

inline node* Query(node *o, int l, int r, int x, int y) {
    if (x == l && r == y) return o;
    register int mid = l + r >> 1;
    if (y <= mid) return Query(o -> ls, l, mid, x, y);
    else if (x > mid) return Query(o -> rs, mid + 1, r, x, y);
    else {
        node *t = new node(x, y);
        t -> ls = Query(o -> ls, l, mid, x, mid), t -> rs = Query(o -> rs, mid + 1, r, mid + 1, y);
        t -> Maintain(); return t; 
    }
}

inline void Update(node *o, int l, int r, int x, int y) {
    if (!y) return; 
    if (l == r) return o -> mx[1][1] += y, void();
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, y);
    else Update(o -> rs, mid + 1, r, x, y);
    o -> Maintain();
}

inline void U(node *o, int l, int r, int x, int y) {
    if (l == r) return o -> mx[0][0] = max(0ll, o -> mx[0][0] + y), void();
    register int mid = l + r >> 1;
    if (x <= mid) U(o -> ls, l, mid, x, y);
    else U(o -> rs, mid + 1, r, x, y);
    o -> Maintain(); 
}

inline void dfs1(int u, int fa) {
    ::fa[u] = fa; size[u] = 1; deep[u] = deep[fa] + 1; 
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

inline void dfs2(int u, int Num) {
    top[u] = Num; dfn[u] = ++ idx; pre[idx] = u; last[Num] = u; 
    if (son[u]) dfs2(son[u], Num);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa[u] && a[i].v != son[u])
            dfs2(a[i].v, a[i].v); 
}

inline ll Q(int u) {
    register node *t = Query(root, 1, n, dfn[u], dfn[last[top[u]]]);
    return max(max(t -> mx[1][0], t -> mx[1][1]), max(t -> mx[0][0], t -> mx[0][1]));
}

inline void Change(int u, int val) {
    if (val == ::val[u]) return ;
    int f1 = top[u]; register node *last, *t;
    register ll mx0, mx1, delta1, delta2;

    last = Query(root, 1, n, dfn[f1], dfn[::last[f1]]);
    mx0 = max(last -> mx[0][0], last -> mx[0][1]);
    mx1 = max(mx0, max(last -> mx[1][0], last -> mx[1][1]));
    Update(root, 1, n, dfn[u], val - ::val[u]);
    ::val[u] = val; 

    while (fa[f1]) {
        t = Query(root, 1, n, dfn[f1], dfn[::last[f1]]);
        delta1 = max(t -> mx[0][1], t -> mx[0][0]) -mx0;
        delta2 = max(max(t -> mx[0][1], t -> mx[0][0]), max(t -> mx[1][0], t -> mx[1][1])) - mx1;
        if (!delta1 && !delta2) break; 
        u = fa[f1]; f1 = top[u]; 
        last = Query(root, 1, n, dfn[f1], dfn[::last[f1]]);
        mx0 = max(last -> mx[0][0], last -> mx[0][1]);
        mx1 = max(mx0, max(last -> mx[1][0], last -> mx[1][1]));
        Update(root, 1, n, dfn[u], delta1);
        U(root, 1, n, dfn[u], delta2);
    }
}

inline void dfs3(int u, int fa) {
    f[u][1] = val[u]; f[u][0] = 0;
    g[u][1] = val[u]; g[u][0] = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        dfs3(v, u);
        g[u][1] += g[v][0];
        g[u][0] += max(g[v][0], g[v][1]);
        if (v == son[u]) continue;
        f[u][1] += g[v][0];
        f[u][0] += max(g[v][0], g[v][1]);
    }
}

int main() {
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    n = read(), m = read();
    for (int i = 2; i <= n; ++i) push(read(), i);
    for (int i = 1; i <= n; ++i) val[i] = read();
    register int x;
    for (int i = 1; i <= m; ++i) {
        register char ch = getc; 
        for (; ch != 'Q' && ch != 'C' && ch != 'A'; ch = getc) ;
        x = read();
        if (ch == 'A') {
            push(x, ++n);
            w[i].opt = 0, w[i].x = n, w[i].y = read();
        }
        else if (ch == 'C') w[i].opt = 0, w[i].x = x, w[i].y = read();
        else w[i].opt = 1, w[i].x = x; 
    }
    dfs1(1, 0), dfs2(1, 1), dfs3(1, 0);
    build(root, 1, n); 
    for (int i = 1; i <= m; ++i)
        if (w[i].opt == 0) Change(w[i].x, w[i].y);
        else printf("%lld\n", Q(w[i].x));
    return 0;
}