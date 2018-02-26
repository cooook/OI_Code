# include <bits/stdc++.h>
const int MAXN = 2005;
const int MAXM = 1000005;
const int inf = 0x3f3f3f3f; 
int f[MAXN], n, pre[MAXM], first[MAXM], dis[MAXM], e = 2, S, T, S1, T1;
bool vis[MAXM]; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int gmin(int &x, const int & y) {
    if (x > y) x = y;
    return x;
}

struct Point {
    int d[2];
    inline bool operator < (const Point & x) const {
        if (d[1] == x.d[1]) return d[0] < x.d[0];
        return d[1] < x.d[1];
    }
    inline int& operator [] (const int &x) {return d[x];}
}pt[MAXN]; 

struct edge{
    int u, v, next, w, c;
}a[MAXM << 1];

inline void add(int u, int v, int w, int c) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].c = c;
    a[e].next = first[u]; first[u] = e++;
}

inline void push(int u, int v, int w, int c) {
    add(u, v, w, c), add(v, u, 0, -c);
}

inline bool bfs() {
    memset(dis, 128, sizeof dis);
    dis[S] = 0;
    std::queue<int> Q; Q.push(S);
    while (!Q.empty()) {
        int u = Q.front(); vis[u] = false; Q.pop();
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v, w = a[i].w;
            if (dis[v] < dis[u] + a[i].c && w) {
                dis[v] = dis[u] + a[i].c; pre[v] = i;
                if (!vis[v]) Q.push(v), vis[v] = true;
            }
        }
    }
    return dis[T] != dis[0];
}

inline int MCMF() {
    int Ans = 0, tmp;
    while (bfs()) {
        tmp = inf;
        for (int i = pre[T]; i; i = pre[a[i].u]) gmin(tmp, a[i].w);
        for (int i = pre[T]; i; i = pre[a[i].u]) Ans += a[i].c * tmp, a[i].w -= tmp, a[i ^ 1].w += tmp;
    }
    return Ans;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) pt[i][0] = read(), pt[i][1] = read();
    std::sort(&pt[1], &pt[n + 1]);
    S1 = 1; T = (n << 1 | 1) + 1;
    S = T + 1;
    for (int i = 1; i <= n; i++) {
        int Max_High = -1;
        push(S1, i << 1, 1, 0);
        push(i << 1, i << 1 | 1, 1, 1);
        push(i << 1, i << 1 | 1, inf, 0);
        push(i << 1 | 1, T, 1, 0);
        for (int j = i - 1; j; j--)
            if (pt[j][0] <= pt[i][0] && pt[j][0] > Max_High) Max_High = pt[j][0], push(j << 1 | 1, i << 1, inf, 0); 
    }
    push(S, S1, 2, 0);
    printf("%d\n", MCMF());
    return 0;
}