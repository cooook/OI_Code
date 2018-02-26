# include <math.h>
# include <stdio.h>
# include <algorithm>
const int MAXN = 505;
const double eps = 1e-16;
int n, u[MAXN], v[MAXN], w[MAXN], cnt;


struct Point {
    double x, y;
    inline void Print() {
        printf("(%f, %f)\n", x, y);
    }
    inline double operator * (const Point &a) const {return x * a.y - y * a.x;}
}st[MAXN];

inline int sgn(double x) {
    return (x > -eps) - (x < eps);
}

struct Line {
    double a, b, c, k; 
    Line(double A = 0.0, double B = 0.0, double C = 0.0) {
        a = A; b = B; c = C; 
        A = fabs(A);
        if (sgn(A) > 0) a /= A, b /= A, c /= A;
		k = atan2(b, a);
    }
    inline bool operator < (const Line &x) const { return k == x.k ? c < x.c : k < x.k; }
}t[MAXN], q[MAXN];

inline Point Get(Line a, Line b) {
    double x = a.a * b.b - b.a * a.b;
    if (sgn(x) == 0) return (Point){23333333.0, 666666666.0};
    return (Point){(a.b * b.c - b.b * a.c) / x, (a.c * b.a - b.c * a.a) / x};
}

inline bool Judge(Point a, Line b) {
    if (a.x == 23333333.0 && a.y == 666666666.0) return false; 
    return sgn(a.x * b.a + a.y * b.b + b.c) <= 0;
}

inline bool Work() {
    std::sort(&t[1], &t[cnt + 1]);
    int l = 1, r = 0; t[0].k = 23333333;
    for (int i = 1; i <= cnt; ++i) if (t[i].k != t[i - 1].k) {
        while (l < r && Judge(Get(q[r], q[r - 1]), t[i])) -- r;
        while (l < r && Judge(Get(q[l], q[l + 1]), t[i])) ++ l;
        q[++r] = t[i];
    }
    while (l < r && Judge(Get(q[r], q[r - 1]), q[l])) -- r;
    while (l < r && Judge(Get(q[l], q[l + 1]), q[r])) ++ l;    
    if (r - l <= 1) return false;
    double Ans = 0.0; int top = 0;
    for (int i = l; i < r; ++i) st[++top] = Get(q[i], q[i + 1]);
    st[++top] = Get(q[l], q[r]);
    for (int i = 1; i <= top; ++i) Ans += st[i % top + 1] * st[i];
    return sgn(fabs(Ans)) > 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &v[i], &u[i], &w[i]);
    for (int i = 1; i <= n; ++i) {
        cnt = 0;
        t[++cnt] = Line(1, 0, 0);  // a > 0
        t[++cnt] = Line(0, 1, 0);  // b > 0
        t[++cnt] = Line(-1, -1, 1); // a + b < 1
        for (int j = 1; j <= n; ++j) if (i != j) {
            double A = 10000.0 / v[i] - 10000.0 / v[j];
            double B = 10000.0 / u[i] - 10000.0 / u[j];
            double C = 10000.0 / w[i] - 10000.0 / w[j];
            t[++cnt] = Line(-(A - C), -(B - C), -C);
        }
        if (Work()) puts("Yes");
        else puts("No");
    }
    return 0;
}
