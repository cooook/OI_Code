# include <bits/stdc++.h> 
const int MAXN = 1e5 + 5; 
int n, Ans[MAXN], mx; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int x, y, val, id; 
    inline bool operator < (const Point &a) const {
        return x < a.x; 
    }
}pt[MAXN];

inline bool cmp(const Point &a, const Point &b) {
    return a.y < b.y; 
}

int tree[1000005];
# define lowbit(_) (_&(-_))

inline int Sum(int x) {
    int Ans = 0;
    for (; x; x -= lowbit(x))  Ans += tree[x];
    return Ans;
}

inline void Update(int x, int val) {
    for (; x <= mx; x += lowbit(x)) tree[x] += val;
}

inline void CDQ(int l, int r) {
    if (l == r) return;
    static Point t[MAXN], Ql[MAXN], Qr[MAXN];
    register int mid = l + r >> 1, zz1, top1 = 0, top2 = 0;
    for (int i = l; i <= r; ++i) t[i] = pt[i];
    std::sort(&t[l], &t[mid + 1], cmp);
    std::sort(&t[mid + 1], &t[r + 1], cmp);
    zz1 = l;  Qr[0].y = 0;
    for (int i = mid + 1; i <= r; ++i) {
        while (zz1 <= mid && t[zz1].y < t[i].y) {
            while (top1 && Ql[top1].x <= t[zz1].x) Update(Ql[top1].y, -Ql[top1].val), -- top1;
            Ql[++top1] = t[zz1]; Update(t[zz1].y, t[zz1].val); ++ zz1;
        }
        while (top2 && Qr[top2].x > t[i].x) -- top2; 
        Qr[++top2] = t[i];
        Ans[t[i].id] += Sum(t[i].y) - Sum(Qr[top2 - 1].y);
    }
    for (; top1; --top1) Update(Ql[top1].y, -Ql[top1].val);
    CDQ(l, mid), CDQ(mid + 1, r); 
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read(); 
    for (int i = 1; i <= n; ++i)
        pt[i].x = read(), pt[i].y = read(), pt[i].val = read(), pt[i].id = i, mx = std::max(mx, pt[i].y);
    std::sort(&pt[1], &pt[n + 1]);
    CDQ(1, n);
    for (int i = 1; i <= n; ++i) printf("%d\n", Ans[i]);
    // while (true); 
    return 0; 
}