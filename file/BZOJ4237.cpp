# include <bits/stdc++.h> 
typedef long long ll;
const int MAXN = 2e5 + 5;
int n;  ll Ans;


char sb[1 << 15], *S = sb, *T = sb;
# define gc (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
inline int read() {
    register int x = 0, f = 1; char ch = gc;
    for (; !isdigit(ch); ch = gc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = gc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int x, y;
    inline bool operator < (const Point &a) const { return x == a.x ? y < a.y : x < a.x; }
}pt[MAXN], q[MAXN], t[MAXN], p[MAXN];

inline bool cmp(Point a, Point b) {
    return a.y < b.y;
}

inline void CDQ(int l, int r) {
    if (l == r) return ;
    register int mid = (l + r) >> 1, top1 = 0, top2 = 0, zz = l;
    for (int i = l; i <= r; ++i) t[i] = pt[i];
    std::sort(&t[l], &t[mid + 1], cmp);
    std::sort(&t[mid + 1], &t[r + 1], cmp);
    q[0].x = q[0].y = -0x7fffffff;
    for (int i = mid + 1; i <= r; ++i) { 
        while (zz <= mid && t[zz].y < t[i].y) {
            while (top1 && p[top1].x <= t[zz].x) -- top1;
            p[++top1] = t[zz]; ++ zz;
        }
        while (top2 && q[top2].x > t[i].x) -- top2;
        q[++top2] = t[i];
        int Ans1 = std::lower_bound(&p[1], &p[top1 + 1], q[top2], cmp) - p, 
            Ans2 = std::lower_bound(&p[1], &p[top1 + 1], q[top2 - 1], cmp) - p;
        Ans += std::max(Ans1 - Ans2, 0);
    }
    CDQ(l, mid), CDQ(mid + 1, r);
}

int main() {
    n = read(); 
    for (int i = 1; i <= n; ++i) pt[i].x = read(), pt[i].y = read();
    std::sort(&pt[1], &pt[n + 1]);
    CDQ(1, n);
    printf("%lld\n", Ans);
    return 0;
}