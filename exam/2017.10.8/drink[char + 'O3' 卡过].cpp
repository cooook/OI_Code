#pragma GCC optimize("O3")
#include <stdio.h>
#define M 2005
int n,m,Q,s,x,y,c,i,j; 
char a[M][M],b[M][M];

 
int main () {
    scanf("%d%d%d",&n,&m,&Q);
    for (i = 1; i <= n; i++) for (j = 1; j <= m; j++) scanf("%d",&s),a[i][j] = s + '0';
    while (Q --) {
        scanf("%d%d%d",&x,&y,&c);
        for (i = x; i <= x + c - 1; ++i) for (j = y; j <= y + c - 1; ++j) b[i][j] = a[i][j];
        for (i = x; i <= x + c - 1; ++i) for (j = y; j <= y + c - 1; ++j) a[x+j-y][y+c-1-i+x] = b[i][j];
    }
    for (i = 1; i <= n; i++,puts("")) for (j = 1; j <= m; j++) printf("%d ",a[i][j] - '0');
}