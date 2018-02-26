# include <stdio.h>
# include <cstring>
const int MAXN = 1e6 + 5;
typedef long long ll; 
char s[MAXN];
int last, cnt, fa[MAXN], trans[MAXN][26], Mx[MAXN], size[MAXN], first[MAXN], e = 1;
ll Ans;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u, v, next; 
} a[MAXN];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void Extend(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1;
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
            fa[nq] = fa[q]; fa[q] = fa[np] = nq;
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    }
    last = np; 
}

inline ll C(int x) {
    return 1ll * x * (x - 1) / 2; 
}

inline void dp(int u) {
    for (int i = first[u]; i; i = a[i].next)
        dp(a[i].v), Ans -= C(size[a[i].v]) * Mx[u], size[u] += size[a[i].v];
    Ans += C(size[u]) * Mx[u];
}

int main() {
    scanf("%s", s + 1); last = ++ cnt; 
    int len = strlen(s + 1); 
    for (int i = len; i; --i) Extend(s[i] - 'a');
    for (int i = 2; i <= cnt; i++) push(fa[i], i);
    dp(1);
    ll res = 0;
    for (int i = 1; i <= len; i++) res += 1ll * i * (i - 1) + 1ll * i * (i - 1) / 2;
    printf("%lld\n", res - Ans * 2);
    return 0;
}