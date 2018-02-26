#include <bits/stdc++.h>
#define ls (o << 1)
#define rs (o << 1 | 1)
#define fi first
#define se second
#define mk(x,y) std::make_pair(x,y)
#define Min(x,y) ((x)<(y)?(x):(y))
typedef std::pair<int,int> pa;
const int MAXN = 30005;
std::map<pa,bool> ma;
int Ans[40005],first[MAXN],e = 1,n,m;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Swap(int &x,int &y) {
    x ^= y; y ^= x; x ^= y;
}

struct edge{
    int u,v,next;
}a[100005<<2],E[100005];

struct Operation{
    int op,x,y;
}C[200005];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

namespace Tarjan {
    int low[MAXN],dfn[MAXN],idx,st[MAXN],top,bcc,belong[MAXN];
    bool vis[MAXN];

    inline void tarjan(int u,int fa) {
        vis[u] = true; st[++top] = u; low[u] = dfn[u] = ++ idx;
        for (int i = first[u]; i; i = a[i].next) {
            if (a[i].v == fa) continue;
            else if (!dfn[a[i].v]) tarjan(a[i].v,u),low[u] = Min(low[u],low[a[i].v]);
            else if (vis[a[i].v]) low[u] = Min(low[u],dfn[a[i].v]); 
        }
        if (low[u] == dfn[u]) {
            register int v; bcc ++;
            do {
                v = st[top--];
                vis[v] = false;
                belong[v] = bcc;
            }while (u != v);
        }
    }
}

int son[MAXN],size[MAXN],Tree_cnt,f[MAXN],deep[MAXN],tree[MAXN],top[MAXN];
int sum[MAXN<<2];

inline void dfs(int u,int fa) {
    size[u] = 1; f[u] = fa; deep[u] = deep[fa] + 1;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v,u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

inline void __dfs(int u,int num) {
    top[u] = num; tree[u] = ++ Tree_cnt;
    if (son[u]) __dfs(son[u],num);
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != f[u] && a[i].v != son[u])
            __dfs(a[i].v,a[i].v);
}

inline void Push_down(int o,int l,int r) {
    if (l == r) return;
    if (sum[o] == 0)
        sum[ls] = sum[rs] = 0;
}

inline void Update(int o,int l,int r,int x,int y) {
    if (x > y) return;
    if (x <= l && r <= y) return sum[o] = 0,void();
    register int mid = l + r >> 1;
    Push_down(o,l,r);
    if (x <= mid) Update(ls,l,mid,x,y);
    if (mid < y) Update(rs,mid+1,r,x,y);
    sum[o] = sum[ls] + sum[rs];
}

inline int Query(int o,int l,int r,int x,int y) {
    if (x > y) return 0;
    if (x <= l && r <= y) return sum[o];
    Push_down(o,l,r);
    register int mid = l + r >> 1,Ans = 0;
    if (x <= mid) Ans += Query(ls,l,mid,x,y);
    if (mid < y) Ans += Query(rs,mid+1,r,x,y);
    return Ans;
}

inline void build(int o,int l,int r) {
    if (l == r) return sum[o] = (l != 1),void();
    register int mid = l + r >> 1;
    build(ls,l,mid); build(rs,mid+1,r);
    sum[o] = sum[ls] + sum[rs];
}

inline void Change(int u,int v) {
    if (u == v) return;
    int f1 = top[u],f2 = top[v];
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) Swap(u,v),Swap(f1,f2);
        Update(1,1,Tree_cnt,tree[f1],tree[u]);
        u = f[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) Swap(u,v);
    Update(1,1,Tree_cnt,tree[son[u]],tree[v]);
}

inline int Query(int u,int v) {
    if (u == v) return 0;
    int f1 = top[u],f2 = top[v],Ans = 0;
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) Swap(u,v),Swap(f1,f2);
        Ans += Query(1,1,Tree_cnt,tree[f1],tree[u]);
        u = f[f1]; f1 = top[u];
    }
    if (deep[u] > deep[v]) Swap(u,v);
    Ans += Query(1,1,Tree_cnt,tree[son[u]],tree[v]);
    return Ans;
}

int main() {
    using Tarjan::tarjan;
    using Tarjan::belong;
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= m; i++) E[i].u = read<int>(),E[i].v = read<int>();
    int cnt = 0;
    while (true) {
        C[++cnt].op = read<int>();
        if (C[cnt].op == -1) {
            cnt --;
            break;
        }
        C[cnt].x = read<int>();
        C[cnt].y = read<int>();
        if (C[cnt].op == 0) ma[mk(C[cnt].x,C[cnt].y)] = true,ma[mk(C[cnt].y,C[cnt].x)] = true;
    }
    for (int i = 1; i <= m; i++) {
        if (ma.count(mk(E[i].u,E[i].v))) continue;
        push(E[i].u,E[i].v); push(E[i].v,E[i].u);
    }
    for (int i = 1; i <= n; i++)
        if (!Tarjan::dfn[i]) tarjan(i,0);
    int tot = e - 1;
    memset(first, 0, sizeof first);
    for (int i = 1; i <= tot; i++) 
        if (belong[a[i].u] != belong[a[i].v])
            push(belong[a[i].u],belong[a[i].v]);
    dfs(1,0); __dfs(1,1);
    build(1,1,Tree_cnt);
    int Query_cnt = 0;
    for (; cnt; cnt--) {
        if (C[cnt].op == 0)  Change(belong[C[cnt].x],belong[C[cnt].y]);
        else Ans[++Query_cnt] = Query(belong[C[cnt].x],belong[C[cnt].y]);
    }
    for (int i = Query_cnt; i; i--) printf("%d\n",Ans[i]);
    return 0;
}