# include <stdio.h>
# include <cstring>
# include <iostream> 
const int MAXN = 305;
const int MAXM = 90005;
int first[MAXN], e = 1, n, m, f[MAXN][MAXN], g[MAXN][MAXN]; 


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

struct edge {
    int u, v, w, next;
} a[MAXM];

inline void push(int u, int v, int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].next = first[u]; first[u] = e++;
}

inline bool Work() {
    memcpy(g, f, sizeof f);
    for (int i = 1; i < e; ++i)
        for (int j = 1; j <= n; ++j)
            gmin(g[j][a[i].v], f[j][a[i].u] + a[i].w); 
    for (int i = 1; i <= n; ++i)
        if (g[i][i] < 0) return true; 
    memcpy(f, g, sizeof g);
    return false; 
}

int main() {
    memset(f, 0x3f, sizeof f);
    n = read(), m = read();
    if (!m) return puts("0"), 0;
    for (int i = 1; i <= n; ++i) f[i][i] = 0;
    bool flag = true; 
    for (int i = 1; i <= m; ++i) {
        register int u = read(), v = read(), w = read();
        push(u, v, w);
        if (w < 0) flag = false;  
    }
    if (flag) return puts("0"), 0;
    for (int i = 1; i <= n; ++i)
        if (Work()) return printf("%d\n", i), 0;
    puts("0");
    return 0;
}
