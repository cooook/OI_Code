# include <bits/stdc++.h>
const int MAXN = 1e5 + 5;  
int n, val[MAXN], m, tmp[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &x, const int &y) {
    if (x > y) x = y; 
}

int main() {
    freopen("T3.in","r",stdin);
    freopen("bl.out","w",stdout);
    n = read();
    for (int i = 1; i <= n; ++i) val[i] = read();
    m = read();
    while (m --) {
        register int l = read(), r = read();
        // printf("%d %d\n", val[l], val[r]);
        for (register int i = l; i <= r; ++i) tmp[i] = val[i];
        std::sort(&tmp[l], &tmp[r + 1]);
        register int Ans = 0x3f3f3f3f;
        for (register int i = l + 1; i <= r; ++i)
            gmin(Ans, tmp[i] - tmp[i - 1]);
        printf("%d\n", Ans);
    } 
    // while (true); 
    return 0; 
}