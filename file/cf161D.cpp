#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
#define MAXN 50005
int first[MAXN],e = 1,n,m,root,size[MAXN],f[MAXN],cnt,num,ton[MAXN],tmp[MAXN];
bool vis[MAXN];ll Ans;


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u;a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void G_root(int u,int fa){
    f[u] = 0,size[u] = 1;
    for(int i = first[u];i;i=a[i].next) 
        if(!vis[a[i].v] && a[i].v != fa){
            register int v = a[i].v;
            G_root(a[i].v,u);
            size[u] += size[v];
            f[u] = std::max(f[u],size[v]);
        }
    f[u] = std::max(f[u],num - f[u]);
    if(f[u] < f[root]) root = u;
}

inline void G_d(int u,int fa,int dis){
    if(dis <= m) {
        Ans += ton[m - dis];
        ++ tmp[dis];
    }
    else return ;
    for(int i = first[u];i;i=a[i].next) {
        register int v = a[i].v;
        if(v == fa || vis[v]) continue;
        G_d(v,u,dis + 1);
    }
    return ;
}

inline void G_Ans(int u) {
    memset(ton,0,sizeof ton); ton[0] = 1;
    for(int i = first[u];i;i=a[i].next) {
        register int v = a[i].v;
        if(vis[v]) continue; 
        memset(tmp,0,sizeof tmp);G_d(v,0,1); 
        for(int j = 1;j<=m;j++) ton[j] += tmp[j]; 
    }
}

inline void dfs(int u){
    vis[u] = 1;G_Ans(u);
    for(int i = first[u];i;i = a[i].next) {
        if(vis[a[i].v]) continue;
        num = size[u]; root = 0;
        G_root(a[i].v,0); dfs(root);
    }
}

int main(){
    n = read<int>(); m = read<int>();
    for(int i = 1;i<n;i++) {
        register int u = read<int>(),v = read<int>();
        push(u,v); push(v,u);
    }
    root = 0; f[0] = 0x7fffffff; num = n;
    G_root(1,0); dfs(root);
    cout << Ans << endl;
    return 0;
}