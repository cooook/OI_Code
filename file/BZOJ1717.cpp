# include <bits/stdc++.h>
const int MAXN = 400005;
int n, k, fa[MAXN], Mx[MAXN], q[MAXN], t[MAXN], last, cnt, size[MAXN];
std::map<int,int> trans[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void extend(int c) {
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1; size[np] = 1;
    for (; p && !trans[p].count(c); p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
            fa[nq] = fa[q]; fa[np] = fa[q] = nq;
            trans[nq] = trans[q];
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    } last = np;
}

inline void Sort() {
    for (int i = 1; i <= cnt; i++) ++ t[Mx[i]];
    for (int i = 1; i <= n; i++) t[i] += t[i-1];
    for (int i = cnt; i; i--) q[t[Mx[i]] --] = i;
    for (int i = cnt; i; i--) size[fa[q[i]]] += size[q[i]];
}

int main() {
    n = read(), k = read();
    last = ++ cnt;
    for (int i = 1; i <= n; i++) extend(read());
    Sort(); int Ans = 0;
    for (int i = 1; i <= cnt; i++)
        if (size[i] >= k) Ans = std::max(Ans, Mx[i]);
    printf("%d\n", Ans);
    // getchar(); getchar();
    return 0;
}