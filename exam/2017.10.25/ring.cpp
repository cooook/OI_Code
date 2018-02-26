#include <bits/stdc++.h>
int full,i,n,vis[1<<21],now;
int main() {
	freopen("ring.in","r",stdin);
	freopen("ring.out","w",stdout);
	scanf("%d",&n);
	if (n == 3) return puts("10111000"), 0;
	for (i = 1; i <= n; i++) printf("0"); vis[now] = true;
	for (full = 1 << n,i = n + 1; i <= full; i++,now = now * 2 % full) {
		if (!vis[now|1]) printf("1"),vis[now|=1] = 1;
		else printf("0"),vis[now] = 1;
	}
	return 0;
}
