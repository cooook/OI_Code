# include <stdio.h>
# include <queue> 
# include <cstring> 
# include <iostream> 
# define int long long 
const int MAXN = 4005, inf = 0x3f3f3f3f3f3f3f3fll;
int T, n, m, first[MAXN], e = 2, Num1, Num2, Sum1, Sum2, val[45][45], S, To;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, w, next;
}a[2000005];

inline void push(int u, int v, int w) {
    a[e] = (edge){u, v, w, first[u]}; first[u] = e++;
    a[e] = (edge){v, u, 0, first[v]}; first[v] = e++;
}

int d[MAXN];

inline bool bfs() {
    std::queue<int> Q;
    memset(d, -1, sizeof d);
    Q.push(S); d[S] = 1;
    while (!Q.empty()) {
        register int u = Q.front(); Q.pop();
        if (u == To) return true;
        for (int i = first[u]; i; i = a[i].next)
            if (d[a[i].v] == -1 && a[i].w)
                d[a[i].v] = d[u] + 1, Q.push(a[i].v); 
    }
    return false;
}

inline int dfs(int u, int cap) {
    if (u == To || !cap) return cap;
    register int Ans = 0; 
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v, w = a[i].w;
        if (d[v] == d[u] + 1 && w) {
            w = dfs(v, std::min(w, cap));
            cap -= w; 
            a[i].w -= w;
            a[i ^ 1].w += w;
            Ans += w;
            if (!cap) break;
        }
    }
    if (!Ans) d[u] = -1;
    return Ans;
}

inline int dinic() {
    int Ans = 0;
    for (; bfs(); Ans += dfs(S, inf)); 
    return Ans;
}

# define D(_, __) ((_ - 1) * m + __)

inline bool Calc(int x) {
    e = 2; memset(first, 0, sizeof first);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if ((i + j) & 1) {
                push(S, D(i,j), x - val[i][j]);
                if (i != 1) push(D(i, j), D(i - 1, j), inf);
                if (j != 1) push(D(i, j), D(i, j - 1), inf);
                if (i != n) push(D(i, j), D(i + 1, j), inf);
                if (j != m) push(D(i, j), D(i, j + 1), inf); 
            }
            else push(D(i, j), To, x - val[i][j]);
        }
    return dinic() == Num1 * x - Sum1;
}

# define Wxh return puts("-1"), void();

inline void Read_In() {
    n = read(), m = read();
    S = 0; To = n * m + 1;
    Num1 = Num2 = Sum1 = Sum2 = 0;
    int Mx = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            val[i][j] = read();
            if ((i + j) & 1) Num1 ++, Sum1 += val[i][j];
            else Num2 ++, Sum2 += val[i][j];
            Mx = std::max(Mx, val[i][j]);
        }
    if (Num1 != Num2) {
        if (Num1 < Num2) std::swap(Num1, Num2), std::swap(Sum1, Sum2);
        if (Sum1 - Sum2 < 0) Wxh
        if ((Sum1 - Sum2) % (Num1 - Num2) != 0) Wxh
        int Ans = (Sum1 - Sum2) / (Num1 - Num2);
        if (Mx > Ans) Wxh
        if (!Calc(Ans)) Wxh
        else printf("%lld\n", Ans * Num1 - Sum1);
    }
    else {
        if (Sum1 != Sum2) Wxh
        int l = Mx, r = inf, mid, Ans;
        while (l <= r) {
            mid = l + r >> 1;
            if (Calc(mid)) Ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf("%lld\n", Ans * Num1 - Sum1);
    }
}

signed main() {
    T = read();
    while (T --) Read_In();
    return 0;
}