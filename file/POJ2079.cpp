# include <stdio.h> 
# include <cstring> 
# include <iostream>
# include <algorithm>
const int MAXN = 50005;
int n, st[MAXN], top, cnt;
bool vis[MAXN];


char sb[1 << 15], *S = sb, *T = sb;
# define gc() (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T) ? 0 : *S++)

inline int read() {
	register int x = 0, f = 1; char ch = gc();
	for (; !isdigit(ch); ch = gc()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ 48);
	return x * f;
}

struct Point {
	int x, y;
	Point() {}
	Point(int _, int __) {x = _; y = __;}
	inline int operator * (const Point &a) const {return x * a.y - y * a.x;}
	inline Point operator - (const Point &a) const {return Point(x - a.x, y - a.y);}
	inline bool operator < (const Point &a) const {return x == a.x ? y < a.y : x < a.x;}
} pt[MAXN], Ans[MAXN];	

inline void gmax(int &x, const int &y) {
	if (x < y) x = y;
}

inline int area(Point x, Point y, Point z) {
	return (y - x) * (z - x);
}

inline void Graham() {
	top = 0; cnt = 0;
	std::sort(&pt[1], &pt[n + 1]);
	for (int i = 1; i <= n; st[++top] = i, ++i)
		while (top > 1 && area(pt[st[top - 1]], pt[st[top]], pt[i]) <= 0) -- top; 
		
	for (int i = 1; i <= top; ++i) vis[st[i]] = true, Ans[++cnt] = pt[st[i]];
	
	top = 0;
	
	for (int i = n; i; st[++top] = i, --i)
		while (top > 1 && area(pt[st[top - 1]], pt[st[top]], pt[i]) <= 0) -- top;
		
	for (int i = 1; i <= top; ++i) if (!vis[st[i]]) Ans[++cnt] = pt[st[i]];
	
	Ans[top + 1] = Ans[1];
}

inline void Rotate() {
	int res = 0, l, r;
	for (int i = 1; i <= cnt; ++i) {
		l = i + 1, r = i + 1;
		for (int j = i + 1; j <= cnt; ++j) {
			while (area(Ans[i], Ans[j], Ans[l + 1]) > area(Ans[i], Ans[j], Ans[l])) ++ (l %= cnt);
			while (area(Ans[j], Ans[i], Ans[r + 1]) > area(Ans[j], Ans[i], Ans[r])) ++ (r %= cnt);
			gmax(res, area(Ans[i], Ans[j], Ans[l]));
			gmax(res, area(Ans[j], Ans[i], Ans[r]));
		}
	}
	printf("%.2f\n", 1.0 * res / 2.0);
}

int main() {
	while ((n = read()) > 0) {
		for (int i = 1; i <= n; ++i) pt[i].x = read(), pt[i].y = read();
		memset(vis, 0, (n + 3) << 2);
		Graham();
		Rotate();
	}
	return 0;
}
