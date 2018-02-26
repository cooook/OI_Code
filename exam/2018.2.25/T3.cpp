# pragma GCC optimize("O3")
# include <cstring>
# include <stdio.h> 
const int mod = 10007;
const int MAXN = 205;
char s[MAXN];
int n, f[MAXN][MAXN][MAXN], N, m, n24, n25, Step; 


struct matrix {
    int a[MAXN << 1][MAXN << 1];
    matrix() { memset(a, 0, sizeof a); }
    inline friend matrix operator * (matrix a, matrix b) {
        matrix Ans; register int i, j, k;
        for (i = 1; i <= N; ++i) 
            for (k = 1; k <= N; ++k)    
                if (a.a[i][k])
                    for (j = 1; j <= N; ++j)
                        (Ans.a[i][j] += a.a[i][k] * b.a[k][j] % mod) %= mod;
        return Ans;
    }
    inline friend matrix operator ^ (matrix a, int k) {
        matrix Ans; for (int i = 1; i <= N; ++i) Ans.a[i][i] = 1;
        for (; k; k >>= 1, a = a * a)
            if (k & 1) Ans = Ans * a;
        return Ans;
    }
}mul;

inline void DP_Init() {
    register int i, j, Len, l, r, k;
    for (i = 1; i <= m; ++i)
        for (j = 1; j < i; ++j)
            f[i][j][0] = 1;
    for (i = 1; i <= m; ++i) f[i][i][0] = 1;
    for (Len = 2; Len <= m; ++Len) {
        for (l = 1; l + Len - 1 <= m; ++l) {
            r = l + Len - 1;
            for (k = 0; k < m; ++k)
                if (s[l] == s[r]) (f[l][r][k] += f[l + 1][r - 1][k]) %= mod;
                else (f[l][r][k + 1] += f[l + 1][r][k] + f[l][r - 1][k]) %= mod;
        }
    }
}

inline void Matrix_Init() {
    register int i; 
    N = n24 + n25 + n25; 
    for (i = 1; i <= n24; ++i) mul.a[i][i] = 24, mul.a[i][i + 1] = 1;
    for (i = 1; i <= n25; ++i) mul.a[i + n24][i + n24] = 25, mul.a[i + n24][i + 1 + n24] = i != n25;
    for (i = 1; i <= n25; ++i) mul.a[i + n24][i + n24 + n25] = 1, mul.a[i + n24 + n25][i + n24 + n25] = 26; 
    mul = mul ^ (Step);
}

int main() {
    scanf("%s%d", s + 1, &n); 
    m = strlen(s + 1); n += m; 
    n24 = m - 1, n25 = m + 1 >> 1, Step = n >> 1;
    DP_Init(); Matrix_Init(); 
    register int Ans = 0, pos1, pos2, num25, i;
    for (i = 0; i <= n24; ++i) {
        pos1 = n24 - i + 1, num25 = m - i + 1 >> 1, pos2 = n24 + n25 + num25;
        (Ans += f[1][m][i] * mul.a[pos1][pos2]) %= mod;
    }
    if (n & 1) {
        (Ans *= 26) %= mod;
        for (i = 0; i <= n24; ++i) {
            if (!((m - i) & 1)) continue;
            pos1 = n24 - i + 1, num25 = m - i + 1 >> 1, pos2 = n24 + num25;
            (Ans += f[1][m][i] * mul.a[pos1][pos2]) %= mod;
        }
    }
    printf("%d\n", Ans);
    return 0;
}