#include <stdio.h>
#include <cstring>
#include <iostream>
const int MAXN = 500005;
int n,c[MAXN],first[MAXN],e = 1,Ans[MAXN],Q[MAXN],deep[MAXN];
double f[MAXN];


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
}a[MAXN];

inline double K(int a,int b) {
    return (c[a] - c[b]) / 1.0 / (deep[a] - deep[b]);
}

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int len) {
    int l = 1, r = len,top = 1,mid;
    while (l <= r) {
        mid = l + r >> 1;
        if (mid == len) {top = len;break;}
        if (K(Q[mid],Q[mid+1]) <= K(Q[mid+1],u)) l = mid + 1,top = mid + 1;
        else r = mid - 1;
    } top ++;
    f[u] = -K(Q[top-1],u);
    int qwq = Q[top];
    Q[top] = u;
    for (int i = first[u]; i; i = a[i].next) deep[a[i].v] = deep[u] + 1,dfs(a[i].v,top);
    Q[top] = qwq;
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) c[i] = read<int>();
    for (int i = 2; i <= n; i++) push(read<int>(),i);
    dfs(1,0);
    for (int i = 2; i <= n; i++) printf("%.10f\n",f[i]);
    return 0;
}
