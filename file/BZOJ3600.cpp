# include <bits/stdc++.h> 
const double alpha = 0.755;
const double eps = 1e-7;
const int MAXN = 600005;
int Ins, Lson[MAXN], Rson[MAXN], Now[MAXN], n, m, len, pre[MAXN];


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    node *ch[2];
    double l, r, val;
    int size, id;
    node() { l = r = val = 0; size = 0; id = 0; }
    node(double L, double R, int ID) ;
    inline bool bad() {
        return ch[0] -> size >= size * alpha || ch[1] -> size >= size * alpha;
    }

    inline void Maintain() {
        size = ch[0] -> size + ch[1] -> size + 1;
    }

    inline void* operator new (size_t);
}*null, *root, *C, *mempool, *lis[MAXN], *val[MAXN];

inline void* node::operator new(size_t) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
    return C ++;
}

node::node(double L, double R, int ID) {
    if (this == null) return;
    l = L; r = R; val = (L + R) / 2;
    ch[0] = ch[1] = null; size = 1; id = ID;
}

inline node* Divide(int l, int r, double L, double R) {
    if (l > r) return null;
    register int mid = l + r >> 1; double M = (L + R) / 2;
    lis[mid] -> l = L; lis[mid] -> r = R; lis[mid] -> val = M;
    lis[mid] -> ch[0] = Divide(l, mid - 1, L, M);
    lis[mid] -> ch[1] = Divide(mid + 1, r, M, R);
    lis[mid] -> Maintain();
    return lis[mid];
}

struct Seg{
    Seg *ls, *rs;
    int pos, mx;
    Seg() { ls = rs = NULL; mx = pos = 0; }
    inline void Maintain() {
        pos = 0; mx = 0;
        if (ls && val[ls -> mx] -> val > val[mx] -> val) pos = ls -> pos, mx = ls -> mx;
        if (rs && val[rs -> mx] -> val > val[mx] -> val) pos = rs -> pos, mx = rs -> mx;
    }
}*Segment;

inline void build(Seg *&o, int l, int r) {
    o = new Seg(); o -> pos = l;
    if (l == r) return ;
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
}

inline void Update(Seg *o, int l, int r, int x, int pos) {
    if (l == r) return o -> mx = pos, void();
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, pos);
    else Update(o -> rs, mid + 1, r, x, pos);
    o -> Maintain();
}

inline void dfs(node *o) {
    if (o == null) return;
    dfs(o -> ch[0]); 
    lis[++len] = o;
    dfs(o -> ch[1]);
}

inline void rebuild(node *&p) {
    len = 0;  dfs(p);
    p = Divide(1, len, p -> l, p -> r);
}

inline int sgn(double x) {
    return (x > -eps) - (x < eps);
}

inline int Cmp(node *o) {
    if (sgn(val[Lson[Ins]] -> val - val[Lson[o -> id]] -> val) == 0) {
        if (sgn(val[Rson[Ins]] -> val - val[Rson[o -> id]] -> val) == 0) return -1;
        return sgn(val[Rson[Ins]] -> val - val[Rson[o -> id]] -> val) > 0;
    }
    return sgn(val[Lson[Ins]] -> val - val[Lson[o -> id]] -> val) > 0; 
}

inline node** Insert(node *&o, double l, double r) {
    register double mid = (l + r) / 2;
    if (o == null) return o = new node(l, r, Ins), val[Ins] = o, &null;
    node **p = &null;
    int d = Cmp(o);
    if (d == -1) { val[Ins] = o; return &null; }
    else if (!d) p = Insert(o -> ch[0], l, mid);
    else p = Insert(o -> ch[1], mid, r);
    if (o -> bad()) p = &o;
    o -> Maintain();
    return p;
}

int ID, Mx;

inline void Query(Seg *o, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        if (!ID || val[Mx] -> val < val[o -> mx] -> val) Mx = o -> mx, ID = o -> pos;
        return ;
    }
    register int mid = l + r >> 1;
    if (x <= mid) Query(o -> ls, l, mid, x, y);
    if (mid < y) Query(o -> rs, mid + 1, r, x, y);
}

inline void Query(int l, int r) {
    ID = 0; Mx = 0;
    Query(Segment, 1, n, l, r);
    printf("%d\n", ID);
}

int main() {
    null = new node(); null -> ch[0] = null -> ch[1] = null; root = null;
    n = read(), m = read();
    build(Segment, 1, n); val[0] = null;
    while (m --) {
        register char ch = getchar();
        for (; ch != 'C' && ch != 'Q'; ch = getchar()) ;
        register int l = read(), r = read();
        if (ch == 'C') {
            register int k = read(); 
            Lson[Ins + 1] = Now[l]; Rson[Ins + 1] = Now[r]; Now[k] = ++ Ins; pre[Ins] = k;
            node **o = Insert(root, 1, 1e9);
            if (*o != null) rebuild(*o);
            Update(Segment, 1, n, k, Ins);
        }
        else Query(l, r);
    }
    return 0;
}