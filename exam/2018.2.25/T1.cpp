# include <vector> 
# include <stdio.h> 
const int MAXN = 405; 
int n, m, d1[MAXN], d2[MAXN], use[MAXN], Ans; 
// std::vector<int> G[MAXN]; 
bool vis[MAXN], QAQ[MAXN][MAXN]; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v;
    edge(int u = 0, int v = 0) : u(u), v(v) {  }
} E[MAXN];

inline void check() {
    for (int i = 1; i < n; ++i)
        if (!QAQ[use[E[i].u]][use[E[i].v]]) return;
    ++ Ans;
}

inline void dfs(int x) {
    if (x == n + 1) return void(check());
    for (int i = 1; i <= n; ++i) if (!vis[i] && d1[i] >= d2[x]) {
        use[x] = i;
        vis[i] = true; 
        dfs(x + 1);
        vis[i] = false; 
        use[x] = 0;
    }
}

int main() {
    // freopen("T1.in","r",stdin);
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        register int u = read(), v = read();
        ++d1[u]; ++d1[v];
        QAQ[u][v] = QAQ[v][u] = true; 
    }
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        E[i] = edge(u, v);
        // G[u].push_back(v); G[v].push_back(u); 
        ++d2[u]; ++d2[v];
    }
    dfs(1);
    printf("%d\n", Ans);
    // while (true); 
    return 0;
}