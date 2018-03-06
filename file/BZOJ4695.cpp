# include <bits/stdc++.h> 
# define int long long 
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

inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
} 

inline void gmax(int &a, const int &b) {
    if (a < b) a = b;
}

struct node {
    node *ls, *rs; 
    int mx, sec_mx, nmx, mx_add;
    int mn, sec_mn, nmn, mn_add;
    int add, Sum, l, r; 
    node(int l = 0, int r = 0):l(l), r(r) {
        ls = rs = NULL;
        mx = sec_mx = -inf; 
        mn = sec_mn =  inf; 
        mx_add = mn_add = add = Sum = 0; 
        nmx = nmn = 0;
    }
    inline void Maintain() {
        nmx = nmn = 0;
        Sum = ls -> Sum + rs -> Sum; 
        mx = std::max(ls -> mx, rs -> mx);
        mn = std::min(ls -> mn, rs -> mn);
        sec_mx = std::max(ls -> sec_mx, rs -> sec_mx);
        sec_mn = std::min(ls -> sec_mn, rs -> sec_mn);
        if (ls -> mx == mx) nmx += ls -> nmx;
        else gmax(sec_mx, ls -> mx);
        if (rs -> mx == mx) nmx += rs -> nmx;
        else gmax(sec_mx, rs -> mx);
        if (ls -> mn == mn) nmn += ls -> nmn;
        else gmin(sec_mn, ls -> mn);
        if (rs -> mn == mn) nmn += rs -> nmn;
        else gmin(sec_mn, rs -> mn);
    }
    inline void Add(int val) {
        Sum += (r - l + 1) * val; 
        mx += val; mn += val; add += val; 
        if (sec_mx != -inf) sec_mx += val;
        if (sec_mn != inf) sec_mn += val;
    }
    inline void Push_down() ; 
}*root;

inline void build(node *&o, int l, int r) {
    o = new node(l, r);
    if (l == r) return o -> mx = o -> mn = o -> Sum = read(), o -> nmx = o -> nmn = 1, void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid); build(o -> rs, mid + 1, r);
    o -> Maintain(); 
}

inline void Update(node *o, int l, int r, int x, int y, int val) {
    if (x <= l && r <= y) return o -> Add(val), void();
    o -> Push_down();
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, y, val);
    if (mid < y) Update(o -> rs, mid + 1, r, x, y, val);
    o -> Maintain();
}

inline void Cbmin(node *o, int l, int r, int x, int y, int val) {
    if (val >= o -> mx) return ;
    register int mid = l + r >> 1; 
    if (x <= l && r <= y && val > o -> sec_mx) {
        o -> Sum += (val - o -> mx) * o -> nmx; 
        if (o -> mn == o -> mx) {
            o -> add += val - o -> mx;
            o -> mx = val;
            o -> mn = o -> mx;
        }
        else if (o -> sec_mn == o -> mx) {
            o -> mx_add += val - o -> mx;
            o -> mx = val;
            o -> sec_mn = o -> mx; 
        }
        else o -> mx_add += val - o -> mx, o -> mx = val; 
    }
    else {
        o -> Push_down();
        if (x <= mid) Cbmin(o -> ls, l, mid, x, y, val);
        if (mid < y) Cbmin(o -> rs, mid + 1, r, x, y, val);
        o -> Maintain(); 
    }
} 

inline void Cbmax(node *o, int l, int r, int x, int y, int val) {
    if (val <= o -> mn) return ;
    register int mid = l + r >> 1;
    if (x <= l && r <= y && val < o -> sec_mn) {
        o -> Sum += (val - o -> mn) * o -> nmn; 
        if (o -> mn == o -> mx) {
            o -> add += val - o -> mn;
            o -> mn = val;
            o -> mx = o -> mn;
        }
        else if (o -> sec_mx == o -> mn) {
            o -> mn_add += val - o -> mn;
            o -> mn = val;
            o -> sec_mx = o -> mn; 
        }
        else o -> mn_add += val - o -> mn, o -> mn = val; 
    }
    else {
        o -> Push_down();
        if (x <= mid) Cbmax(o -> ls, l, mid, x, y, val);
        if (mid < y) Cbmax(o -> rs, mid + 1, r, x, y, val);
        o -> Maintain(); 
    }
}

inline void node::Push_down() {
    if (!(add || mx_add || mn_add)) return;
    if (add) ls -> Add(add), rs -> Add(add);
    register int lst = mx - mx_add;
    if (ls -> mx == lst) Cbmin(ls, ls -> l, ls -> r, ls -> l, ls -> r, mx);
    if (rs -> mx == lst) Cbmin(rs, rs -> l, rs -> r, rs -> l, rs -> r, mx);
    lst = mn - mn_add;
    if (ls -> mn == lst) Cbmax(ls, ls -> l, ls -> r, ls -> l, ls -> r, mn);
    if (rs -> mn == lst) Cbmax(rs, rs -> l, rs -> r, rs -> l, rs -> r, mn); 
    add = mx_add = mn_add = 0;
}

inline int Qsum(node *o, int l, int r, int x, int y) {
    if (x == l && r == y) return o -> Sum;
    o -> Push_down();
    register int mid = l + r >> 1;
    if (y <= mid) return Qsum(o -> ls, l, mid, x, y);
    else if (x > mid) return Qsum(o -> rs, mid + 1, r, x, y);
    return Qsum(o -> ls, l, mid, x, mid) + Qsum(o -> rs, mid + 1, r, mid + 1, y);
}

inline int Query(node *o, int l, int r, int x, int y, int opt) {
    if (x == l && r == y) return opt ? o -> mn : o -> mx;
    o -> Push_down();
    register int mid = l + r >> 1;
    if (y <= mid) return Query(o -> ls, l, mid, x, y, opt);
    else if (x > mid) return Query(o -> rs, mid + 1, r, x, y, opt);
    else return opt ? 
    std::min(Query(o -> ls, l, mid, x, mid, opt), Query(o -> rs, mid + 1, r, mid + 1, y, opt)): 
    std::max(Query(o -> ls, l, mid, x, mid, opt), Query(o -> rs, mid + 1, r, mid + 1, y, opt)); 
}

signed main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read();
    build(root, 1, n);
    m = read(); 
    while (m --) {
        register int opt = read(), l = read(), r = read();
        switch (opt) {
            case 1:Update(root, 1, n, l, r, read()); break;
            case 2:Cbmax(root, 1, n, l, r, read()); break;
            case 3:Cbmin(root, 1, n, l, r, read()); break;
            case 4:printf("%lld\n", Qsum(root, 1, n, l, r)); break;
            case 5:printf("%lld\n", Query(root, 1, n, l, r, false)); break;
            case 6:printf("%lld\n", Query(root, 1, n, l, r, true)); break; 
        }
    }
    return 0; 
}