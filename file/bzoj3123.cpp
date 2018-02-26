#include <stdio.h>
#include <cstring>
#include <algorithm>
const int MAXN = 100005;
int first[MAXN],e=1,cnt,n,m,q,val[MAXN],id[MAXN],num,Hash[MAXN],sz;
int belong[MAXN],fa[MAXN][25],size[MAXN],root[MAXN],Ans,deep[MAXN];
bool vis[MAXN];


template<typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    int l,r,sum;
}tree[20000005];

#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define sum(x) tree[x].sum

struct edge{
    int u,v,next;
}a[MAXN<<3];

inline void push(int u,int v){
    a[e].u = u;a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

void insert(int &o,int old,int l,int r,int x){
    o = ++cnt; tree[o] = tree[old]; sum(o)++;
    if (l == r) return;
    int m = l+r>>1;
    if (x <= m) insert(ls(o),ls(old),l,m,x);
    else insert(rs(o),rs(old),m+1,r,x);
    return;
}

inline void swap(int &x,int &y){x^=y;y^=x;x^=y;}

inline void Hash_init(){
    std::sort(&Hash[1],&Hash[n+1]);
    sz = std::unique(&Hash[1],&Hash[n+1]) - Hash - 1;
}

inline int GHash(int x){
    return std::lower_bound(&Hash[1],&Hash[sz+1],x) - Hash;
}

void build(int &o,int l,int r){
    o = ++cnt;
    sum(o) = 0;
    if (l==r) return;
    int m = l + r >> 1;
    build(ls(o),l,m);
    build(rs(o),m+1,r);
    return;
}

void dfs(int u,int f,int be){
    size[u] = 1;
    vis[u] = 1;deep[u] = deep[f]+1;
    fa[u][0] = f;belong[u] = be;
    insert(root[u],root[f],1,sz,GHash(val[u]));
    for (int i = 1;i <= 19;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for (int i = first[u]; i; i = a[i].next){
        if (a[i].v == f) continue;
        dfs(a[i].v,u,be);
        size[u]+=size[a[i].v];
    }
    return;
}

inline int lca(int x,int y){
    if (deep[x]<deep[y])swap(x,y);
    int t=deep[x]-deep[y];
    for (int i = 0; i <= 19; i++)
        if (t&(1<<i))
            x=fa[x][i];
    if (x == y)return x;
    for(int i = 19; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}

int Query(int u,int v,int k){
    int x = lca(u,v),y = fa[x][0];
    int l = 1,r = sz;
    int root_u = root[u],root_v = root[v],root_lca = root[x],root_fa = root[y];
    while(l < r){
        int tmp = tree[tree[root_u].l].sum-tree[tree[root_fa].l].sum+tree[tree[root_v].l].sum-tree[tree[root_lca].l].sum;
        int m = l + r >> 1;
        if (tmp >= k){
            root_u = tree[root_u].l;root_lca = tree[root_lca].l;
            root_v = tree[root_v].l;root_fa = tree[root_fa].l;
            r = m;
        }
        else{
            k -= tmp;
            root_u = tree[root_u].r;root_lca=tree[root_lca].r;
            root_v = tree[root_v].r;root_fa =tree[root_fa].r;
            l = m + 1;
        }
    }
    return Hash[l];
}

int main(){
    read<int>();
    n=read<int>();m=read<int>();q=read<int>();
    for (int i = 1; i <= n; i++)val[i]=read<int>(),Hash[i]=val[i];
    for (int i = 1; i <= m; i++){
        int u=read<int>(),v=read<int>();
        push(u,v);push(v,u);
    }Hash_init();
    build(root[0],1,sz);
    for (int i = 1; i <= n; i++)if (!vis[i])dfs(i,0,++num),id[num]=i;
    while(q--){
        char ch=getchar();
        while(ch != 'Q' && ch != 'L') ch = getchar();
        if (ch == 'Q'){
            int x = read<int>()^Ans,y = read<int>()^Ans,k = read<int>()^Ans;
            printf("%d\n",Ans = Query(x,y,k));
        }
        else{
            int x = read<int>()^Ans,y = read<int>()^Ans;
            if  (size[id[belong[x]]] > size[id[belong[y]]]) swap(x,y);
            push(y,x); push(x,y);
            size[id[belong[y]]] += size[id[belong[x]]];
            dfs(x,y,belong[y]);
        }
    }
    return 0;
}
