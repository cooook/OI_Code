# include <bits/stdc++.h>
const int mod = 9999991;
int f, n;


inline int qpow(int x, int k) {
	int Ans = 1;
	for (; k; k >>= 1, x = 1ll * x * x % mod)
		if (k & 1) Ans = 1ll * Ans * x % mod;
	return Ans;
}

int main() {
	scanf("%d", &n);
	f = 1;
	for (int i = 2; i < n; ++i) f = 1ll * i * f % mod;
	printf("%d\n", 1ll * f * qpow(n, n - 2) % mod);
	return 0;
}
