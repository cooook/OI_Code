#include <stdio.h>
#include <cstring>
#include <math.h>
#include <iostream>
#define MAXN 1000005
int n,m; int r[MAXN],p[MAXN],s[MAXN];


template<typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

double f[1<<10];

inline double Calc(int S) {
    int ri = 0,pi = 0,si = 0,tot;
    for (int i = 1; i <= n; i++)
        if ((1<<i-1) & S) ri += r[i],pi += p[i],si += s[i];
    tot = ri + pi + si;
    double Ans = 0;
    Ans = std::max(Ans,ri * 3.0 / tot + pi * 1.0 / tot);
    Ans = std::max(Ans,pi * 3.0 / tot + si * 1.0 / tot);
    Ans = std::max(Ans,si * 3.0 / tot + ri * 1.0 / tot);
    return Ans;
}

inline void Solve() {
    int All = (1 << n) - 1,S;
    for (int i = 0; i < All; i++) f[i] = -1e9;
    for (int i = All; i; i--) {
        double tmp = Calc(i) + f[i];
        for (int j = 1; j <= n; j++)
            if ((1<<j-1) & i) S = i ^ (1 << j - 1),f[S] = std::max(f[S],tmp);
    }
    printf("%.12f\n",f[0]);
}

int main (){
    freopen("rps.in","r",stdin);
    freopen("rps.out","w",stdout);
    n = read<int>();
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        r[i] = read<int>();
        p[i] = read<int>();
        s[i] = read<int>();
        if (r[i] != r[i-1] && i != 1) flag = false;
        if (p[i] != p[i-1] && i != 1) flag = false;
        if (s[i] != s[i-1] && i != 1) flag = false;
    }
    if (n == 1 || flag) {
        double Ans = 0.0;
        Ans = std::max(Ans,r[1] / 100.0 + p[1] / 300.0);
        Ans = std::max(Ans,p[1] / 100.0 + s[1] / 300.0);
        Ans = std::max(Ans,s[1] / 100.0 + r[1] / 300.0);
        printf("%.12f\n",Ans * n);
        return 0;
    }
    if (n <= 10) Solve();
    return 0;
}