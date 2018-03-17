# include <bits/stdc++.h>
const int mod = 105225319;  
const int MAXN = 1005; 
int n, m, C[MAXN][MAXN], f[MAXN], g[MAXN], h[MAXN], pw[MAXN * MAXN], Inv2; 


inline void upd(int &x, const int &y) {
	(x += y) %= mod; 
}

int main() {
	scanf("%d%d", &n, &m); Inv2 = mod + 1 >> 1;
	if (n == 1) return puts("0"), 0; 
	C[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	pw[0] = 1;
	for (int i = 1; i <= n * n; ++i) pw[i] = 1ll * pw[i - 1] * (m + 1) % mod;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= i; ++j)
			upd(g[i], 1ll * C[i][j] * pw[(i - j) * j] % mod * Inv2 % mod);  // 这里的除2是除去了颜色. 
	for (int i = 1; i <= n; ++i) {
		f[i] = g[i];
		for (int j = 1; j < i; ++j)
			upd(f[i], -2ll * C[i - 1][j - 1] * f[j] % mod * g[i - j] % mod); // 这里考虑了颜色. 
	}
	h[0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j)
			upd(h[i], 1ll * C[i - 1][j] * f[j + 1] % mod * h[i - j - 1] % mod); 
	printf("%d\n", (h[n] + mod) % mod);
	return 0; 
}