# include <stdio.h> 
# include <iostream>
const int MAXN = 7005; 
int n, k[2], val[2][MAXN], T; 
int __result[MAXN][2];
bool used[7005][2];
int vis[7005][2];
 
 
char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline int dfs(int x, bool who) {
    if (used[x][who]) return __result[x][who];
    if (x == 1) return __result[x][who] = 0; 
    if (vis[x][who] == T) return 3;
    vis[x][who] = T;
    register int res, nxt;
    bool flag2 = true, flag3 = false, flag1 = false, flag4 = false; 
    for (int i = 1; i <= k[who]; ++i) {
        nxt = x + val[who][i];
        if (nxt > n) nxt -= n;
        res = dfs(nxt, who ^ 1);
        if (res == 0) { flag3 = true; break; }
        if (res != 1) flag2 = false;
        if (res == 2) flag1 = true;
        if (res == 3) flag4 = true; 
    }
    if (!flag4 || flag1 || flag2 || flag3) {
        if (flag3) __result[x][who] = 1, used[x][who] = true;
        else if (flag1) __result[x][who] = 2, used[x][who] = true; 
        else if (flag2) __result[x][who] = 0, used[x][who] = true; 
        return __result[x][who];
    }
    return 3;  
}
 
int main() {
    register int i; 
    n = read(); 
    for (k[0] = read(), i = 1; i <= k[0]; ++i) val[0][i] = read();
    for (k[1] = read(), i = 1; i <= k[1]; ++i) val[1][i] = read(); 
    for (int i = 2; i <= n; ++i) {
    	++ T;
        int res = dfs(i, 0); 
        if (!res) printf("Lose");
        else if (res == 1) printf("Win");
        else printf("Loop");
        printf("%c", " \n"[i == n]);
        
        if (res == 3)
        	for (int j = 1; j <= n; ++j) {
        		if (vis[j][0] == T && !used[j][0])
        			used[j][0] = 1, __result[j][0] = 2;
        		if (vis[j][1] == T && !used[j][1])
        			used[j][0] = 1, __result[j][0] = 2;
        	}
    }
    for (int i = 2; i <= n; ++i) {
    	++ T;
        int res = dfs(i, 1);
        if (!res) printf("Lose");
        else if (res == 1) printf("Win");
        else printf("Loop");
        printf("%c", " \n"[i == n]);
        if (res == 3)
        	for (int j = 1; j <= n; ++j) {
        		if (vis[j][0] == T && !used[j][0])
        			used[j][0] = 1, __result[j][0] = 2;
        		if (vis[j][1] == T && !used[j][1])
        			used[j][1] = 1, __result[j][1] = 2;
        	}
    }
    return 0; 
}
