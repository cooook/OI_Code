# include <stdio.h> 
# include <cstring>
# include <iostream>
const int MAXN = 7005; 
int n, k[2], val[2][MAXN]; 
int __result[MAXN][2];
bool vis[7005][2];

char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int dfs(int x, bool who) {
	printf ("x = %d who = %d vis = %d\n", x, who, vis[x][who]);
    if (__result[x][who] != -1) return __result[x][who];
    if (vis[x][who]) return 2;
    if (x == 1) return __result[x][who] = 0;
    vis[x][who] = true;
    register int nxt, res;
    for (int i = 1; i <= k[who]; ++i) {
        nxt = x + val[who][i];
        if (nxt > n) nxt -= n;
        res = dfs(nxt, who ^ 1); 
        if (res == 0) return vis[x][who] = false, __result[x][who] = 1;
        if (res == 2) __result[x][who] = 2; 
    }
    vis[x][who] = false; 
    if (__result[x][who] == -1) __result[x][who] = 0;
    return __result[x][who]; 
}

int main() {
    freopen("game1.in","r",stdin);
    // freopen("T1.out","w",stdout);
    register int i; 
    n = read(); 
    for (k[0] = read(), i = 1; i <= k[0]; ++i) val[0][i] = read();
    for (k[1] = read(), i = 1; i <= k[1]; ++i) val[1][i] = read();
    memset(__result, -1, sizeof __result); 
    for (int i = 2; i <= n; ++i) {
        int res = dfs(i, 0);
        if (!res) printf("Lose");
        else if (res == 1) printf("Win");
        else printf("Loop");
        printf("%c", " \n"[i == n]);
    }
    memset(__result, -1, sizeof __result); 
    for (int i = 2; i <= n; ++i) {
        int res = dfs(i, 1);
        if (!res) printf("Lose");
        else if (res == 1) printf("Win");
        else printf("Loop");
        printf("%c", " \n"[i == n]);
    }
    while (true); 
    return 0; 
}
