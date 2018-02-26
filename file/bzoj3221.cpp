#include <stdio.h>
#include <iostream>
#define int long long
const int MAXN = 100005;
int first[MAXN],e = 1,n,m,root[MAXN],cnt,Now_Num,Last_Ans;


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

struct node{
    int l,r,sum,a,b;
}tree[MAXN*200];

#define ls(o) tree[o].l
#define rs(o) tree[o].r
#define sum(o) tree[o].sum

inline void Update(int &o,int old,int l,int r,int x,int y,int a,int b){
    o = ++ cnt; tree[o] = tree[old];
    if (l == x && y == r){
        tree[o].a += a; tree[o].b += b;
        tree[o].sum += 1ll * a * (r - l + 1) + 1ll * (r - l) * (r - l + 1) / 2 * b;
        return;
    }
    register int mid = (l + r) >> 1;
    if (y <= mid) Update(ls(o),ls(old),l,mid,x,y,a,b);
    else if (mid < x) Update(rs(o),rs(old),mid+1,r,x,y,a,b);
    else{
        Update(ls(o),ls(old),l,mid,x,mid,a,b);
        Update(rs(o),rs(old),mid+1,r,mid+1,y,a + (mid - x + 1) * b, b);
    }
    tree[o].sum = tree[ls(o)].sum + tree[rs(o)].sum + tree[o].a * (r - l + 1) + (r - l) * (r - l + 1) / 2 * tree[o].b;
}

inline int Query(int o,int l,int r,int x,int y){
    if (l == x && r == y) return tree[o].sum;
    register int mid = (l + r) >> 1,Ans = tree[o].a * (y - x + 1) + tree[o].b * ((x - l) * (y - x + 1) + (y - x + 1) * (y - x) / 2);
    if (y <= mid) return Query(ls(o),l,mid,x,y) + Ans;
    else if (x > mid) return Query(rs(o),mid+1,r,x,y) + Ans;
    else return Query(ls(o),l,mid,x,mid) + Query(rs(o),mid+1,r,mid+1,y) + Ans;
}

int size[MAXN],deep[MAXN],son[MAXN],top[MAXN],fa[MAXN],tot,id[MAXN];

inline void dfs(int u,int fa){
    size[u] = 1; deep[u] = deep[fa] + 1; ::fa[u] = fa;
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v,u); size[u] += size[v];
        if (size[son[u]] < size[v]) son[u] = v;
    }
}

inline void dfs2(int u,int Num){
    top[u] = Num; id[u] = ++ tot;
    if (son[u]) dfs2(son[u],Num);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa[u] && a[i].v != son[u])
            dfs2(a[i].v,a[i].v);
}

inline int lca(int u,int v){
    int f1 = top[u], f2 = top[v];
    while (f1 != f2){
        if (deep[f1] < deep[f2]) std::swap(f1,f2), std::swap(u,v);
        u = fa[f1], f1 = top[u];
    }
    if (deep[u] > deep[v]) std::swap(u,v);
    return u;
}

inline void Tree_Update_Up(int u,int father,int a,int b){
    int f1 = top[u];
    while (f1 != top[father]){
        a += (deep[u] - deep[f1]) * b;
        Update(root[Now_Num],root[Now_Num],1,n,id[f1],id[u],a,-b);
        u = fa[f1]; f1 = top[u]; a += b;
    }
    a += (deep[u] - deep[father]) * b;
    Update(root[Now_Num],root[Now_Num],1,n,id[father],id[u],a,-b);
}

inline void Tree_Update_Down(int u,int father,int a,int b){
    int f1 = top[u];
    while (f1 != top[father]){
        a -= (deep[u] - deep[f1]) * b;
        Update(root[Now_Num],root[Now_Num],1,n,id[f1],id[u],a,b);
        u = fa[f1]; f1 = top[u]; a -= b;
    }
    a -= (deep[u] - deep[father]) * b;
    Update(root[Now_Num],root[Now_Num],1,n,id[father],id[u],a,b);
}

inline int Query(int u,int v){
    int Ans = 0,f1 = top[u], f2 = top[v];
    while (f1 != f2){
        if (deep[f1] < deep[f2]) std::swap(f1,f2), std::swap(u,v);
        Ans += Query(root[Now_Num],1,n,id[f1],id[u]);
        u = fa[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) std::swap(u,v);
    Ans += Query(root[Now_Num],1,n,id[u],id[v]);
    return Ans;
}

int WTF;

signed main(){
    n = read<int>(); m = read<int>();
    for (int i = 1; i < n; i++){
        register int u = read<int>(), v = read<int>();
        push(u,v), push(v,u);
    } dfs(1,0); dfs2(1,1);
    while (m--){
        Last_Ans = 0;
        char ch = getchar();
        while (ch != 'c' && ch != 'q' && ch != 'l') ch = getchar();
        if (ch == 'c'){
            root[++WTF] = root[Now_Num];
            Now_Num = WTF;
            register int u = read<int>() ^ Last_Ans,v = read<int>() ^ Last_Ans,a = read<int>(),b = read<int>();
            int Lca = lca(u,v);
            Tree_Update_Up(u,Lca,a,b);
            a += b * (deep[u] + deep[v] - 2 * deep[Lca]);
            Tree_Update_Down(v,Lca,a,b);
            a -= b * (deep[v] - deep[Lca]);
            Update(root[Now_Num],root[Now_Num],1,n,id[Lca],id[Lca],-a,0);
        }
        else if (ch == 'q'){
            int u = read<int>() ^ Last_Ans,v = read<int>() ^ Last_Ans;
            printf("%lld\n",Last_Ans = Query(u,v));
        }
        else{
            int x = read<int>() ^ Last_Ans;
            Now_Num = x;
        }
    }
    return 0;
}
