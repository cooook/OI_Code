# include <stdio.h> 
# include <iostream> 
# define int long long 
const int inf = 1e16; 
int n, m; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(int &x, const int &y) {
    if (x < y) x = y;
}

struct Mark {
    int a, b; // f(x) --> std::max(x + a, b); 
    Mark(int a = 0, int b = 0) : a(a), b(b) {  }
    inline Mark operator + (const Mark &x) const {
        return Mark((a == -inf || x.a == -inf) ? -inf : (a + x.a), std::max((b == -inf || x.a == -inf) ? -inf : (b + x.a), x.b));
    }

    inline int operator () (const int &x) const {
        return std::max(x + a, b);
    }

    inline friend void operator += (Mark &C, const Mark &b) { C = C + b; }

    inline bool Judge() {
        return a != 0 || b != -inf; 
    }
};

inline Mark Max(const Mark &a, const Mark &b) {
    return Mark(std::max(a.a, b.a), std::max(a.b, b.b));
}

struct node {
    node *ls, *rs; 
    Mark add, __add;  
    int mx, __mx; 
    node() {
        ls = rs = NULL;
        add = __add = Mark(0, -inf);
        mx = __mx = -inf; 
    }
    inline void Push_down() {
        if (__add.Judge()) {
            gmax(ls -> __mx, __add(ls -> mx));
            gmax(rs -> __mx, __add(rs -> mx));
            ls -> __add = Max(ls -> __add, ls -> add + __add);
            rs -> __add = Max(rs -> __add, rs -> add + __add);
            __add.a = 0, __add.b = -inf;
        }
        if (add.Judge()) {
            ls -> mx = add(ls -> mx);
            rs -> mx = add(rs -> mx);
            ls -> add += add; rs -> add += add;
            add.a = 0, add.b = -inf; 
        }
    }
}*root;

inline void build(node *&o, int l, int r) {
    o = new node(); 
    if (l == r) return o -> mx = o -> __mx = read(), void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid), build(o -> rs, mid + 1, r);
}

inline void Update(node *o, int l, int r, int x, int y, Mark val) {
    if (x <= l && r <= y) {
        // printf("l=%lld r=%lld x=%lld y=%lld\n", l, r, x, y);
        if (l == r) gmax(o -> __mx, val(o -> mx)), o -> mx = val(o -> mx);
        else o -> __add = Max(o -> __add, o -> add + val), o -> add += val;
        // printf("%d %d %d %d\n", o -> add.a, o -> add.b, o -> __add.a, o -> __add.b);
        return ;
    }
    o -> Push_down();
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, y, val);
    if (mid < y) Update(o -> rs, mid + 1, r, x, y, val);
}

inline void Query(node *o, int l, int r, int x, int op) {
    if (l == r) return printf("%lld\n", op ? o -> __mx : o -> mx), void();
    o -> Push_down();
    register int mid = l + r >> 1;
    if (x <= mid) Query(o -> ls, l, mid, x, op);
    else Query(o -> rs, mid + 1, r, x, op);
}

signed main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read(), m = read(); 
    build(root, 1, n);
    register int opt, l, r, x;
    while (m --) {
        opt = read(), l = read();
        if (opt == 1) r = read(), x = read(), Update(root, 1, n, l, r, Mark(x, -inf));
        else if (opt == 2) r = read(), x = read(), Update(root, 1, n, l, r, Mark(-x, 0));
        else if (opt == 3) r = read(), x = read(), Update(root, 1, n, l, r, Mark(-inf, x));
        else Query(root, 1, n, l, opt == 5);
    }
    return 0; 
}