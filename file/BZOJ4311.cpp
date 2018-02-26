# include <vector> 
# include <stdio.h> 
# include <iostream>
# include <algorithm>  
# define int long long 
const int MAXN = 200005;
int n, cnt, Query_tot;
int Ans[MAXN]; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int gmax(int &x, const int &y) {
    if (x < y) x = y;
    return x;
}

struct Point {
    int d[2];
    inline int& operator [] (const int &x) {return d[x];}
    inline int operator ^ (const Point &x) const {return d[0] * x.d[0] + d[1] * x.d[1];}
    inline int operator * (const Point &x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
    inline Point operator - (const Point &x) const {return (Point){d[0] - x.d[0], d[1] - x.d[1]};}
    inline bool operator < (const Point &x) const {return d[0] == x.d[0] ? d[1] > x.d[1] : d[0] < x.d[0];}  
};

typedef std::vector<Point> Vec;

struct Add{Point x;int L, R;}A[MAXN];
struct Query{Point x; int t;}Q[MAXN];
struct node{
    node *ls, *rs;
    node() {ls = rs = NULL;}
    Vec G, Ans; 
}*root;

inline void Build(Vec &a, Vec &Ans) {
    if (a.empty()) return;
    std::sort(a.begin(), a.end());
    for (std::vector<Point>::iterator it = a.begin(); it != a.end(); ++it) {
        while (Ans.size() > 1 && (Ans[Ans.size() - 1] - Ans[Ans.size() - 2]) * (*it - Ans[Ans.size() - 2]) > 0) 
            Ans.pop_back();
        Ans.push_back(*it);
    }
    a.clear();
}

inline void build(node *&o, int l, int r) {
    o = new node;
    if (l == r) return ;
    register int mid = l + r >> 1;
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
}

inline void Update(node *o, int l, int r, int x, int y, Point val) {
    if (x <= l && r <= y) return o -> G.push_back(val), void();
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, y, val);
    if (mid < y) Update(o -> rs, mid + 1, r, x, y, val);
}

inline void dfs(node *o) {
    if (!o) return;
    Build(o -> G, o -> Ans);
    dfs(o -> ls);
    dfs(o -> rs);
}

inline void Query_Hall(Vec &a, Point x, int &Ans) {
    if (a.empty()) return;
    int l = 0, r = a.size() - 1, mid1, mid2;
    while (l + 3 <= r) {
        mid1 = (l + l + r) / 3;
        mid2 = (l + r + r) / 3;
        if ((a[mid1] ^ x) >= (a[mid2] ^ x)) r = mid2;
        else l = mid1; 
    }
    for (int i = l; i <= r; ++i) gmax(Ans, a[i] ^ x);
}

inline void Query(node *o, int l, int r, int ql, int qr) {
    if (!o || ql > qr) return;
    int k = qr + 1, mid = l + r >> 1; 
    for (int i = ql; i <= qr; ++i) {
        Query_Hall(o -> Ans, Q[i].x, Ans[i]);
        if (Q[i].t > mid && k == qr + 1) k = i;
    }
    Query(o -> ls, l, mid, ql, k - 1);
    Query(o -> rs, mid + 1, r, k, qr);
}

signed main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        int op = read();
        if (op == 1) A[++cnt].x[0] = read(), A[cnt].x[1] = read(), A[cnt].L = i;
        else if (op == 2) A[read()].R = i;
        else Q[++Query_tot].x[0] = read(), Q[Query_tot].x[1] = read(), Q[Query_tot].t = i;
    }
    build(root, 1, n);
    for (int i = 1; i <= cnt; ++i) Update(root, 1, n, A[i].L, !A[i].R ? n : A[i].R, A[i].x);
    dfs(root);
    Query(root, 1, n, 1, Query_tot);
    for (int i = 1; i <= Query_tot; ++i) printf("%lld\n", Ans[i]);
    // getchar(); getchar(); 
    return 0;
}