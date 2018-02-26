# include <bits/stdc++.h>
const int MAXN = 1e5 + 5;
const int inf = 1 << 16;
int n, m, limit, pass, Time;


char sb[1 << 15], *S = sb, *T = sb;
# define gc() (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
inline int read() {
    register int x = 0, f = 1; char ch = gc();
    for (; !isdigit(ch); ch = gc()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int Max(int a, int b) {
    return a > b ? a : b;
}

inline void gmax(int &a, int b) {
    if (a < b) a = b;
}

inline void gmin(int &a, int b) {
    if (a > b) a = b;
}

struct node {
    node *ch[2];
    int size;
    inline void* operator new (size_t, node *ls, node *rs, int s);
}*C, *mempool, *root[MAXN], *null;

inline void* node::operator new(size_t, node *ls, node *rs, int s) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
    C -> ch[0] = ls; C -> ch[1] = rs; C -> size = s;
    return C ++;
}

inline node* Insert(node *o, int val, int full) {
    if (!full) return new(o -> ch[0], o -> ch[1], o -> size + 1) node;
    if (val & full) return new(o -> ch[0], Insert(o -> ch[1], val, full >> 1), o -> size + 1) node;
    else return new(Insert(o -> ch[0], val, full >> 1), o -> ch[1], o -> size + 1) node;
}

inline int Query(node *o, node *old, int val, int full) {
    if (!full) return 0;
    register bool d = val & full;
    if (o -> ch[d ^ 1] -> size - old -> ch[d ^ 1] -> size) return Query(o -> ch[d ^ 1], old -> ch[d ^ 1], val, full >> 1) | full;
    else return Query(o -> ch[d], old -> ch[d], val, full >> 1);
}

struct TAT{
    node *root;
    int pos;
    TAT(node *t, int p = 0) {root = t; pos = p;}
    inline bool operator < (const TAT& a) const {return pos < a.pos;}
};

typedef std::vector<TAT> Vec;

struct Seg{
    Seg *ls, *rs;
    Vec G;
    Seg() {
        ls = rs = NULL;
        G.clear();
        G.push_back(TAT(Insert(null, 0, inf), 0));
    } 
}*rt;

inline void build(Seg *&o, int l, int r) {
    o = new Seg();
    if (l == r) return;
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
}

inline void Update(Seg *o, int l, int r, int x, int val) {
    o -> G.push_back(TAT(Insert(o -> G.back().root, val, inf), Time));
    if (l == r) return;
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, val);
    else Update(o -> rs, mid + 1, r, x, val);
}

inline int Query_On_Trie(Seg *o) {
    TAT tmp = TAT(null, Time - limit + 1);
    std::vector<TAT>::iterator it;
    it = std::lower_bound(o -> G.begin(), o -> G.end(), tmp);
    if (it != o -> G.begin()) -- it;
    return Query(o -> G.back().root, it -> root, pass, inf);
}

inline int Query(Seg *o, int l, int r, int x, int y) {
    if (x == l && r == y) return Query_On_Trie(o);
    register int mid = l + r >> 1;
    if (y <= mid) return Query(o -> ls, l, mid, x, y);
    else if (x > mid) return Query(o -> rs, mid + 1, r, x, y);
    else return Max(Query(o -> ls, l, mid, x, mid), Query(o -> rs, mid + 1, r, mid + 1, y));
}

inline int Get_Ans(int l, int r) {
    int Ans = 0;
    if (limit != 0) Ans = Query(rt, 1, n, l, r);
    gmax(Ans, Query(root[r], root[l - 1], pass, inf));
    return Ans;
}

int main() {
    freopen("Cooook.in","r",stdin);
    freopen("Cooook.out","w",stdout);
    null = new(null, null, 0) node;
    null -> ch[0] = null -> ch[1] = null;
    root[0] = Insert(null, 0, inf);

    n = read(), m = read();
    for (int i = 1; i <= n; ++i) root[i] = Insert(root[i - 1], read(), inf);
    bool flag = false;
    build(rt, 1, n);
    while (m --) {
        register int op = read();
        if (!op) {
            flag = true; ++ Time;
            register int x = read(), val = read();
            Update(rt, 1, n, x, val);
        }
        else {
            if (!flag) ++ Time;
            register int l = read(), r = read();
            pass = read(); limit = read();
            gmin(limit, Time);
            printf("%d\n", Get_Ans(l, r));
        }
    }
    return 0;
}
