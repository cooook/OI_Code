# include <stdio.h>
# include <iostream> 
# define RG register 
typedef long long ll; 
const int MAXN = 1e5 + 5;  
int first[MAXN], e = 1, n, m, deep[MAXN], f[MAXN][18], in[MAXN], out[MAXN], idx, pos[MAXN], Now_rt; 
 
 
inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
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
    bool tag; 
    inline void rev();
    inline void Splay();
    inline void rotate();
    inline bool isrt();
    inline bool dir();
    inline void Push_down();
}null[MAXN];
 
inline bool node::isrt(){
    return f -> ch[0] != this && f -> ch[1] != this;
}
 
inline bool node::dir(){
    return f -> ch[1] == this;
}
 
inline void node::Push_down(){
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}
 
inline void node::rev(){
    std::swap(ch[0],ch[1]); tag ^= 1;
}
 
inline void node::rotate(){
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    ch[d ^ 1] = fa; fa -> f = this; this -> f = pa;
}
 
inline void node::Splay(){
    Push_down(); 
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()){
            t -> f -> Push_down(), t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
    }
    else t -> Push_down(), Push_down();
}
 
struct Seg {
    Seg *ls, *rs; 
    ll Sum, add;
    Seg() { ls = rs = NULL; Sum = add = 0; }
}*root;
 
inline void build(Seg *&o, int l, int r) {
    o = new Seg();
    if (l == r) return o -> Sum = deep[pos[l]], void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid), build(o -> rs, mid + 1, r);
    o -> Sum = o -> ls -> Sum + o -> rs -> Sum;
}
 
inline void Update(Seg *o, int l, int r, int x, int y, int val) {
    if (x > y) return ;
    // printf("%d %d %d %d\n", l, r, x, y);
    o -> Sum += (y - x + 1) * val;
    if (x == l && r == y) return o -> add += val, void();
    register int mid = l + r >> 1;
    if (y <= mid) Update(o -> ls, l, mid, x, y, val);
    else if (x > mid) Update(o -> rs, mid + 1, r, x, y, val);
    else Update(o -> ls, l, mid, x, mid, val), Update(o -> rs, mid + 1, r, mid + 1, y, val);
}
 
inline ll Query(Seg *o, int l, int r, int x, int y) {
    if (x > y) return 0;
    // printf("%d %d %d %d\n", l, r, x, y);
    if (x == l && r == y) return o -> Sum;
    RG ll Ans = (y - x + 1) * o -> add;
    RG int mid = l + r >> 1;
    if (y <= mid) return Query(o -> ls, l, mid, x, y) + Ans;
    else if (x > mid) return Query(o -> rs, mid + 1, r, x, y) + Ans;
    else return Query(o -> ls, l, mid, x, mid) + Query(o -> rs, mid + 1, r, mid + 1, y) + Ans;
}
 
inline void dfs(int u, int fa) {
    f[u][0] = fa; deep[u] = deep[fa] + 1; 
    for (int i = 1; i <= 17; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
    in[u] = ++idx; pos[idx] = u; 
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        null[v].f = &null[u]; 
        dfs(v, u);
    }
    out[u] = idx; 
}
 
inline int lca(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    register int t = deep[u] - deep[v];
    for (int i = 17; ~i; --i)
        if (t >> i & 1) u = f[u][i];
    if (u == v) return u;
    for (int i = 17; ~i; --i)
        if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
 
inline int find(int x, int depth) {
    int t = deep[x] - depth;
    for (int i = 17; ~i; --i)
        if (t >> i & 1) x = f[x][i];
    return x; 
}
 
inline void Add(int x, int val) {
    // printf("Add %d\n", x);
    if (x == Now_rt) Update(root, 1, n, 1, n, val);
    else {
        RG int Lca = lca(Now_rt, x), t;
        if (Lca != x) Update(root, 1, n, in[x], out[x], val);
        else t = find(Now_rt, deep[x] + 1), 
            Update(root, 1, n, 1, in[t] - 1, val), 
            Update(root, 1, n, out[t] + 1, n, val);
    }
}
 
inline void Tree_Add(node *x, int val) {
    node *o = x; o -> Push_down();
    while (o -> ch[0] != null) o = o -> ch[0], o -> Push_down();
    Add(o - null, val); 
}
 
inline void Access(node *x) {
    node *y = null;
    while (x != null) {
        x -> Splay();
        // printf("Access x = %d\n", x - null);
        if (x -> ch[1] != null) Tree_Add(x -> ch[1], 1);
        x -> ch[1] = y;
        if (y != null) Tree_Add(y, -1);
        y = x; x = x -> f;
    }
}
 
inline void Make_root(node *x) {
    Access(x); x -> Splay(); x -> rev(); Now_rt = x - null;
}
 
inline double Tree_Query(int x) {
    if (x == Now_rt) return 1.0 * root -> Sum / n;
    else {
        RG int Lca = lca(Now_rt, x), t;
        if (Lca != x) return 1.0 * Query(root, 1, n, in[x], out[x]) / (out[x] - in[x] + 1);
        else {
            t = find(Now_rt, deep[x] + 1);
            return
            1.0 * (Query(root, 1, n, 1, in[t] - 1) + Query(root, 1, n, out[t] + 1, n)) 
            / (in[t] - 1 + n - out[t]);
        }
    }
}
 
char opt[20]; 
 
int main() {
    n = read(); m = read();
    for (int i = 0; i <= n; ++i)
        null[i].ch[0] = null[i].ch[1] = null[i].f = null, null[i].tag = false;
    for (int i = 1; i < n; ++i) {
        RG int u = read(), v = read();
        push(u, v), push(v, u);
    }
    Now_rt = 1;  dfs(1, 0); 
    build(root, 1, n);
    while (m --) {
        scanf("%s", opt);
        // printf("%s\n", opt);
        RG int x = read(); 
        if (opt[2] == 'L') Access(&null[x]);
        else if (opt[2] == 'C') Make_root(&null[x]);
        else printf("%.10f\n", Tree_Query(x));
    }
    return 0;
}