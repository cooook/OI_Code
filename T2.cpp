# include <bits/stdc++.h> 
# define fi first
# define se second
# define mk std::make_pair
typedef std::pair<int, int> pii; 
const int inf = 0x3f3f3f3f; 
const int MAXN = 1e5 + 5; 
int n, Q, first[MAXN], e = 1; 
bool vis[MAXN];


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, next;
} a[MAXN << 2];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
} 

inline void add(int u, int v) {
    push(u, v), push(v, u); 
}

pii Split[MAXN << 2]; 
int dis[2][20][MAXN], belong[20][MAXN], id[MAXN], Size[20], cnt;

inline void gmax(register int &x, const register int &y) {
    if (x < y) x = y;
} 

inline void bfs(int x, int *dis) {
    std::queue<int> Q;
    Q.push(x); dis[x] = 0;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next)
            if (dis[a[i].v] != inf) 
                dis[a[i].v] = dis[u] + 1, Q.push(a[i].v);
    }
}

inline void build(int num, std::vector<int> Point, std::vector<pii> Line) {
    ++ cnt;  register int N = Point.size(); Size[cnt] = N; 
    if (N == 3) return; 
    for (int i = 0; i < N; ++i) id[Point[i]] = i, belong[num][Point[i]] = cnt; 
    std::vector<int> Tmp_Point;
    std::vector<pii> Tmp_Line; 
    int Mx = inf, ID = -1, tmp;
    for (register int i = 0; i < Line.size(); ++i) {
        tmp = id[Line[i].se] - id[Line[i].fi] + 1; 
        gmax(tmp, N - tmp + 2);
        if (Mx > tmp) Mx = tmp, ID = i;
    }

    Split[cnt] = Line[ID];

    for (int i = id[Line[ID].fi]; i <= id[Line[ID].se]; ++i)
        Tmp_Point.push_back(Point[i]), add(Point[i], i == id[Line[ID].se] ? Line[ID].fi : Point[i + 1]), vis[Point[i]] = true; 
    for (auto i:Line)
        if (i != Line[ID] && id[i.fi] >= id[Line[ID].fi] && id[i.se] <= id[Line[ID].se])
            Tmp_Line.push_back(i), add(i.fi, i.se);
    bfs(Line[ID].fi, dis[0][num]); bfs(Line[ID].se, dis[1][num]); 
    build(num + 1, Tmp_Point, Tmp_Line);

    Tmp_Point.clear(); Tmp_Line.clear();

    for (int i = id[Line[ID].se]; i != id[Line[ID].fi] + 1; (++i) %= N)
        Tmp_Point.push_back(Point[i]), add(Point[i], i == id[Line[ID].fi] ? Line[ID].se : Point[(i + 1) % N]);
    
    for (auto i:Line)
        if (!vis[i.fi] && !vis[i.se])
            Tmp_Line.push_back(i), add(i.fi, i.se);
    bfs(Line[ID].fi, dis[0][num]); bfs(Line[ID].se, dis[1][num]);
    build(num + 1, Tmp_Point, Tmp_Line);
    for (int i = 0; i < N; ++i) vis[Point[i]] = false; 
}

inline void Query(int num, int x, int y) {
    if (x == y) return puts("0"), void(); 
    if (belong[num][x] == belong[num][y] && Size[belong[num][x]] == 3) return puts("1"), void();
    else if (x == Split[belong[num][x]].fi) printf("%d\n", dis[0][num][y]);
    else if (x == Split[belong[num][x]].se) printf("%d\n", dis[1][num][y]);
    else if (y == Split[belong[num][y]].fi) printf("%d\n", dis[0][num][x]);
    else if (y == Split[belong[num][y]].se) printf("%d\n", dis[1][num][y]); 
    else if (belong[num][x] == belong[num][y]) Query(num + 1, x, y);
    else printf("%d\n", std::min(
        std::min(dis[0][num][x] + dis[0][num][y], dis[0][num][x] + dis[1][num][y] + 1),
        std::min(dis[1][num][x] + dis[0][num][y] + 1, dis[1][num][x] + dis[1][num][y])
    )); 
}

int main() {
    freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    std::vector<pii> G; 
    std::vector<int> S;
    memset(dis, 0x3f, sizeof dis); 
    n = read();
    for (int i = 1; i <= n - 3; ++i) {
        register int u = read(), v = read();
        if (u > v) std::swap(u, v);
        G.push_back(mk(u, v));
    }
    for (int i = 1; i <= n; ++i) S.push_back(i);
    build(1, S, G);
    Q = read();
    while (Q --) {
        register int u = read(), v = read();
        Query(1, u, v); 
    } 
    while (true); 
    return 0; 
}