# include <bits/stdc++.h>
const int MAXN = 4e5 + 5;
int n, m, k, type; 


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge { int u, v; } a[MAXN] ;
inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
} 

struct node {
    node *ch[2], *f; 
    bool tag; int mn, val;
    inline void Maintain();
    inline bool dir();
    inline bool isrt();
    inline void rotate();
    inline void Splay();
    inline void rev();
    inline void Push_down();
} null[MAXN], *Node[MAXN], *Edge[MAXN];

inline void node::Maintain() {
    mn = 0x3f3f3f3f;
    gmin(mn, val);
    gmin(mn, ch[0] -> mn);
    gmin(mn, ch[1] -> mn);
}

inline bool node::dir() {
    return f -> ch[1] == this;
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    fa -> f = this; f = pa; ch[d ^ 1] = fa;
    fa -> Maintain(); Maintain();
}

inline void node::rev() {
    std::swap(ch[0], ch[1]);
    tag ^= 1;
}

inline void node::Push_down() {
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}

inline void node::Splay() {
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()) {
            t -> f -> Push_down(), t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
}

inline void Access(node *x) {
    node *y = null;
    while (x != null) {
        x -> Splay();
        x -> ch[1] = y;
        x -> Maintain();
        y = x; x = x -> f;
    }
}

inline void Make_root(node *x) {
    Access(x); x -> Splay(); x -> rev();
}

inline void Link(node *x, node *y) {
    Make_root(x); x -> f = y;
}

inline void Cut(node *x, node *y) {
    Make_root(x); Access(y); y -> Splay(); 
    y -> ch[0] = x -> f = null; y -> Maintain();
}

inline node* find(node *x) {
    Access(x); x -> Splay();
    while (x -> ch[0] != null) x -> Push_down(), x = x -> ch[0];
    return x;
}

struct Tree {
    int size, l, r;
}tree[MAXN * 10];

int root[MAXN], cnt;

# define ls tree[o].l, tree[old].l
# define rs tree[o].r, tree[old].r

inline void Update(int &o, int old, int l, int r, int x) {
    o = ++ cnt; tree[o] = tree[old]; tree[o].size ++;
    if (l == r) return ;
    register int mid = l + r >> 1;
    if (x <= mid) Update(ls, l, mid, x);
    else Update(rs, mid + 1, r, x);
}

inline int Query(int o, int old, int l, int r, int x, int y) {
    if (x == l && r == y) return tree[o].size - tree[old].size;
    register int mid = l + r >> 1;
    if (y <= mid) return Query(ls, l, mid, x, y);
    else if (x > mid) return Query(rs, mid + 1, r, x, y);
    else return Query(ls, l, mid, x, mid) + Query(rs, mid + 1, r, mid + 1, y);
} 

inline void Link(int u, int v, int id) {
    Link(Node[u], Edge[id]); Link(Edge[id], Node[v]);
}

inline void Cut(int u, int v, int id) {
    Cut(Node[u], Edge[id]); Cut(Edge[id], Node[v]);
}

int main() {
    n = read(), m = read(), k = read(), type = read();
    for (int i = 0; i < MAXN; ++i) null[i].ch[0] = null[i].ch[1] = null[i].f = null, null[i].tag = false, null[i].mn = null[i].val = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i) Node[i] = &null[i];
    for (int i = 1; i <= m; ++i) a[i].u = read(), a[i].v = read(), Edge[i] = &null[i + n], Edge[i] -> mn = Edge[i] -> val = i;
    int val; 
    for (int i = 1; i <= m; ++i) {
        if (a[i].u == a[i].v) { root[i] = root[i - 1]; continue; }
        register node *x = find(Node[a[i].u]), *y = find(Node[a[i].v]);
        if (x != y) val = 0;
        else {
            Make_root(Node[a[i].u]);
            Access(Node[a[i].v]);
            Node[a[i].u] -> Splay();
            int ID = Node[a[i].u] -> mn;
            Cut(a[ID].u, a[ID].v, ID);
            val = ID;
        }
        Link(a[i].u, a[i].v, i);
        Update(root[i], root[i - 1], 0, m, val);
    }
    int Ans = 0;
    while (k --) {
        if (!type) Ans = 0;
        register int l = read() ^ Ans, r = read() ^ Ans;
        printf("%d\n", Ans = n - Query(root[r], root[l - 1], 0, m, 0, l - 1)); 
    }
    return 0;
}