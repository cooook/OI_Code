#include <bits/stdc++.h>
#define MAXN 100005
int n,r,c,first[MAXN],e = 1,id[MAXN],val[MAXN],Ans;
int dis[MAXN],fa[MAXN],du[MAXN],Now;
std::queue<int>Q;
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
struct edge{
    int u,v,next;
}a[MAXN*50];
 
inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
} 
 
struct Point{
    int d[2],id,now;
    inline int& operator [] (const int &x) {return d[x];}
    inline bool operator < (const Point &x) const{
        return d[Now] == x.d[Now]?d[Now^1]<x.d[Now^1]:d[Now]<x.d[Now];
    }
    inline bool operator == (const Point &x) const{
        return d[0] == x.d[0] && d[1] == x.d[1];
    }
}pt[MAXN];
 
struct Hash_table{
    struct E{
        Point u;
        int v,next;
    }a[MAXN];
    int first[76545],e;
    Hash_table(){e = 1;memset(first,0,sizeof first);}
  
    #define x_P 9091
    #define y_P 7307
    #define P 76543
 
    inline int& New(int Hash,Point x) {
        a[e].u = x; a[e].v = 0; a[e].next = first[Hash]; first[Hash] = e++;
        return a[e-1].v;
    }
 
    inline bool count(Point x) {
        int Hash = ((x[0]%x_P)+x_P) % x_P * ((x[1]%y_P)+y_P) % y_P % P;
        for(int i = first[Hash];i;i=a[i].next) if(a[i].u == x) return true;
        return false;
    }
  
    inline int& operator [] (Point x){
        int Hash = ((x[0]%x_P)+x_P) % x_P * ((x[1]%y_P)+y_P) % y_P % P;
        for(int i = first[Hash];i;i=a[i].next) if(a[i].u == x) return a[i].v;
        return New(Hash,x);
    }
}ma;
 
int low[MAXN],dfn[MAXN],cnt,belong[MAXN],scc,size[MAXN],st[MAXN],top;
bool vis[MAXN];
inline void tarjan(int u) {
    low[u] = dfn[u] = ++cnt;
    st[++top] = u; vis[u] = true;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (!dfn[v]) tarjan(v),low[u] = low[u]<low[v]?low[u]:low[v];
        else if (vis[v]) low[u] = low[u] < dfn[v]?low[u]:dfn[v]; 
    }
    if (low[u] == dfn[u]) {
        int v; scc ++;
        do {
            v = st[top--];
            vis[v] = false;
            size[scc] ++;
            belong[v] = scc;
        } while (u != v);
    }
}
 
inline void Tuopu() {
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next) {
            du[a[i].v] --;
            dis[a[i].v] = std::max(dis[u] + size[a[i].v],dis[a[i].v]);
            if (!du[a[i].v]) Q.push(a[i].v);
        }
    }
}
 
inline void Add(int Woc) {
    Now = Woc - 1; int l = 0,r = 0;
    std::sort(&pt[1],&pt[n+1]);
    while (r < n) {
        l = r + 1; r = l;
        while (pt[r + 1][Now] == pt[l][Now] && r < n) r ++;
        int x = 0;
        for (int i = l; i <= r; i++) if (pt[i].id == Woc) {x = i; break;}
        if (!x) continue;
        for (int i = l; i <= r; i++) {
            if (i == x) continue;
            push(pt[x].now,pt[i].now);
            if (pt[i].id == Woc) push(pt[i].now,pt[x].now);
        }
    }
}
 
int main() {
    n = read<int>(); r = read<int>(); c = read<int>();
    for (int i = 1; i <= n; i++) {
        pt[i][0] = read<int>(),pt[i][1] = read<int>(),pt[i].id = read<int>(),pt[i].now = i;
        ma[(Point){pt[i][0],pt[i][1]}] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (pt[i].id != 3) continue;
        if (ma.count((Point){pt[i][0]-1,pt[i][1]-1})) push(i,ma[(Point){pt[i][0]-1,pt[i][1]-1}]);
        if (ma.count((Point){pt[i][0]-1,pt[i][1]})) push(i,ma[(Point){pt[i][0]-1,pt[i][1]}]);
        if (ma.count((Point){pt[i][0]-1,pt[i][1]+1})) push(i,ma[(Point){pt[i][0]-1,pt[i][1]+1}]);
        if (ma.count((Point){pt[i][0],pt[i][1]-1})) push(i,ma[(Point){pt[i][0],pt[i][1]-1}]);
        if (ma.count((Point){pt[i][0],pt[i][1]+1})) push(i,ma[(Point){pt[i][0],pt[i][1]+1}]);
        if (ma.count((Point){pt[i][0]+1,pt[i][1]-1})) push(i,ma[(Point){pt[i][0]+1,pt[i][1]-1}]);
        if (ma.count((Point){pt[i][0]+1,pt[i][1]})) push(i,ma[(Point){pt[i][0]+1,pt[i][1]}]);
        if (ma.count((Point){pt[i][0]+1,pt[i][1]+1})) push(i,ma[(Point){pt[i][0]+1,pt[i][1]+1}]);
    }
    Add(1); Add(2);
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
    memset(first,0,sizeof first);
    int tot = e - 1;
    for (int i = 1; i <= tot; i++)
        if (belong[a[i].u] != belong[a[i].v]) 
            push(belong[a[i].u],belong[a[i].v]),du[belong[a[i].v]]++;
    for (int i = 1; i <= scc; i++) if (!du[i]) Q.push(i),dis[i] = size[i];
    Tuopu(); int Ans = 0;
    for (int i = 1; i <= scc; i++) Ans = std::max(Ans,dis[i]);
    printf("%d\n",Ans);
    // while (true);
    return 0;
}