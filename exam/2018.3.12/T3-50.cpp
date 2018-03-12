# pragma GCC optimize("O3")
# include <bits/stdc++.h>
# define RG register 
const int MAXN = 1e5 + 5;  
const int inf = 0x3f3f3f3f;
int n, Q, val[MAXN], now, Ans[MAXN * 10], id[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(RG int &x, const RG int &y) {
    if (x > y) x = y; 
}

inline void gmax(RG int &x, const RG int &y) {
    if (x < y) x = y;
}

struct Line {
    int l, r, id; 
    inline bool operator < (const Line &x) const {
        if (now == 0)
            return l == x.l ? r < x.r : l < x.l; 
        else return r == x.r ? l < x.l : r < x.r;
    }
} pt[MAXN * 10];

struct node {
    node *ls, *rs;
    int last, mx_l, mn_l, mx_r, mn_r, tag_Ans, tag_mx, tag_mn;
    bool Mark; 
    Line val;
    node() { ls = rs = NULL; Mark = false; last = -inf; }
    node(Line val):val(val) { 
        ls = rs = NULL; 
        Mark = 0; tag_mx = -1; tag_Ans = tag_mn = inf; 
        last = -inf; 
        mn_l = mx_l = val.l, mx_r = mn_r = val.r; 
    }
    inline void Set(RG int mn, RG int mx, RG int ans) {
        gmin(tag_Ans, ans); 
        if (tag_mx != -1) gmin(tag_Ans, mn - tag_mx); 
        if (last != -inf) gmin(Ans[val.id], mn - last);
        gmin(Ans[val.id], tag_Ans); 
        gmin(tag_mn, mn); tag_mx = mx; last = mx; 
        Mark = true; 
    } 
    inline void Push_down() {
        if (Mark) {
            if (ls) ls -> Set(tag_mn, tag_mx, tag_Ans);
            if (rs) rs -> Set(tag_mn, tag_mx, tag_Ans);
            tag_mx = -1, tag_mn = inf; tag_Ans = inf; Mark = false; 
        }
    }
    inline void Maintain() {
        mn_l = mx_l = val.l, mn_r = mx_r = val.r;
        if (ls) gmax(mx_l, ls -> mx_l), gmin(mn_r, ls -> mn_r), gmin(mn_l, ls -> mn_l), gmax(mx_r, ls -> mx_r);
        if (rs) gmax(mx_l, rs -> mx_l), gmin(mn_r, rs -> mn_r), gmin(mn_l, rs -> mn_l), gmax(mx_r, rs -> mx_r);
    }
    inline void* operator new (size_t); 
}*root, *C, *mempool;

inline void* node::operator new (size_t) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15); 
    return C ++; 
}

inline void build(node *&o, int l, int r) {
    if (l > r) return ;
    register int mid = l + r >> 1; now = rand() & 1;
    std::nth_element(&pt[l], &pt[mid], &pt[r + 1]);
    o = new node(pt[mid]);
    build(o -> ls, l, mid - 1); build(o -> rs, mid + 1, r);
    o -> Maintain();
}

inline void Query(node *o, int x, int val) {
    if (!o) return; 
    if (x < o -> mn_l || x > o -> mx_r) return ;
    o -> Push_down();
    if (x >= o -> mx_l && x <= o -> mn_r) return o -> Set(val, val, inf), void();
    if (x <= o -> val.r && x >= o -> val.l) {
        if (o -> last != -inf)
            gmin(Ans[o -> val.id], val - o -> last);
        o -> last = val;
    }
    Query(o -> ls, x, val), Query(o -> rs, x, val);
}

inline void dfs(node *o) {
    if (!o) return ;
    o -> Push_down();
    dfs(o -> ls);
    dfs(o -> rs); 
}

int main() {
    memset(Ans, 0x3f, sizeof Ans);
    n = read();
    for (int i = 1; i <= n; ++i) val[i] = read(), id[i] = i; 
    std::sort(&id[1], &id[n + 1], [&](const int &x, const int &y) -> bool { return val[x] < val[y]; });
    Q = read();
    for (int i = 1; i <= Q; ++i) pt[i].l = read(), pt[i].r = read(), pt[i].id = i;
    build(root, 1, Q);
    for (int i = 1; i <= n; ++i) Query(root, id[i], val[id[i]]);
    dfs(root);
    for (int i = 1; i <= Q; ++i) printf("%d\n", Ans[i]);
    return 0; 
}