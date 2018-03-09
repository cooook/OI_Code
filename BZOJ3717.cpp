# include <bits/stdc++.h> 
# define lowbit(_) ((_)&(-_))
const int inf = 0x3f3f3f3f; 
int n, m, a[25], c[105], f[1 << 24], g[1 << 24], val[1 << 24];


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), val[1 << i - 1] = a[i];
    for (int i = 1; i <= m; ++i) scanf("%d", &c[i]);
    std::sort(&c[1], &c[m + 1], std::greater<int>()); 
    memset(f, 0x3f, sizeof f); 
    f[0] = 1; g[0] = c[1];
    register int full = (1 << n) - 1, w, Mx;
    for (int i = 1; i <= full; ++i) {
        for (int j = i; j; j -= w) {
            w = lowbit(j);
            if (f[i ^ w] == inf) continue; 
            if (g[i ^ w] >= val[w]) {
                if (f[i] > f[i ^ w] || (f[i] == f[i ^ w] && g[i] < g[i ^ w] - val[w]))
                    f[i] = f[i ^ w], g[i] = g[i ^ w] - val[w]; 
            }
            else if (c[f[i ^ w] + 1] >= val[w]) {
                if (f[i] > f[i ^ w] + 1 || (f[i] == f[i ^ w] + 1 && g[i] < c[f[i ^ w] + 1] - val[w]))
                    f[i] = f[i ^ w] + 1, g[i] = c[f[i ^ w] + 1] - val[w];
            }
        }
    }
    if (f[full] == inf) puts("NIE");
    else printf("%d\n", f[full]);
    // while (true); 
    return 0;
}