# include <bits/stdc++.h> 
const int MAXN = 105;
int n, m, val[MAXN][MAXN], id[MAXN][MAXN], cnt, c[MAXN], Num[1005], bl[1005];
bool vis[1005];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

namespace Min_Cut {

    const int inf = 0x3f3f3f3f;

    int first[1000000], e = 2, d[1000000], T, S;

    struct edge {
        int u, v, w, next; 
    }a[2000005];

    inline void add(int u, int v, int w) {
        a[e].u = u; a[e].v = v; a[e].w = w; 
        a[e].next = first[u]; first[u] = e++;
    } 

    inline void push(int u, int v, int w) {
        add(u, v, w); add(v, u, 0);
    }

    inline bool bfs() {
        std::queue<int> Q;
        Q.push(S);
        memset(d, -1, sizeof d);
        d[S] = 1;
        while (!Q.empty()) {
            register int u = Q.front(); Q.pop();
            for (int i = first[u]; i; i = a[i].next) 
                if (d[a[i].v] == -1 && a[i].w)
                    d[a[i].v] = d[u] + 1, Q.push(a[i].v);
        }
        return d[T] != -1;
    } 

    inline int dfs(int u, int cap) {
        if (u == T || !cap) return cap;
        int Ans = 0;
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v, w = a[i].w;
            if (d[v] == d[u] + 1 && a[i].w) {
                w = dfs(v, std::min(cap, w));
                Ans += w;
                cap -= w;
                a[i].w -= w;
                a[i ^ 1].w += w;
                if (!cap) break;
            }
        }
        if (!Ans) d[u] = -1;
        return Ans;
    }

    inline int dinic() {
        int Ans = 0;
        while (bfs()) Ans += dfs(S, inf);
        return Ans;
    }
}

using namespace Min_Cut;

int main() {
    n = read(), m = read();
    T = ++ cnt; 
    for (int i = 1; i <= n; i++) 
        if (!bl[c[i] = read()]) {
            bl[c[i]] = ++ cnt;
            push(cnt, T, m * c[i] * c[i]);
        }
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            val[i][j] = read(), id[i][j] = ++cnt;
    int Ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            if (i == j) push(id[i][i], bl[c[i]], inf), push(id[i][i], T, c[i]);
            if (i != j) push(id[i][j], id[i + 1][j], inf), push(id[i][j], id[i][j - 1], inf);
            if (val[i][j] > 0) push(S, id[i][j], val[i][j]), Ans += val[i][j];
            else push(id[i][j], T, -val[i][j]);
        }
    printf("%d\n", Ans - dinic());
    return 0;
}