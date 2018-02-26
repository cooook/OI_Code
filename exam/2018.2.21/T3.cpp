# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
const int MAXN = 4e5 + 5;
int n, last, cnt, fa[MAXN], Mx[MAXN], L[MAXN], R[MAXN], idx, f[MAXN][18], val[MAXN], id[2][MAXN], size[MAXN], Q, tot, root[MAXN], first[MAXN], e = 1;
std::map<int, int> trans[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node {
    int l, r, sum; 
} tree[MAXN * 18];

inline void Update(int &o, int old, int l, int r, int x) {
    o = ++ tot; tree[o] = tree[old]; tree[o].sum ++;
    if (l == r) return;
    register int mid = l + r >> 1;
    if (x <= mid) Update(tree[o].l, tree[old].l, l, mid, x);
    else Update(tree[o].r, tree[old].r, mid + 1, r, x);
}

inline int Query(int o, int old, int l, int r, int x, int y) {
    if (x == l && r == y) return tree[o].sum - tree[old].sum;
    register int mid = l + r >> 1;
    if (y <= mid) return Query(tree[o].l, tree[old].l, l, mid, x, y);
    else if (x > mid) return Query(tree[o].r, tree[old].r, mid + 1, r, x, y);
    else return Query(tree[o].l, tree[old].l, l, mid, x, mid) + Query(tree[o].r, tree[old].r, mid + 1, r, mid + 1, y);
}
 
struct edge {
    int u, v, next;  
} a[MAXN];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u, int fa) {
    L[u] = ++ idx; f[u][0] = fa; 
    for (int i = 1; i <= 17; ++i) f[u][i] = f[f[u][i-1]][i-1];
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa) dfs(a[i].v, u); 
    R[u] = idx;
}

inline int Insert(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1;  
    for (; p && !trans[p].count(c); p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        register int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            register int nq = ++ cnt; 
            Mx[nq] = Mx[p] + 1; fa[nq] = fa[q]; fa[np] = fa[q] = nq;
            trans[nq] = trans[q];
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    }
    return last = np;
}

inline void Query(int l, int r) {
    if (l > r) return printf("%d\n", n), void();
    int Len = r - l + 1;
    int rt = id[1][l];
    for (int i = 17; ~i; --i)
        if (Mx[f[rt][i]] >= Len) rt = f[rt][i];
    int Ans = 0;
    if (l >= Len + 1) Ans += Query(root[l - Len - 1], root[0], 1, idx, L[rt], R[rt]);
    if (r != n) Ans += Query(root[n], root[r + 1], 1, idx, L[rt], R[rt]);
    printf("%d\n", Ans);
}

int main() {
    // freopen("T3.in", "r", stdin);
    // freopen("my.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; ++i) val[i] = read();
    -- n;
    for (int i = 1; i <= n; ++i) val[i] = val[i + 1] - val[i];
    last = ++ cnt;
    for (int i = n; i; --i) id[0][i] = Insert(val[i]);
    last = 1;
    for (int i = n; i; --i) id[1][i] = Insert(-val[i]);
    for (int i = 2; i <= cnt; ++i) push(fa[i], i); 
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) Update(root[i], root[i - 1], 1, idx, L[id[0][i]]);
    Q = read(); 
    while (Q --) {
        register int l = read(), r = read() - 1;
        Query(l, r);
    }
    // while (true);
    return 0;
}