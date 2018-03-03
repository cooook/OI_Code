# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
typedef long long ll; 
const int inf = 0x3f3f3f3f;
const int MAXN = 2e5 + 5;  
int val[MAXN], first[MAXN], e = 1, n, m; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline bool gmax(ll &a, const ll &b) {
    return a < b ? a = b, true : false; 
}

struct edge {
    int u, v, next;
} a[MAXN];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++; 
}

struct node {
    node *ch[2], *f;
    ll val[2], mx[2][2]; 
    inline bool dir();
    inline bool isrt();
    inline void Splay();
    inline void rotate();
    inline void Maintain();
}null[MAXN];

inline void Init(node* x, int val) {
    x -> ch[0] = x -> ch[1] = x -> f = null;
    x -> val[0] = 0; x -> val[1] = val; 
    x -> Maintain(); 
}

inline bool node::dir() {
    return f -> ch[1] == this; 
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this; 
}

inline void node::Splay() {
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()) (t -> dir() == dir() ? t : this) -> rotate();
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    fa -> f = this; f = pa; ch[d ^ 1] = fa; 
    fa -> Maintain(); Maintain();  
}

inline void node::Maintain() {
    if (this == null) return ;
    memset(mx, 0xef, sizeof mx);
    if (ch[0] == null && ch[1] == null) {
        mx[0][0] = val[0];
        mx[1][1] = val[1]; 
    }
    else if (ch[0] == null) {
        gmax(mx[0][0], val[0] + ch[1] -> mx[1][0]);
        gmax(mx[0][0], val[0] + ch[1] -> mx[0][0]);
        gmax(mx[1][0], val[1] + ch[1] -> mx[0][0]);
        gmax(mx[0][1], val[0] + ch[1] -> mx[1][1]);
        gmax(mx[0][1], val[0] + ch[1] -> mx[0][1]);
        gmax(mx[1][1], val[1] + ch[1] -> mx[0][1]);
    }
    else if (ch[1] == null) {
        gmax(mx[0][0], ch[0] -> mx[0][0] + val[0]);
        gmax(mx[0][0], ch[0] -> mx[0][1] + val[0]);
        gmax(mx[0][1], ch[0] -> mx[0][0] + val[1]);
        gmax(mx[1][0], ch[0] -> mx[1][0] + val[0]);
        gmax(mx[1][0], ch[0] -> mx[1][1] + val[0]);
        gmax(mx[1][1], ch[0] -> mx[1][0] + val[1]);
    }
    else {
        register int l1, l2, i, r1, r2; 
        for (l1 = 0; l1 < 2; ++l1)
            for (l2 = 0; l2 < 2; ++l2)
                for (i = 0; i < 2; ++i)
                    for (r1 = 0; r1 < 2; ++r1)
                        for (r2 = 0; r2 < 2; ++r2) {
                            if ((i & l2) | (i & r1)) continue; 
                            gmax(mx[l1][r2], ch[0] -> mx[l1][l2] + val[i] + ch[1] -> mx[r1][r2]);
                        }
    }
}

inline void Access(node *x) {
    node *y = null;
    while (x != null) {
        x -> Splay();
        if (x -> ch[1] != null) 
            x -> val[0] += std::max(std::max(x -> ch[1] -> mx[1][0], x -> ch[1] -> mx[1][1]), std::max(x -> ch[1] -> mx[0][1], x -> ch[1] -> mx[0][0])), 
            x -> val[1] += std::max(x -> ch[1] -> mx[0][0], x -> ch[1] -> mx[0][1]);
        if (y != null) 
            x -> val[0] -= std::max(std::max(y -> mx[1][0], y -> mx[1][1]), std::max(y -> mx[0][1], y -> mx[0][0])),
            x -> val[1] -= std::max(y -> mx[0][0], y -> mx[0][1]); 
        x -> ch[1] = y;
        x -> Maintain();
        y = x; x = x -> f; 
    }
}

inline void Change(int x, int y) {
    Access(&null[x]); (&null[x]) -> Splay();
    (&null[x]) -> val[1] -= val[x]; 
    (&null[x]) -> val[1] += y;
    val[x] = y;
    (&null[x]) -> Maintain();
}

inline void dfs(int u, int fa) {
    (&null[u]) -> val[0] = 0; (&null[u]) -> val[1] = val[u];
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v, u);
        (&null[u]) -> val[0] += std::max((&null[v]) -> val[0], (&null[v]) -> val[1]);
        (&null[u]) -> val[1] += (&null[v]) -> val[0]; 
        (&null[v]) -> f = &null[u];
    }
    (&null[u]) -> Maintain(); 
}

int main() {
    null -> ch[0] = null; null -> ch[1] = null; null -> f = null; 
    null -> val[0] = null -> val[1] = null -> mx[0][0] = 
    null -> mx[1][1] = null -> mx[1][0] = null -> mx[0][1] = -inf;
    n = read(); m = read();
    for (int i = 2; i <= n; ++i) push(read(), i);
    for (int i = 1; i <= n; ++i) val[i] = read(), Init(&null[i], val[i]);  
    dfs(1, 0); 
    register int x, v;
    while (m --) {
        register char ch = getc;
        for (; ch != 'Q' && ch != 'C' && ch != 'A'; ch = getc) ;
        x = read();
        if (ch == 'Q') {
            Access(&null[x]), (&null[x]) -> Splay();
            printf("%lld\n", std::max(null[x].val[0], null[x].val[1]));
        }
        else if (ch == 'C') v = read(), Change(x, v);
        else {
            v = read(); val[++n] = v;
            Init(&null[n], v); Access(&null[x]); (&null[x]) -> Splay();
            (&null[n]) -> f = &null[x];
            (&null[x]) -> val[0] += std::max(v, 0);
            (&null[x]) -> Maintain(); 
        }
    }
    // while (true); 
    return 0;
}