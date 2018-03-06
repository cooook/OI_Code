# include <set>
# include <map>
# include <time.h>
# include <math.h> 
# include <stdio.h>
# include <cstring>
# include <stdlib.h>
# include <iostream>
# include <algorithm>
const int MAXN = 505; 
const double eps = 1e-5; 
int n; double alpha, h[MAXN], r[MAXN]; 


struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0):x(x), y(y) {  }
};

struct Circle {
    double x, r; 
    inline double F(double a) {
        double delta = fabs(a - x);
        if (delta > r) return 0;
        return sqrt(r * r - delta * delta);
    }
}c[MAXN];

struct Line {
    Point st, end; 
    inline double F(double a) {
        if (a < st.x || a > end.x) return 0;
        return st.y + (end.y - st.y) / (end.x - st.x) * (a - st.x); 
    }
}l[MAXN];

inline double F(double x) {
    double Ans = 0;
    for (int i = 1; i <= n + 1; ++i)
        Ans = std::max(Ans, c[i].F(x));
    for (int i = 1; i <= n; ++i)
        Ans = std::max(Ans, l[i].F(x));
    return Ans;
}

inline double simpson(double l, double r, double L, double R, double mid) {
    return (r - l) / 6 * (L + 4 * mid + R); 
}

inline double Simpson(double l, double r, double mid, double S, double fl, double fr, double fm) {
    double lm = (l + mid) / 2, rm = (mid + r) / 2, flm = F(lm), frm = F(rm), L = simpson(l, mid, fl, fm, flm), R = simpson(mid, r, fm, fr, frm);
    if (fabs(L + R - S) < eps) return L + R;
    else return Simpson(l, mid, lm, L, fl, fm, flm) + Simpson(mid, r, rm, R, fm, fr, frm); 
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    scanf("%d%lf", &n, &alpha);
    double K = 1.0 / tan(alpha), mx = -1e9, mn = 1e9;
    for (int i = 1; i <= n + 1; ++i)
        scanf("%lf", &h[i]), h[i] += h[i - 1];
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &r[i]); 
    for (int i = 1; i <= n + 1; ++i)
        c[i] = (Circle){h[i] * K, r[i]}, 
        mn = std::min(mn, c[i].x - c[i].r), mx = std::max(mx, c[i].x + c[i].r);
    for (int i = 1; i <= n; ++i) {
        double delta_r = c[i + 1].r - c[i].r, delta_x = c[i + 1].x - c[i].x, rate = delta_r / delta_x;
        l[i].st.x = rate * c[i].r; l[i].st.y = sqrt(c[i].r * c[i].r - l[i].st.x * l[i].st.x);
        l[i].end.x = rate * c[i + 1].r; l[i].end.y = sqrt(c[i + 1].r * c[i + 1].r - l[i].end.x * l[i].end.x);
        l[i].st.x = c[i].x - l[i].st.x; l[i].end.x = c[i + 1].x - l[i].end.x;
    }
    double fl = F(mn), fr = F(mx), fm = F((mn + mx) / 2); 
    printf("%.2f\n", Simpson(mn, mx, (mn + mx) / 2, simpson(mn, mx, fl, fr, fm), F(mn), F(mx), F((mn + mx) / 2)) * 2);
    return 0;
}