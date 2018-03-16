# include <stdio.h>
# include <iostream>
# define RG register 
const int MAXN = 2005;  
const int mod = 1e9 + 7; 
int n, val[MAXN], f[MAXN][MAXN][3], g[MAXN][MAXN][2]; 


inline void upd(int &x, const int &y) {
    (x += y) %= mod; 
}

int main() {
    RG int i, j, c, Ans = 0;  
    for (scanf("%d", &n), i = 1; i <= n; ++i) scanf("%d", &val[i]);
    g[0][0][0] = 1;
    for (i = 1; i <= n; ++i) {
        for (j = 0; j <= i + 1; ++j) {
            if (val[i] != 0) {
                c = std::max(2, j + 1);
                upd(g[i][c][0], g[i - 1][j][0]);
                upd(g[i][c][1], g[i - 1][j][1]);
            }
            if (val[i] != 1) {
                c = std::max(0, j - 1);
                upd(g[i][c][0], g[i - 1][j][0]);
                upd(g[i][c][1], g[i - 1][j][1]);
                upd(g[i][c][1], g[i - 1][j][0]);
            }
        }
    }
    f[n + 1][0][0] = 1;
    for (i = n; i; --i) {
        for (j = 0; j <= n - i; ++j) {
            if (val[i] != 0) {
                c = std::max(0, j - 1);
                upd(f[i][c][0], f[i + 1][j][0]);
                upd(f[i][c][1], f[i + 1][j][0]);
                upd(f[i][c][1], f[i + 1][j][1]);
                upd(f[i][c][2], f[i + 1][j][2]);
                upd(f[i][c][2], f[i + 1][j][1] * 2 % mod);
                upd(f[i][c][2], f[i + 1][j][0]);
            }
            if (val[i] != 1) {
                c = j + 1;
                upd(f[i][c][0], f[i + 1][j][0]);
                upd(f[i][c][1], f[i + 1][j][1]);
                upd(f[i][c][2], f[i + 1][j][2]);
            }
        }
    }
    for (i = 0; i <= n; ++i)
        upd(Ans, (1ll * g[i][0][0] * f[i + 1][0][2] % mod + 1ll * g[i][0][1] * f[i + 1][0][1] % mod) % mod);
    printf("%d\n", Ans);
    return 0; 
}

// 一道好题.  
// 首先有结论:如果一个01划分是合法的当且仅当左边的后缀和0的个数大于1的个数, 右边前缀和0的个数小于等于1的个数时才合法, 我们就拿这个来DP
// 先搞一下下证明.  
// 对于左边, 如果Sum[0] <= Sum[1]则可以把所选的0换为1, 这样字典序更大. 
// 对于右边, 如果Sum[0] > Sum[1]则可以把01划分右移, 此时的最长长度更大.  
// 假装我证明完了... 
// 我的dp数组定义为f[i][j][0/1/2]为01划分后面的需要再选j个1才能达到合法的状态, 且已经选了0/1/2个数的权值和..  
// g[i][j][0/1]与之定义差不多.  
// 考虑g, f的转移, 枚举j, 然后考虑选不选当前的这个1, 转移就好了.  
// 最后枚举分界点, 用f和g数组计算即可.