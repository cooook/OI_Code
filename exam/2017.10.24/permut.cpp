#include <stdio.h>
#include <iostream>
const int MAXN = 1005,mod = 10000;
int T,n,k,f[MAXN][MAXN],sum[MAXN][MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Pre_Work() {
    for (int i = 0; i <= k; i++) sum[1][i] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            f[i][j] = (sum[i-1][j] - (j<i?0:sum[i-1][j-i]) + mod) % mod;
            sum[i][j] = (sum[i][j-1] + f[i][j]) % mod;
        }
    }
}

struct Query {
    int d[2];
    inline int& operator [] (const int &x) {return d[x];}
}Q[MAXN];

int main() {
    // freopen("permut.in","r",stdin);
    // freopen("permut.out","w",stdout);
    T = read<int>();
    for (int i = 1; i <= T; i++) {
        Q[i][0] = read<int>(),Q[i][1] = read<int>();
        n = std::max(Q[i][0],n);
        k = std::max(Q[i][1],k);
    }
    Pre_Work();
    for (int i = 1; i <= T; i++) printf("%d\n",f[Q[i][0]][Q[i][1]]);
    return 0;
}
