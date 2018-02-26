# include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 600005;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
int n, cnt, trans[MAXN][26], fa[MAXN], Mx[MAXN], last, val[MAXN], first[MAXN], e = 1;
char s[MAXN]; ll size[MAXN], mx[MAXN], mn[MAXN], Ans1[MAXN], Ans2[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'? f = -f:0;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void Add(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1; ++ size[np]; 
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
            fa[nq] = fa[q]; fa[np] = fa[q] = nq;
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        } 
    } last = np;
}

inline void gmax(ll &a, ll b) {if (a < b) a = b;}
inline void gmin(ll &a, ll b) {if (a > b) a = b;}

inline void dp(int u) {
    if (!size[u]) mx[u] = -inf, mn[u] = inf;
    for (int i = first[u]; i; i = a[i].next) {
        dp(a[i].v);
        if (mx[u] != -inf && mx[a[i].v] != -inf && mn[u] != inf && mn[a[i].v] != inf) 
            gmax(Ans2[Mx[u]], std::max(mx[u] * mx[a[i].v], mn[u] * mn[a[i].v]));
        gmax(mx[u], mx[a[i].v]);
        gmin(mn[u], mn[a[i].v]);
        Ans1[Mx[u]] += size[u] * size[a[i].v];
        size[u] += size[a[i].v];
    }
}

int main() {
    std::fill(Ans2, Ans2 + MAXN, -inf);
    n = read();
    scanf("%s", s + 1); last = ++ cnt;
    for (int i = 1; i <= n; i++) val[i] = read();
    for (int i = n; i; --i) Add(s[i] - 'a'), mx[last] = mn[last] = val[i];
    for (int i = 2; i <= cnt; i++) push(fa[i], i); dp(1);
    for (int i = n - 1; ~i; i--) Ans1[i] += Ans1[i + 1], gmax(Ans2[i], Ans2[i + 1]);
    for (int i = 0; i < n; i++) 
        if (Ans1[i]) printf("%lld %lld\n", Ans1[i], Ans2[i]);
        else puts("0 0");
    return 0;
}