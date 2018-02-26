#include <stdio.h>
#define int long long 
const int mod = 998244353;
int n,m,k,Ans,f[1005][1005],g[1005][1005];


template<typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

signed main () {
    freopen("city.in","r",stdin);
    freopen("city.out","w",stdout);
    n = read<int>(); m = read<int>(); k = read<int>();
    if (n > m) {printf("0\n"); return 0;}
    if ((long long) n * k < m) {printf("0\n"); return 0;}
    f[0][0] = 1;
    for (int i = 0; i <= m; i++) g[0][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            f[i][j] = ((long long)g[i-1][j - 1] - (j-k-1 >= 0?g[i-1][j - k - 1]:0)+mod)%mod;
            g[i][j] = ((long long)f[i][j] + g[i][j-1]) % mod;
        }
    printf("%lld\n",f[n][m]);
    return 0;
}