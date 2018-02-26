# include <stdio.h>
# include <cstring>
# include <iostream>
const int MAXN = 2e5 + 5;
int trans[MAXN][26], Mx[MAXN], fa[MAXN], cnt, last, id[MAXN], n, size[MAXN]; char s[MAXN];


inline int Extend(int c) {
    int np = ++ cnt, p = last; last = np; Mx[np] = Mx[p] + 1; ++ size[np];
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            fa[nq] = fa[q]; fa[q] = fa[np] = nq;
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    } return np;
}

inline void Sort() {
    static int q[MAXN], t[MAXN];
    for (int i = 1; i <= cnt; i++) ++ t[Mx[i]];
    for (int i = 1; i <= n; i++) t[i] += t[i - 1];
    for (int i = cnt; i; i--) q[t[Mx[i]] --] = i;
    for (int i = cnt; i; i--) size[fa[q[i]]] += size[q[i]];
}

#define ls o << 1
#define rs o << 1 | 1

inline void gmin(int &x,int y) {
    if (x > y) x = y;
}

struct Tree{
    int mn[MAXN << 1], tag[MAXN << 1];

    Tree() {
        memset(mn, 0x3f, sizeof mn);
        memset(tag, 0x3f, sizeof tag);
    }

    inline void Push_down(int o) {
        gmin(mn[ls], tag[o]); gmin(tag[ls], tag[o]);
        gmin(mn[rs], tag[o]); gmin(tag[rs], tag[o]);
        tag[o] = 0x3f3f3f3f;
    }

    inline void Update(int o,int l,int r,int x,int y,int val) {
        if (x > y) return;
        if (x <= l && r <= y) return gmin(mn[o], val), gmin(tag[o], val), void();
        Push_down(o);
        register int mid = l + r >> 1;
        if (x <= mid) Update(ls, l, mid, x, y, val);
        if (mid < y) Update(rs, mid + 1, r, x, y, val);
    }

    inline int Query(int o, int l,int r,int x) {
        if (l == r) return mn[o];
        Push_down(o);
        register int mid = l + r >> 1;
        if (x <= mid) return Query(ls, l, mid, x);
        else return Query(rs, mid + 1, r, x);
    }
}T[2]; 

int main() {
    scanf("%s", s + 1); n = strlen(s + 1); last = ++ cnt;
    for (int i = 1; s[i]; i++) id[i] = Extend(s[i] - 'a');
    Sort();
    for (int i = 1; i <= n; i++)
        if (size[id[i]] == 1)
            T[0].Update(1, 1, n, i - Mx[fa[id[i]]], i, Mx[fa[id[i]]] + 1),
            T[1].Update(1, 1, n, i - Mx[id[i]] + 1, i - Mx[fa[id[i]]] - 1, i);
    int t;
    for (int i = 1; i <= n; i++){
        t = std::min(T[0].Query(1, 1, n,i), T[1]. Query(1, 1, n, i) - i + 1);
        if (t <= 0x3f3f3f3f - i) printf("%d\n", t);
        else puts("0");
    }
    return 0;
}