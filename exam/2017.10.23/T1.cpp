#pragma GCC optimize("O3")
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#define int long long
const int MAXN = 6015;
int fa[MAXN],n,m,k;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int find(int x) {
    return fa[x] == x?x:fa[x] = find(fa[x]);
}

struct Point{
    int d[2];
    inline int& operator [] (const int &x) {
        return d[x];
    }
    inline void in() {
        d[0] = read<int>(); d[1] = read<int>();
    }
    inline bool operator < (Point x) const {
        return d[0] == x[0] ? d[1] < x[1] : d[0] < x[0];
    }
}pt[MAXN];

inline double dis(Point x,Point y) {
    return (x[0]-y[0])*(x[0]-y[0]) + (x[1]-y[1])*(x[1]-y[1]);
}

inline bool Judge(double x) {
    double p = x * 2,D = p * p;
    for (int i = 1; i <= k + 2; i++)  fa[i] = i;
    for (register int i = 1; i <= k; i++) {
        if (pt[i][1] < p) fa[i] = k + 1;
        if (pt[i][1] + p > m) fa[i] = k + 2;
    }
    if (find(k + 1) == find(k + 2)) return false;
    for (register int i = 1; i <= k; i++)
        for (register int j = i + 1; j <= k; j++) {
            if (pt[j][0] - pt[i][0] >= p) break;
            register int fax = find(i),fay = find(j);
            if (fax == fay) continue;
            if (dis(pt[i],pt[j]) < D) fa[fax] = fay;
            if (find(k + 1) == find(k + 2)) return false;
        }
    return true;
}

signed main() {
    n = read<int>(); m = read<int>(); k = read<int>();
    for (int i = 1; i <= k; i++) pt[i].in();
    std::sort(&pt[1],&pt[k+1]);
    double l = 0.0, r = m / 2.0,mid,Ans;
    while (l + 1e-7 < r) {
        mid = (l + r) / 2.0;
        if (Judge(mid)) l = mid,Ans = mid;
        else r = mid;
    }
    printf("%.6lf\n",Ans);
    return 0;
}
