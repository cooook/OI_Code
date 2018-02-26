# include <math.h>
# include <stdio.h> 
# include <algorithm>
const int MAXN = 5e4+5;
const double eps = 1e-10;
const double inf = 1e16;
int n, top, st[MAXN], cnt;
bool vis[MAXN];


struct Point {
    double d[2];
    Point () {d[0] = d[1] = 0.0;}
    Point (double _, double __) {d[0] = _; d[1] = __;}
    inline void read() {scanf("%lf%lf", &d[0], &d[1]);}
    inline void Print() {printf("%.5f %.5f\n", d[0], d[1]);}
    inline double& operator [] (const int &x) {return d[x];}
    inline Point operator * (const double &x) {return (Point){d[0] * x, d[1] * x};}
    inline double operator * (const Point &x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
    inline double operator / (const Point &x) const {return d[0] * x.d[0] + d[1] * x.d[1];}
    inline Point operator / (const double &x) const {return (Point){d[0] / x, d[1] / x};}
    inline Point operator + (const Point &x) const {return (Point) {d[0] + x.d[0], d[1] + x.d[1]};}
    inline Point operator - (const Point &x) const {return (Point) {d[0] - x.d[0], d[1] - x.d[1]};}
    inline bool operator < (const Point &x) const {return d[0] == x.d[0] ? d[1] < x.d[1] : d[0] < x.d[0];}
}pt[MAXN], hall[MAXN];

inline double dis(Point x, Point y) {
    return sqrt((x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]));
}

inline void Graham() {
    std::sort(&pt[1], &pt[n + 1]);
    top = 0; 
    for (int i = 1; i <= n; st[++top] = i, ++i)
        while (top > 1 && (pt[st[top]] - pt[st[top - 1]]) * (pt[i] - pt[st[top - 1]]) <= 0) -- top;
    for (int i = 1; i <= top; ++i) hall[++cnt] = pt[st[i]], vis[st[i]] = true; 

    top = 0;
    for (int i = n; i; st[++top] = i, --i)
        while (top > 1 && (pt[st[top]] - pt[st[top - 1]]) * (pt[i] - pt[st[top - 1]]) <= 0) -- top;
    for (int i = 1; i <= top; ++i) if (!vis[st[i]]) hall[++cnt] = pt[st[i]];

    hall[cnt + 1] = hall[1];
}

double Ans = inf; 
Point t[4];

inline int cmp(double t) {
    return (t > -eps) - (t < eps);
}

inline void Rotate_And_Calculate() {
    int l = 1, r = 1, h = 1;
    double Dis, L, R, hight;

    for (int i = 1; i <= cnt; ++i) {
        while (cmp((hall[i + 1] - hall[i]) * (hall[h + 1] - hall[i]) - (hall[i + 1] - hall[i]) * (hall[h] - hall[i])) >= 0) h = h % cnt + 1;
        while (cmp((hall[i + 1] - hall[i]) / (hall[r + 1] - hall[i]) - (hall[i + 1] - hall[i]) / (hall[r] - hall[i])) >= 0) r = r % cnt + 1;
        if (i == 1) l = r;
        while (cmp((hall[i + 1] - hall[i]) / (hall[l + 1] - hall[i]) - (hall[i + 1] - hall[i]) / (hall[l] - hall[i])) <= 0) l = l % cnt + 1; 
        
        Dis = dis(hall[i], hall[i + 1]);
        L = (hall[i] - hall[i + 1]) / (hall[l] - hall[i]) / Dis;
        R = (hall[i + 1] - hall[i]) / (hall[r] - hall[i]) / Dis;
        hight = fabs((hall[i + 1] - hall[i]) * (hall[h] - hall[i]) / Dis);

        if ((L + R) * hight < Ans) {
            Ans = (L + R) * hight;
            t[0] = hall[i] + (hall[i + 1] - hall[i]) / Dis * R;
            t[1] = t[0] + (hall[r] - t[0]) / dis(hall[r], t[0]) * hight;
            t[2] = t[1] + (hall[i] - hall[i + 1]) / Dis * (L + R);
            t[3] = t[0] + t[2] - t[1];
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) pt[i].read();
    Graham();
    Rotate_And_Calculate();

    printf("%.5f\n", Ans);

    int first_print_pos = 0;
    for (int i = 1; i < 4; ++i)
        if (cmp(t[first_print_pos][1] - t[i][1]) > 0)
            first_print_pos = i;
        else if (cmp(t[first_print_pos][1] - t[i][1]) == 0 && cmp(t[i][0] - t[first_print_pos][0]) < 0) 
            first_print_pos = i;
    for (int i = 0; i < 4; ++i) t[first_print_pos].Print(), (++ first_print_pos) %= 4;
    return 0;
}