#include <stdio.h>
#include <cstring>
#include <queue>
#include <iostream>
#define MAXN 300005
int n,s,first[MAXN],e = 1,root,rt,fa[MAXN],L,R,st[MAXN],top,dis[MAXN],Ans;
bool flag,tag[MAXN],vis[MAXN];


template<typename _t>
inline void read(_t &x){
    x = 0;bool flag = false; char ch = getchar();
    for (;!isdigit(ch); ch=getchar()) if (ch == '-') flag = true;
    for (;isdigit(ch); ch=getchar()) x = x * 10 + (ch ^ 48);
    if (flag) x = -x;
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w){
    a[e].u=u;a[e].v=v;a[e].w=w;
    a[e].next=first[u];first[u]=e++;
}

inline void bfs(int x) {
    memset(dis,0,sizeof dis);
    memset(vis,0,sizeof vis);
    std::queue<int>Q;Q.push(x); dis[x] = 0;
    while (!Q.empty()) {
        register int u = Q.front();Q.pop();
        vis[u] = true;
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v;
            if (vis[v]) continue;
            fa[v] = u;            
            if (tag[v]) dis[v] = dis[u];
            else  dis[v] = dis[u] + a[i].w;
            Q.push(v);
        }
    }
}

inline bool Judge(int mid) {
    int l = 1,r = top;
    while (st[1] - st[l+1] <= mid && l <= top) l ++;
    while (st[r-1] - st[top] <= mid && r) r --;
    return st[l] - st[r] <= s;
}

int main(){
    read(n); read(s);
    for (int i = 1; i < n; i++) {
        register int u,v,w;
        read(u); read(v); read(w);
        push(u,v,w); push(v,u,w);
    }
    bfs(1); 
    for (int i = 1; i <= n; i++) if (dis[i] > dis[root]) root = i;
    bfs(root);
    for (int i = 1; i <= n; i++) if (dis[i] > dis[rt]) rt = i; 
    R = dis[rt];
    st[++top] = dis[rt];
    while (rt != root) {
        st[++top] = dis[rt];    
        tag[rt] = true;
        rt = fa[rt];
    }
    st[++top] = dis[root];
    bfs(root);
    for (int i = 1; i <= n; i++) L = std::max(L,dis[i]);
    while (L<=R) {
        register int mid = L + R >> 1;
        if (Judge(mid)) Ans = mid, R = mid - 1;
        else L = mid + 1;
    }
    printf("%d\n",Ans);
    return 0;
}