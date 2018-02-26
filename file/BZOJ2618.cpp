# include <bits/stdc++.h> 
const int MAXN = 3505;
int n, cnt, m;


struct Point {
    double x, y;
    inline double operator * (const Point &a) const {return x * a.y - y * a.x;}
    inline Point operator - (const Point &a) const {return (Point){x - a.x, y - a.y};}
    inline Point operator + (const Point &a) const {return (Point){x + a.x, y + a.y};}
    inline Point operator * (const double &a) const {return (Point){x * a, y * a};}
}pt[55], Ans[MAXN];

struct Line {
    Point a, b; double k;
    inline bool operator < (const Line &x) const { return k == x.k ? ((x.b - a) * (b - a) < 0) : k < x.k; }
}l[MAXN], t[MAXN];

inline void Init() {
    for (int i = 1; i <= cnt; ++i)
        l[i].k = atan2(l[i].b.y - l[i].a.y, l[i].b.x - l[i].a.x);
    std::sort(&l[1], &l[cnt + 1]);

    int sz = 0;

    for (int i = 1; i <= cnt; ++i) {
        if (l[i].k != l[i - 1].k) ++ sz;
        l[sz] = l[i];
    }

    cnt = sz;
}

inline bool Judge(Point x, Line y) {
    return (y.a - x) * (y.b - x) < 0;
}

inline Point Get(Line a, Line b) {
    double S1 = (a.a-b.a)*(a.a-b.b), S2 = (a.b-b.b)*(a.b-b.a);
    double k = S1 / (S1 + S2);
    return a.a + (a.b - a.a) * k;
}

inline void Solver() {
    int L = 1, R = 0;
    t[++R] = l[1]; t[++R] = l[2];
    for (int i = 3; i <= cnt; ++i) {
        while (L < R && Judge(Get(t[R], t[R - 1]), l[i])) -- R;
        while (L < R && Judge(Get(t[L], t[L + 1]), l[i])) ++ L;
        t[++ R] = l[i];
    }
    while (L < R && Judge(Get(t[R], t[R - 1]), t[L])) -- R;
    cnt = 0;
    for (int i = L; i < R; ++i) Ans[++cnt] = Get(t[i], t[i + 1]);
    Ans[++cnt] = Get(t[R], t[L]);
    double res = 0.0;
    for (int i = 1; i <= cnt; ++i)
        res += Ans[i] * Ans[i % cnt + 1];
    printf("%.3f\n", fabs(res / 2.0));
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &m);
        for (int j = 1; j <= m; ++j) {
            scanf("%lf%lf", &pt[j].x, &pt[j].y);
            if (j == 1) continue;
            l[++cnt].a = pt[j - 1];
            l[cnt].b = pt[j];
        }
        l[++cnt].a = pt[m];
        l[cnt].b = pt[1];
    }
    Init();
    Solver();
    return 0;
}