# include <set> 
# include <stdio.h> 
# include <cstring> 
# include <iostream> 
const int MAXN = 1e5 + 5; 
int first[MAXN], e = 1, n, fa[MAXN], size[MAXN], f[MAXN], root, Num; 
bool vis[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(int &x, const int &y) {
    if (x < y) x = y; 
}

struct edge {
    int u, v, w, next;
} a[MAXN];

std::multiset<int> S; 

inline void push(int u, int v, int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u, int fa, bool dep) {
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v; 
        if (v == fa) continue; 
    }
}

int main() {
    n = read();
    f[0] = n; 
    return 0;
}