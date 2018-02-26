# include <bits/stdc++.h> 
const int MAXN = 3000005;
int top[MAXN], fa[MAXN], deep[MAXN], n, dfn[MAXN], idx, first[MAXN], e = 1, Q, cnt, son[MAXN], size[MAXN];
std::vector<int> t[1005];


char sb[1 << 15], *S = sb, *T = sb;
# define getc (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge { 
    int u, v, next;
} a[MAXN << 1];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs1(int u) {
    dfn[u] = ++ idx; size[u] = 1;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa[u]) continue;
        fa[v] = u; deep[v] = deep[u] + 1; 
        dfs1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

inline void dfs2(int u, int Num) {
    top[u] = Num;
    if (son[u]) dfs2(son[u], Num);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa[u] && a[i].v != son[u])
            dfs2(a[i].v, a[i].v);
}

inline int lca(int u, int v) {
    int f1 = top[u], f2 = top[v];
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) std::swap(f1, f2), std::swap(u, v);
        u = fa[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) std::swap(u, v);
    return u;
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    Q = read(); n = 1;
    while (Q--) {
        char ch = getc; 
        while (ch != 'A' && ch != 'Q') ch = getc;
        if (ch == 'A') {
            int x = read(); push(x, ++n), push(n, x);
        }
        else {
            int k = read(); ++ cnt;
            for (int i = 1; i <= k; ++i) t[cnt].push_back(read());
        }
    }
    dfs1(1); dfs2(1, 1);
    for (int i = 1; i <= cnt; ++i) {
        int Mn_id = t[i][0], Mx_id = t[i][0];
        for (int j = 1; j < t[i].size(); ++j) {
            if (dfn[Mn_id] > dfn[t[i][j]]) Mn_id = t[i][j];
            if (dfn[Mx_id] < dfn[t[i][j]]) Mx_id = t[i][j];
        }
        printf("%d\n", lca(Mn_id, Mx_id));
    }
    // while (true); 
    return 0;
}