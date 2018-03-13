# include <stdio.h> 
# include <iostream>
# include <algorithm> 
const int MAXN = 2e5 + 5;
const int inf = 0x3f3f3f3f; 
int n, val[MAXN], first[MAXN], e = 1, Hash[MAXN], cnt; 
 
 
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
 
struct edge {
    int u, v, next;
} a[MAXN << 1];
 
inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++; 
}
 
namespace Solver_1 {
    int f[3005][3005]; 
    inline void dp(int u, int fa) {
        register int Mn;
        for (int i = 1; i <= cnt; ++i) 
            f[u][i] = val[u] != i;
        for (int i = first[u]; i; i = a[i].next) {
            Mn = inf; 
            register int v = a[i].v; 
            if (v == fa) continue; 
            dp(v, u);
            for (int j = cnt; j; --j) {
                gmin(Mn, f[v][j]);
                f[u][j] += Mn; 
            }
        }
    }
    inline void Main() {
        dp(1, 0);
        int Ans = inf;
        for (int i = 1; i <= cnt; ++i)
            gmin(Ans, f[1][i]);
        printf("%d\n", Ans);
    }
}
 
namespace Lian {
    int st[MAXN], top, T[MAXN];
    inline void dfs(int u, int fa) {
        st[++top] = val[u];
        for (int i = first[u]; i; i = a[i].next) 
            if (a[i].v != fa) dfs(a[i].v, u); 
    } 
    inline void Update(register int x, register int val) { for (; x <= cnt; x += x & (-x)) gmax(T[x], val); }
    inline int Query(int x) {
        int Ans = 0;
        for (; x; x -= x & (-x))
            gmax(Ans, T[x]);
        return Ans; 
    }
    inline void Main() {
        dfs(1, 0);
        register int Ans = 0;
        for (int i = 1; i <= n; ++i) {
            register int t = Query(st[i]); // 考试的时候把st[i]写成了val[i], 导致最后的10分没有拿到...  
            gmax(Ans, t + 1);
            Update(st[i], t + 1);
        }
        printf("%d\n", n - Ans);
    }
}
 
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) val[i] = read();
    for (int i = 1; i <= n; ++i) Hash[i] = val[i];
    std::sort(&Hash[1], &Hash[n + 1]);
    cnt = std::unique(&Hash[1], &Hash[n + 1]) - Hash - 1;
    for (int i = 1; i <= n; ++i) val[i] = std::lower_bound(&Hash[1], &Hash[cnt + 1], val[i]) - Hash;
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        push(u, v), push(v, u); 
    }
    if (n <= 3000) Solver_1::Main();
    else Lian::Main(); 
    return 0; 
}
/*
    考试时候写的暴力, 应该是可以拿到50分的分数, 但是由于一些疏漏, 只拿到了40分的分数..  
    以后造一条链的时候要注意不要1连2, 2连3...  
    这样可能拍不出来一些错误...  
    应该先造出一个排列然后再造链...  
*/