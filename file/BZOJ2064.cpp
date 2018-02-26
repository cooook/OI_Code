#include <bits/stdc++.h>
int a[25],f[1<<21],g[1<<21],n,m,i,j;
int main() {
    for (scanf("%d",&n),i = 1; i <= n; i++) scanf("%d",&a[i]);
    for (scanf("%d",&m),n += m; i <= n; i++) scanf("%d",&a[i]),a[i] = -a[i];
    for (i = 1; i < 1 << n; i++) {
        for (j = 1; j <= n; j++) if (i & (1 << j - 1)) break; g[i] = g[i^(1<<j-1)] + a[j];
        for (j = 1; j <= n; j++) if (i & (1 << j - 1)) f[i] = std::max(f[i^(1<<j-1)]+(!g[i]),f[i]);
    } return printf("%d\n",n-2*f[(1<<n)-1]), 0;
}