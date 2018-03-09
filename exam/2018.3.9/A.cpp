# include <stdio.h>
# include <cstring> 
# include <iostream>
const int MAXN = 1005; 
int n, m, val[MAXN][MAXN], Begin[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Data {
    int val, rk;
    Data(int val = 0, int rk = 0): val(val), rk(rk) {  }
    inline bool operator < (const Data &x) const {
        return rk < x.rk; 
    }
} ; 

int ton[1005];
bool vis[1005];

inline bool Judge(int x) {
    memset(vis, true, sizeof vis); 
    register int Ans;
    for (int i = 1; i <= n; ++i) Begin[i] = 1; 
    begin:;
    memset(ton, 0, sizeof ton);
    Ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = Begin[i]; j <= m; ++j)
            if (vis[val[i][j]]) { ++ ton[val[i][j]], ++ Ans; Begin[i] = j; break; }
    
    for (int i = 1; i <= m; ++i)
        if (ton[i] > x) { vis[i] = false; goto begin; }
    return Ans == n; 
}

int main() {
    // freopen("sports2.in","r",stdin);
    // freopen("sports.out","w",stdout);
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            val[i][j] = read();
    
    int l = 1, r = n, Ans, mid;
    while (l <= r) {
        mid = l + r >> 1;
        if (Judge(mid)) Ans = mid, r = mid - 1;
        else l = mid + 1; 
    }
    printf("%d\n", Ans);
    // printf("%d\n", clock());
    // while (true); 
    return 0; 
}