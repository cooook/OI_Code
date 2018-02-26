#pragma GCC optimize("O3")
#include <stdio.h>
#include <queue>
const int MAXN = 100005;
int n,first[MAXN],e = 1,f[MAXN][20],deep[MAXN],m,size[MAXN],Num,root,F[MAXN],pre[MAXN],cnt;
bool vis[MAXN],State[MAXN];


char xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read() {
    int x = 0, f = 1; char ch = getc();
    for (; ch < '0' | ch > '9'; ch = getc()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getc()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Heap{
    std::priority_queue<int> Q,G;
    inline void push(int x){Q.push(x);}
    inline void erase(int x){G.push(x);}
    inline int size(){return Q.size() - G.size();}
    inline int top(){
        while (!G.empty() && G.top() == Q.top()) Q.pop(), G.pop(); 
        return Q.empty()?0:Q.top();
    }
    inline int sec_top(){
        if (size() < 2) return 0; 
        int x = top(); Q.pop();
        int y = top(); Q.push(x);
        return y;
    }
}Ans,w[MAXN],g[MAXN];

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u; a[e].v = v; 
    a[e].next = first[u]; first[u] = e++;
}

inline void G_root(int u,int fa){
    size[u] = 1; F[u] = 0;
    for (int i = first[u]; i; i = a[i].next)
        if (!vis[a[i].v] && a[i].v != fa){
            G_root(a[i].v,u);
            size[u] += size[a[i].v];
            F[u] = std::max(size[a[i].v],F[u]);
        }
    F[u] = std::max(F[u],Num - F[u]);
    if (F[u] < F[root]) root = u;
}

inline void dfs(int u,int fa){
    f[u][0] = fa; deep[u] = deep[fa] + 1;
    for (int i = 1; i <= 18; i++) f[u][i] = f[f[u][i-1]][i-1];
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa) dfs(a[i].v,u);
}

inline int lca(int u,int v){
    if (deep[u] < deep[v]) std::swap(u,v);
    int t = deep[u] - deep[v];
    for (int i = 18; ~i; i--)
        if (t >> i & 1)
            u = f[u][i];
    if (u == v) return u;
    for (int i = 18; ~i; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i],v = f[v][i];
    return f[u][0];
}

inline int dis(int u,int v){
    return deep[u] + deep[v] - 2 * deep[lca(u,v)];
}

inline void Divide(int u,int fa){
    pre[u] = fa; vis[u] = true;
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (vis[v] || v == fa) continue;
        root = 0; Num = size[u]; G_root(v,u);
        Divide(root,u);
    }
}

inline void On(int from){
    w[from].erase(0);
    if (w[from].size() == 1) Ans.erase(w[from].top());
    for (int u = from; pre[u]; u = pre[u]){
        int f = pre[u], Dis = dis(f,from), tmp = g[u].top(); g[u].erase(Dis);
        if (Dis == tmp){
            int Mx = w[f].top() + w[f].sec_top(), Sz = w[f].size();
            w[f].erase(Dis);
            if (g[u].top()) w[f].push(g[u].top());
            tmp = w[f].top() + w[f].sec_top();
            if (Mx > tmp){
                if (Sz >= 2) Ans.erase(Mx);
                if (w[f].size() >= 2) Ans.push(tmp);
            }
        }
    }
}

inline void Off(int from){
    w[from].push(0);
    if (w[from].size() == 2) Ans.push(w[from].top());
    for (int u = from; pre[u]; u = pre[u]){
        int f = pre[u], Dis = dis(f,from), tmp = g[u].top(); g[u].push(Dis);
        if (Dis > tmp){
            int Mx = w[f].top() + w[f].sec_top(), Sz = w[f].size();
            if (tmp) w[f].erase(tmp);
            w[f].push(Dis);
            tmp = w[f].top() + w[f].sec_top();
            if (Mx < tmp){
                if (Sz >= 2) Ans.erase(Mx);
                if (w[f].size() >= 2) Ans.push(tmp);
            }
        }
    }
}

int main(){
    n = read();
    for (int i = 1; i < n; i++){
        register int u = read(),v = read();
        push(u,v), push(v,u);
    } F[0] = n; dfs(1,0); Num = n; G_root(1,0); Divide(root,0);
    for (int i = 1; i <= n; i++) g[i].push(0);
    for (int i = 1; i <= n; i++) Off(i); cnt = n;
    m = read();
    while (m --){
        char ch = getchar();
        while (ch != 'G' && ch != 'C') ch = getchar();
        if (ch == 'G'){
            if (cnt <= 1) printf("%d\n",cnt - 1);
            else printf("%d\n",Ans.top());
        }
        else{
            int x = read();
            if (State[x]) Off(x), cnt ++;
            else On(x), cnt --;
            State[x] ^= 1;
        }
    }
    return 0;
}