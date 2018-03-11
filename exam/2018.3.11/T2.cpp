# include <bits/stdc++.h> 
# define fi first
# define se second
# define mk std::make_pair
typedef std::pair<int, int> pii; 
const int inf = 0x3f3f3f3f; 
const int MAXN = 1e5 + 5; 
int n, Q, first[MAXN], e = 1, Ans[MAXN];


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

int dis[2][20][MAXN], id[20][MAXN], cnt;
bool vis[20][MAXN];

inline void gmax(register int &x, const register int &y) {
    if (x < y) x = y;
} 

inline void bfs(int x, int *dis) {
    std::queue<int> Q;
    Q.push(x); dis[x] = 0;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next)
            if (dis[a[i].v] == inf) 
                dis[a[i].v] = dis[u] + 1, Q.push(a[i].v);
    }
}

struct Query {
    int x, y, id; 
    Query(int x = 0, int y = 0, int id = 0):x(x), y(y), id(id) {  }
} ;

inline void build(int num, std::vector<int> Point, std::vector<pii> Line, std::vector<Query> Que) {
    ++ cnt;  register int N = Point.size();
    for (int i = 0; i < N; ++i) id[num][Point[i]] = i, dis[0][num][Point[i]] = dis[1][num][Point[i]] = inf; 
    if (N == 3) {
        for (auto i:Que) Ans[i.id] = i.x != i.y;
        return; 
    }

    std::vector<int> Tmp_Point;
    std::vector<pii> Tmp_Line; 
    std::vector<Query> Tmp_Que;
    int Mx = inf, ID = -1, tmp;
    for (register int i = 0; i < Line.size(); ++i) {
        if (id[num][Line[i].se] < id[num][Line[i].fi]) std::swap(Line[i].fi, Line[i].se);
        tmp = id[num][Line[i].se] - id[num][Line[i].fi] + 1; 
        gmax(tmp, N - tmp + 2);
        if (Mx > tmp) Mx = tmp, ID = i;
    }

    e = 1; 
    for (int i = 0; i < N; ++i)
        add(Point[i], Point[(i + 1) % N]);
    for (auto i:Line)
        add(i.fi, i.se);
    bfs(Line[ID].fi, dis[0][num]); bfs(Line[ID].se, dis[1][num]); 
    for (auto i:Point) first[i] = 0;

    for (int i = id[num][Line[ID].fi]; i <= id[num][Line[ID].se]; ++i)
        Tmp_Point.push_back(Point[i]), vis[num][Point[i]] = true; 
    for (auto i:Line)
        if (i != Line[ID] && id[num][i.fi] >= id[num][Line[ID].fi] && id[num][i.se] <= id[num][Line[ID].se])
            Tmp_Line.push_back(i), add(i.fi, i.se);

    for (auto i:Que)
        if (vis[num][i.x] ^ vis[num][i.y])
            Ans[i.id] = std::min(
                std::min(dis[0][num][i.x] + dis[0][num][i.y], dis[1][num][i.x] + dis[0][num][i.y] + 1),
                std::min(dis[1][num][i.x] + dis[1][num][i.y], dis[0][num][i.x] + dis[1][num][i.y] + 1)
            );
        else if (vis[num][i.x] & vis[num][i.y]) Tmp_Que.push_back(i);

    build(num + 1, Tmp_Point, Tmp_Line, Tmp_Que);

    Tmp_Point.clear(); Tmp_Line.clear(); Tmp_Que.clear(); 

    for (int i = id[num][Line[ID].se]; i != id[num][Line[ID].fi] + 1; (++i) %= N)
        Tmp_Point.push_back(Point[i]);
    
    for (auto i:Line)
        if (!vis[num][i.fi] || !vis[num][i.se])
            Tmp_Line.push_back(i);

    for (auto i:Que) 
        if (!vis[num][i.x] && !vis[num][i.y])
            Tmp_Que.push_back(i); 
    build(num + 1, Tmp_Point, Tmp_Line, Tmp_Que);
    for (int i = 0; i < N; ++i) vis[num][Point[i]] = false; 
}

int main() {
    std::vector<pii> G; 
    std::vector<int> S;
    std::vector<Query> Que; 
    memset(dis, 0x3f, sizeof dis); 
    n = read();
    for (int i = 1; i <= n - 3; ++i) {
        register int u = read(), v = read();
        if (u > v) std::swap(u, v);
        G.push_back(mk(u, v));
    }
    for (int i = 1; i <= n; ++i) S.push_back(i);
    Q = read();
    for (int i = 1; i <= Q; ++i) Que.push_back(Query(read(), read(), i));
    build(1, S, G, Que);
    for (int i = 1; i <= Q; ++i)
        printf("%d\n", Ans[i]);
    return 0; 
}
