#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
typedef long long ll;
#define MAXN 35
int n,m,a[MAXN][MAXN],f[MAXN][MAXN],T,g[MAXN][MAXN];
ll Ans;


template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return  x * f;
}

inline void dfs(int x,int y,ll f_val,ll g_val) {
    if (x > n || y > m) return;
    if (x == n && y == m) {
        f_val += a[x][y] * a[x][y];
        g_val += a[x][y];
        Ans = std::min(Ans,f_val * (n + m - 1) - g_val * g_val);
        return;
    }
    dfs(x + 1,y,f_val + a[x][y] * a[x][y],g_val + a[x][y]);
    dfs(x,y + 1,f_val + a[x][y] * a[x][y],g_val + a[x][y]);
}

int main() {
    // freopen("in.in","r",stdin);
    
    T = read<int>();

    while (T --) {
        n = read<int>(); m = read<int>();
        // memset(f,0x3f,sizeof f);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] = read<int>();
        // (n + m - 1) * 平方的和 - 和的平方最小
        Ans = 0x3f3f3f3f3f3fll;
        dfs(1,1,0,0);
        printf("%lld\n",Ans);
    }

    // while (true);

    return 0;
}