# include <math.h> 
# include <stdio.h>
# include <algorithm> 
# define int long long 
const int MAXN = 1e6 + 5;
int n, top;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int d[2];
    inline int& operator [] (const int &x) {return d[x];}
    inline int operator * (const Point &x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
    inline Point operator - (const Point &x) const {return (Point){d[0] - x.d[0], d[1] - x.d[1]};}
    inline bool operator < (const Point &x) const {return d[0] == x.d[0] ? d[1] > x.d[1] : d[0] < x.d[0];}
} pt[MAXN], Ans[MAXN];

inline double K(Point x, Point y) {
    return (x[1] - y[1]) / 1.0 / (x[0] - y[0]);
}

template <typename _t>
inline _t gmin(_t &x, const _t &y) {
    if (x > y) x = y;
    return x;
}

inline double Q(Point x, double k) {
    if (k == 0) return 1e18;
    return k * x[0] + x[1] / k + x[0] + x[1];
}

inline double Calc(int x) {
    double k1 = -(x == 1 ? 0 : K(Ans[x - 1], Ans[x])), k2 = -(x == top ? -1e9 : K(Ans[x], Ans[x + 1]));
    if (k1 > k2) return 1e18;
    double Min_Cost = sqrt(Ans[x][1] / 1.0 / Ans[x][0]);
    if (k1 <= Min_Cost && Min_Cost <= k2) return Q(Ans[x], Min_Cost);
    return std::min(Q(Ans[x], k1), Q(Ans[x], k2));
}

signed main() {
    n = read(); 
    for (int i = 1; i <= n; ++i) pt[i][0] = read(), pt[i][1] = read(); 
    std::sort(&pt[1], &pt[n + 1]);
    for (int i = 1; i <= n; Ans[++top] = pt[i], ++i)
        while (top > 1 && (Ans[top] - Ans[top - 1]) * (pt[i] - Ans[top - 1]) > 0) -- top; 
    double Ans = 1e18;
    for (int i = 1; i <= top; ++i) gmin(Ans, Calc(i));
    printf("%.4f\n", Ans);
    return 0;
}