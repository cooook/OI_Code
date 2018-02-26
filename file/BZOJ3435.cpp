#define WX
#include <bits/stdc++.h>
#define pb insert
typedef std::set<int>::iterator D;
typedef long long ll;
const int MAXN = 100005;
const double alpha = 0.755;
int n,first[MAXN],e = 1,size[MAXN],g[MAXN],root,Num,pre[MAXN],f[MAXN][18],deep[MAXN],r[MAXN],d[MAXN][18],rebuild,Time;
int vis[MAXN]; ll Ans; std::set<int> G[MAXN]; bool use[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    #define size(_) ((_)?(_)->size:(0))
    node *ch[2];
    int size,v,r;
    inline int cmp(int x)const{
        if (x == v) return -1;
        return x < v?0:1;
    }
    node(){ch[0] = ch[1] = NULL; v = 0;size = 0;}
    node(int x){ch[0] = ch[1] = NULL; v = x; size = 1; r = rand();}
    inline void* operator new(size_t);
    inline void operator delete(void *p);
    inline void Maintain(){size = 1 + size(ch[0]) + size(ch[1]);}
}*C,*mempool,*Sum[MAXN],*Up_Sum[MAXN];

std::vector<node*> bin;

inline void* node::operator new(size_t){
    node *p;
    if (!bin.empty()){
        p = bin.back();
        bin.pop_back();
    }
    else {
        if (C == mempool) C = new node[1<<15], mempool = C + (1 << 15);
        p = C ++;
    } return p;
}

inline void node::operator delete(void *p){
    bin.push_back((node*)p);
}

inline int Rank(node *o,int k){
    int Ans = 0;
    while (o){
        if (k >= o -> v) Ans += size(o -> ch[0]) + 1, o = o -> ch[1];
        else o = o -> ch[0];
    } return Ans;
}

inline void rotate(node *&o,int d){
    node *k = o -> ch[d ^ 1]; 
    o -> ch[d ^ 1] = k -> ch[d];
    k -> ch[d] = o;
    o -> Maintain();
    k -> Maintain();
    o = k;
}

inline void Insert(node *&o,int x){
    if (!o) o = new node(x);
    else{
        int d = x < o -> v?0:1;
        Insert(o -> ch[d],x);
        if (o -> ch[d] -> r < o -> r) rotate(o,d ^ 1);
    }
    o -> Maintain();
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w){
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

inline void G_size(int u,int fa){
    size[u] = 1;
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa && !use[a[i].v] && vis[a[i].v] == Time)
            G_size(a[i].v,u), size[u] += size[a[i].v];
}

inline void G_root(int u,int fa){
    g[u] = 0;
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (v == fa || use[v] || vis[v] != Time) continue;
        g[u] = std::max(g[u],size[v]);
        G_root(v,u);
    }
    g[u] = std::max(g[u],Num - g[u]);
    if (g[u] < g[root]) root = u;
}

inline void Init(int u){
    for (int i = 1; i <= 17; i++) 
        f[u][i] = f[f[u][i-1]][i-1], 
        d[u][i] = d[f[u][i-1]][i-1] + d[u][i-1];
}

inline int dis(int u,int v){
    if (deep[u] < deep[v]) std::swap(u,v);
    int t = deep[u] - deep[v], Ans = 0;
    for (int i = 17; ~i; i--)
        if (t >> i & 1) Ans += d[u][i], u = f[u][i];
    if (u == v) return Ans;
    for (int i = 17; ~i; i--)
        if (f[u][i] != f[v][i])
            Ans += d[u][i] + d[v][i],
            u = f[u][i], v = f[v][i];
    return Ans + d[u][0] + d[v][0];
}

inline void Remove(node *&o){
    if (!o) return;
    Remove(o -> ch[0]);
    Remove(o -> ch[1]);
    delete o; o = NULL;
}

inline void __dfs(int u){
    Remove(Sum[u]); Remove(Up_Sum[u]); vis[u] = Time; use[u] = false;
    for (D it = G[u].begin(); it != G[u].end(); ++ it) __dfs(*it);
    G[u].clear();
}

inline void Dfs(int u,int fa,node *&Sum,node *&Up_Sum,int p){
    Insert(Sum,dis(u,p) - r[u]); Insert(Up_Sum,dis(u,pre[p]) - r[u]);
    for (int i = first[u]; i; i = a[i].next)
        if (!use[a[i].v] && vis[a[i].v] == Time && a[i].v != fa) Dfs(a[i].v,u,Sum,Up_Sum,p);
}

inline void Div(int u){
    use[u] = true; 
    Dfs(u,0,Sum[u],Up_Sum[u],u); G_size(u,0);
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (vis[v] != Time || use[v]) continue;
        Num = size[v]; root = 0; G_root(v,0); pre[root] = u; G[u].pb(root); Div(root);
    }
}

inline void Build(int x){
    ++ Time; __dfs(x); 
    G_size(x,0);
    Num = size[x]; root = 0; G_root(x,0);
    pre[root] = pre[x];
    if (pre[x]) G[pre[x]].erase(x), G[pre[x]].pb(root);
    Div(root); 
}

inline void Update(int x){
    int Dis1,Dis2; rebuild = 0;
    if (pre[x]) G[pre[x]].pb(x);
    for (int u = x; u; u = pre[u]){
        Dis1 = dis(x,pre[u]);
        Dis2 = dis(u,x);
        if (pre[u]){
            Ans += Rank(Sum[pre[u]],r[x] - Dis1);
            Ans -= Rank(Up_Sum[u],r[x] - Dis1);
        }
        Insert(Sum[u],Dis2 - r[x]);
        Insert(Up_Sum[u],Dis1 - r[x]);
        if (pre[u] && (size(Sum[pre[u]]) + 1) * alpha < size(Sum[u])) rebuild = pre[u];
    }
    if (rebuild) Build(rebuild);
}

int main(){
    read<int>();
    n = read<int>(); g[0] = n;
    for (int i = 1; i <= n; i++){
        int x = read<int>() ^ (Ans % 1000000000), y = read<int>();
        r[i] = read<int>();
        if (x) push(x,i,y) ,push(i,x,y);
        f[i][0] = x; deep[i] = deep[x] + 1; 
        d[i][0] = y; pre[i] = x;
        Init(i); Update(i);
        printf("%lld\n",Ans);
    }
    return 0;
}