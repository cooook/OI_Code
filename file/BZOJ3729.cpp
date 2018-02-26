# include <bits/stdc++.h> 
const int MAXN = 1e6+5;
int n, first[MAXN], e = 1, L[MAXN], R[MAXN], cnt, deep[MAXN], val[MAXN], mod, m, rt, Last;
bool _root[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, next; 
} a[MAXN << 1];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

struct node {
    node *ch[2], *f;
    int Sum[2], val, dep;
    inline bool dir(); 
    inline bool isrt();
    inline void Splay(node*);
    inline void rotate();
    inline void Maintain();
}*root, null[MAXN << 1], *tree[MAXN << 1];

inline bool node::dir() {
    return f -> ch[1] == this; 
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::Splay(node *fa = null) {
    for (node *t = f; f != fa; rotate(), t = f)
        if (t -> f != fa) (t -> dir() == dir()?t : this) -> rotate();
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    ch[d ^ 1] = fa; fa -> f = this; this -> f = pa;
    fa -> Maintain(); Maintain();
}

inline void node::Maintain() {
    Sum[dep] = val; Sum[dep ^ 1] = 0; 
    Sum[0] ^= ch[0] -> Sum[0] ^ ch[1] -> Sum[0];
    Sum[1] ^= ch[0] -> Sum[1] ^ ch[1] -> Sum[1];
}

inline node* Pre(node *x) {
    x = x -> ch[0];
    while (x -> ch[1] != null) x = x -> ch[1];
    return x;
}

inline node* Next(node *x) {
    x = x -> ch[1];
    while (x -> ch[0] != null) x = x -> ch[0];
    return x;
}

inline void Split(node *&l, node *&r) {
    l -> Splay(); l = Pre(l);
    r -> Splay(); r = Next(r);
    l -> Splay(); r -> Splay(l);
}

inline node* Div(int l, int r) {
    if (l > r) return null; 
    int mid = l + r >> 1;
    tree[mid] -> ch[0] = Div(l, mid - 1);
    tree[mid] -> ch[0] -> f = tree[mid];
    tree[mid] -> ch[1] = Div(mid + 1, r);
    tree[mid] -> ch[1] -> f = tree[mid];
    tree[mid] -> Maintain();
    return tree[mid]; 
}

inline void dfs(int u, int fa) {
    L[u] = ++ cnt; tree[cnt] -> dep = deep[u]; tree[cnt] -> val = val[u];
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        deep[v] = deep[u] ^ 1;
        dfs(v, u);
    }
    R[u] = ++ cnt; tree[cnt] -> dep = deep[u]; tree[cnt] -> val = 0;
}

inline void Change(int x, int y) {
    y %= (mod + 1);
    tree[L[x]] -> Splay(); tree[L[x]] -> val = y; tree[L[x]] -> Maintain();
}

inline void Query(int x) {
    node *l = tree[L[x]], *r = tree[R[x]];
    Split(l, r);
    int Ans = r -> ch[0] -> Sum[deep[x] ^ (deep[x] == deep[rt])];
    if (deep[x] != deep[rt]) Ans ^= tree[L[x]] -> val;
    puts(Ans ? "MeiZ" : "GTY");
    Last += Ans != 0;
}

inline void Add(int u, int v, int x) {
    if (!L[u]) return;
    L[v] = ++ cnt; R[v] = ++ cnt; deep[v] = deep[u] ^ 1;
    tree[L[v]] -> dep = deep[v]; tree[R[v]] -> dep = deep[v];
    tree[L[v]] -> val = x % (mod + 1);
    tree[L[v]] -> ch[1] = tree[R[v]];
    tree[R[v]] -> f = tree[L[v]];
    tree[L[v]] -> Maintain();
    node *r = tree[R[u]], *l; r -> Splay();
    l = Pre(r); 
    l -> Splay(); r -> Splay(l);
    r -> ch[0] = tree[L[v]]; 
    tree[L[v]] -> f = r;
    r -> Maintain();
}

int main() {
    n = read(); mod = read(); 
    for (int i = 0; i <= n << 5; i++)
        null[i].ch[0] = null[i].ch[1] = null[i].f = null,
        null[i].Sum[0] = null[i].Sum[1] = null[i].val = 0,
        tree[i] = &null[i];
    for (int i = 1; i <= n; i++) val[i] = read() % (mod + 1); 
    rt = 0;
    for (int i = 1; i < n; i++) {
        register int u = read(), v = read();
        push(u, v); _root[v] = true; 
    }
    for (int i = 1; i <= n; i++)
        if (!_root[i]) { rt = i; break; }
    ++ cnt;
    dfs(rt, 0);
    ++ cnt;
    root = Div(1, cnt);
    m = read();
    while (m --) {
        register int op = read(), x, y, z;
        if (op == 1) Query(read() ^ Last);
        else if (op == 2) x = read() ^ Last, y = read() ^ Last, Change(x, y);
        else x = read() ^ Last, y = read() ^ Last, z = read() ^ Last, Add(x, y, z);
    }
    return 0;
}