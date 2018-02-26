# include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 155;
int d[MAXN], Sum, n;
__float128 f[MAXN], t = 1.0; 


int main() {
	scanf("%d", &n);
	f[0] = 1;
	bool flag = false; 
	for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &d[i]);
		if (!d[i] || d[i] >= n) flag = true;
		Sum += d[i] - 1;
		t *= f[d[i] - 1];
	}
	if (n == 1 && d[1] == 0) return puts("1"), 0;
	if (Sum != n - 2 || flag) return puts("0"), 0;
	__float128 Ans = f[n - 2] / t;
	printf("%lld\n", (ll)(Ans + 0.5));
	return 0;
}
