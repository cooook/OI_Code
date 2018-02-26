# include <math.h>
# include <stdio.h> 
# include <algorithm>
# define int long long 
const double eps = 0;
const int MAXN = 200005;
int n, cnt;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    double x, y;
};

struct Line { // ax + by + c >= 0
    double a, b, c, k; int id;
    Line(double A = 0.0, double B = 0.0, double C = 0.0, double ID = 0.0) {
        a = A; b = B; c = C; id = ID;
        k = atan2(b, a);
    }
    inline bool operator < (const Line &x) const {
        return k == x.k ? c > x.c : k < x.k;
    }
}t[MAXN], q[MAXN];

inline int sgn(double x) {
    return (x > -eps) - (x < eps);
}

inline Point Get(Line a, Line b) {
    double w = a.a * b.b - a.b * b.a;
    return (Point){(a.b * b.c - a.c * b.b) / w, (a.c * b.a - a.a * b.c) / w};
}

inline bool Judge(Point a, Line b) {
    return sgn(b.a * a.x + b.b * a.y + b.c) < 0;
}

inline bool Judge(int id) {
    int l = 1, r = 0, last = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (t[i].id > id) continue;
        if (t[i].k == t[last].k) continue;
        while (l < r && Judge(Get(q[r], q[r - 1]), t[i])) -- r;
        while (l < r && Judge(Get(q[l], q[l + 1]), t[i])) ++ l; 
        q[++r] = t[i]; last = i;
    }
    while (l < r && Judge(Get(q[r], q[r - 1]), q[l])) -- r;
    while (l < r && Judge(Get(q[l], q[l + 1]), q[r])) ++ l;
    return r - l > 1;
}

signed main() {
    n = read();
    t[++cnt] = Line(-1, 0, 0, 0); // a <= 0
    t[++cnt] = Line(0, 1, 0, 0);  // b >= 0
    for (int i = 1; i <= n; ++i) {
        register int x = read(), down = read(), up = read();
        t[++cnt] = Line(1ll * x * x, x, -down, i);
        t[++cnt] = Line(- 1ll * x * x, -x, up, i);
    }
    std::sort(&t[1], &t[cnt + 1]);
    t[0].k = 23333333333;
    int l = 1, r = n, mid, Ans = 0;
    while (l <= r) {
        mid = l + r >> 1;
        if (Judge(mid)) Ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%lld\n", Ans);
    return 0;
}