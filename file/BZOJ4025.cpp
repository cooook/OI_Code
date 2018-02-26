# include <stdio.h> 
const int MAXN = 100005;


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct data {
    int u, v, st, end;
} G[MAXN];

int main() {
    n = read(), m = read(), T = read();
    for (int i = 1; i <= m; ++i) G[i].u = read(), G[i].v = read(), G[i].st = read(), G[i].end = read();
    
    return 0;
}