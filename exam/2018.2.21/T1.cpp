# include <bits/stdc++.h> 
const int mod = 1e9 + 7;
int n, k, N, f[5];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct matrix {
    int a[5][5];
    matrix() { memset(a, 0, sizeof a); }
    inline matrix operator * (matrix b) {
        matrix Ans;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                for (int k = 1; k <= N; ++k)
                    (Ans.a[i][j] += 1ll * a[i][k] * b.a[k][j] % mod) %= mod;
        return Ans;
    }
    inline friend void operator *= (matrix &a, matrix b) { a = a * b; }
    inline friend matrix operator ^ (matrix a, int k) {
        matrix Ans; for (int i = 1; i <= N; ++i) Ans.a[i][i] = 1;
        for (; k; k >>= 1, a *= a)
            if (k & 1) Ans *= a;
        return Ans;
    }
}mul;

inline void Work() {
    int S1, S2, S3;
    if (n <= 2) S1 = n - 2 < 0 ? 0 : f[n - 2], S2 = n - 1 < 0 ? 0 : f[n - 1], S3 = n - 1 < 0 ? 0 : f[n];
    else {
        matrix fib; fib.a[1][1] = 1; N = 3;
        fib *= mul ^ (n - 2); S1 = fib.a[1][3];
        fib *= mul; S2 = fib.a[1][3];
        fib *= mul; S3 = fib.a[1][3];
    }
    matrix c, Ans; N = 2;
    c.a[1][1] = (S1 + 1) % mod; c.a[2][1] = S2; c.a[1][2] = S2; c.a[2][2] = S3;
    Ans.a[1][1] = Ans.a[1][2] = 1;
    Ans *= c ^ k;
    printf("%d\n", Ans.a[1][1]);
}

int main() {
    mul.a[1][1] = mul.a[1][2] = mul.a[2][1] = mul.a[1][3] = mul.a[3][3] = 1;
    f[0] = 0; f[1] = 1; f[2] = 2;
    int T = read();
    while (T --) {
        n = read(), k = read();
        Work(); 
    }
    return 0;
}