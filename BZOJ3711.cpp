# include <stdio.h> 
# include <cstring> 
# include <iostream> 
# define RG register 
const int mod = 1000000007; 
const int MAXN = 1000005;
const int inf = 0x3f3f3f3f; 
int n, c[MAXN], d[MAXN], first[MAXN], e = 1, tot; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; RG char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Data {
    int Mx, Sum; 
    Data(RG int Mx = 0, RG int Sum = 0):Mx(Mx), Sum(Sum) {  }  
    inline Data operator + (const RG Data &x) const {
        if (Mx != x.Mx) return Mx < x.Mx ? x : *this; 
        else return Data(Mx, (x.Sum + Sum) % mod);
    }
} f[MAXN];

struct node {
    node *ls, *rs;
    Data val;
    node() { ls = rs = NULL; val = Data(); }
    inline void Maintain() {
        val = ls -> val + rs -> val;
    }
} *root, mempool[MAXN << 2];

# define newnode() (mempool + (tot ++))

inline void build(RG node *&o, RG int l, RG int r) {
    o = newnode();
    o -> ls = o -> rs = NULL; o -> val = Data(); 
    if (l == r) return;
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
}

inline void Update(RG node *o, RG int l, RG int r, RG int x, RG Data val) {
    if (l == r) return o -> val = Data(val.Mx + (val.Mx != 0 ? 1 : 0), val.Sum), void(); 
    register int mid = l + r >> 1; 
    if (x <= mid) Update(o -> ls, l, mid, x, val);
    else Update(o -> rs, mid + 1, r, x, val); 
    o -> Maintain(); 
}

inline Data Query(RG node *o, RG int l, RG int r, RG int x, RG int y) {
    if (x > y) return Data(0, 0); 
    if (x == l && r == y) return o -> val;
    register int mid = l + r >> 1;
    if (y <= mid) return Query(o -> ls, l, mid, x, y);
    else if (x > mid) return Query(o -> rs, mid + 1, r, x, y);
    else return Query(o -> ls, l, mid, x, mid) + Query(o -> rs, mid + 1, r, mid + 1, y);
}

struct edge {
    int u, next; Data val; 
} a[MAXN];

inline void push(RG int u, RG int W, RG Data val) {
    a[e].u = u; a[e].val = val; a[e].next = first[W]; first[W] = e++; 
}

inline void gmin(RG int &x, const RG int &y) {
    if (x > y) x = y;
}

inline void gmax(RG int &x, const RG int &y) {
    if (x < y) x = y; 
}

inline void Solve(RG int l, RG int r) {
    if (l == r) return ;
    register int mid = l + r >> 1;  
    Solve(l, mid);
    register int mx = -inf, mn = inf, i; e = 1;
    tot = 0; 
    build(root, l, mid);
    // std::fill(&first[mid + 1], &first[r + 1], 0);
    memset(&first[mid + 1], 0, (r - mid) << 2);
    for (i = mid; i >= l; --i) {
        if (mn < mx) break; // 不能是小于等于.... 
        if (i + mx <= r && i + mn > mid) {
            if (i + mx <= r) push(i, std::max(i + mx, mid + 1), f[i]);
            if (i + mn < r) push(i, i + mn + 1, Data(0, 0)); // i + mn + 1 ... 
        }
        gmin(mn, d[i]), gmax(mx, c[i]); 
    }
    mx = -inf, mn = inf; 
    for (i = mid + 1; i <= r; ++i) {
        gmax(mx, c[i]); gmin(mn, d[i]);
        if (mn < mx) break; 
        for (int j = first[i]; j; j = a[j].next)
            Update(root, l, mid, a[j].u, a[j].val);
        if (i - mn <= mid && i - mx >= l)
            f[i] = f[i] + Query(root, l, mid, std::max(i - mn, l), std::min(mid, i - mx));
    }
    Solve(mid + 1, r);
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read();
    int mn = inf, mx = -inf; 
    for (int i = 1; i <= n; ++i) {
        c[i] = read(), d[i] = read();
        gmin(mn, d[i]), gmax(mx, c[i]); 
        if (mx <= i && i <= mn) f[i].Mx = 1, f[i].Sum = 1;
    }
    Solve(1, n);
    if (f[n].Mx != 0) printf("%d %d\n", f[n].Mx, f[n].Sum);
    else puts("NIE"); 
    // while (true); 
    return 0; 
}