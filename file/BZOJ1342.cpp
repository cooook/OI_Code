# include <math.h> 
# include <stdio.h> 
# include <algorithm>
const double eps = 1e-10;
const int MAXN = 100005;
int n, cnt; 


inline int read() {
	int x = 0, f = 1; char ch = getchar();
	for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
	for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline int sgn(double x) {
    return (x > -eps) - (x < eps);
}

struct Point {
	double x, y;
};

struct Line { // ax + by + c >= 0
	double a, b, c, k; int id;
	Line(double A = 0.0, double B = 0.0, double C = 0.0, int ID = 0) {
		a = A; b = B; c = C; id = ID;
		A = fabs(A);
		if (A != 0) a /= A, b /= A, c /= A;
		k = atan2(b, a);
	} 
	inline bool operator < (const Line &x) const { return k == x.k ? c > x.c : k < x.k; }
}t[MAXN], q[MAXN];

inline Point Get(Line a, Line b) {
    double d = a.a * b.b - a.b * b.a;
    return (Point){(a.b * b.c - b.b * a.c) / d, (a.c * b.a - b.c * a.a) / d};
}

inline bool check(Point a, Line b) {
    return sgn(a.x * b.a + a.y * b.b + b.c) < 0;
}

inline bool Judge(int x) {
    int l = 1, r = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (t[i].id > x) continue;
        while (l < r && check(Get(q[r], q[r - 1]), t[i])) -- r;
        while (l < r && check(Get(q[l], q[l + 1]), t[i])) ++ l; 
    }
    while (l < r && check(Get(q[r], q[r - 1]), q[l])) -- r;
    while (l < r && check(Get(q[l], q[l + 1]), q[r])) ++ l;
    return r - l > 1;
} 

int main() {
    n = read();
    t[++cnt] = Line(0, 1, 0, 0);
    t[++cnt] = Line(-1, 0, 0, 0);
    for (int i = 1; i <= n; ++i) {
        register int x = read(), down = read(), up = read();
        t[++cnt] = Line(x * x, x, -down, i);
        t[++cnt] = Line(-x * x, - x, up, i);
    }
    std::sort(&t[1], &t[cnt + 1]);
    int l = 1, r = n, mid, Ans;
    while (l <= r) {
        mid = l + r >> 1;
        if (Judge(mid)) l = mid + 1, Ans = mid;
        else r = mid - 1;
    }
    printf("%d\n", Ans);
    getchar(); getchar();
	return 0;
}