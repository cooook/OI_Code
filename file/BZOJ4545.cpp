# include <stdio.h>
# include <cstring>
#define int long long 
typedef long long ll;
const int MAXN = 400005;
int n, first[MAXN], e = 1, id[MAXN], m; ll Ans; char s[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int u, v, next; char c;
}a[MAXN];

inline void push(int u,int v, char c) {
    a[e].u = u; a[e].v = v; a[e].c = c;
    a[e].next = first[u]; first[u] = e++;
}

struct node{
    node *ch[2], *f; int size, add;
    inline void rotate();
    inline void Push_down();
    inline void Add(int);
    inline void Splay();
    inline bool dir();
    inline bool isrt();
}null[MAXN];

inline void Init(int x) {
    null[x].ch[0] = null[x].ch[1] = null[x].f = null;
    null[x].size = 0; null[x].add = 0;
}

inline bool node::dir()  {
    return f -> ch[1] == this;
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::Push_down() {
    if (add) ch[0] -> Add(add), ch[1] -> Add(add), add = 0;
}

inline void node::Add(int x) {
    size += x; add += x;
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    ch[d ^ 1] = fa; fa -> f = this; f = pa;
}

inline void node::Splay() {
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f) {
        if (!t -> isrt()) {
            t -> f -> Push_down(), t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
    }
}

inline void Access(node *x) {
    for (node *y = null; x != null; y = x, x = x -> f) x -> Splay(), x -> ch[1] = y; 
}

inline void Link(node *x,node *y) {
    Access(x); x -> Splay(); x -> Add(y -> size); y -> f = x;
}

inline void Cut(node *x) {
    Access(x); x -> Splay(); x -> ch[0] -> Add(- x -> size);
    x -> ch[0] -> f = null; x -> ch[0] = null;
}

int trans[MAXN][3], fa[MAXN], Mx[MAXN], cnt;

inline int expend(int p, int c) {
    int np = ++ cnt; Mx[np] = Mx[p] + 1; Init(cnt); null[cnt].size = 1;
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1, Link(&null[1], &null[cnt]), Ans += Mx[np];
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q, Link(null + q, null + np), Ans += Mx[np] - Mx[q];
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1; 
            Init(cnt); Cut(null + q);  Ans -= Mx[q] - Mx[fa[q]];
            fa[nq] = fa[q]; Link(null + fa[q], null + nq);
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            fa[np] = fa[q] = nq; Link(null + nq, null + q), Link(null + nq, null + np);
            Ans += Mx[nq] - Mx[fa[nq]] + Mx[q] - Mx[fa[q]] + Mx[np] - Mx[fa[np]];
            for (; p && trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    }
    return np;
}

inline void dfs(int u, int fa) {
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa)
            id[a[i].v] = expend(id[u], a[i].c - 'a'), dfs(a[i].v, u);
    first[u] = 0;
}

inline void Read_Edge(int cnt){
    for (int i = 1; i <= cnt; i++) {
        register int u = read(), v = read();
        char c = getchar();
        while (c < 'a' || c > 'c') c = getchar();
        push(u, v, c); push(v, u, c);
    } 
}

inline int Query() {
    int root = 1;
    for (int i = 1; s[i]; i++)
        if (trans[root][s[i] - 'a']) root = trans[root][s[i] - 'a'];
        else return 0;
    (&null[root]) -> Splay();
    return (&null[root]) -> size;
}

signed main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    read();  n = read(); 
    Read_Edge(n - 1);
    Init(0); Init(1); 
    id[1] = ++ cnt; dfs(1, 0);
    m = read();
    while (m --) {
        int opt = read();
        if (opt == 1) printf("%lld\n", Ans);
        else if (opt == 2) {
            int u = read(), p = read(); Read_Edge(p - 1);
            dfs(u, 0);
        }
        else scanf("%s", s + 1), printf("%lld\n", Query());
    }
    return 0;
}