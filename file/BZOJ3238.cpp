# include <bits/stdc++.h>
const int MAXN = 1000005;
int trans[MAXN][26], fa[MAXN], Mx[MAXN], n, first[MAXN], e = 1, last, cnt, size[MAXN];
char s[MAXN]; long long Ans;


struct edge{
    int u, v, next;
}a[MAXN];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline int Extend(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1; ++ size[np];
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
    } last = np;
}

inline void dp(int u) {
    long long tmp = 0;
    for (int i = first[u]; i; i = a[i].next)
        dp(a[i].v), size[u] += size[a[i].v], 
        tmp -= 1ll * size[a[i].v] * (size[a[i].v] - 1) / 2;
    tmp += 1ll * size[u] * (size[u] - 1) / 2;
    Ans -= tmp * Mx[u] * 2;
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1); last = ++ cnt;
    for (int i = n; i; i--) Extend(s[i] - 'a');
    for (int i = 2; i <= cnt; i++) push(fa[i], i);
    dp(1);
    for (int i = 2; i <= n; i++) 
        Ans += 1ll * (i - 1) * i / 2 + 1ll * (i - 1) * i;
    printf("%lld\n", Ans);
    return 0;
}