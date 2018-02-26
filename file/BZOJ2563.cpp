#include <stdio.h>
#include <algorithm>
#define MAXN 10005
#define int long long
int n,m,val[MAXN],Ans;


template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

signed main() {
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= n; i++) val[i] = read<int>() << 1;
    for (int i = 1; i <= m; i++) {
        register int u = read<int>(),v = read<int>(),w = read<int>();
        val[u] += w; val[v] += w;
    }
    std::sort(&val[1],&val[n+1]);

    for (int i = n; i; i--) 
        if (i & 1) Ans -= val[i];
        else Ans += val[i];

    printf("%lld\n",Ans >> 1);

    return 0;
}