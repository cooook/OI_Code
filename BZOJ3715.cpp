# include <bits/stdc++.h>
const int MAXN = 1e5 + 5;
const int inf = 0x3f3f3f3f;  
int T, n, w[MAXN][4]; 


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

inline void gmax(int &x, const int &y) {
    if (x < y) x = y;
}

inline void Work() {
    n = read(); 
    int mx1 = -inf, mx2 = -inf, mn1 = inf, mn2 = inf;
    for (int i = 1; i <= n; ++i) {
        w[i][0] = read();
        w[i][1] = read();
        w[i][2] = read();
        w[i][3] = read();
        gmin(mn1, w[i][0]);
        gmax(mx1, w[i][1]);
        gmin(mn2, w[i][2]);
        gmax(mx2, w[i][3]);
    }  
    bool flag = false; 
    for (int i = 1; i <= n; ++i) {
        if (mn1 == w[i][0] && mx1 == w[i][1] && mn2 == w[i][2] && mx2 == w[i][3])
            flag = true; 
    }
    puts(flag ? "TAK" : "NIE"); 
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    T = read();
    while (T --) Work(); 
    // while (true); 
    return 0;
}