#include <stdio.h>
#include <cstring>
#define MAXN 500005
int first[MAXN][2],e[2],n,m,from,to,mer[800005],vis[MAXN],T;
bool flag;


template<typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int v,next;
}a[800005 << 1][2];

inline void push(int u,int v,int w) {
    a[e[w]][w].v = v;
    a[e[w]][w].next = first[u][w]; first[u][w] = e[w] ++;
}

inline void Merge() {
    ++ n;
    int type = read<int>(),k = read<int>();
    for (int i = 1; i <= k; i++) mer[i] = read<int>();
    if (k == 1) {
        push(mer[1],n,0);
        push(n,mer[1],1);
    }
    else for (int i = 1; i <= k; i++) {
        if (!type) push(n,mer[i],1);
        else push(mer[i],n,0);
    }
}

inline void dfs(int u) {
    if (vis[u] == T) return;
    vis[u] = T;
    if (flag) return;
    if (u == to) return flag = true,void();
    int use = u < to?0:1;
    for (int i = first[u][use]; i; i = a[i][use].next) {
        register int v = a[i][use].v;
        dfs(v); if (flag) return;
    }
}

inline void Query() {
    ++T;
    from = read<int>(); to = read<int>();
    if (from == to) {
        printf("1\n");
        return;
    }   
    flag = false;
    dfs(from);
    printf("%d\n",flag);
}

int main() {
    e[0] = e[1] = 1;
    n = read<int>(); m = read<int>();
    while (m --) {
        int op = read<int>();
        if (op == 0) Merge();
        else Query();
    }
    // md这是颗树 ... 
    return 0;
}