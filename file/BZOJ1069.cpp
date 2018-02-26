# include <stdio.h> 
# include <algorithm>
const double eps = 1e-8;
const int MAXN = 2e3 + 5;
int n, st[MAXN], top, cnt;
bool vis[MAXN];


struct Point {
    double x, y;
    inline void read() {scanf("%lf%lf", &x, &y);}
    inline void print() {printf("%f %f\n", x, y);}
    inline double operator * (const Point &a) const {return x * a.y - y * a.x;}
    inline double operator / (const Point &a) const {return x * a.x + y * a.y;}
    inline Point operator / (const double &a) const {return (Point){x/a, y/a};}
    inline Point operator * (const double &a) const {return (Point){x*a, y*a};}
    inline bool operator < (const Point &a) const{return x == a.x?y<a.y:x<a.x;}
    inline Point operator - (const Point &a)const{return (Point){x-a.x,y-a.y};}
    inline Point operator + (const Point &a)const{return (Point){x+a.x,y+a.y};}
}pt[MAXN], Ans[MAXN];

inline int sgn(double t) {
    return (t > -eps) - (t < eps);
}

inline void Graham() {
    std::sort(&pt[1], &pt[n + 1]);
    for (int i = 1; i <= n; st[++top] = i, ++i)
    	while (top > 1 && sgn((pt[st[top]] - pt[st[top - 1]]) * (pt[i] - pt[st[top - 1]])) <= 0) -- top;
    for (int i = 1; i <= top; ++i) vis[st[i]] = true, Ans[++cnt] = pt[st[i]];
    
    top = 0;
    
    for (int i = n; i; st[++top] = i, --i)
    	while (top > 1 && sgn((pt[st[top]] - pt[st[top - 1]]) * (pt[i] - pt[st[top - 1]])) <= 0) -- top;
    for (int i = 1; i <= top; ++i) if (!vis[st[i]]) Ans[++cnt] = pt[st[i]];
    
    Ans[cnt + 1] = Ans[1]; 
}

inline void gmax(double &x, const double &y) {
	if (x < y) x = y;
}

inline double area(Point a, Point b, Point c) {
	return (b - a) * (c - a);
}

inline void Rotating() {
	register int l, r;
	double res = 0.0;
	for (int i = 1; i <= cnt; ++i) {
		l = i + 1, r = i + 1;
		for (int j = i + 1; j <= cnt; ++j) {
			while (sgn(area(Ans[i], Ans[j], Ans[l + 1]) - area(Ans[i], Ans[j], Ans[l])) > 0) l = l % cnt + 1;
			while (sgn(area(Ans[j], Ans[i], Ans[r + 1]) - area(Ans[j], Ans[i], Ans[r])) > 0) r = r % cnt + 1;
			gmax(res, area(Ans[i], Ans[j], Ans[l]) + area(Ans[j], Ans[i], Ans[r]));
		}
	}
	
	printf("%.3f\n", res / 2.0);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) pt[i].read(); 
    Graham();
    Rotating();
    return 0;
}
