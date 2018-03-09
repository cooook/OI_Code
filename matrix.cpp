# include <bits/stdc++.h> 
const int MAXN = 1e5 + 5; 
int n, m, k, val[MAXN], a[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct matrix {
    int a[405][405];
    matrix() { clear(); }
    inline void clear() { memset(a, 0, sizeof a); }
    inline matrix operator * (const matrix &x) const {
        matrix Ans;  register int i, j, k; 
        for (i = 1; i <= n; ++i)
            for (k = 1; k <= n; ++k) if (a[i][k])
                for (j = 1; j <= n; ++j) if (x.a[k][j])
                    Ans.a[i][j] += a[i][k] * x.a[k][j];
        return Ans;
    }

    inline friend matrix operator ^ (matrix x, int k) {
        matrix Ans; for (int i = 1; i <= n; ++i) Ans.a[i][i] = 1;
        for (; k; k >>= 1, x = x * x)
            if (k & 1) Ans = Ans * x;
        return Ans; 
    }

    inline void Print() {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                printf("%02d%c", a[i][j], " \n"[j == n]);
    }
}mul, res, f;

int main() {
    freopen("frog2.in","r",stdin);
    freopen("frog.out","w",stdout);
    n = read();
    for (int i = 1; i <= n; ++i) val[i] = read(), f.a[1][i] = val[i];
    m = read(), k = read();
    for (int i = 1; i <= n; ++i) res.a[i][i] = 1;
    for (int i = 1; i <= m; ++i) {
        a[i] = read();
        mul.clear();
        for (int j = 1; j <= n; ++j) mul.a[j][j] = 1;
        mul.a[a[i] - 1][a[i]] = 1;
        mul.a[a[i]][a[i]] = -1;
        mul.a[a[i] + 1][a[i]] = 1;
        res = res * mul;
    }
    res.Print();
    // res = res ^ k;
    return 0; 
}