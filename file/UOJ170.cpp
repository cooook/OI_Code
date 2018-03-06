# include <stdio.h> 
# include <iostream> 
const int inf = 0x3f3f3f3f; 
int n, m, Mx, Mn, Sec_Mn, Sec_Mx; 


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
        mx_add = __mx_add1 = mn_add = __mn_add1 = add = __add1 = __add2 = __mn_add2 = __mx_add2 = 0; 
    }
    int mx, __mx, mn, __mn, sec_mn, sec_mx, l, r;
    int mx_add, __mx_add1, __mx_add2, mn_add, __mn_add1, __mn_add2, add, __add1, __add2; // 带下划线的都是历史版本, 后面加1的是最小, 加2的是最大.  
    inline void Now() {
        Mn = mn; Mx = mx; Sec_Mn = sec_mn; Sec_Mx = sec_mx; 
    }
    inline void Add_All(int A) {
        if (sec_mn != inf) sec_mn += A;
        if (sec_mx != -inf) sec_mx += A;
        gmin(__mx_add1, mx_add + A);
        gmax(__mx_add2, mx_add + A);
        gmin(__mn_add1, mn_add + A);
        gmax(__mn_add2, mn_add + A);
        gmin(__add1, add + A);
        gmax(__add2, add + A);
        gmin(__mn, mn + A);
        gmax(__mx, mx + A);
        mx += A; mn += A; mx_add += A; mn_add += A; add += A;
    }
    inline void Add(int A, int Mn_A, int Mx_A) {
        if (Mn != Sec_Mx && sec_mx != -inf) sec_mx += A;
        if (Mx != Sec_Mn && sec_mn != inf) sec_mn += A; 
        gmin(__add1, add + Mn_A);
        gmax(__add2, add + Mx_A);
        add += A; 
    }
    inline void Add_Mx(int A, int Mn_A, int Mx_A) {
        if (Sec_Mn == Mx) sec_mn += A;
        gmin(__mx_add1, mx_add + Mn_A);
        gmax(__mx_add2, mx_add + Mx_A);
        gmax(__mx, mx + Mx_A);
        mx += A; mx_add += A; 
    }
    inline void Add_Mn(int A, int Mn_A, int Mx_A) {
        if (Sec_Mx == Mn) sec_mx += A;
        gmin(__mn_add1, mn_add + Mn_A);
        gmax(__mn_add2, mn_add + Mx_A);
        gmin(__mn, mn + Mn_A);
        mn += A; mn_add += A;
    }
    inline void Push_down() {
        if (l == r) return; 
        ls -> Now();
        int Min = std::min(ls -> mn, rs -> mn), Max = std::max(ls -> mx, rs -> mx);

        if (ls -> mn == Min) ls -> Add_Mn(mn_add, __mn_add1, __mn_add2);
        else if (ls -> mn == Max) ls -> Add_Mn(mx_add, __mx_add1, __mx_add2);
        else ls -> Add_Mn(add, __add1, __add2);

        if (ls -> mx == Max) ls -> Add_Mx(mx_add, __mx_add1, __mx_add2);
        else if (ls -> mx == Min) ls -> Add_Mx(mn_add, __mn_add1, __mn_add2);
        else ls -> Add_Mx(add, __add1, __add2);

        ls -> Add(add, __add1, __add2);

        rs -> Now();
        
        if (rs -> mn == Min) rs -> Add_Mn(mn_add, __mn_add1, __mn_add2);
        else if (rs -> mn == Max) rs -> Add_Mn(mx_add, __mx_add1, __mx_add2);
        else rs -> Add_Mn(add, __add1, __add2);

        if (rs -> mx == Max) rs -> Add_Mx(mx_add, __mx_add1, __mx_add2);
        else if (rs -> mx == Min) rs -> Add_Mx(mn_add, __mn_add1, __mn_add2);
        else rs -> Add_Mx(add, __add1, __add2);

        rs -> Add(add, __add1, __add2);

        add = __add1 = __add2 = 0;
        mx_add = __mx_add1 = __mx_add2 = 0;
        mn_add = __mn_add1 = __mn_add2 = 0; 
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
    if (l <= o -> l && o -> r <= r) return o -> Add_All(val), void(); 
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
            register int delta = val - o -> mn;
            o -> Now(); 
            if (o -> mn == o -> mx) o -> Add_Mx(delta, 0, delta);
            o -> Add_Mn(delta, 0, delta);  
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
            register int delta = val - o -> mx; 
            o -> Now();
            if (o -> mn == o -> mx) o -> Add_Mn(delta, delta, 0);
            o -> Add_Mx(delta, delta, 0);
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

int main() {
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
    }
    return 0; 
}