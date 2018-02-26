#include <map>
#include <stdio.h>
#include <iostream>
#define MAXN 100005
#define inf 0x3f3f3f3f
int n,a[MAXN],Ans = 1;
std::map<int,bool> ma;


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int gcd(int x,int y) {
    return !y?x:gcd(y,x%y);
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    int begin = a[1],d = inf; ma[a[1]] = true;
    for (int i = 2; i <= n; i++) {
        if (d == inf && abs(a[i] - begin) == 1) {
            ma.clear();
            ma[a[i]] = true;
            Ans ++;
            begin = a[i];
            d = inf;
            continue;
        }
        if ((d != inf && gcd(abs(a[i] - begin),d) == 1) || ma[a[i]]) {
            ma.clear();
            ma[a[i]] = true;
            Ans ++;
            begin = a[i];
            d = inf;
        }
        else {
            ma[a[i]] = true;
            if (d == inf) d = abs(a[i] - begin);
            else  d = gcd(abs(a[i] - begin),d);
            begin = std::min(begin,a[i]);
        }
    }
    printf("%d\n",Ans);
    // getchar(); getchar();
    return 0;
}