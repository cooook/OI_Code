# include <bits/stdc++.h>
# define RG register  
const int MAXN = 1e5 + 5;
int fa[MAXN], n, id[MAXN], Mx, cnt;
bool Can_Union; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(RG int &x, const RG int &y) {
    if (x < y) x = y; 
}

struct matrix {
    int x1, x2, y1, y2;
    matrix(int x1 = 0, int x2 = 0, int y1 = 0, int y2 = 0): x1(x1), x2(x2), y1(y1), y2(y2) {  } 
    inline matrix operator + (const RG matrix &x) const {
        return matrix(std::min(x1, x.x1), std::max(x2, x.x2), std::min(y1, x.y1), std::max(y2, x.y2));
    }
    inline friend void operator += (RG matrix &x, const RG matrix &y) { x = x + y; }
    inline void read() { 
        x1 = ::read() + 1, x2 = ::read();
        y1 = ::read() + 1, y2 = ::read();
        gmax(Mx, x2);
    }
    inline bool operator < (const matrix &x) const {
        if (x1 == x.x1) {
            if (x2 == x.x2) {
                if (y1 == x.y1) return y2 < x.y2;
                return y1 < x.y1; 
            }
            return x2 < x.x2; 
        } return x1 < x.x1;
    }
}val[MAXN], Ans[MAXN];

inline int find(RG const int &x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

inline void Link(RG int x, RG int y) {
    if ((x = find(x)) == (y = find(y))) return ; 
    val[x] += val[y];  fa[y] = x;
    Can_Union = true; 
}

inline bool cmp(const RG int &x, const RG int &y) {
    return val[x].y2 == val[y].y2 ? val[x].y1 < val[y].y1 : val[x].y2 < val[y].y2; 
}

struct node {
    node *ls, *rs;
    std::vector<int> G[2]; 
    node() { ls = rs = NULL; }
} *root; 

inline void build(node *&o, RG int l, RG int r) {
    o = new node();
    if (l == r) return;
    register int mid = l + r >> 1;
    build(o -> ls, l, mid), build(o -> rs, mid + 1, r);
}

inline void Work1(node *o, RG int l, RG int r, RG int x, RG int y, const RG int &val) {
    if (x <= l && r <= y) {
        for (register int i = o -> G[1].size() - 1; ~i; --i) {
            register int t = o -> G[1][i]; 
            if (fa[t] != t || find(t) == find(val)) { o -> G[1].pop_back(); continue; }
            if (::val[t].y2 < ::val[val].y1) break;
            Link(val, t); o -> G[1].pop_back(); 
        }
        return ;
    }
    register int mid = l + r >> 1;
    if (x <= mid) Work1(o -> ls, l, mid, x, y, val);
    if (mid < y) Work1(o -> rs, mid + 1, r, x, y, val); 
}

inline void Work2(node *o, RG int l, RG int r, RG int x, const RG int &val) {
    for (RG int i = o -> G[0].size() - 1; ~i; --i) {
        RG int t = o -> G[0][i]; 
        if (fa[t] != t || find(t) == find(val)) { o -> G[0].pop_back(); continue; }
        if (::val[t].y2 < ::val[val].y1) break;
        Link(val, t); o -> G[0].pop_back();
    }
    if (l == r) return ;
    register int mid = l + r >> 1;
    if (x <= mid) Work2(o -> ls, l, mid, x, val);
    else Work2(o -> rs, mid + 1, r, x, val); 
}

inline void Update1(node *o, RG int l, RG int r, RG int x, RG int y, const RG int &val) {
    if (x <= l && r <= y) return o -> G[0].push_back(val), void(); 
    register int mid = l + r >> 1;
    if (x <= mid) Update1(o -> ls, l, mid, x, y, val);
    if (mid < y) Update1(o -> rs, mid + 1, r, x, y, val); 
}

inline void Update2(node *o, RG int l, RG int r, RG int x, const RG int &val) {
    o -> G[1].push_back(val);
    if (l == r) return ;
    register int mid = l + r >> 1;
    if (x <= mid) Update2(o -> ls, l, mid, x, val);
    else Update2(o -> rs, mid + 1, r, x, val); 
}

int main() {
    n = read();
    for (RG int i = 1; i <= n; ++i) fa[i] = id[i] = i, val[i].read(); 
    std::sort(&id[1], &id[n + 1], cmp); 
    build(root, 1, Mx); 
    for (RG int i = 1; i <= n; ++i) {
        Can_Union = true; 
        while (Can_Union) {
            Can_Union = false; 
            Work1(root, 1, Mx, val[id[i]].x1, val[id[i]].x2, id[i]);
            Work2(root, 1, Mx, val[id[i]].x1, id[i]);
            Work2(root, 1, Mx, val[id[i]].x2, id[i]); 
        }
        Update1(root, 1, Mx, val[id[i]].x1, val[id[i]].x2, id[i]);
        Update2(root, 1, Mx, val[id[i]].x1, id[i]);
        if (val[id[i]].x1 != val[id[i]].x2) Update2(root, 1, Mx, val[id[i]].x2, id[i]);
    }
    for (RG int i = 1; i <= n; ++i) if (fa[i] == i) Ans[++cnt] = val[i], -- Ans[cnt].x1, -- Ans[cnt].y1; 
    std::sort(&Ans[1], &Ans[cnt + 1]);
    printf("%d\n", cnt);
    for (RG int i = 1; i <= cnt; ++i)
        printf("%d %d %d %d\n", Ans[i].x1, Ans[i].x2, Ans[i].y1, Ans[i].y2);
    return 0; 
}

/**
 * 通过矩形的面积的并这一算法想到了按x坐标排序, 查询y坐标, 用并查集维护合并关系来做这一初始思路
 * 发现如果把矩形拆成上下两条直线的话不太可做, 并且也无法快速的维护和谁相交. 
 * CA爷的做法就显得非常暴力了, 就是在我的做法的基础上, 为了能维护和谁相交, 就对于线段树中每个节点开个vector, 虽然会有重的, 但是如果不计算也是没有关系的.
 * 这种做法的时间复杂度看起来非常玄学, 但是还是可以跑过的...  
 * 另一种做法貌似是榜首的做法, 没有很看懂是什么意思, 也不懂单调栈是谁单调..  
*/