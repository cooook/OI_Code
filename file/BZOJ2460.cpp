#include <stdio.h>
#include <algorithm>
#define MAXN 1005
typedef long long ll;
int n; ll Ans,use[MAXN];


template<typename _t>
inline _t read(){
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-' ) f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct data{
    ll d[2];
    inline ll& operator [] (const int x) {return d[x];}
    inline bool operator < (const data &a)const {
        return d[1] > a.d[1];
    }
}a[MAXN];

inline bool Insert(ll x) {
    for (int i = 62;~i;i--) if (x >> i & 1) {
        if (!use[i]) {use[i] = x; return true;}
        x ^= use[i];
    }
    return false;
}

// 线性基

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) a[i][0] = read<ll>(),a[i][1] = read<ll>();
    std::sort(&a[1],&a[n+1]);
    for (int i = 1; i <= n; i++) if (Insert(a[i][0])) Ans += a[i][1];
    printf("%lld\n",Ans);
    return 0;
}