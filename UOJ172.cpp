# include <queue> 
# include <stdio.h> 
# include <cstring> 
# define int long long 
# define RG register
# define debug(...) fprintf(stderr, __VA_ARGS__); 
typedef long long ll; 
const int MAXN = 5e5 + 5; 
char s[MAXN]; int Next[MAXN], n, T, cnt, len[MAXN], dis[MAXN]; 
bool vis[MAXN]; 
ll w; 


inline void KMP(char *s) {
    memset(Next, 0, sizeof Next);
    int fix = 0;
    for (int i = 2; s[i]; ++i) {
        while (fix && s[fix + 1] != s[i]) fix = Next[fix]; 
        if (s[fix + 1] == s[i]) ++ fix; 
        Next[i] = fix;
    }
    RG int tmp = Next[n]; 
    cnt = 0;
    for (; tmp; tmp = Next[tmp]) len[++cnt] = n - tmp;
}

inline void bfs() {
    memset(dis, 0x3f, sizeof dis); 
    memset(vis, 0, sizeof vis); 
    std::queue<int> Q; 
    dis[0] = n; Q.push(0);
    while (!Q.empty()) {
        RG int u = Q.front(); Q.pop(); vis[u] = false; 
        for (RG int i = 1; i <= cnt; ++i) {
            RG int v = (u + len[i]) % n;
            if (dis[v] > dis[u] + len[i]) {
                dis[v] = dis[u] + len[i]; 
                if (!vis[v]) vis[v] = true, Q.push(v); 
            }
        }
    }
}

signed main() {
    scanf("%lld", &T);
    while (T --) {
        scanf("%lld%lld", &n, &w);
        scanf("%s", s + 1);
        KMP(s);
        bfs();
        RG ll Ans = 0;
        for (int i = 0; i <= n; ++i) if (dis[i] <= w) Ans += (ll)(w - dis[i]) / n + 1;
        printf("%lld\n", Ans);
    }
    return 0; 
}