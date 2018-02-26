#include <bits/stdc++.h>
#define MAXN 100005
#define P(x) ((x&1)?(x+1):(x-1))
int n,m,Col[MAXN],Ans[MAXN],first[MAXN],e = 1,cnt;


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
}a[MAXN<<1];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline bool dfs(int u) {
    if (Col[u]) return Col[u] & 1;
    Col[u] = 1;Col[P(u)] = 2;
    Ans[++cnt] = u;
    for (int i = first[u]; i; i = a[i].next) 
        if (!dfs(a[i].v)) return false;
    return true;
}

inline bool Work() {
    for (int i = 1; i <= n << 1; i++) {
        if (Col[i]) continue;
        cnt = 0;
        if (!dfs(i)) {
            for (int j = 1; j <= cnt; j++)
                Col[Ans[j]] = Col[P(Ans[j])] = 0;
            if (!dfs(P(i))) return false;
        } 
    }
    return true;
}

int main() {
    freopen("spo.in","r",stdin);
    freopen("spo.out","w",stdout);
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= m; i++) {
        register int u = read<int>(),v = read<int>();
        push(u,P(v)); push(v,P(u));
    }
    if (Work()) {
        for (int i = 1; i <= n << 1; i++)
            if (Col[i] == 1) printf("%d\n",i);
    }
    else puts("NIE");
    return 0;
}