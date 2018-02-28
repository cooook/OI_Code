# include <bits/stdc++.h>
const int mod = 1e9 + 7;
const int MAXN = 4005;
int f[MAXN][MAXN], n; 


int main() {
    scanf("%d", &n);
    int Ans = 0;
    f[1][1] = 1; 
    for (int i = 2; i <= n; ++i) {
        f[i][1] = 1;
        for (int j = 2; j <= i; ++j)
            f[i][j] = (f[i - 1][j - 1] + 1ll * f[i - 1][j] * j % mod) % mod;
    }
    for (int i = 1; i <= n; ++i) (Ans += 1ll * i * f[n][i] % mod) %= mod;
    printf("%d\n", Ans);
    return 0;
}