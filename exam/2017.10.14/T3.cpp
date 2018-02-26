#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define int long long 
#define MAXN 1000005
int prime[MAXN],mn[MAXN],g[5005][5005],f[2][5005],now,last,n,m,p,C[5005],cnt,size[MAXN],a[MAXN],mx;
bool _prime[MAXN];
 
 
template <typename _t>
inline _t read() {
    register _t x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline void G_prime() {
    for (int i = 2; i <= m; i++) {
        if (!_prime[i]) prime[++cnt] = i,mn[i] = cnt;
        for (int j = 1; prime[j] * i <= m; j++) {
            _prime[i*prime[j]] = true,mn[i*prime[j]] = j;
            if (i % prime[j] == 0) break;
        }
    }
}
 
inline void Update(int x,int type) {
    while (mn[x]) size[mn[x]] += type, x /= prime[mn[x]];
}
 
inline int Query() {
    int Ans = 1,tmp;
    for (int i = 1; i <= cnt; i++) {
        tmp = size[i];
        while (tmp--) (Ans *= prime[i]) %= p;
    }
    return Ans;
}
 
signed main() {
    n = read<int>(); m = read<int>(); p = read<int>(); G_prime();
    for (int i = 1; i <= n; i++) a[i] = read<int>(),mx = a[i] > mx?a[i]:mx;
    for (int i = 1; i <= m && i <= mx; i++) Update(m-i+1,1),Update(i,-1),C[i] = Query();
    g[1][1] = 1;
    for (int i = 2; i <= mx; i++)
        for (int j = 2; j <= i && j <= mx; j++) g[i][j] = (g[i-1][j-1] * j % p + g[i-1][j] * (j - 1) % p) % p;
    now = 1,last = 0;
    f[last][0] = 1; C[0] = 1;
    for (int i = 1; i <= n; i++,now ^= 1,last ^= 1) {
        f[now][0] = 0;
        if (a[i] == 1) f[now][0] = f[now][1] = (f[last][0] * m % p - (a[i-1] == 1?f[last][1]:0) + p) % p;
        else for (int j = 2; j <= m && j <= a[i]; j++)
            f[now][j] = ((f[last][0] * C[j] % p * g[a[i]][j] % p - (a[i-1] >= j?f[last][j] * g[a[i]][j] % p:0)) + p) % p,
            (f[now][0] += f[now][j]) %= p;
    }
    return printf("%lld\n",f[last][0]), 0;
}