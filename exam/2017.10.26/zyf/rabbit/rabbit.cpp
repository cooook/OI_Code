#include <stdio.h>
#define int long long 
const int MAXN = 2005;
int n,mod,f[MAXN][MAXN];


signed main() {
	freopen("rabbit.in","r",stdin);
	freopen("rabbit.out","w",stdout);
	scanf("%lld%lld",&n,&mod); f[1][1] = 1;
	for (int i = 2,sum; i <= n; i++) {
		sum = 0;
		for (int j = 1; j <= i; j++)
			(sum += f[i-1][i-j]) %= mod, f[i][j] = sum;
	}
	printf("%lld\n",f[n][n] * 2 % mod);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
