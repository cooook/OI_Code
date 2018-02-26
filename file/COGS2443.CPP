#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define P(x) ((x&1)?(x+1):(x-1))
#define MAXN 20005
int Col[MAXN],Ans[MAXN],first[MAXN],e = 1,cnt,n,m;


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
}a[MAXN << 2];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline bool dfs(int u) {
    if (Col[u]) return Col[u] & 1;
    Col[u] = 1; Col[P(u)] = 2; Ans[++cnt] = u;
    for (int i = first[u]; i; i = a[i].next)
        if (!dfs(a[i].v)) return false;
    return true;
}

inline bool Work() {
    memset(Col,0,sizeof Col);
    for (int i = 1; i <= n << 1; i++) {
        if (Col[i]) continue;
        cnt = 0;
        if (!dfs(i)) {
            for (int j = 1; j <= cnt; j++)
                Col[Ans[j]] = Col[P(Ans[j])] = 0;
            if (!dfs(P(i))) return false;
        }
    }
    for (int i = 1; i <= n << 1; i++)
        if (Col[i] == 1) printf("%d ",i);
    return printf("\n"),true;
}

int main() {
    freopen("T3_.in","r",stdin);
    freopen("T3_.out","w",stdout);
    while (scanf("%d%d",&n,&m) == 2) {
        memset(first,0,sizeof first); e = 1;
        while (m--) {
            int op = read<int>(),x = read<int>(),y;
            if (op > 2) y = read<int>();
            switch(op) {
                case 1:push(P(x),x);break;
                case 2:push(x,P(x));break;
                case 3:push(P(x),x);push(P(y),y);break;
                case 4:push(P(x),x);push(y,P(y));break;
                case 5:push(P(x),y);push(P(y),x);break;
                case 6:push(y,x);push(P(x),P(y));break;
                case 7:push(y,P(x));push(x,P(y));break;
                case 8:push(x,P(x));push(y,P(y));break;
                case 9:push(x,P(y));push(y,P(x));push(P(x),y);push(P(y),x);break;
                case 10:push(x,y);push(y,x);push(P(x),P(y));push(P(y),P(x));break;
                case 11:push(x,y);push(P(y),P(x));push(P(x),P(y));push(y,x);break;
                case 12:push(x,P(y));push(y,P(x));break;
            }
        }
        if (!Work()) puts("die");
    }
}