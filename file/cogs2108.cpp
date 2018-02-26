#include <stdio.h>
const int MAXN = 1005,mod = 1e9+7;
int n,m,k,f[3][205][205];
char s1[MAXN],s2[MAXN];


int main(){
    // freopen("2015substring.in","r",stdin);
    // freopen("2015substring.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s%s",s1+1,s2+1);
    f[0][0][0] = f[1][0][0] = f[2][0][0] = 1;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++)
            for (int p = 0; p <= k; p++){
                int now = i % 3;
                f[now][j][p] = f[(now+2)%3][j][p];
                if (s1[i] == s2[j]){
                    (f[now][j][p] += f[(now+2)%3][j-1][p-1]) %= mod;
                    if (s1[i-1] == s2[j-1] && i >= 2) 
                        (f[now][j][p] += (f[(now+2)%3][j-1][p] - f[(now+1)%3][j-1][p] + mod) % mod) %= mod;
                }
            }
    printf("%d\n",f[n%3][m][k]);
    return 0;
}