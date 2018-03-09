# include <stdio.h>
# include <cstring>  
const int mod = 10007; 
const int MAXN = 205; 
char s[MAXN]; int n, f[MAXN][MAXN][MAXN], n25, n24, All, m; 


struct matrix {
    int a[405][405];
    matrix() { clear(); }
    inline void clear() { memset(a, 0, sizeof a); }
    inline matrix operator * (const matrix &x) const {
        matrix Ans;  register int i, j, k; 
        for (i = 1; i <= All; ++i)
            for (k = 1; k <= All; ++k) if (a[i][k])
                for (j = 1; j <= All; ++j) if (x.a[k][j])
                    (Ans.a[i][j] += a[i][k] * x.a[k][j] % mod) %= mod;
        return Ans;
    }

    inline friend matrix operator ^ (matrix x, int k) {
        matrix Ans; for (int i = 1; i <= All; ++i) Ans.a[i][i] = 1;
        for (; k; k >>= 1, x = x * x)
            if (k & 1) Ans = Ans * x;
        return Ans; 
    }

    inline void Print() {
        for (int i = 1; i <= All; ++i)
            for (int j = 1; j <= All; ++j)
                printf("%d%c", a[i][j], " \n"[j == All]);
    }
}mul;

inline void Init() {
    for (int i = 1; i <= m; ++i)    
        for (int j = 1; j <= i; ++j)
            f[i][j][0] = 1;
    for (int len = 2; len <= m; ++len)
        for (int l = 1; l + len - 1 <= m; ++l) {
            register int r = l + len - 1;
            for (int k = 0; k < m; ++k)
                if (s[l] == s[r]) (f[l][r][k] += f[l + 1][r - 1][k]) %= mod;
                else (f[l][r][k + 1] += f[l + 1][r][k] + f[l][r - 1][k]) %= mod;
        }
}

inline void Matrix_Init() {
    All = n24 + n25 * 2; 
    for (int i = 1; i <= n24; ++i) {
        mul.a[i][i] = 24; 
        if (i != 1) mul.a[i - 1][i] = 1;
    }
    for (int i = 1; i <= n25; ++i) mul.a[i + n24][i + n24] = 25, mul.a[i + n24 - 1][i + n24] = 1;
    for (int i = 1; i <= n25; ++i) mul.a[i + n24 + n25][i + n24 + n25] = 26, mul.a[i + n24][i + n24 + n25] = 1; 
    mul = mul ^ (n >> 1); 
    // mul.Print();
}

int main() {
    // freopen("T3.in","r",stdin);
    // freopen("T3.out","w",stdout);
    scanf("%s%d", s + 1, &n); 
    m = strlen(s + 1); n += m; 
    n24 = m - 1, n25 = m + 1 >> 1;
    Init();  Matrix_Init(); 
    register int pos1, pos2, last, Ans = 0;
    for (int i = 0; i <= n24; ++i) {
        last = m - i; pos1 = n24 - i + 1; pos2 = n24 + n25 + (last + 1 >> 1);
        (Ans += f[1][m][i] * mul.a[pos1][pos2] % mod) %= mod; 
    }
    if (n & 1) {
        Ans = Ans * 26 % mod; 
        for (int i = 0; i <= n24; ++i) {
            last = m - i;
            if (!(last & 1)) continue; 
            pos1 = n24 - i + 1; pos2 = n24 + (last + 1 >> 1);
            (Ans += f[1][m][i] * mul.a[pos1][pos2] % mod) %= mod;
        }
    }
    printf("%d\n", Ans);
    // while (true); 
    return 0; 
}