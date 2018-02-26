# include <stdio.h> 
# include <algorithm>
const int MAXN = 5e5+5;
int n, top, Ans[MAXN], Down[MAXN]; 
bool vis[MAXN]; 


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int d[2];
    Point(){}
    Point(int x, int y) {d[0] = x; d[1] = y;}
    inline int& operator [] (const int &x) {return d[x];}
    inline int operator * (const Point &x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
    inline bool operator < (const Point &x) const {return d[0] == x.d[0] ? d[1] < x.d[1] : d[0] < x.d[0];}
    inline Point operator - (const Point &x) const {return Point(d[0] - x.d[0], d[1] - x.d[1]);} 
}pt[MAXN];

inline int dis(Point x, Point y) { 
    return (x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]);
}

inline void gmax(int &x, const int &y) {
    if (x < y) x = y;
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i) pt[i][0] = read(), pt[i][1] = read();
    if (n == 2) return printf("%d\n", dis(pt[1], pt[2])), 0;
    std::sort(&pt[1], &pt[n + 1]);

    for (int i = 1; i <= n; Ans[++top] = i, ++i)
        while (top > 1 && (pt[Ans[top]] - pt[Ans[top - 1]]) * (pt[i] - pt[Ans[top - 1]]) <= 0) -- top; 
    for (int i = 1; i <= top; ++i) vis[Ans[i]] = true;

    int t = 0;

    for (int i = n; i; Down[++t] = i, --i) 
        while (t > 1 && (pt[Down[t]] - pt[Down[t - 1]]) * (pt[i] - pt[Down[t - 1]]) <= 0) -- t;

    for (int i = 1; i <= t; ++i) if (!vis[Down[i]]) Ans[++top] = Down[i], vis[Down[i]] = true;

    int j = 2; Ans[top + 1] = Ans[1];

    int res = 0;
    
    for (int i = 1; i <= top; ++i) {
        while ((pt[Ans[i + 1]] - pt[Ans[i]]) * (pt[Ans[j + 1]] - pt[Ans[i]]) > (pt[Ans[i + 1]] - pt[Ans[i]]) * (pt[Ans[j]] - pt[Ans[i]])) 
            j = (j == top) ? 1 : j + 1;
        gmax(res, dis(pt[Ans[i]], pt[Ans[j]]));
    }
    
    printf("%d\n", res);
    return 0;  
}