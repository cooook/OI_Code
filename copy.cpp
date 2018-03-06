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
    inline void Add(int x, int y_mn, int y_mx) { 
        gmin(__add1, add + y_mn); gmax(__add2, add + y_mx);
        gmin(__mn, mn + y_mn); gmax(__mx, mx + y_mx);
        mn += x; mx += x; sec_mx += x; sec_mn += x; 
        add += x;
    }
    inline void Add_Mx(int x, int y) {
        gmax(__mx, mx + y); gmax(__mx_add, mx_add + y);
        mx += x; mx_add += x; 
    }
    inline void Add_Mn(int x, int y) {
        gmin(__mn, mn + y); gmin(__mn_add, mn_add + y);
        mn += x; mn_add += x;
    }
    inline void Mx_Push_down(int lv, int rv, int lV, int rV) {
        if (!mx_add && !__mx_add) return ;
        if (lv >= rv) {
            if (lv == lV) ls -> Add(mx_add, __mx_add, __mx_add);
            else ls -> Add_Mx(mx_add, __mx_add);
        }
        if (lv <= rv) {
            if (rv == rV) rs -> Add(mx_add, __mx_add, __mx_add);
            else rs -> Add_Mx(mx_add, __mx_add);
        }
        mx_add = __mx_add = 0;
    }
    inline void Mn_Push_down(int lv, int rv, int lV, int rV) {
        if (!mn_add && !__mn_add) return ;
        // printf("%d %d\n", l, r);
        if (lv <= rv) {
            if (lv == lV) ls -> Add(mn_add, __mn_add, __mn_add);
            else ls -> Add_Mn(mn_add, __mn_add);
        }
        if (lv >= rv) {
            if (rv == rV) rs -> Add(mn_add, __mn_add, __mn_add);
            else rs -> Add_Mn(mn_add, __mn_add);
        }
        mn_add = __mn_add = 0;
    }
    inline void Push_down() {
        if (l == r) return; 
        register int lmn = ls -> mn, rmn = rs -> mn, lmx = ls -> mx, rmx = rs -> mx; 
        ls -> Add(add, __add1, __add2);
        rs -> Add(add, __add1, __add2); 
        Mn_Push_down(lmn, rmn, lmx, rmx), Mx_Push_down(lmx, rmx, lmn, rmn);
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
    // printf("%d %d %d %d\n", o -> l, o -> r, l, r);
    if (l <= o -> l && o -> r <= r) return o -> Add(val, val, val), void();
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
            // printf("%d %d %d %d %d %d\n", o -> l, o -> r, l, r, o -> sec_mx, o -> sec_mn);
            register int delta = val - o -> mn;
            if (o -> sec_mx == o -> mn) o -> sec_mx = val; 
            if (o -> mn == o -> mx) o -> Add(delta, delta, delta);
            else o -> Add_Mn(delta, delta);
            // printf("mx=%d mn=%d sec_mx = %d sec_mn = %d\n", o -> mx, o -> mn, o -> sec_mx, o -> sec_mn);
            // printf("%d ls -> mn = %d %d %d %d\n", o -> __mn, o -> ls -> __mn, o -> ls -> mn, o -> __add1, o -> mn_add);
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
            // printf("%d %d %d %d %d %d\n", o -> l, o -> r, l, r, o -> sec_mx, o -> sec_mn);
            register int delta = val - o -> mx;
            if (o -> sec_mn == o -> mx) o -> sec_mn = val;  
            if (o -> mn == o -> mx) o -> Add(delta, delta, delta);
            else o -> Add_Mx(delta, delta);
            // printf("mx=%d mn=%d sec_mx = %d sec_mn = %d\n", o -> mx, o -> mn, o -> sec_mx, o -> sec_mn);
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
    if (o -> l == o -> r) return; 
    o -> Push_down();
    dfs(o -> ls);
    dfs(o -> rs); 
}

int main() {
    freopen("Cooook.in","r",stdin);
    freopen("Cooook.out","w",stdout);
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
    // while (true); 
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