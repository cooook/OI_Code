# include <bits/stdc++.h> 
# define RG register 
# define int long long 
std::priority_queue<int> Q;
const int MAXN = 2e5 + 5; 
int f[MAXN], n, m, first[MAXN], e = 1; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(RG int &a, const RG int &y) {
    if (a < y) a = y; 
}

struct edge {
    int u, v, next; 
} a[MAXN << 1];

inline void push(RG int u, RG int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(RG int u, RG int fa) {
    RG int tmp = 0; 
    for (RG int i = first[u]; i; i = a[i].next) {
        RG int v = a[i].v;
        if (v == fa) continue; 
        dfs(v, u);
        gmax(tmp, f[v]);
    }
    RG bool flag = false;
    f[u] += tmp; 
    for (RG int i = first[u]; i; i = a[i].next) {
        if (a[i].v == fa) continue; 
        if (!flag && tmp == f[a[i].v])
            flag = true;
        else Q.push(f[a[i].v]); 
    }
}

signed main() {
    freopen("Cooook.in","r",stdin);
    freopen("bl.out","w",stdout);
    n = read(), m = read() - 1; 
    for (int i = 1; i <= n; ++i) f[i] = read();
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        push(u, v), push(v, u);
    }
    dfs(1, 0);
    RG int Ans = f[1];
    while (m -- && !Q.empty()) Ans += Q.top(), Q.pop();
    printf("%lld\n", Ans);
    // while (true); 
    return 0; 
}