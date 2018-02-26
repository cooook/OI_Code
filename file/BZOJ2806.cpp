# include <stdio.h> 
# include <cstring> 
# include <iostream> 
const int inf = 0x3f3f3f3f;
const int MAXN = 1e7 + 5; 
char s[MAXN];
int n, m, last, Len, f[MAXN], trans[MAXN][2], fa[MAXN], Mx[MAXN], cnt, a[MAXN];
 
 
template <typename _t>
inline void gmin(_t &x, const _t &y) { if (x > y) x = y; }
template <typename _t> 
inline void gmax(_t &x, const _t &y) { if (x < y) x = y; }
 
inline void Extend(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[last] + 1;
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c]; 
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
            fa[nq] = fa[q]; fa[q] = fa[np]= nq;
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    }
    last = np;
}
 
inline bool Judge(int x) {
    int root = 1, match = 0, l = 1, r = 0; 
    f[0] = 0;
    for (int i = 1; s[i]; i++) {
        f[i] = f[i-1] + 1;
        if (!trans[root][s[i] - '0']) {
            while (root && !trans[root][s[i] - '0']) root = fa[root];
            if (!root) root = 1, match = 0;
            else gmin(match, Mx[root]), ++ match, root = trans[root][s[i] - '0'];
        }
        else ++ match, root = trans[root][s[i] - '0'];
        if (match >= x) {
            while (l <= r && i - a[l] > match) ++ l;
            while (l <= r && f[a[r]] >= f[i - x]) -- r;
            a[++r] = i - x;
            gmin(f[i], f[a[l]]);
        }
        else l = 1, r = 0;
    }
    return f[Len] / 1.0 / Len <= 0.1;
}
 
inline void Work() {
    scanf("%s", s + 1);
    Len = strlen(s + 1);
    int l = 0, r = Len, mid, Ans = 0; 
    while (l <= r) {
        mid = l + r >> 1; 
        if (Judge(mid)) Ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", Ans);
}
 
int main() {
    scanf("%d%d", &n, &m);
    last = ++ cnt;
    for (int i = 1; i <= m; i++) {
        last = 1;
        scanf("%s", s + 1);
        for (int j = 1; s[j]; j++) Extend(s[j] - '0');
    }
    while (n--) Work();
    return 0;
} 