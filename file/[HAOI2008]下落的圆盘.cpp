#pragma GCC optimize("O3")
#include <math.h>
#include <stdio.h>
#include <algorithm>
const double PI = acos(-1.0);
#define MAXN 1005
int n,cnt; double r[MAXN],x[MAXN],y[MAXN];


struct Seg{
    double l,r;
    inline bool operator < (const Seg & a) const {
        return l == a.l?r < a.r : l < a.l;
    }
}a[MAXN*MAXN];

inline double dis(double x0,double y0,double x1,double y1) {
    return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

inline double Work(){
    double Ans = 0.0,last = -PI;
    std::sort(&a[1],&a[cnt+1]);
    for (int i = 1;i<=cnt;i++) {
        if (a[i].l < last && last < a[i].r) Ans += a[i].r - last;
        if (a[i].l >= last) Ans += a[i].r - a[i].l;
        if (a[i].r > last) last = a[i].r;
    }
    return Ans;
}

inline void Calc(){
    double alpha,beta,up,down,Ans = 0.0;
    for (int i = 1;i<=n;i++) {
        bool no_len = false; cnt = 0;
        for (int j = i + 1;j<=n;j++) {
            double d = dis(x[i],y[i],x[j],y[j]);
            if (d > r[i] + r[j]) continue;
            if (d + r[i] < r[j]) {no_len = true; break;}
            if (d + r[j] < r[i]) continue;
            alpha = atan2(x[i] - x[j],y[i] - y[j]);
            beta = acos((r[i] * r[i] + d * d - r[j] * r[j])/(2.0*d*r[i]));
            up = alpha + beta; down = alpha - beta;
            if (up > PI) a[++cnt] = (Seg){-PI,up - 2.0 * PI},up = PI;
            if (down < -PI) a[++cnt] = (Seg){down + 2.0 * PI,PI},down = - PI;
            a[++cnt] = (Seg){down,up};
        }
        if (no_len) continue;
        Ans += (2.0 * PI - Work()) * r[i];
    }
    printf("%.3f\n",Ans);
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++) scanf("%lf%lf%lf",&r[i],&x[i],&y[i]);
    Calc();
    return 0;
}