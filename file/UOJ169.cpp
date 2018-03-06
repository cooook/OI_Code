# include <stdio.h> 
# include <iostream> 
const int inf = 0x3f3f3f3f;
int n, m; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &x, const int &y) {
    if (x > y) x = y;
}

struct node {
    node *ls, *rs; 
    int mn, __mn, sec_mn, l, r, add, __add, sec_add, __sec_add; 
    node(int l = 0, int r = 0):l(l), r(r) {
        ls = rs = NULL;
        mn = __mn = sec_mn = inf;
        add = __add = sec_add = __sec_add = 0; 
    }
    inline void M_Change(int x, int y) { // x -> add, y -> __add
        gmin(__mn, y + mn), gmin(__add, y + add);
        mn += x; add += x; 
    }
    inline void Change(int x, int y) {
        gmin(__sec_add, sec_add + y);
        if (sec_mn != inf) sec_mn += x;
        sec_add += x;
    }
    inline void M_Push_down() {
        if (l == r) return add = __add = 0, void();
        if (!add && !__add) return ;
        register int L = ls -> mn, R = rs -> mn;
        if (L <= R) ls -> M_Change(add, __add);
        if (L >= R) rs -> M_Change(add, __add);
        add = __add = 0; 
    }
    inline void Push_down() {
        if (l == r) return ;
        register int L = ls -> mn, R = rs -> mn; 
        M_Push_down();
        if (L < R) rs -> M_Change(sec_add, __sec_add);
        if (L > R) ls -> M_Change(sec_add, __sec_add);
        ls -> Change(sec_add, __sec_add);
        rs -> Change(sec_add, __sec_add);
        sec_add = __sec_add = 0;
    }
    inline void Maintain() {
        mn = std::min(ls -> mn, rs -> mn);
        sec_mn = std::min(ls -> sec_mn, rs -> sec_mn);
        if (ls -> mn != mn) gmin(sec_mn, ls -> mn);
        if (rs -> mn != mn) gmin(sec_mn, rs -> mn);
        __mn = std::min(ls -> __mn, rs -> __mn);
    }
}*root;

inline void build(node *&o, int l, int r) {
    o = new node(l, r); 
    if (l == r) return o -> mn = o -> __mn = read(), void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
    o -> Maintain(); 
}

inline void Update(node *o, int x, int y, int val) {
    if (x <= o -> l && o -> r <= y)
        return o -> M_Change(val, val), o -> Change(val, val), void();
    register int mid = o -> l + o -> r >> 1;
    o -> Push_down();
    if (x <= mid) Update(o -> ls, x, y, val);
    if (mid < y) Update(o -> rs, x, y, val);
    o -> Maintain();
}

inline void Cbmax(node *o, int x, int y, int val) {
    if (val <= o -> mn) return ;
    if (x <= o -> l && o -> r <= y) {
        if (val < o -> sec_mn) o -> M_Change(val - o -> mn, val - o -> mn);
        else {
            o -> Push_down();
            Cbmax(o -> ls, x, y, val);
            Cbmax(o -> rs, x, y, val);
            o -> Maintain();
        }
    }
    else {
        o -> Push_down();
        register int mid = o -> l + o -> r >> 1;
        if (x <= mid) Cbmax(o -> ls, x, y, val);
        if (mid < y) Cbmax(o -> rs, x, y, val);
        o -> Maintain();
    }
}

inline int Query(node *o, int x, int y, int opt) {
    if (x == o -> l && o -> r == y) return opt ? o -> __mn : o -> mn;
    register int mid = o -> l + o -> r >> 1;
    o -> Push_down(); 
    if (y <= mid) return Query(o -> ls, x, y, opt);
    else if (x > mid) return Query(o -> rs, x, y, opt);
    else return std::min(Query(o -> ls, x, mid, opt), Query(o -> rs, mid + 1, y, opt));
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read(), m = read();
    build(root, 1, n);
    while (m --) {
        register int opt = read(), l = read(), r = read(), c;
        if (opt <= 2) {
            c = read();
            if (opt == 1) Update(root, l, r, c);
            else Cbmax(root, l, r, c);
        }
        else printf("%d\n", Query(root, l, r, opt == 4));
    }
    // while (true); 
    return 0; 
}