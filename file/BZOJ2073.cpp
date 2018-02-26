#include <stdio.h>
#include <iostream>
#include <cstring>
const int MAXN = 17;
int n,m,w[MAXN],t[MAXN],f[1<<17],full,sum[1<<17],mx[1<<17];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

int main() {
    memset(f,0x3f,sizeof f); f[0] = 0;
    m = read<int>(); n = read<int>(); full = 1 << n;
    for (int i = 1; i <= n; i++) t[i] = read<int>(),w[i] = read<int>();
    for (int i = 1; i < full; i++)
        for (int j = 1; j <= n; j++)
            if (i & (1 << j - 1))
                sum[i] += w[j],mx[i] = std::max(mx[i],t[j]);
    for (int i = 1; i < full; i++)
        for (int j = i; j; j = (j - 1) & i) 
            if (sum[j] <= m)
                f[i] = std::min(f[i],f[i^j]+mx[j]);
    printf("%d\n",f[full-1]);
    return 0;
}