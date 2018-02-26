#include <stdio.h>
#include <cstring>
#include <iostream>
#define GD puts("GOOD")
#define BD puts("BAD")
#define MAXN 505
int T,n,m,p[MAXN][2],first[MAXN],e = 1;


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
}a[3005];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline int read_char() {
    char ch = getchar();
    for (; ch != 'm' && ch != 'h'; ch = getchar()) ;
    return ch == 'm';
}

int dfn[MAXN],low[MAXN],cnt,st[MAXN],top,belong[MAXN],scc;
bool vis[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++ cnt; st[++top] = u; vis[u] = true;
    for (int i = first[u]; i; i = a[i].next) 
        if (!dfn[a[i].v]) tarjan(a[i].v),low[u] = std::min(low[u],low[a[i].v]);
        else if (vis[a[i].v]) low[u] = std::min(low[u],dfn[a[i].v]);
    if (low[u] == dfn[u]) {
        scc ++;
        register int v;
        do {
            v = st[top--];
            vis[v] = false;
            belong[v] = scc;
        } while (u != v);
    }
}

int main() {    
    T = read<int>();
    while (T --) {
        memset(dfn,0,sizeof dfn);
        memset(low,0,sizeof low);
        memset(first,0,sizeof first);
        memset(belong,0,sizeof belong);
        e = 1; cnt = 0;
        n = read<int>(); m = read<int>(); 
        int tot = 0;
        for (int i = 1; i <= n; i++) p[i][0] = ++tot,p[i][1] = ++tot;
        for (int i = 1; i <= m; i++) {
            register int op1 = read_char(),x = read<int>(),op2 = read_char(),y = read<int>();
            push(p[x][op1^1],p[y][op2]);
            push(p[y][op2^1],p[x][op1]);
        }
        for (int i = 1; i <= n << 1; i++) 
            if (!dfn[i]) tarjan(i);
        for (int i = 1; i <= n; i++)
            if (belong[p[i][0]] == belong[p[i][1]])
                {BD;goto here;}
        GD;
        here:;
    }
    return 0;
}