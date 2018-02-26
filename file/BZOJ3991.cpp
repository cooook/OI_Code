# include <bits/stdc++.h>
# define int long long 
const int MAXN = 1e5 + 5;
const int inf = 0x3f3f3f3f;
int n, deep[MAXN], dfn[MAXN], idx, f[MAXN][20], d[MAXN][20], first[MAXN], e = 1, m, pre[MAXN];
bool vis[MAXN];


char sb[1 << 15], *S = sb, *T = sb;
# define gc (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
inline int read() {
    register int x = 0, f = 1; char ch = gc;
    for (; !isdigit(ch); ch = gc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = gc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, w, next;
} a[MAXN << 1];

inline void push(int u, int v, int w) {
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u, int fa) {
    for (int i = 1; i <= 17; ++i) f[u][i] = f[f[u][i-1]][i-1], d[u][i] = d[u][i - 1] + d[f[u][i-1]][i-1];
    dfn[u] = ++ idx; pre[idx] = u;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        f[v][0] = u; d[v][0] = a[i].w; deep[v] = deep[u] + 1;
        dfs(v, u); 
    }
}

inline int dis(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    register int t = deep[u] - deep[v], Ans = 0;
    for (int i = 17; ~i; --i) 
        if (t >> i & 1) Ans += d[u][i], u = f[u][i];
    if (u == v) return Ans;
    for (int i = 17; ~i; --i)
        if (f[u][i] != f[v][i])
            Ans += d[u][i] + d[v][i], u = f[u][i], v = f[v][i];
    return Ans + d[u][0] + d[v][0]; 
}

std::set<int> t;

signed main() {
    n = read(), m = read();
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read(), w = read();
        push(u, v, w), push(v, u, w);
    } dfs(1, 0); t.insert(-2333); t.insert(inf);
    int Ans = 0;
    std::set<int>::iterator it;
    while (m --) {
        register int x = read(), type, tmp = 0, l, r;
        if (!vis[x]) { t.insert(dfn[x]); type = 1; }
        else { t.erase(dfn[x]); type = -1; }
        vis[x] ^= 1;
        l = *--t.lower_bound(dfn[x]); r = *t.upper_bound(dfn[x]);
        if (l != -2333) Ans += type * dis(pre[l], x);
        if (r != inf) Ans += type * dis(pre[r], x);
        if (l != -2333 && r != inf) Ans -= type * dis(pre[l], pre[r]);
        if (t.size() > 2) it = t.end(), --it, --it, tmp = dis(pre[*++t.begin()], pre[*it]);
        printf("%lld\n", Ans + tmp);
    }
    return 0;
}