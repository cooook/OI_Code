# include <bits/stdc++.h> 
const int MAXN = 50005; 
int n, hight, T, pos[MAXN], tree[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct matrix {
    int x1, x2, w, id; 
    inline bool operator < (const matrix &x) const {
        return x1 == x.x1 ? x2 < x.x2 : x1 < x.x1; 
    }
}c[MAXN], d[MAXN]; 

# define lowbit(_) ((_) & (-_))

inline void gmax(register int &x, const register int &y) {
    if (x < y) x = y;
}

inline void Update(register int x, register int val) {
    for (; x <= n; x += lowbit(x)) gmax(tree[x], val);
}

inline int Query(register int x) {
    register int Ans = 0;
    for (; x; x -= lowbit(x))
        gmax(Ans, tree[x]);
    return Ans; 
}

int main() {
    T = read();
    while (T --) {
        memset(tree, 0, sizeof tree);
        n = read(), hight = read();
        register int y1, y2; 
        for (int i = 1; i <= n; ++i) {
            c[i].id = i;
            c[i].x1 = read(), y1 = read(), c[i].x2 = read(), y2 = read();
            c[i].w = abs(y1 - y2);
            if (c[i].x1 > c[i].x2) std::swap(c[i].x1, c[i].x2);
        }

        for (int i = 1; i <= n; ++i) {
            d[i].id = i;
            d[i].x1 = read(), y1 = read(), d[i].x2 = read(), y2 = read();
            d[i].w = abs(y1 - y2);
            if (d[i].x1 > d[i].x2) std::swap(d[i].x1, d[i].x2);
        }
        std::sort(&c[1], &c[n + 1]); std::sort(&d[1], &d[n + 1]);
        for (int i = 1; i <= n; ++i) pos[c[i].id] = i; 
        bool flag = true; 
        for (int i = n; i; --i) {
            if (Query(pos[d[i].id]) + d[i].w > hight) { flag = false; break; }
            Update(pos[d[i].id], d[i].w);
        }
        puts(flag ? "TAK" : "NIE"); 
    }
    return 0; 
}

/*
    没做出来太不应该了...  
    光纠结于如果两个东西的权值加起来大于怎么判断是不是在两侧...  
    其实只要处理在两侧的矩形的权值最大值和自己相加合不合法就可以了
    我真是太愚蠢了... 
*/