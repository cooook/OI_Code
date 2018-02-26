# pragma GCC optimize("O2")
# include <vector>
# include <stdio.h> 
# include <iostream> 
# include <algorithm>
# define int long long 
# define pb push_back

const int inf = 0x3f3f3f3f3f3f3f3fll;

int Ans, Last, n;

char s[5];


inline int gmax(int &x, const int &y) {
    if (x < y) x = y;
    return x; 
}

inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int d[2];
    inline int& operator [] (const int &x) {return d[x];}
    inline int operator * (const Point &x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
    inline Point operator + (const Point &x) const {return (Point){d[0] + x.d[0], d[1] + x.d[1]};}
    inline Point operator - (const Point &x) const {return (Point){d[0] - x.d[0], d[1] - x.d[1]};}
    inline bool operator < (const Point &x) const {return d[0] == x.d[0] ? d[1] < x.d[1] : d[0] < x.d[0];}
}cur; 

inline int Calc(Point &x, Point &y) {
    return x[0] * y[0] + x[1] * y[1];
}

typedef std::vector<Point> Vec;

struct node{
    node *ls, *rs;
    Vec G, Up, Down; 
    inline void* operator new (size_t); 
}*root, *C, *mempool;

inline void* node::operator new (size_t) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
    return C ++; 
}

inline void Build(node *&o, int l, int r) {
    o = new node();
    if (l == r) return ;
    register int mid = l + r >> 1; 
    Build(o -> ls, l, mid);
    Build(o -> rs, mid + 1, r); 
}

inline void Graph_Build(Vec &G, Vec &Up, Vec &Down) {
    std::sort(G.begin(), G.end());
    int Size = (int)G.size();
    std::vector<Point>::iterator it1, it2;
    for (int i = 0; i < Size; ++i) 
        if ((int)(Up.size()) < 2) Up.pb(G[i]);
        else {
            while ((int)Up.size() >= 2) {
                it1 = Up.end(); -- it1;
                it2 = it1; -- it2;
                if ((G[i] - *it2) * (*it1 - *it2) < 0) Up.pop_back();
                else break; 
            }
            Up.pb(G[i]);
        }
    for (int i = 0; i < Size; ++i)
        if ((int)Down.size() < 2) Down.pb(G[i]);
        else {
            while ((int)Down.size() >= 2) {
                it1 = Down.end(); -- it1;
                it2 = it1; -- it2;
                if ((G[i] - *it2) * (*it1 - *it2) > 0) Down.pop_back();
                else break;
            }
            Down.pb(G[i]);
        }
    for (it1 = Up.begin(); it1 != Up.end(); ++it1) printf("Up %lld %lld\n", (*it1)[0], (*it1)[1]);
    for (it2 = Down.begin(); it2 != Down.end(); ++it2) printf("Down %lld %lld\n", (*it2)[0], (*it2)[1]);
    G.clear(); 
}

inline void Push(node *o, int l, int r, int x, Point val) {
    o -> G.pb(val);
    if (r == x) printf("Build%lld %lld\n", l, r), Graph_Build(o -> G, o -> Up, o -> Down);
    if (l == r) return ;
    register int mid = l + r >> 1;
    if (x <= mid) Push(o -> ls, l, mid, x, val);
    else Push(o -> rs, mid + 1, r, x, val);
}

inline void __(Vec &v) {
    int l = 0, r = v.size() - 1, mid1, mid2;
    // for (int i = 0; i < v.size(); ++i) printf("%d %d\n", v[i][0], v[i][1]);
    while (l + 3 <= r) {
        mid1 = (l + l + r) / 3;
        mid2 = (l + r + r) / 3;
        if (Calc(cur, v[mid1]) > Calc(cur, v[mid2])) r = mid2;
        else l = mid1;
    }
    for (int i = l; i <= r; i++) gmax(Ans, Calc(v[i], cur));
}

inline void Query(node *o, int l, int r, int x, int y) {
    if (x <= l && r <= y) return __(cur[1] > 0?o -> Up : o -> Down), void();
    register int mid = l + r >> 1;
    if (x <= mid) Query(o -> ls, l, mid, x, y);
    if (mid < y) Query(o -> rs, mid + 1, r, x, y); 
}

inline void Query(int l, int r) {
    Ans = -inf;
    // printf("%lld %lld %lld %lld\n", cur[0], cur[1], l, r);
    Query(root, 1, n, l, r);
    printf("%lld\n", Last = Ans);
} 

signed main() {
    freopen("r1.in","r",stdin);
    freopen("r.out","w",stdout);
    n = read(); 
    scanf("%s", s);
    bool flag = (s[0] != 'E');
    int cnt = 0;
    Build(root, 1, n);
    for (int i = 1; i <= n; ++i) {
        register char ch = getchar();
        register int l, r; 
        for (; ch != 'A' && ch != 'Q'; ch = getchar()) ;
        if (ch == 'A') l = read() ^ (flag * (Last & 0x7fffffff)), r = read() ^ (flag * (Last & 0x7fffffff)), Push(root, 1, n, ++ cnt, (Point){l, r});
        else {
            cur[0] = read() ^ (flag * (Last & 0x7fffffff));
            cur[1] = read() ^ (flag * (Last & 0x7fffffff));
            l = read() ^ (flag * (Last & 0x7fffffff));
            r = read() ^ (flag * (Last & 0x7fffffff)); 
            Query(l, r);
        }
    }
    // while (true); 
    return 0;
}