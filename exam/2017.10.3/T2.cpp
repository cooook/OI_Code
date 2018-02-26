#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define int long long 
int n,m,h[305][305],cnt,id[305][305],dis[305*305],first[305*305],e = 1;
bool vis[305*305];
std::queue<int>Q;


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct edge{
    int u,v,next,w;
}a[1000005];

inline void push(int u,int v,int w){
    a[e].u=u;a[e].v=v;a[e].w=w;
    a[e].next=first[u];first[u]=e++;
}

inline void spfa(int x) {
    vis[x] = 1;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop(); vis[u] = 0;
        for (int i = first[u];i;i = a[i].next) {
            register int v = a[i].v;
            if (dis[v] > std::max(0ll,dis[u] + a[i].w)) {
                dis[v] = std::max(0ll,dis[u] + a[i].w);
                if (!vis[v]) vis[v] = 1,Q.push(v);
            }
        }
    }
}

signed main(){
    n = read<int>(); m = read<int>();
    memset(dis,0x3f,sizeof dis);
    n ++; m ++; n ++; m ++;
    for (int i = 1;i<=n;i++)
        for (int j = 1;j<=m;j++) 
            id[i][j] = ++ cnt;
    for (int i = 2;i<n;i++)
        for (int j = 2;j<m;j++)
            h[i][j] = read<int>();
    dis[1] = 0; Q.push(1);
    for (int i = 1;i<=n;i++)
        for (int j = 1;j<=m;j++) {
            if (i > 1) push(id[i][j],id[i-1][j],h[i][j] - h[i-1][j]),push(id[i-1][j],id[i][j],h[i-1][j] - h[i][j]);
            if (j > 1) push(id[i][j],id[i][j-1],h[i][j] - h[i][j-1]),push(id[i][j-1],id[i][j],h[i][j-1] - h[i][j]);
        } 
    spfa(1);
    for (int i = 2;i<n;i++,puts(""))
        for (int j = 2;j<m;j++)
            printf("%lld ",dis[id[i][j]]);
    getchar(); getchar();
    return 0;
}