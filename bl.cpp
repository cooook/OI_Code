# include <bits/stdc++.h> 
const int MAXN = 5e5 + 5;
int n, m, val[MAXN], mn[MAXN], mx[MAXN]; 


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

inline void gmax(int &a, const int &b) {
    if (a < b) a = b; 
} 

int main() {
    freopen("Cooook.in","r",stdin);
    freopen("bl.out","w",stdout);
    n = read();
    for (int i = 1; i <= n; ++i) mx[i] = mn[i] = val[i] = read();
    m = read();
    while (m --) {
        register int opt = read(), l = read(), r = read(), x;
        if (opt == 1) {
            x = read();
            for (int i = l; i <= r; ++i) val[i] += x;
        }
        else if (opt == 2) {
            x = read();
            for (int i = l; i <= r; ++i) gmax(val[i], x);
        }
        else if (opt == 3) {
            x = read();
            for (int i = l; i <= r; ++i)
                gmin(val[i], x);
        }
        else if (opt == 4) {
            int Ans = 0;
            for (int i = l; i <= r; ++i)
                Ans += val[i];
            printf("%d\n", Ans);
        }
        else if (opt == 5) {
            int Ans = INT_MIN;
            for (int i = l; i <= r; ++i)
                gmax(Ans, val[i]);
            printf("%d\n", Ans);
        }
        else {
            int Ans = INT_MAX;
            for (int i = l; i <= r; ++i)
                gmin(Ans, val[i]);
            printf("%d\n", Ans);
        }
    }
    // while (true); 
    return 0; 
}