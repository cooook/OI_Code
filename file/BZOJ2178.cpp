# include <bits/stdc++.h>
const int MAXN = 1005;
const double eps = 1e-13;
int n;  
bool Not_Use[MAXN]; 


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int sgn(double x) {
    return (x > -eps) - (x < eps); 
}

struct Point {
    double x, y;
    inline bool operator < (const Point &a) const {
        return x == a.x ? y < a.y : x < a.x; 
    }
};

template <typename _t>
inline _t sqr(_t x) {
    return x * x;
}

inline double dis(Point a, Point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); 
}

struct Circle {
    Point pt;  int r; 
}c[MAXN];

inline bool Judge_In(Circle a, Circle b) {
    if (sgn(a.pt.x - b.pt.x) && sgn(a.pt.y - b.pt.y) && sgn(a.r - b.r)) return false; 
    register double Dis = dis(a.pt, b.pt);
    if (sgn(a.r + Dis - b.r) < 0) return true;
    return false;
}

inline double F(double x) {
    double Ans = 0.0; int cnt = 0;
    static Point line[MAXN]; 
    for (int i = 1; i <= n; ++i) {
        if (sgn(fabs(x - c[i].pt.x) - c[i].r) > 0) continue; 
        double delta = fabs(x - c[i].pt.x), Len = sqrt(sqr(c[i].r) - sqr(delta));
        line[++cnt] = (Point){c[i].pt.y - Len, c[i].pt.y + Len};
    }
    if (!cnt) return 0.0;
    std::sort(&line[1], &line[cnt + 1]);
    double last = -2001;
    for (int i = 1; i <= cnt; ++i) {
        Ans += std::max(0.0, line[i].y - std::max(last, line[i].x));
        last = std::max(last, line[i].y);
    }
    return Ans; 
}

inline double simpson(double l, double r, double L, double R, double Mid) {
    return (r - l) / 6 * (L + R + 4 * Mid); 
}

inline double Simpson(double l, double r, double mid, double A, double Left, double Right, double Mid) {
    register double Lmid = (l + mid) / 2, Rmid = (mid + r) / 2, FL = F(Lmid), FR = F(Rmid);
    register double L = simpson(l, mid, Left, Mid, FL), R = simpson(mid, r, Mid, Right, FR);
    if (fabs(L + R - A) <= eps) return L + R;
    return Simpson(l, mid, Lmid, L, Left, Mid, FL) + Simpson(mid, r, Rmid, R, Mid, Right, FR); 
}

int main() {
    // freopen("BZOJ.in", "r", stdin);
    n = read(); 
    for (int i = 1; i <= n; ++i) c[i].pt.x = read(), c[i].pt.y = read(), c[i].r = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (Judge_In(c[i], c[j])) { Not_Use[i] = true; break; }
        }
    static Circle tmp[MAXN];
    int cnt = 0; 
    double mn = 2000, mx = -2000;
    for (int i = 1; i <= n; ++i) if (!Not_Use[i]) tmp[++cnt] = c[i], mn = std::min(mn, c[i].pt.x - c[i].r), mx = std::max(mx, c[i].pt.x + c[i].r);
    n = cnt; 
    for (int i = 1; i <= n; ++i) c[i] = tmp[i];
    double Left = F(mn), Right = F(mx), Mid = F((mn + mx) / 2.0);
    printf("%.3f\n", Simpson(mn, mx, (mn + mx) / 2.0, simpson(mn, mx, Left, Right, Mid), Left, Right, Mid));
    // printf("%d\n", clock());
    // while (true); 
    return 0;
}