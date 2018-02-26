# include <bits/stdc++.h> 
# define mk std::make_pair
# define fi first
# define se second
# define pb push_back

const int MAXN = 1e6 + 5;
const double eps = 1e-8;

int n, m, Q;


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) { }
    inline double operator * (const Point &a) const {return x * a.y - y * a.x;}
    inline Point operator - (const Point &a) const {return Point(x - a.x, y - a.y);}
};

inline int sgn(double x) {
    return (x > -eps) - (x < eps);
}

namespace Graph {
    Point pt[MAXN];
    
    struct edge {
        int u, v, w; double k;
        edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {
            Point tmp = pt[v] - pt[u];
            k = atan2(tmp.y, tmp.x);
        }
    } a[MAXN << 1];

    typedef std::pair<double, int> pii;

    int rk[MAXN], belong[MAXN], tot, Inf_Area;
    bool vis[MAXN];

    std::vector<int> G[MAXN];

    inline void ReadIn() {
        for (int i = 1; i <= n; ++i) 
            scanf("%lf%lf", &pt[i].x, &pt[i].y);

        for (int i = 1; i <= m; ++i) {
            register int u = read(), v = read(), w = read();
            a[i << 1] = edge(u, v, w); 
            a[i << 1 | 1] = edge(v, u, w);
        }
    }

    inline void dfs(int u, int id) {
        if (vis[id]) return ;
        ++ tot;  double Ans = 0.0; 
        while (!vis[id]) {
            vis[id] = true; belong[id] = tot;
            Ans += pt[u] * pt[a[id].v];
            u = a[id].v;
            register int Rank = rk[id ^ 1];
            if (!Rank) id = G[u].back();
            else id = G[u][Rank - 1];
        }
        if (Ans < 0) Inf_Area = tot;
    }

    inline void Work() {
        ReadIn();
        pii *tmp = new pii[2 * m + 5];
        for (int i = 2; i <= (m << 1 | 1); ++i) tmp[i] = mk(a[i].k, i);
        std::sort(&tmp[2], &tmp[2 * m + 2]);
        for (int i = 2; i <= (m << 1 | 1); ++i) {
            int id = tmp[i].se;
            rk[id] = G[a[id].u].size();
            G[a[id].u].pb(id);
        }

        delete[] tmp;

# ifndef ONLINE_JUDGE
        for (int i = 1; i <= n; ++i) for (auto j:G[i]) dfs(i, j);
# else 
        for (int i = 1; i <= n; ++i) for (int j = 0; j < G[i].size(); ++j) dfs(i, G[i][j]);
# endif 
    }
}

namespace Scan_The_Lines {
    struct Querys {
        Point pt; int id; 
        Querys() {}
        Querys(Point pt, int id) : pt(pt), id(id) { }
        inline bool operator < (const Querys &a) const { return sgn(pt.x - a.pt.x) == 0 ? id < a.id : pt.x < a.pt.x; }
    }q[MAXN], key[MAXN];

    double Now; int cnt, Ans[MAXN];

    struct Information {
        double k; Point pt; int id;
        Information(Point a, Point b, int id) : pt(a), id(id) {
            k = (b.y - a.y) / (b.x - a.x);
        }
        inline bool operator < (const Information &a) const {
            double y0 = pt.y + k * (Now - pt.x), y1 = a.pt.y + a.k * (Now - a.pt.x);
            if (sgn(y0 - y1) == 0) return k < a.k;
            return sgn(y0 - y1) < 0; 
        }
    };

    std::set<Information> S;
    typedef std::set<Information>::iterator Iter; 
    Iter it[MAXN];

    inline void ReadIn() {
        Q = read();
        for (int i = 1; i <= Q << 1; ++i) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            q[i] = Querys(Point(x, y), i); 
        }
    }

    inline void Work() {
        ReadIn();
        using namespace Graph; 
        for (int i = 1; i <= m; ++i) {
            register int u = i << 1;
            if (pt[a[u].u].x > pt[a[u].v].x) u |= 1;
            if (sgn(pt[a[u].u].x - pt[a[u].v].x) != 0) {
                key[++cnt] = Querys(pt[a[u].u], u);
                key[++cnt] = Querys(pt[a[u].v], -u);
            }
        }
        std::sort(&key[1], &key[cnt]);
        std::sort(&q[1], &q[Q << 1 | 1]);
        for (int i = 1, j = 1; i <= Q << 1; ++i) {
            for (; j <= cnt && key[j].pt.x <= q[i].pt.x; ++j) {
                Now = key[j].pt.x;  int id = key[j].id;
                if (id < 0) S.erase(it[-id]);
                else it[id] = S.insert(Information(pt[a[id].u], pt[a[id].v], id)).fi;
            }
            Now = q[i].pt.x;
            Point b = q[i].pt; ++ b.x;
            Iter t = S.lower_bound(Information(q[i].pt, b, 0));
            if (t == S.end()) Ans[q[i].id] = Inf_Area;
            else Ans[q[i].id] = belong[t -> id ^ 1];
        }
    }
}

namespace MST{
    int f[MAXN][20], d[MAXN][20], fa[MAXN], first[MAXN], e, deep[MAXN];
    bool vis[MAXN]; 
    struct edge{
        int u, v, w, next; 
        inline bool operator < (const edge &a) const {return w < a.w;}
    } a[MAXN << 1], ed[MAXN];

    inline void push(int u, int v, int w) {
        a[e].u = u; a[e].v = v; a[e].w = w; 
        a[e].next = first[u]; first[u] = e++;
    }

    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    inline void dfs(int u) {
        vis[u] = true;
        for (int i = 1; i <= 18; ++i) f[u][i] = f[f[u][i-1]][i-1], d[u][i] = std::max(d[u][i-1], d[f[u][i-1]][i-1]);  
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v;
            if (v == f[u][0]) continue;
            f[v][0] = u; d[v][0] = a[i].w; deep[v] = deep[u] + 1;
            dfs(v);
        }
    }

    inline int Query(int u, int v) {
        if (u == Graph::Inf_Area || v == Graph::Inf_Area) return -1;
        if (find(u) != find(v)) return -1;
        if (deep[u] < deep[v]) std::swap(u, v);
        int Ans = 0, t = deep[u] - deep[v];
        for (int i = 18; ~i; --i) if (t >> i & 1) Ans = std::max(Ans, d[u][i]), u = f[u][i];
        if (u == v) return Ans;
        for (int i = 18; ~i; --i)
            if (f[u][i] != f[v][i])
                Ans = std::max(Ans, d[u][i]), Ans = std::max(Ans, d[v][i]), u = f[u][i], v = f[v][i];
        Ans = std::max(Ans, d[u][0]), Ans = std::max(Ans, d[v][0]);
        return Ans;
    }

    inline void Work() {
        e = 1;
        for (int i = 1; i <= Graph::tot; ++i) fa[i] = i;
        for (int i = 1; i <= m; ++i) {
            register int u = i << 1;
            ed[i].u = Graph::belong[u];
            ed[i].v = Graph::belong[u | 1];
            ed[i].w = Graph::a[u].w;
        }
        std::sort(&ed[1], &ed[m + 1]);
        for (int i = 1; i <= m; ++i) {
            register int u = ed[i].u, v = ed[i].v, w = ed[i].w;
            if (u == Graph::Inf_Area || v == Graph::Inf_Area) continue;
            if (find(u) == find(v)) continue;
            push(u, v, w), push(v, u, w);
            fa[find(u)] = find(v);
        } 

        for (int i = 1; i <= Graph::tot; ++i) if (!vis[i]) dfs(i);

        using Scan_The_Lines::Ans;
        for (int i = 1; i <= Q; ++i) printf("%d\n", Query(Ans[2 * i - 1], Ans[2 * i]));
    }
}

int main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    n = read(), m = read(); 
    Graph::Work();
    Scan_The_Lines::Work();
    MST::Work();
    // while (true);
    return 0;
}