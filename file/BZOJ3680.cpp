#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
#define FIRE(x) (x *= 0.98)
using namespace std;
typedef long long ll;
const int N = 10005;
const double inf = 1e17;
const double PI = acos(-1.0);
const double eps = 1e-3;
struct Point{
    double x, y, w;
    Point(){}
    Point(double _x, double _y):x(_x), y(_y) {}
    Point operator -(const Point &b)const{
        return Point(x - b.x,y - b.y);
    }
    double operator *(const Point &b)const{
        return x*b.x + y*b.y;
    }
}now, ans, po[N];
double dist(Point a, Point b) {return sqrt((a-b)*(a-b));}
int n;
double tot = inf;
double statistic(Point p) {
    double res = 0.0;
    for(int i = 0; i < n; ++i) res += dist(p, po[i]) * po[i].w;
    if(res < tot) tot = res, ans = p;
    return res;
}
double Rand() {return (rand()%1000 + 1) / 1000.0;}
void SA(double T) {
    double alpha, sub;
    while(T > eps) {
        alpha = 2.0 * PI * Rand();
        Point t(now.x + T * cos(alpha), now.y + T * sin(alpha));
        sub = statistic(now) - statistic(t);
        if(sub >= 0 || exp(sub / T) >= Rand()) now = t;
        FIRE(T);
    }
    T = 0.001;
    for(int i = 1; i <= 1000; ++i) {
        alpha = 2.0 * PI * Rand();
        Point t(ans.x + T * cos(alpha) * Rand(), ans.y + T * sin(alpha) * Rand());
        statistic(t);
    }
}
int main(){
    srand(123456);
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%lf%lf%lf", &po[i].x, &po[i].y, &po[i].w);
        now.x += po[i].x;   now.y += po[i].y;
    }
    now.x /= n; now.y /= n;
    double T = 1000.0;
    SA(T);
    printf("%.3f %.3f\n", ans.x, ans.y);
    return 0;
}