#include <bits/stdc++.h>
using std::min;
const int MAXN = 2005ul,inf = 0x7fffffff;
#define S 0
#define T (n+1)
int n,m,from[MAXN],to[MAXN],c[MAXN],d[MAXN],du[MAXN],sum_flow;


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

namespace Max_flow{
    int first[MAXN],e,d[MAXN],Q[MAXN];
    struct edge{
        int u,v,next,w;
    }a[10005];
    inline void add(int u,int v,int w){
        a[e].u=u;a[e].v=v;a[e].w=w;
        a[e].next = first[u];first[u] = e++;
    }
    inline void push(int u,int v,int w){
        add(u,v,w); add(v,u,0);
    }
    inline void clear(){
        memset(first,0,sizeof first);e = 2;
    }
    inline bool bfs(){
        memset(d,-1,sizeof d);
        int l = 0,r = 1;
        d[S] = 0;Q[l] = S;
        while(l<r) {
            int u = Q[l++];
            for(int i = first[u];i;i=a[i].next) 
                if(d[a[i].v] == -1 && a[i].w) d[a[i].v] = d[u] + 1,Q[r++] = a[i].v;
        } 
        return d[T] != -1;
    }
    inline int dfs(int u,int cap){
        if(u == T || !cap) return cap;
        int Ans = 0;
        for(int i = first[u];i;i=a[i].next) {
            register int v = a[i].v,w = a[i].w;
            if(d[v] == d[u] + 1 && w) {
                w = dfs(v,min(w,cap-Ans));
                Ans += w;
                a[i].w -= w;
                a[i^1].w += w;
                if(cap == Ans) return Ans;
            }
        }
        if(!Ans) d[u] = -1;
        return Ans;
    }
    inline int dinic(){
        int Ans = 0;
        while(bfs()) Ans += dfs(S,inf);
        return Ans;
    }
}

inline bool Judge(int x){
    Max_flow::clear();
    for(int i = 1;i<=m;i++) {
        if(c[i] > x) return 0;
        if(d[i] <= x)  Max_flow::push(from[i],to[i],1);
    }
    for(int i = 1;i<=n;i++) 
        if(du[i] > 0) Max_flow::push(S,i,du[i]>>1);
        else Max_flow::push(i,T,(-du[i])>>1);
    if(Max_flow::dinic() == sum_flow) return 1;
    return 0;
}

int main(){
    n = read<int>(); m = read<int>();
    for(int i = 1;i<=m;i++) {
        from[i] = read<int>(); to[i] = read<int>(); c[i] = read<int>();d[i] = read<int>();
        if(c[i] > d[i]) std::swap(from[i],to[i]),std::swap(c[i],d[i]);
        du[from[i]] ++; du[to[i]] --;
    }
    for(int i = 1;i<=n;i++) {
        if(du[i] % 2 != 0) {puts("NIE"); return 0;}
        sum_flow += abs(du[i]) >> 1;
    } sum_flow >>= 1;
    int l = 0,r = 1000,Ans = -1,mid;
    while(l<=r) {
        mid = l + r >> 1;
        if(Judge(mid)) Ans = mid , r = mid - 1;
        else l = mid + 1;
    } printf("%d\n",Ans);
    // getchar(); getchar();
    return 0;
}