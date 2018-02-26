#include <stdio.h>
#include <cstring>
const int MAXN = 2005;
int T,n,m,k,first[MAXN],e = 1,f[MAXN];
bool vis[MAXN],flag; 


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next,w;
}a[MAXN*MAXN];

inline void push(int u,int v,int w) {
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

void dfs(int u) {
    if (flag) return;
    vis[u] = true;
    for (int v,i = first[u]; i; i = a[i].next) {
        v = a[i].v;
        if (vis[v]) {
            if (f[v] + f[u] != a[i].w)  return flag = true,void();
            continue;
        }
        f[v] = a[i].w - f[u];
        dfs(v);
        if (flag) return;
    }
}

int main() {
    T = read<int>();
    while (T--) {
        flag = false;
        memset(f,0,sizeof f);
        memset(vis,false,sizeof vis);
        memset(first,0,sizeof first); e = 1;
        n = read<int>(); m = read<int>(); k = read<int>();
        for (int x,y,w,i = 1; i <= k; i++) {
            x = read<int>(),y = read<int>(),w = read<int>();
            push(x,y+n,w),push(y+n,x,w);
        }
        for (int i = 1; i <= n + m; i++)
            if (!vis[i]) dfs(i);
        printf("%s\n",flag?"No":"Yes");
    }
    return 0;
}