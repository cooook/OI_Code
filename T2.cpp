# include <queue> 
# include <stdio.h> 
# include <cstring> 
# include <iostream> 
# include <algorithm> 
const int MAXN = 1e5 + 5; 
int n, Q, first[MAXN], e = 1, dis[MAXN], Ans[MAXN];
bool vis[MAXN], used[MAXN]; 


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

struct Query {
    int x, y, id; 
    inline bool operator < (const Query &a) const {
        return x < a.x; 
    }
}Que[MAXN];

struct cmp {
    inline bool operator () (const int &a, const int &b) {
        return dis[a] < dis[b]; 
    }
};

inline void Spfa(int x) {
    if (used[x]) return; used[x] = true; 
    // std::queue<int> S;
    std::priority_queue<int, std::vector<int>, cmp > S;
    for (int i = 1; i <= n; ++i) dis[i] = 0x3f3f3f3f; 
    S.push(x); vis[x] = 0;  dis[x] = 0;
    while (!S.empty()) {
        register int u = S.top(); S.pop(); vis[u] = false; 
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v;
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                if (!vis[v]) vis[v] = true, S.push(v); 
            }
        }
    }
}

int main() {
    // freopen("T2.in","r",stdin);
    // freopen("T2.out","w",stdout);
    n = read();
    for (int i = 1; i <= n; ++i)
        add(i, i == n ? 1 : i + 1); 
    for (int i = 1; i <= n - 3; ++i) {
        register int u = read(), v = read();
        add(u, v); 
    }
    Q = read();
    for (int i = 1; i <= Q; ++i) {
        Que[i].x = read(), Que[i].y = read(); Que[i].id = i; 
        if (Que[i].x > Que[i].y) std::swap(Que[i].x, Que[i].y);
    }
    std::sort(&Que[1], &Que[Q + 1]);
    for (int i = 1; i <= Q; ++i) {
        if (!used[Que[i].x]) Spfa(Que[i].x);
        Ans[Que[i].id] = dis[Que[i].y]; 
        // printf("%d\n", dis[Que[i].y]);
    }
    for (int i = 1; i <= Q; ++i)
        printf("%d\n", Ans[i]);
    // while (true); 
    return 0; 
}