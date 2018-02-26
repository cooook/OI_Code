# include <queue> 
# include <stdio.h>
# include <cstring>
# include <iostream>
# include <algorithm>
const int MAXN = 55;
const int MAX_EDGE = 2e6 + 5;
const int MAX_NODE = 1e6 + 5;
const int inf = 0x3f3f3f3f;
int n, Hash1[MAXN], Hash2[MAXN], cnt1, cnt2, Cooook[MAXN][2], first[MAX_NODE], e = 2, dis[MAX_NODE], S, T, pre[MAX_NODE];
bool mp[MAXN][MAXN], vis[MAX_NODE];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int d[2];
    inline int& operator [] (const int &x) {return d[x];}
} pt[MAXN];

struct edge{
    int u, v, next, w, c;
} a[MAX_EDGE];

inline void add(int u, int v, int w, int c) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].c = c;
    a[e].next = first[u]; first[u] = e++;
}

inline void push(int u, int v, int w, int c) {
    add(u, v, w, c), add(v, u, 0, -c);
}

inline bool bfs() {
    std::queue<int> Q;
    Q.push(S);
    memset(dis, 0x3f, sizeof dis);
    dis[S] = 0;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop(); vis[u] = false;
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v;
            if (dis[v] > dis[u] + a[i].c && a[i].w) {
                dis[v] = dis[u] + a[i].c; pre[v] = i;
                if (!vis[v]) vis[v] = true, Q.push(v);
            }
        }
    }
    return dis[T] != 0x3f3f3f3f; 
}

inline int gmin(int &x, const int &y) {
    if (x > y) x = y;
    return x;
}

inline int MCMF() {
    int Ans = 0, tmp;
    while (bfs()) {
        tmp = 0x3f3f3f3f;
        for (int i = pre[T]; i; i = pre[a[i].u]) gmin(tmp, a[i].w);
        for (int i = pre[T]; i; i = pre[a[i].u]) a[i].w -= tmp, a[i ^ 1].w += tmp;
        Ans += dis[T] * tmp; 
    }
    return Ans;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) pt[i][0] = read(), pt[i][1] = read(), Hash1[i] = pt[i][0], Hash2[i] = pt[i][1];
    std::sort(&Hash1[1], &Hash1[n + 1]);
    std::sort(&Hash2[1], &Hash2[n + 1]);
    cnt1 = std::unique(&Hash1[1], &Hash1[n + 1]) - Hash1 - 1;
    cnt2 = std::unique(&Hash2[1], &Hash2[n + 1]) - Hash2 - 1;
    for (int i = 1; i <= n; i++) {
        pt[i][0] = std::lower_bound(&Hash1[1], &Hash1[cnt1 + 1], pt[i][0]) - Hash1;
        pt[i][1] = std::lower_bound(&Hash2[1], &Hash2[cnt2 + 1], pt[i][1]) - Hash2;
        mp[pt[i][0]][pt[i][1]] = true;
        ++ Cooook[pt[i][0]][0];
        ++ Cooook[pt[i][1]][1];
    }
    T = cnt1 + cnt2 + cnt2 + 1;
    for (int i = 1; i <= cnt1; i++) push(S, i, Cooook[i][0], 0);
    for (int i = 1; i <= cnt1; i++)
        for (int j = 1; j <= cnt2; j++)
            push(i, cnt1 + j, 1, mp[i][j]);
    for (int i = 1; i <= cnt2; i++) 
        push(cnt1 + i, cnt1 + cnt2 + i, Cooook[i][1], 0), 
        push(cnt1 + cnt2 + i, T, inf, 0);
    printf("%d\n", MCMF());
    // getchar(); getchar();
    return 0;
}