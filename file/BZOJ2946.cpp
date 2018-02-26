# include <bits/stdc++.h>
const int MAXN = 5005;
int n,trans[MAXN][26], fa[MAXN], Mx[MAXN], res[MAXN], last, cnt, q[MAXN], t[MAXN], d[MAXN]; char s[MAXN]; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'? f = -f:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &a, int b) {
    if (a > b) a = b;
}

inline void gmax(int &a, int b) {
    if (a < b) a = b;
}

inline int Extend(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1;
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

inline void Top_Sort() {
    for (int i = 1; i <= cnt; i++) d[i] = Mx[i];
    for (int i = 1; i <= cnt; i++) ++ t[Mx[i]];
    for (int i = 1; i <= 2000; i++) t[i] += t[i-1];
    for (int i = cnt; i; i--) q[t[Mx[i]] --] = i;
}

inline void Query() {
    scanf("%s", s + 1); 
    int root = 1, c, Len = 0;
    memset(res, 0, sizeof res);
    for (int i = 1; s[i]; i++) {
        c = s[i] - 'a';
        while (!trans[root][c] && root) root = fa[root];
        if (!root) root = 1, Len = 0;
        else gmin(Len, Mx[root]), ++ Len, root = trans[root][c];
        gmax(res[root], Len);
    }
    for (int i = cnt; i >= 1; i--) gmax(res[fa[q[i]]], res[q[i]]);
    for (int i = 1; i <= cnt; i++) gmin(d[i], res[i]);
}

int main() {
    n = read(); last = ++ cnt;
    scanf("%s", s + 1);
    if (n == 1) return printf("%d\n", strlen(s + 1)), 0;
    for (int i = 1; s[i]; i++) Extend(s[i] - 'a');
    Top_Sort();
    for (int i = 1; i < n; i++) Query();
    int Ans = 0;
    for (int i = 1; i <= cnt; i++) gmax(Ans, d[i]);
    printf("%d\n", Ans);
    return 0;
}