# include <stdio.h> 
# include <cstring> 
# include <iostream>
const int inf = 0x3f3f3f3f;
int n, m; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
}

struct matrix {
    int a[305][305];
    matrix() { Init(); }
    inline void Init() { memset(a, 0x3f, sizeof a); }
    inline friend matrix operator * (const matrix &a, const matrix &b) {
        matrix Ans;  register int i, j, k;
        for (i = 1; i <= n; ++i)
            for (k = 1; k <= n; ++k) if (a.a[i][k] < inf)
                for (j = 1; j <= n; ++j) if (b.a[k][j] < inf)
                    gmin(Ans.a[i][j], a.a[i][k] + b.a[k][j]);
        return Ans;
    }
    inline bool Judge() {
        for (int i = 1; i <= n; ++i)
            if (a[i][i] < 0) return true;
        return false;
    }
}g[15], Ans, tmp;

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) g[0].a[i][i] = Ans.a[i][i] = 0; 
    for (int i = 1; i <= m; ++i) {
        register int u = read(), v = read(), w = read();
        g[0].a[u][v] = w;
    }
    register int cnt = 0;
    for (int i = 1; i <= 9; ++i) g[i] = g[i - 1] * g[i - 1]; 
    if (!g[9].Judge()) return puts("0"), 0;
    for (int i = 9; ~i; --i) {
        tmp = Ans * g[i];
        if (!tmp.Judge()) Ans = tmp, cnt |= 1 << i; 
    }
    printf("%d\n", cnt + 1);
    return 0;
}