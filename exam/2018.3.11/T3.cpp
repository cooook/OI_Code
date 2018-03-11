# include <bits/stdc++.h> 
# define RG register 
const int MAXN = 32005;
int f[MAXN][505], n, first[MAXN], e = 1, pos[MAXN], fa[MAXN], val[MAXN], Max_Deep[MAXN]; 
long long Ans; 
# define f(_, __) f[_][__ + 250]
 
 
char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; RG char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
struct edge {
    int u, v, w, next, id;  
} a[MAXN << 1], E[MAXN];
 
inline void push(RG int u, RG int v, RG int w, RG int id) {
    a[e].id = id; a[e].u = u; a[e].v = v; a[e].w = w; 
    a[e].next = first[u]; first[u] = e++;
}
 
inline void gmax(register int &x, const register int &y) {
    if (x < y) x = y; 
}
 
inline void dfs(RG int u, RG int fa) {
    f(u, 0) = 1; 
    ::fa[u] = fa; Max_Deep[u] = 0;
    for (RG int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue ;
        dfs(v, u);
        pos[a[i].id] = v;
        gmax(Max_Deep[u], Max_Deep[v] + 1);
        for (RG int j = -Max_Deep[v]; j <= Max_Deep[v]; ++j)
            f(u, j + val[v]) += f(v, j); 
    }
}
 
inline void Update(RG int x, RG int w) {
    val[x] = 1;
    register int Sum = 0;
    for (register int u = x; fa[u]; u = fa[u]) {
        Sum += val[u];
        for (RG int i = -Max_Deep[x]; i <= Max_Deep[x]; ++i)
            f(fa[u], i + Sum - 2) -= f(x, i),
            f(fa[u], i + Sum) += f(x, i);
        for (RG int i = -Max_Deep[x]; i <= Max_Deep[x]; ++i)
            Ans += 1ll * f(x, i) * (f(fa[u], 1 - i - Sum) - f(u, 1 - i - Sum - val[u])) * w;
    }
}
 
int main() {
    n = read();
    for (RG int i = 1; i <= n; ++i) val[i] = -1; 
    for (register int i = 1; i < n; ++i) {
        register int u = read(), v = read(), w = read();
        push(u, v, w, i), push(v, u, w, i); 
        E[i].u = u; E[i].v = v; E[i].w = w; E[i].id = i; 
    }
    dfs(1, 0);
    std::sort(&E[1], &E[n], [](const edge &a, const edge &b) -> bool { return a.w > b.w; });
 
    for (RG int i = 1; i < n; ++i) Update(pos[E[i].id], E[i].w);
    printf("%lld\n", Ans);
    return 0;
}