# include <bits/stdc++.h>
const int MAXN = 1.2e6 + 5;
int last, n, Mx[MAXN], fa[MAXN], cnt, val[MAXN];
std::map<int, int> trans[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Extend(int x) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1; 
    for (; p && !trans[p].count(x); p = fa[p]) trans[p][x] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][x];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
            fa[nq] = fa[q]; fa[np] = fa[q] = nq;
            trans[nq] = trans[q];
            for (; trans[p][x] == q; p = fa[p]) trans[p][x] = nq;
        }
    } last = np; 
}

int main() {
    n = read(); last = ++ cnt;
    for (int i = 1; i <= n << 1; i++) Extend(i <= n? val[i] = read():val[i - n]);
    int root = 1;
    std::map<int, int>::iterator it;
    while (n --) {
        it = trans[root].begin();
        printf("%d", it -> first);
        if (n) printf(" "), root = it -> second;
    }
    return 0;
}