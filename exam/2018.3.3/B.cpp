# include <bits/stdc++.h> 
const int MAXN = 1e5 + 5;
int n, m, q, c, first[MAXN], e = 1, root[MAXN], top[MAXN], fa[MAXN], size[MAXN], deep[MAXN], dfn[MAXN], pre[MAXN], son[MAXN], idx, cnt, Now_Root; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, next;
} a[MAXN << 1];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
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
    top[u] = Num; dfn[u] = ++ idx; pre[idx] = u;
    if (son[u]) dfs2(son[u], Num);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa[u] && a[i].v != son[u])
            dfs2(a[i].v, a[i].v);
}

struct node {
    int l, r, sum, add;
} tree[MAXN * 20];

inline void Update(int &o, int old, int l, int r, int x, int y, int val) {
    o = ++ cnt; tree[o] = tree[old], tree[o].sum += (y - x + 1) * val; 
    if (x == l && r == y) return tree[o].add += val, void();
    register int mid = l + r >> 1;
    if (y <= mid) Update(tree[o].l, tree[old].l, l, mid, x, y, val);
    else if (x > mid) Update(tree[o].r, tree[old].r, mid + 1, r, x, y, val);
    else Update(tree[o].l, tree[old].l, l, mid, x, mid, val), Update(tree[o].r, tree[old].r, mid + 1, r, mid + 1, y, val);
}

inline int Query(int o, int l, int r, int x) {
    if (l == r) return tree[o].sum;
    register int mid = l + r >> 1;
    if (x <= mid) return Query(tree[o].l, l, mid, x) + tree[o].add;
    else return Query(tree[o].r, mid + 1, r, x) + tree[o].add; 
}

inline void Push(int u, int v, int d) {
    int f1 = top[u], f2 = top[v];
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) std::swap(f1, f2), std::swap(u, v);
        Update(Now_Root, Now_Root, 1, n, dfn[f1], dfn[u], d);
        u = fa[f1]; f1 = top[u]; 
    }
    if (deep[u] > deep[v]) std::swap(u, v);
    Update(Now_Root, Now_Root, 1, n, dfn[u], dfn[v], d);
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read(); m = read(); q = read(), c = read();
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        push(u, v), push(v, u);
    }
    dfs1(1, 0), dfs2(1, 1);
    for (int i = 1; i <= m; ++i) {
        Now_Root = root[i - 1]; 
        register int u = read(), v = read(), d = read();
        Push(u, v, d);
        root[i] = Now_Root; 
    }
    while (q --) {
        register int u = read(), p = read(), Ans; 
        int t = Query(root[m], 1, n, dfn[u]);
        if (t < p * c) Ans = -1;
        else {
            int l = 1, r = m, mid;
            while (l <= r) {
                mid = l + r >> 1;
                if (Query(root[mid], 1, n, dfn[u]) < p * c) l = mid + 1;
                else Ans = mid, r = mid - 1;
            }
        }
        printf("%d %d\n", Ans, t % c);
    }
    // while (true); 
    return 0;
}