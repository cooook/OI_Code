# pragma GCC optimize("O3")
# include <stdio.h>
# include <iostream>
const int MAXN = 5e4 + 5; 
int n, first[MAXN], e = 1, T, Ans, size[MAXN], w[MAXN];


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, next;
} a[MAXN << 1];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dp(int u, int fa, bool now) {
    register int last = size[u], i, v;
    if (!w[u]) now = 1;
    for (i = first[u]; i; i = a[i].next) {
        v = a[i].v;
        if (v == fa) continue; 
        last -= size[v] * w[v];
        dp(v, u, now ^ 1);
    }
    if (now) Ans ^= last; 
}

# define Add_Edge u = read(), v = read(), push(u, v), push(v, u) 

int main() {
    T = read();
    register int u, v, i; 
    while (T --) {
        n = read(); Ans = 0; e = 1; 
        for (i = 1; i + 3 <= n; i += 4) {
            size[i] = read(), first[i] = 0;
            size[i + 1] = read(), first[i + 1] = 0;
            size[i + 2] = read(), first[i + 2] = 0;
            size[i + 3] = read(), first[i + 3] = 0;
        } 

        for (; i <= n; ++i) size[i] = read(), first[i] = 0; 


        for (i = 1; i + 3 <= n; i += 4) {
            w[i] = read();
            w[i + 1] = read();
            w[i + 2] = read();
            w[i + 3] = read();
        }
        for (; i <= n; ++i) w[i] = read(); 

        for (i = 1; i + 3 < n; i += 4) {
            Add_Edge;
            Add_Edge;
            Add_Edge;
            Add_Edge;
        }

        for (; i < n; ++i) Add_Edge;

        dp(1, 0, 1);
        puts(Ans ? "YES" : "NO");
    }
    return 0;
}