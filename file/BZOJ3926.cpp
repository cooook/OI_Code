# include <bits/stdc++.h> 
const int MAXN = 2e6+5;
int n, du[MAXN], trans[MAXN][10], c, fa[MAXN], Mx[MAXN], id[MAXN], cnt, first[MAXN], e = 1, s[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar(); 
    for (; ch > '9' | ch < '0'; ch = getchar()) ch == '-'? f = -f:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN << 1];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline int Extend(int p, int c) {
    int np = ++ cnt; Mx[np] = Mx[p] + 1;
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt;
            Mx[nq] = Mx[p] + 1;
            fa[nq] = fa[q]; fa[np] = fa[q] = nq;
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    } return np;
}

inline void dfs(int u,int fa) {
    id[u] = Extend(id[fa], s[u]);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa) dfs(a[i].v, u);
}

int main() {
    n = read(); c = read(); id[0] = ++ cnt;
    for (int i = 1; i <= n; i++) s[i] = read();
    for (int i = 1; i < n; i++) {
        register int u = read(), v = read();
        push(u,v), push(v,u);
        du[u] ++; du[v] ++;
    }
    for (int i = 1; i <= n; i++)
        if (du[i] == 1) dfs(i, 0);
    long long Ans = 0;
    for (int i = 2; i <= cnt; i++)
        Ans += Mx[i] - Mx[fa[i]];
    printf("%lld\n", Ans);
    return 0;
}