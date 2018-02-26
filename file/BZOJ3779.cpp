#include <bits/stdc++.h>
#define int long long 
#define ls o << 1
#define rs o << 1 | 1
const int MAXN = 100005;
int n,m,cnt,in[MAXN],out[MAXN],Sum[MAXN<<2],tag[MAXN<<2],first[MAXN],e = 1,deep[MAXN],pre[MAXN],Now_Root,f[MAXN][18];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    node *ch[2],*f;
    int tag;
    inline void Push_down();
    inline void rev();
    inline bool dir();
    inline bool isrt();
    inline void rotate();
    inline void Splay();
}null[MAXN<<2];

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int fa){
    in[u] = ++ cnt; deep[u] = deep[fa] + 1; pre[cnt] = u; f[u][0] = fa;
    for (int i = 1; i <= 17; i++) f[u][i] = f[f[u][i-1]][i-1];
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa) null[a[i].v].f = &null[u],dfs(a[i].v,u);
    out[u] = cnt;
}

inline int lca(int u,int v){
    if (deep[u] < deep[v]) std::swap(u,v);
    int t = deep[u] - deep[v];
    for (int i = 17; ~i; i--)
        if (t >> i & 1) u = f[u][i];
    if (u == v) return u;
    for (int i = 17; ~i; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}

inline int find_father(int u,int depth){
    int d = deep[u] - depth;
    for (int i = 17; ~i; i--)
        if (d >> i & 1) u = f[u][i];
    return u;
}
 
inline void build(int o,int l,int r){
    tag[o] = 0;
    if (l == r) return Sum[o] = deep[pre[l]], void();
    register int mid = l + r >> 1;
    build(ls,l,mid), build(rs,mid+1,r);
    Sum[o] = Sum[ls] + Sum[rs];
}

inline void Update(int o,int l,int r,int x,int y,int val){
    if (x > y) return;
    Sum[o] += (y - x + 1) * val;
    if (x == l && r == y) return tag[o] += val, void();
    register int mid = l + r >> 1;
    if (y <= mid) Update(ls,l,mid,x,y,val);
    else if (x > mid) Update(rs,mid+1,r,x,y,val);
    else Update(ls,l,mid,x,mid,val), Update(rs,mid+1,r,mid+1,y,val);
}

inline int Query(int o,int l,int r,int x,int y){
    if (x > y) return 0;
    if (x == l && r == y) return Sum[o];
    register int Ans = tag[o] * (y - x + 1), mid = l + r >> 1;
    if (y <= mid) return Query(ls,l,mid,x,y) + Ans;
    else if (x > mid) return Query(rs,mid+1,r,x,y) + Ans;
    else return Query(ls,l,mid,x,mid) + Query(rs,mid+1,r,mid+1,y) + Ans;
}

inline bool node::isrt(){
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline bool node::dir(){
    return f -> ch[1] == this;
}

inline void node::Push_down(){
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}

inline void node::rev(){
    std::swap(ch[0],ch[1]); tag ^= 1;
}

inline void node::rotate(){
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    ch[d ^ 1] = fa; fa -> f = this; this -> f = pa;
}

inline void node::Splay(){
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()){
            t -> f -> Push_down(), t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
}

inline void Add(int x,int val){
    if (x == Now_Root) Update(1,1,n,1,n,val);
    else{
        int Lca = lca(x,Now_Root),t;
        if (x != Lca) Update(1,1,n,in[x],out[x],val);
        else t = find_father(Now_Root,deep[x] + 1), Update(1,1,n,1,in[t]-1,val), Update(1,1,n,out[t]+1,n,val);
    }
}

inline void Deep_Min(node *o,int val){
    if (o == null) return;
    o -> Push_down();
    while (o -> ch[0] != null)
        o = o -> ch[0], o -> Push_down();
    Add(o - null,val);
}

inline void Access(node *x){
    node *y = null;
    while (x != null)
        x -> Splay(),
        Deep_Min(x -> ch[1],1),
        x -> ch[1] = y, 
        Deep_Min(y,-1),
        y = x, x = x -> f;
}

inline double Query_Sum(int x){
    if (x == Now_Root) return Query(1,1,n,1,n) / 1.0 / n;
    else{
        int Lca = lca(x,Now_Root),t;
        if (x != Lca) return Query(1,1,n,in[x],out[x]) / 1.0 / (out[x] - in[x] + 1);
        else {
            t = find_father(Now_Root,deep[x] + 1);
            return (Query(1,1,n,1,in[t] - 1) + Query(1,1,n,out[t]+1,n)) / 1.0 / ((in[t] - 1) + (n - out[t]));
        }
    }
}

inline void Make_root(node *x){
    Access(x); x -> Splay(); x -> rev();
    Now_Root = x - null;
}

signed main(){
    n = read<int>(), m = read<int>();
    for (int i = 0; i <= n; i++)
        null[i].ch[0] = null[i].ch[1] = null[i].f = null, null[i].tag = false;
    for (int i = 1,u,v; i < n; i++) {
        int u = read<int>(), v = read<int>();
        push(u,v), push(v,u); 
    }
    dfs(1,0);
    build(1,1,n);
    Now_Root = 1;
    char s[15];
    while (m --){
        scanf("%s",s);
        if (s[2] == 'L') Access(&null[read<int>()]);
        else if (s[2] == 'C') Make_root(&null[read<int>()]);
        else printf("%.10f\n",Query_Sum(read<int>()));
    }
    return 0;
}