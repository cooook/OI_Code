# pragma GCC optimize("O3")
# include <stdio.h> 
# include <cstring> 
int n, k, mod; 
char s[105]; 


struct matrix {
    int a[105][105]; 
    matrix() { clear(); }
    inline void clear() { memset(a, 0, sizeof a); }
    inline matrix operator * (const matrix &x) const {
        matrix Ans;
        for (int i = 1; i <= n; ++i)    
            for (int k = 1; k <= n; ++k) if (a[i][k])
                for (int j = 1; j <= n; ++j) if (x.a[k][j])
                    (Ans.a[i][j] += 1ll * a[i][k] * x.a[k][j] % mod) %= mod;
        return Ans; 
    }

    inline friend matrix operator + (matrix x, matrix y) {
        matrix Ans; 
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                Ans.a[i][j] = (x.a[i][j] + y.a[i][j]) % mod;
        return Ans; 
    } 
}mul, res, power;

inline void Quick_Power(int n) {
    if (n == 1) return res = mul, power = mul, void();  
    Quick_Power(n >> 1);
    res = res + res * power;
    power = power * power; 
    if (n & 1) power = power * mul, res = res + power;
}

int main() {
    // freopen("T3.in","r",stdin);
    // freopen("T3.out","w",stdout);
    scanf("%d", &n); 
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; s[j]; ++j)
            mul.a[i][j] = s[j] == 'Y';
    }
    scanf("%d%d", &k, &mod); 
    int Ans = 0;
    Quick_Power(k - 1);
    for (int i = 1; i <= n; ++i)
        (Ans += res.a[i][i]) %= mod;
    printf("%d\n", Ans);
    // while (true);
    return 0; 
}

// n ^ 2 