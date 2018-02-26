#include <bits/stdc++.h>
const int MAXN = 100005;
int T,top[MAXN],f[MAXN],deep[MAXN],size[MAXN],pos[MAXN],son[MAXN],n,m,first[MAXN],e = 1,cnt;
int vis[MAXN<<2],tag[MAXN<<2];
 
 
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(; ch > '9' || ch < '0'; ch = getchar()) if (ch=='-')f=-f;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x*f;
}
 
struct edge{
    int u,v,next;
}a[MAXN<<1];
 
inline void push(int u,int v){
    a[e].u=u;a[e].v=v;a[e].next=first[u];first[u] = e ++;
}
 
inline void dfs(int u){
    size[u] = 1;
    for(int i = first[u];i;i=a[i].next) {
        register int v = a[i].v;
        if (v == f[u])continue;
        f[v] = u; deep[v] = deep[u] + 1;
        dfs(v); size[u] += size[v];
        if (size[v]>size[son[u]]) son[u] = v;
    }
}
 
inline void __dfs__(int u,int num){
    top[u] = num;pos[u] = ++cnt;
    if (son[u]) __dfs__(son[u],num);
    for(int i = first[u];i;i=a[i].next) if (a[i].v!=f[u]&&a[i].v!=son[u]) __dfs__(a[i].v,a[i].v);
}
 
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
 
inline void Push_down(int o){
    if (tag[o]) {
        tag[o<<1] = tag[o<<1|1] = 1;
        vis[o<<1] = vis[o<<1|1] = 1;
        tag[o] = 0;
    }
}

inline void Maintain(int o) {
    vis[o] = 0;
    vis[o] |= vis[o << 1];
    vis[o] |= vis[o << 1 | 1];
}
 
inline void Update(int o,int l,int r,int x,int y){
    if (x<=l&&r<=y) {tag[o] = 1;vis[o] = 1;return;}
    register int mid = l + r >> 1;
    Push_down(o);
    if (x<=mid) Update(lson,x,y);
    if (mid<y) Update(rson,x,y);
    Maintain(o);
}
 
inline int Query(int o,int l,int r,int x,int y){
    if (x <= l && r <= y) return vis[o];
    register int mid = l + r >> 1,Ans = 0; Push_down(o);
    if (x <= mid) Ans += Query(lson,x,y);
    if (mid < y) Ans += Query(rson,x,y);
    return Ans;
}

inline int Lca(int u,int v) {
    int f1 = top[u],f2 = top[v];
    while(f1 != f2) {
        if (deep[f1]<deep[f2]) std::swap(f1,f2),std::swap(u,v);
        u = f[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) std::swap(u,v);
    return u;
}

inline int Query(int u,int v) {
    int f1 = top[u],f2 = top[v],Ans = 0;
    while(f1 != f2) {
        if (deep[f1]<deep[f2]) std::swap(f1,f2),std::swap(u,v);
        Ans += Query(1,1,n,pos[f1],pos[u]);
        u = f[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) std::swap(u,v);
    if (pos[u] <= pos[v]) Ans += Query(1,1,n,pos[u],pos[v]);
    return Ans;
}

inline void Change(int u,int v){
    int f1 = top[u],f2 = top[v];
    while(f1 != f2) {
        if (deep[f1]<deep[f2]) std::swap(f1,f2),std::swap(u,v);
        Update(1,1,n,pos[f1],pos[u]);
        u = f[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) std::swap(u,v);
    if (pos[u]<=pos[v]) Update(1,1,n,pos[u],pos[v]);
}

inline void Clear() {
    e = 1; cnt = 0;
    memset(first,0,sizeof first);
    memset(top,0,sizeof top);
    memset(f,0,sizeof f);
    memset(pos,0,sizeof pos);
    memset(vis,0,sizeof vis);
    memset(tag,0,sizeof tag);
    memset(son,0,sizeof son);
    memset(size,0,sizeof size);
    memset(deep,0,sizeof deep);
}

struct Query{
    int u,v,lca;
    inline bool operator < (const Query &x) const {
        return deep[lca] > deep[x.lca];
    }
}Q[MAXN];
 
int main(){
    freopen("Tree.in","r",stdin);
    freopen("Tree_cut.out","w",stdout);
    T = read<int>();
    while (T --) {
        Clear();
        n = read<int>(); m = read<int>();
        for (int i = 1; i < n; i++) {
            register int u = read<int>(),v = read<int>();
            push(u,v); push(v,u);
        } dfs(1); __dfs__(1,1);
        int Ans = 0;
        for (int i = 1; i <= m; i++) Q[i].u = read<int>(),Q[i].v = read<int>(),Q[i].lca = Lca(Q[i].u,Q[i].v);
        std::sort(&Q[1],&Q[m + 1]);
        for (int i = 1; i <= m; i++) {
            if (Query(Q[i].u,Q[i].v)) continue;
            Ans ++; Change(Q[i].u,Q[i].v);
        }
        printf("%d\n",Ans); 
    }
    return 0;
}