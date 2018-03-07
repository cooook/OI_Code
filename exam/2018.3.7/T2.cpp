# include <set>
# include <stdio.h> 
# include <iostream> 
# define int long long 
const int MAXN = 2e5 + 5;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n, m, first[MAXN], e = 1; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

template <typename _t>
inline void gmax(_t &x, const _t &y) {
    if (x < y) x = y;
}

template <typename _t>
struct My_Heap {
    std::multiset<_t, std::greater<_t> > S; 
    _t mx;
    inline _t top() { return mx; }
    inline void push(const register _t& x) { S.insert(x); mx = *S.begin(); }
    inline void pop(const register _t& x) { S.erase(x); mx = *S.begin(); }
};

struct node {
    node *ch[2], *f; 
    My_Heap<std::pair<int, node*> > cmx; bool tag;
    int Sum, val; std::pair<int, node*> mx, Mx; 
    inline bool isrt();
    inline bool dir();
    inline void rotate();
    inline void Splay();
    inline void Push_down(); 
    inline void Maintain(); 
    inline void Clear(); 
    inline void Down(); 
}null[MAXN]; 

# define fi first
# define se second
# define mk std::make_pair
typedef std::pair<int, node*> pii;

inline void node::Maintain() {
    Sum = ch[0] -> Sum + ch[1] -> Sum + val; 
    mx = mk(-inf, null);
    Mx = mk(-inf, null); 
    gmax(Mx, ch[0] -> Mx);
    gmax(Mx, cmx.top());
    gmax(Mx, ch[1] -> Mx);
    gmax(mx, ch[0] -> mx);
    gmax(mx, mk(cmx.top().fi + ch[0] -> Sum + val, cmx.top().se));
    gmax(mx, mk(ch[1] -> mx.fi + ch[0] -> Sum + val, ch[1] -> mx.se));
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline bool node::dir() {
    return f -> ch[1] == this; 
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this; 
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    ch[d ^ 1] = fa; fa -> f = this; f = pa;
    fa -> Maintain(); Maintain(); 
}

inline void node::Clear() {
    val = 0; Sum = 0; tag = true; 
    mx = Mx;
}

inline void node::Push_down() {
    if (tag) ch[0] -> Clear(), ch[1] -> Clear(), tag ^= 1;
}

inline void node::Down() {
    if (!isrt()) f -> Down();
    Push_down(); 
}

inline void node::Splay() {
    Down();
    for (node *t = f; !isrt(); rotate(), t = f) 
        if (!t -> isrt())
            (t -> dir() == dir() ? t : this) -> rotate();
}

inline void Access(node *x) {
    node *y = null;
    while (x != null) {
        x -> Splay();
        if (x -> ch[1] != null)
            x -> cmx.push(mk(x -> ch[1] -> mx.fi, x -> ch[1] -> mx.se));
        if (y != null)
            x -> cmx.pop(mk(y -> mx.fi, y -> mx.se));
        x -> ch[1] = y; 
        x -> Maintain();
        y = x; x = x -> f; 
    }
}

struct edge {
    int u, v, next; 
} a[MAXN << 1];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u, int fa) {
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v, u);
        null[v].f = &null[u];
        null[u].cmx.push(mk(null[v].mx.fi, null[v].mx.se));
    }
    null[u].Maintain();
}

signed main() {
    null -> ch[0] = null -> ch[1] = null -> f = null;
    null -> tag = false; null -> Sum = null -> val = 0; 
    n = read(), m = read(); 
    for (int i = 1; i <= n; ++i) null[i].val = null[i].Sum = read(),
        null[i].ch[0] = null[i].ch[1] = null[i].f = null, null[i].tag = false, null[i].cmx.push(mk(0, &null[i]));
    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        push(u, v), push(v, u);
    }
    dfs(1, 0);
    int Ans = 0;
    while (m --) {
        Access(&null[1]);
        if (null[1].mx.fi <= 0) break;
        node *t = null[1].mx.se; 
        Ans += null[1].mx.fi; 
        Access(null[1].mx.se);
        t -> Splay();
        t -> Clear();
    }
    printf("%lld\n", Ans);
    return 0; 
}

/*
    错误之处: LCT Splay的时候应该先旋转, 再把t赋成f, 否则t不对. 
*/