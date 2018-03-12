# include <bits/stdc++.h> 
# define RG register
const int MAXN = 1e5 + 5; 
const int inf = 0x3f3f3f3f; 
int n, val[MAXN], Ans[MAXN * 10], root[MAXN], cnt, first[MAXN], Mn, Mx, e, T[MAXN];  


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(RG int &x, const RG int &y) {
    if (x > y) x = y; 
}

inline void gmax(RG int &x, const RG int &y) {
    if (x < y) x = y; 
}

struct edge {
    int w, v, next; 
} a[MAXN * 20]; 

inline void push(int u, int v, int w) {
    a[e].v = v; a[e].w = w; a[e].next = first[u]; first[u] = e++;
}

struct _233 {
    int l, r, id;
}Q[MAXN * 20];

struct node {
    int l, r, mn; 
    node() { mn = inf; }
}tree[MAXN * 20];

# define ls(o) tree[o].l
# define rs(o) tree[o].r

inline void Update(int &o, int old, int l, int r, int x, int val) {
    o = ++ cnt; tree[o] = tree[old];
    if (l == r) return gmin(tree[o].mn, val), void();
    register int mid = l + r >> 1;
    if (x <= mid) Update(tree[o].l, tree[old].l, l, mid, x, val);
    else Update(tree[o].r, tree[old].r, mid + 1, r, x, val);
    tree[o].mn = std::min(tree[ls(o)].mn, tree[rs(o)].mn);
}

inline int Query(int o, int l, int r, int x, int y) {
    if (x > y) return inf;  
    if (x == l && r == y) return tree[o].mn;
    register int mid = l + r >> 1;
    if (y <= mid) return Query(ls(o), l, mid, x, y);
    else if (x > mid) return Query(rs(o), mid + 1, r, x, y);
    else return std::min(Query(ls(o), l, mid, x, mid), Query(rs(o), mid + 1, r, mid + 1, y));
}

inline void U(RG int x, RG int val) {
    for (; x <= n; x += x & (-x)) gmin(T[x], val);
}
 
inline int Q(RG int x) {
    RG int Ans = inf;
    for (; x; x -= (x) & (-x)) gmin(Ans, T[x]);
    return Ans; 
}

inline void Work() {
    e = 1; cnt = 0;
    memset(first, 0, n + 1 << 2);  
    memset(Mn, 0x3f, n + 1 << 2);
    RG int last = 0; 
    for (int i = n; i; --i) {
        Update(root[i], root[i + 1], val[i], i);
        while (true) {
            if (!last) last = Query(root[i + 1], Mn, Mx, val[i], Mx);
            else last = Query(root[last + 1], Mn, Mx, val[i], (val[i] + val[last]) >> 1);  
            if (last == inf) break; 
            push(i, last, val[last] - val[i]);
        }
    }
    std::sort(&Q[1], &Q[m + 1], [&](const _233 &a, const _233 &b) -> bool { return a.l == b.l ? a.r < b.r : a.l < b.l; });
    register int zz = n; 
    for (int i = m; i; --i) {
        for (; zz >= Q[i].x && zz; --zz)
            for (int j = first[zz]; j; j = a[j].next) U(a[j].v, a[j].w);
        gmin(Ans[Q[i].id], Q(Q[i].y));
    }
}

int main() {
    n = read(); val[0] = inf; 
    for (int i = 1; i <= n; ++i) val[i] = read(); 
    m = read();
    for (int i = 1; i <= m; ++i) Q[i].id = i, Q[i].l = read(), Q[i].r = read(), Ans[i] = inf; 
    Work();
    std::reverse(&val[1], &val[n]);
    for (int i = 1; i <= m; ++i) Q[i].l = n - Q[i].l + 1, Q[i].r = n - Q[i].r + 1;
    Work();
    for (int i = 1; i <= m; ++i) printf("%d\n", Ans[i]);
    return 0; 
}