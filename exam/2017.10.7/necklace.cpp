#include <stdio.h>
#define MAXN 1005
double f[MAXN][MAXN][15],p[MAXN][15],g[MAXN][MAXN][15],s[MAXN][MAXN],Ans = 0.0; int n,m;


int main() {
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%lf",&p[i][j]);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            g[j][j][i] = p[j][i];
            for (int k = j + 1; k <= n; k++)
                g[j][k][i] = g[j][k-1][i] * p[k][i];
        }
    s[0][0] = 1.0;
    for (int i = 1; i <= n; i++) s[0][i] = 1.0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++){
                f[i][j][k] = s[i-1][j] * p[i][k];
                if (i-j-1 >= 0) f[i][j][k] -= (s[i-j-1][j] - f[i-j-1][j][k]) * g[i-j][i][k];
                s[i][j] += f[i][j][k];
            }
    }
    for (int i = 1; i <= n; i++) 
        Ans += i * (s[n][i] - s[n][i-1]);
    printf("%.5f\n",Ans);
    return 0;
}