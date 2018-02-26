# pragma GCC optimize("O3")
# include <vector>
# include <stdio.h> 
# include <iostream> 
# include <algorithm>
const int MAXN = 3e4 + 5; 
int first[MAXN], e = 1, son[MAXN], size[MAXN], deep[MAXN], top[MAXN], father[MAXN], cnt, id[MAXN], pre[MAXN], n, Q;
double K, Ans1, Ans2; 


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    double d[2];
    inline double& operator [] (const int &x) {return d[x];}
    inline double operator * (const Point &x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
    inline Point operator - (const Point &x) const {return (Point){d[0] - x.d[0], d[1] - x.d[1]};}
    inline bool operator < (const Point &x) const {return d[0] == x.d[0] ? d[1] > x.d[1] : d[0] < x.d[0];}
}pt1[MAXN], pt2[MAXN]; 

typedef std::vector<Point> Vec;
typedef std::vector<Point>::iterator Dit;

inline double Get(Point &x, Point &y) {
    return (y[1] - x[1]) / 1.0 / (y[0] - x[0]);
}

template <typename _t>
inline _t gmax(_t &x, const _t &y) {
    if (x < y) x = y;
    return x;
}

struct edge{
    int u, v, next; 
} a[MAXN << 1];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u, int fa) {
    father[u] = fa; size[u] = 1; deep[u] = deep[fa] + 1;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v; 
        if (v == fa) continue;
        dfs(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v]) son[u] = v;
    }
}

inline void __dfs(int u, int Num) {
    top[u] = Num; id[u] = ++ cnt; pre[cnt] = u;
    if (son[u]) __dfs(son[u], Num);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != father[u] && a[i].v != son[u])
            __dfs(a[i].v, a[i].v); 
}

struct node{
    node *ls, *rs;
    Vec G[2], Ans[2];
    inline void* operator new (size_t);
}*C, *mempool, *root;

inline void* node::operator new(size_t) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
    return C ++;
}

inline void Build_Hall(Vec &a, Vec &Ans) {
    std::sort(a.begin(), a.end());

    for (Dit it = a.begin(); it != a.end(); Ans.push_back(*it), ++it)
        while (Ans.size() > 1 && (Ans[Ans.size() - 1] - Ans[Ans.size() - 2]) * (*it - Ans[Ans.size() - 2]) >= 0) Ans.pop_back();
    
    a.clear();
}

inline void build(node *&o, int l, int r) {
    o = new node;
    for (int i = l; i <= r; ++i) 
        o -> G[0].push_back(pt1[pre[i]]), 
        o -> G[1].push_back(pt2[pre[i]]);
    Build_Hall(o -> G[0], o -> Ans[0]);
    Build_Hall(o -> G[1], o -> Ans[1]);
    if (l == r) return;
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
}

inline void Query_Hall(Vec &a, double &res) {
    int l = 0, r = a.size() - 2, mid, Ans = 0;
    Point P = (Point){1.0, K};
    while (l <= r) {
        mid = l + r >> 1;
        Point T = a[mid + 1] - a[mid];
        if (T * P <= 0) Ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    gmax(res, a[Ans][1] - a[Ans][0] * K);
    if (Ans + 1 <= a.size() - 1) gmax(res, a[Ans + 1][1] - a[Ans + 1][0] * K);
}

inline void Query(node *o, int l, int r, int x, int y) {
    if (x <= l && r <= y) return Query_Hall(o -> Ans[0], Ans1), Query_Hall(o -> Ans[1], Ans2), void();
    register int mid = l + r >> 1;
    if (x <= mid) Query(o -> ls, l, mid, x, y);
    if (mid < y) Query(o -> rs, mid + 1, r, x, y);
}

inline bool Judge(int u, int v) {
    Ans1 = -1e18; Ans2 = -1e18; 
    int f1 = top[u], f2 = top[v];
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) std::swap(f1, f2), std::swap(u, v);
        Query(root, 1, n, id[f1], id[u]);
        u = father[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) std::swap(u, v);
    Query(root, 1, n, id[u], id[v]);
    return Ans1 + Ans2 > 1e-7;
}

inline void Query(int u, int v) {
    double l = 0.0, r = 1e5; 
    while (l + 1e-5 < r) {
        K = (l + r) / 2;
        if (Judge(u, v)) l = K;
        else r = K;
    }
    printf("%.4f\n", (l + r) / 2);
}

int main() {
    n = read(); 
    for (int i = 1; i <= n; ++i) scanf("%lf", &pt1[i].d[0]);
    for (int i = 1; i <= n; ++i) scanf("%lf", &pt1[i].d[1]);
    for (int i = 1; i <= n; ++i) scanf("%lf", &pt2[i].d[0]);
    for (int i = 1; i <= n; ++i) scanf("%lf", &pt2[i].d[1]);
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        push(u, v), push(v, u);
    }
    dfs(1, 0); __dfs(1, 1);
    build(root, 1, n);
    Q = read();
    while (Q --) {
        register int u = read(), v = read();
        Query(u, v);
    }
    return 0;
}

