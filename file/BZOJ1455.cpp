# include <bits/stdc++.h>
const int MAXN = 1000005; 
int n, fa[MAXN], val[MAXN];
bool vis[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    int l, r, key, d;
}tree[MAXN];

# define ls tree[x].l
# define rs tree[x].r
# define val tree[x].key
# define dep tree[x].d

inline int find(int x) {
    return fa[x] == x?x:fa[x] = find(fa[x]);
}

inline int merge(int x,int y) {
    if (!x || !y) return !x?y:x;
    if (tree[x].key > tree[y].key) std::swap(x,y);
    rs = merge(rs, y);
    if (tree[ls].d < tree[rs].d) std::swap(ls, rs);
    dep = tree[rs].d + 1;
    return x;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) fa[i] = i, tree[i].key = read();
    int m = read(), x, y; tree[0].d = -1;
    while (m --) {
        char ch = getchar();
        for (; ch != 'K' && ch != 'M'; ch = getchar()) ;
        x = read();
        if (ch == 'M') {
            y = read();
            if (vis[x] || vis[y]) continue;
            int _ = find(x), __ = find(y);
            if (_ == __) continue;
            fa[_] = fa[__] = merge(_, __);
        }
        else {
            if (vis[x]) {
                puts("0");
                continue;
            }
            int p = find(x);
            printf("%d\n", tree[p].key); vis[p] = true;
            fa[p] = merge(tree[p].l, tree[p].r); fa[fa[p]] = fa[p];
        }
    }
    return 0;
}