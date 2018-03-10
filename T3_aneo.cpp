# include <set> 
# include <stdio.h> 
# include <iostream> 
const int MAXN = 3e4 + 5; 
int n, m, first[MAXN], e = 1, deep[MAXN], f[MAXN][18], son[MAXN], root[MAXN], cnt, Max; 
long long Ans; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(register int &x, const register int &y) {
    if (x < y) x = y; 
}

struct edge {
    int u, v, w, next;
} a[MAXN << 1];

inline void push(register int u, register int v, register int w) {
    a[e].u = u; a[e].v = v; a[e].w = w; a[e].next = first[u]; first[u] = e++; 
}

int Sum[MAXN << 2];
# define ls o << 1
# define rs o << 1 | 1 

std::multiset<int> S; 
std::multiset<int>::iterator it; 

int Sum, Now; 

inline void dfs(int u, int fa, int dep) {
    if (dep) Ans += Now;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v; 
        if (v == fa) continue;
        dfs(v, u, dep ^ 1);
    }
}

int main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("T3.in","r",stdin);
    // freopen("T3.out","w",stdout);
    n = read(); 
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read(), w = read();
        push(u, v, w), push(v, u, w); ++ son[u]; ++ son[v]; 
        gmax(Max, w);
    }
    for (int i = 1; i <= n; ++i) {
        Now = 0; it = S.begin(); 
        Ans += dfs(1, 0);
    }
    printf("%lld\n", Ans >> 1);
    while (true); 
    return 0; 
}