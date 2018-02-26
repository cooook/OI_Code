# include <math.h> 
# include <stdio.h>
# include <algorithm>
const int MAXN = 605;
const double eps = 1e-8;
int n, cnt, tot, Sum;
double heng1[MAXN], heng2[MAXN], all[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) {this -> x = x; this -> y = y;}
    inline double operator * (const Point &a) const {return x * a.y - y * a.x;}
    inline Point operator * (const double &a) const {return Point(x * a, y * a);}
    inline Point operator - (const Point &a) const {return Point(x - a.x, y - a.y);}
    inline Point operator + (const Point &a) const {return Point(x + a.x, y + a.y);}
    inline bool operator < (const Point &a) const {return x < a.x;}
    inline void Print() {
        printf("x=%f y=%f\n", x, y);
    }
}pt[MAXN];

inline int sgn(double a) {
    return (a > -eps) - (a < eps);
}

struct Line {
    Point a, b; double k;
    inline bool operator < (const Line &x) const {return k == x.k ? (x.b - a) * (b - a) > 0 : k < x.k;}
}t[MAXN], q[MAXN], hall[MAXN];

inline Point Get(Line a, Line b) {
    // (a.b-a.a).Print(); (b.b-b.a).Print();
    double S1 = (a.a-b.a)*(a.a-b.b), S2 = (a.b-b.b)*(a.b-b.a);
    double k = S1 / (S1 + S2);
    return (a.a + (a.b - a.a) * k);
}

inline bool Judge(Point x, Line y) {
    return sgn((y.a - x) * (y.b - x)) < 0;
}

inline void Work() {
    int L = 1, R = 0;
    q[++R] = t[1];
    q[++R] = t[2];
    for (int i = 3; i <= cnt; ++i) {
        while (L < R && Judge(Get(q[R], q[R - 1]), t[i])) -- R;
        while (L < R && Judge(Get(q[L], q[L + 1]), t[i])) ++ L;
        q[++R] = t[i];
    }
    while (L < R && Judge(Get(q[R], q[R - 1]), q[L])) -- R;
    cnt = 0;
    for (int i = L + 1; i <= R; ++i) {
        hall[++cnt] = (Line){Get(q[i], q[i - 1]), q[i].b - q[i].a, 233333};
        heng2[cnt] = hall[cnt].a.x;
    }
    hall[0] = (Line){Get(q[L], q[L + 1]), q[L].b - q[L].a, 233333};
}

inline void gmin(double &x, const double &y) {
    if (x > y) x = y;
}

inline double Up(double x) {
    int pos = std::upper_bound(&heng2[1], &heng2[cnt + 1], x) - heng2 - 1;
    // printf("%f\n", hall[pos].a.y);
    return (hall[pos].a.y + hall[pos].b.y / hall[pos].b.x * (x - hall[pos].a.x));
}

inline double Down(double x) {
    int pos = std::upper_bound(&heng1[1], &heng1[n], x) - heng1 - 1;
    // if (!pos)
    return t[pos].a.y + t[pos].b.y / t[pos].b.x * (x - t[pos].a.x);
}

inline bool cmp(const Line &a, const Line &b) {
    return a.a.x < b.a.x;
}

int main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    n = read();
    for (int i = 1; i <= n; ++i) pt[i].x = read();
    for (int i = 1; i <= n; ++i) pt[i].y = read();
    for (int i = 1; i < n; ++i) t[i].a = pt[i], t[i].b = pt[i + 1], t[i].k = atan2(t[i].b.y - t[i].a.y, t[i].b.x - t[i].a.x);
    std::sort(&t[1], &t[n]); t[0].k = 2333333333;
    for (int i = 1; i < n; ++i) if (t[i].k != t[i-1].k) t[++cnt] = t[i];
    Work();

    for (int i = 1; i < n; ++i) t[i].a = pt[i], t[i].b = pt[i + 1] - pt[i], heng1[i] = pt[i].x;

    for (int i = 1; i <= n; ++i) all[++tot] = pt[i].x;
    for (int i = 1; i <= cnt; ++i) all[++tot] = hall[i].a.x;
    std::sort(&all[1], &all[tot + 1]);
    tot = std::unique(&all[1], &all[tot + 1]) - all - 1;
    std::sort(&hall[1], &hall[cnt + 1], cmp);
    std::sort(&heng2[1], &heng2[cnt + 1]);

    double Ans = 1e18;

    for (int i = 1; i <= tot; ++i)
        if(all[i] >= pt[1].x && all[i] <= pt[n].x)
            gmin(Ans, Up(all[i]) - Down(all[i]));

    printf("%.3f\n", Ans);
    return 0;
}