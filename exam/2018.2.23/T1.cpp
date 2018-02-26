# pragma GCC optimize("O3")
# include <stdio.h> 
# include <iostream>
const int inf = 0x7fffffff;
const int MAXN = 1e5 + 5;
int n, val[MAXN], m;


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS ++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(int &a, const int &b) {
    if (a < b) a = b;
}

inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
}

struct node {
    node *ls, *rs;
    int mx, mn, cnt, cnt_add, val_add, val; 
    bool tag;
    node() { ls = rs = NULL; cnt = val_add = cnt_add = tag = 0;}
    inline void Add(int x) { mx += x; mn += x; val_add += x; }
    inline void Cnt_Add(int x) { cnt += x; cnt_add += x; }
    inline void Set(int x) { 
        tag = true; val = mn = mx = x; val_add = 0;
    }
    inline void Push_down() {
        if (tag) {
            if (ls) ls -> Set(val);
            if (rs) rs -> Set(val);
            tag = false; 
        }
        if (val_add) {
            if (ls) ls -> Add(val_add);
            if (rs) rs -> Add(val_add);
            val_add = 0;
        }
        if (cnt_add) {
            if (ls) ls -> Cnt_Add(cnt_add);
            if (rs) rs -> Cnt_Add(cnt_add);
            cnt_add = 0;
        }
    }
    inline void Maintain() {
        mx = -inf; mn = inf;
        if (ls) gmin(mn, ls -> mn), gmax(mx, ls -> mx);
        if (rs) gmin(mn, rs -> mn), gmax(mx, rs -> mx);
    }
}*root; 

inline void build(node *&o, int l, int r) {
    o = new node();
    if (l == r) return o -> mx = o -> mn = val[l], void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
    o -> Maintain();
}

inline void Update(node *o, int l, int r, int x, int y, int val) {
    if (!val) return ;
    if (x == l && r == y) return o -> Add(val), o -> Cnt_Add(1), void();
    register int mid = l + r >> 1;
    o -> Push_down();
    if (y <= mid) Update(o -> ls, l, mid, x, y, val);
    else if (x > mid) Update(o -> rs, mid + 1, r, x, y, val);
    else Update(o -> ls, l, mid, x, mid, val), Update(o -> rs, mid + 1, r, mid + 1, y, val);
    o -> Maintain();
}

inline void Gmax(node *o, int l, int r, int x, int y, int val) {
    if (o -> mn >= val) return;
    if (x == l && r == y && o -> mx < val) return o -> Set(val), o -> Cnt_Add(1), void();
    o -> Push_down();
    register int mid = l + r >> 1;
    if (y <= mid) Gmax(o -> ls, l, mid, x, y, val);
    else if (x > mid) Gmax(o -> rs, mid + 1, r, x, y, val);
    else Gmax(o -> ls, l, mid, x, mid, val), Gmax(o -> rs, mid + 1, r, mid + 1, y, val);
    o -> Maintain();
}

inline void Query(int x) {
    node *o = root;
    int l = 1, r = n, mid;
    while (l < r) {
        mid = l + r >> 1;
        o -> Push_down();
        if (x <= mid) o = o -> ls, r = mid;
        else o = o -> rs, l = mid + 1;
    }
    printf("%d %d\n", o -> mn, o -> cnt);
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i) val[i] = read();
    build(root, 1, n);
    m = read(); 
    int x, y, z;
    while (m --) {
        char ch = getc;
        while (ch != 'A' && ch != 'M' && ch != 'Q') ch = getc;
        if (ch == 'A') {
            x = read(), y = read(), z = read();
            Update(root, 1, n, x, y, z);
        }
        else if (ch == 'M') {
            x = read(), y = read(), z = read();
            Gmax(root, 1, n, x, y, z);
        }
        else Query(read());
    }
    return 0;
}