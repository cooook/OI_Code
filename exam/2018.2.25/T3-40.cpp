# pragma GCC optimize("O3")
# include <stdio.h>
# include <cstring>
# include <iostream>
const int MAXN = 205;
const int mod = 10007;
int f[3005][MAXN][MAXN], n, m;
char s[MAXN]; 


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void upd(int &a, const int &b) {
    a += b; if (a >= mod) a -= mod;
}

int main() {
    scanf("%s%d", s + 1, &n);
    n += (m = strlen(s + 1));
    f[0][0][m + 1] = 1;
    for (int i = 1; i <= n / 2; ++i) {
        for (int l = 0; l < m; ++l) 
            for (int r = m + 1; r > 1; --r) {
                if (s[l + 1] == s[r - 1]) 
                    upd(f[i][l + 1][r - 1], f[i - 1][l][r]),
                    upd(f[i][l][r], f[i - 1][l][r] * 25 % mod);
                else 
                    upd(f[i][l + 1][r], f[i - 1][l][r]), 
                    upd(f[i][l][r - 1], f[i - 1][l][r]),
                    upd(f[i][l][r], f[i - 1][l][r] * 24 % mod); 
            }
        for (int l = 0; l < m; ++l)
            upd(f[i][l + 1][1], f[i - 1][l][1]), 
            upd(f[i][l][1], 25 * f[i - 1][l][1] % mod);
        for (int r = m + 1; r > 1; --r)
            upd(f[i][m][r - 1], f[i - 1][m][r]),
            upd(f[i][m][r], 25 * f[i - 1][m][r] % mod);
        upd(f[i][m][1], 26 * f[i - 1][m][1] % mod);
    }
    int Ans = 0;
    for (int l = 0; l <= m; ++l)
        for (int r = 1; r <= l + 1; ++r)
            upd(Ans, f[n / 2][l][r]);
    printf("%d\n", Ans);
    if (n & 1) {
        Ans = 26 * Ans % mod;
        for (int i = 0; i < m; ++i)
            upd(Ans, f[n / 2][i][i + 2]); 
    }
    printf("%d\n", Ans);
    while (true);
    return 0;
}