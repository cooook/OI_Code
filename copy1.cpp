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

inline void gmax(int &x, const int &y) {
    if (x < y) x = y;
}

struct node {
    node *ls, *rs; 
    node(int l = 0, int r = 0) : l(l), r(r) {
        mx = __mx = sec_mx = -inf;
        mn = __mn = sec_mn = inf;   
        mx_add = __mx_add = mn_add = __mn_add = add = __add1 = __add2 = 0; 
    }
    int mx, __mx, mn, __mn, sec_mn, sec_mx, l, r;
    int mx_add, __mx_add, mn_add, __mn_add, add, __add1, __add2; // __add1 --> mn, __add2 --> mx;  
    inline void Add(int x, int mn_y, int mx_y) { 
        gmin(__add1, add + mn_y); gmax(__add2, add + mx_y);
        if (sec_mn != inf) sec_mn += x;
        if (sec_mx != -inf) sec_mx += x; 
        add += x;
    }
    inline void Add_Mx(int x, int y) {
        if (sec_mn == mx) sec_mn += x;
        gmax(__mx, mx + y); gmax(__mx_add, mx_add + y);
        mx += x; mx_add += x; 
    }
    inline void Add_Mn(int x, int y) {
        if (sec_mx == mn) sec_mx += x; 
        gmin(__mn, mn + y); gmin(__mn_add, mn_add + y);
        mn += x; mn_add += x;
    }
    inline void Mx_Push_down(int lv, int rv, int lV, int rV) {
        if (!mx_add && !__mx_add) return ;
        if (lv >= rv) {
            ls -> Add_Mx(mx_add, __mx_add);
            if (lv == lV) ls -> mn = ls -> mx, gmin(ls -> __mn, ls -> mn);
        }
        if (lv <= rv) {
            rs -> Add_Mx(mx_add, __mx_add);
            if (rv == rV) rs -> mn = rs -> mx, gmin(rs -> __mn, rs -> mn);
        }
        mx_add = __mx_add = 0;
    }
    inline void Mn_Push_down(int lv, int rv, int lV, int rV) {
        if (!mn_add && !__mn_add) return ;
        // printf("%d %d\n", l, r);
        if (lv <= rv) {
            ls -> Add_Mn(mn_add, __mn_add);
            if (lv == lV) ls -> mx = ls -> mn, gmax(ls -> __mx, ls -> mn);
        }
        if (lv >= rv) {
            rs -> Add_Mn(mn_add, __mn_add);
            if (rv == rV) rs -> mx = rs -> mn, gmax(rs -> __mx, rs -> mn);
        }
        mn_add = __mn_add = 0;
    }
    inline void Push_down() {
        if (l == r) return; 
        register int lmn = ls -> mn, rmn = rs -> mn, lmx = ls -> mx, rmx = rs -> mx; 
        printf("l=%d r=%d lmn = %d rmn = %d lmx = %d rmx = %d mn_add = %d mx_add = %d\n", l, r, lmn, rmn, lmx, rmx, mn_add, mx_add);
        Mn_Push_down(lmn, rmn, lmx, rmx), Mx_Push_down(lmx, rmx, lmn, rmn);
        if (lmn < rmn) rs -> Add_Mn(add, __add1);
        if (lmn > rmn) ls -> Add_Mn(add, __add1);
        if (lmx > rmx) rs -> Add_Mx(add, __add2);
        if (lmx < rmx) ls -> Add_Mx(add, __add2);
        if (ls -> sec_mn < lmx) 
            ls -> Add(add, __add1, __add2);
        if (rs -> sec_mn < rmx) 
            rs -> Add(add, __add1, __add2); 
        printf("mn = %d mx = %d\n", mn, mx);
        add = __add1 = __add2 = 0; 
    }
    inline void Maintain() {
        if (l == r) return; 
        mx = std::max(ls -> mx, rs -> mx);
        mn = std::min(ls -> mn, rs -> mn);
        sec_mx = std::max(ls -> sec_mx, rs -> sec_mx);
        sec_mn = std::min(ls -> sec_mn, rs -> sec_mn);
        __mx = std::max(ls -> __mx, rs -> __mx);
        __mn = std::min(ls -> __mn, rs -> __mn);
        if (ls -> mx != mx) gmax(sec_mx, ls -> mx);
        if (rs -> mx != mx) gmax(sec_mx, rs -> mx);
        if (ls -> mn != mn) gmin(sec_mn, ls -> mn);
        if (rs -> mn != mn) gmin(sec_mn, rs -> mn);
    }
}*root;

inline void Update(node *o, int l, int r, int val) {
    if (l <= o -> l && o -> r <= r) {
        // printf("%d %d %d %d\n", o -> l, o -> r, l, r);
        // printf("%d %d\n", o -> mn, o -> mx);
        if (o -> mn == o -> mx) o -> Add_Mx(val, val), o -> mn = o -> mx, gmin(o -> __mn, o -> mn);
        else if (o -> sec_mn == o -> mx) o -> Add_Mx(val, val), o -> Add_Mn(val, val), o -> sec_mn = o -> mx, o -> sec_mx = o -> mn; 
        else o -> Add_Mx(val, val), o -> Add_Mn(val, val), o -> Add(val, val, val);
        // o -> Add_Mx(val, val), o -> Add_Mn(val, val), o -> Add(val, val, val);
        // printf("%d %d\n", o -> mn, o -> mx);
        // printf("%d %d\n", o -> mn_add, o -> __mn_add);
        return; 
    }
    o -> Push_down();
    register int mid = o -> l + o -> r >> 1;
    if (l <= mid) Update(o -> ls, l, r, val);
    if (mid < r) Update(o -> rs, l, r, val);
    o -> Maintain();
}

inline void Cbmax(node *o, int l, int r, int val) {
    if (val <= o -> mn) return ;
    if (l <= o -> l && o -> r <= r) {
        if (val < o -> sec_mn) {
            printf("%d %d %d %d mn=%d mx=%d sec_mn=%d sec_mx=%d\n", o -> l, o -> r, l, r, o -> mn, o -> mx, o -> sec_mn, o -> sec_mx);
            register int delta = val - o -> mn;
            if (o -> mn == o -> mx) o -> mx = val, gmax(o -> __mx, val);
            else if (o -> mn == o -> sec_mx) o -> sec_mx = val; 
            o -> Add_Mn(delta, delta);
            printf("%d %d %d %d mn=%d mx=%d sec_mn=%d sec_mx=%d\n", o -> l, o -> r, l, r, o -> mn, o -> mx, o -> sec_mn, o -> sec_mx);
            // o -> Push_down(); 
            // o -> Maintain(); 
        }
        else {
            o -> Push_down();
            Cbmax(o -> ls, l, r, val);
            Cbmax(o -> rs, l, r, val);
            o -> Maintain(); 
        }
    }
    else {
        o -> Push_down();
        register int mid = o -> l + o -> r >> 1;
        if (l <= mid) Cbmax(o -> ls, l, r, val);
        if (mid < r) Cbmax(o -> rs, l, r, val);
        o -> Maintain(); 
    }   
}

inline void Cbmin(node *o, int l, int r, int val) {
    if (val >= o -> mx) return ;
    if (l <= o -> l && o -> r <= r) {
        if (val > o -> sec_mx) {
            // printf("%d %d %d %d\n", o -> l, o -> r, l, r);
            // printf("%d %d\n", o -> mx, o -> mn);
            register int delta = val - o -> mx; 
            if (o -> mn == o -> mx) o -> mn = val, gmax(o -> __mn, val);
            else if (o -> sec_mn == o -> mx) o -> sec_mn = val;
            o -> Add_Mx(delta, delta);
            // printf("%d\n", delta);
            // o -> Maintain(); 
            // printf("%d %d\n", o -> mx, o -> __mx_add);
        }
        else {
            o -> Push_down();
            Cbmin(o -> ls, l, r, val);
            Cbmin(o -> rs, l, r, val);
            o -> Maintain(); 
        }
    }
    else {
        o -> Push_down();
        register int mid = o -> l + o -> r >> 1;
        if (l <= mid) Cbmin(o -> ls, l, r, val);
        if (mid < r) Cbmin(o -> rs, l, r, val);
        o -> Maintain(); 
    }
}

inline int Query(node *o, int l, int r, int opt) {
    if (l == o -> l && o -> r == r) return opt == 0 ? o -> mn : (opt == 1 ? o -> __mn : o -> __mx);
    o -> Push_down(); 
    register int mid = o -> l + o -> r >> 1;
    if (r <= mid) return Query(o -> ls, l, r, opt);
    else if (l > mid) return Query(o -> rs, l, r, opt);
    else
        return opt != 2 ? 
        std::min(Query(o -> ls, l, mid, opt), Query(o -> rs, mid + 1, r, opt)): 
        std::max(Query(o -> ls, l, mid, opt), Query(o -> rs, mid + 1, r, opt)); 
}

inline void build(node *&o, int l, int r) {
    o = new node(l, r);
    if (l == r) return o -> mx = o -> mn = o -> __mn = o -> __mx = read(), void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid), build(o -> rs, mid + 1, r);
    o -> Maintain();  
}

inline void dfs(node *o) {
    if (o -> l == o -> r) return printf("val[%d]=%d\n", o -> l, o -> mx), void();
    o -> Push_down();
    dfs(o -> ls),
    dfs(o -> rs); 
}

int main() {
    freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read(), m = read();
    build(root, 1, n);
    while (m --) {
        register int opt = read(), l = read(), r = read();
        switch (opt) {
            case 1:Update(root, l, r, read()); break; 
            case 2:Cbmax(root, l, r, read()); break; 
            case 3:printf("%d\n", Query(root, l, r, 0)); break; 
            case 4:printf("%d\n", Query(root, l, r, 1)); break; 
            case 5:Cbmin(root, l, r, read()); break; 
            case 6:printf("%d\n", Query(root, l, r, 2)); break; 
        }
        // dfs(root);
    }
    while (true); 
    return 0; 
}

/*
    opt : 
    1 :: a + c;
    2 :: a = max(a, c);
    3 :: min(a);
    4 :: min(his);
    5 :: a = min(a, c);
    6 :: max(his);
*/