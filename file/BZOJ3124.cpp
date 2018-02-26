#include <stdio.h>
#include <iostream>
#define int long long
const int MAXN = 200005;
int n,first[MAXN],e = 1,dis[MAXN],Max_Dis,size[MAXN],st[MAXN],top,f[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w){
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int fa,int &root){
    if (dis[u] > dis[root]) root = u;
    f[u] = fa;
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa)
            dis[a[i].v] = dis[u] + a[i].w,
            dfs(a[i].v,u,root);
}

inline void Dfs(int u,int fa){
    size[u] = dis[u] == Max_Dis;
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa)
            dis[a[i].v] = dis[u] + a[i].w,
            Dfs(a[i].v,u),size[u] += (bool)size[a[i].v];
}

signed main(){
    // freopen("fuck_you.in","r",stdin);
    n = read<int>();
    for (int i = 1; i < n; i++){
        register int u = read<int>(),v = read<int>(),w = read<int>();
        push(u,v,w), push(v,u,w);
    }
    int L = 0,R = 0;
    dfs(1,0,L);
    dis[L] = 0, dfs(L,0,R);
    printf("%lld\n",Max_Dis = dis[R]);
    int x = R;
    while (x != L) st[++top] = x,x = f[x];
    st[++top] = L;
    dis[L] = 0, Dfs(L,0);
    int l = 0,r = top;
    for (int i = top; i; i--) if (size[st[i]] > 1) l = i;
    dis[R] = 0, Dfs(R,0);
    for (int i = 1; i <= top; i++) if (size[st[i]] > 1) r = i;
    printf("%lld\n",std::max(0ll,r - l));
    return 0;
}
