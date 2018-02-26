#include <stdio.h>
#include <cstring>
int T,n,m,ton[30]; char s[205][205];


int main() {
	freopen("quilt.in","r",stdin);
	freopen("quilt.out","w",stdout);
	scanf("%d",&T);
	while (T --) {
		bool flag = true;
		memset(ton,0,sizeof ton);
		scanf("%d%d",&n,&m);
		for (int i = 1; i <= n; i++) {
			scanf("%s",s[i] + 1);
			for (int j = 1; j <= m; j++)
				ton[s[i][j] - 'a' + 1] ++;
		}
		bool can = (n & 1) & (m & 1);
		int Num = (n & 1) * (m >> 1) + (m & 1) * (n >> 1);
		for (int i = 1; i <= 26; i++) {
			ton[i] %= 4;
			if (!ton[i]) continue;
			if (ton[i] >= 2) {
				if (Num) Num--, ton[i] -= 2;
			}
			if (ton[i] == 1) {
				if (can) ton[i] = 0,can = false;
			}	
		}
		for (int i = 1; i <= 26; i++) 	
			if (ton[i]) flag = false;
		if (flag) puts("Yes");
		else puts("No");
 	}
 	fclose(stdin);
 	fclose(stdout);
	return 0;
}
