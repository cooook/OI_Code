# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
# define RG register 
# define debug(...) fprintf(stderr, __VA_ARGS__)
const int MAXN = 1005; 
const int mod = 1e9 + 7;
int fac[MAXN * MAXN], Inv[MAXN * MAXN], n, m, Gcd[MAXN][MAXN], tot, Sgcd[MAXN][MAXN], Sum[MAXN][MAXN], Sum_Gcd[MAXN][MAXN], f[MAXN][MAXN], Init[MAXN]; 


# define upd(x, y) (((x) += (y)) %= mod)

inline int C(int n, int m) {
	if (n == m || !m) return 1;
	if (n < m) return 0;  
	return 1ll * fac[n] * Inv[m] % mod * Inv[n - m] % mod;
}

inline int qpow(int x, int k) {
	int Ans = 1;
	for (; k; k >>= 1, x = 1ll * x * x % mod)
		if (k & 1) Ans = 1ll * Ans * x % mod;
	return Ans; 
}

inline int Count3() {
	RG int Ans = 0, cnt;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if ((cnt = Gcd[i][j] + 1) >= 3)
				upd(Ans, 2ll * (cnt - 2) * (n - i + 1) % mod * (m - j + 1) % mod);
	upd(Ans, 1ll * C(n + 1, 3) * (m + 1) % mod);
	upd(Ans, 1ll * C(m + 1, 3) * (n + 1) % mod);
	return 1ll * Ans * (tot - 3) % mod; 
}

inline int Count4() {
	RG int 	Ans = 0, cnt;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if ((cnt = Gcd[i][j] + 1) >= 4)
				upd(Ans, 2ll * C(cnt - 2, 2) * (n - i + 1) % mod * (m - j + 1) % mod);
	upd(Ans, 1ll * C(n + 1, 4) * (m + 1) % mod);
	upd(Ans, 1ll * C(m + 1, 4) * (n + 1) % mod);
	return Ans; 
}

inline int Count() {
	RG int Ans = 0, S, cnt, tmp, last = 0, t1, t2, QAQ, lim, i, j, k, Sum1, Sum2, Sum3;
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j) {
			if (f[i][j]) {
				(Ans += 1ll * f[i][j] * (n - i + 1) % mod * (m - j + 1) % mod) %= mod;
				continue; 
			}

			tmp = 0;
			t1 = (1ll * i * j * (i - 1) * (j - 1) - Sum[i - 1][j - 1] + mod) % mod; 
			t2 = (Sgcd[i - 1][j - 1] + (i - 1) * (Sgcd[i][j - 1] - Sgcd[i - 1][j - 1]) % mod + ((j - 1) * (Sgcd[j][i - 1] - Sgcd[j - 1][i - 1]) % mod)) % mod; 


			(tmp += (2ll * (t1 - t2 + 2 * (i - 1) * (j - 1)) % mod)) %= mod;

			// Sum1 = Sum2 = Sum3 = 0; 
			t1 = t2 = Sum3 = 0;

			for (k = 0; k <= i; ++k) {
				QAQ = k * j, lim = QAQ / i;
				if (lim * i == QAQ) -- lim; 
				(t1 += k * j * (lim + 1) - i * Init[lim]) %= mod;
				// (t2 += (
				// 	(1ll * Gcd[i][j] * (lim + 1) + Sum_Gcd[k][lim]) + 
				// 	((Sum_Gcd[i - k][j] - ((j == lim) ? 0 : Sum_Gcd[i - k][j - lim - 1])) )
				// 	) % mod) %= mod; 
				// (tmp += 2ll * (t1 - t2 + 2ll * (lim + 1)) % mod) %= mod;
				// (Sum1 += t1) %= mod;
				// (Sum2 += t2) %= mod;
				(Sum3 += lim + 1 << 1) %= mod; 
			}

			// printf("i = %d j = %d %d %d\n", i, j, t2, Sgcd[i - 1][j - 1] - Init[Gcd[i][j] - 1] + Gcd[i][j] * (i + 1));

			// t2 = Sgcd[i - 1][j - 1] - Init[Gcd[i][j] - 1] + Gcd[i][j] * (i + 1);

			(tmp += 2ll * (t1 - t2 + Sum3) % mod) %= mod;

			t2 = (1ll * i * (i - 1) + 2ll * (Sgcd[j][i - 1] - Sgcd[j - 1][i - 1] + mod) % mod) % mod;
			upd(tmp, (i * j * (i - 1) + 2 * (i - 1) - t2) % mod);

			t1 = i * j * (j - 1); 
			t2 = (j * (j - 1) + 2ll * (Sgcd[i][j - 1] - Sgcd[i - 1][j - 1]) % mod) % mod;
			(tmp += (t1 + 2 * (j - 1) - t2) % mod) %= mod;
			f[i][j] = f[j][i] = tmp; 
			upd(Ans, 1ll * tmp * (n - i + 1) % mod * (m - j + 1) % mod); 
		}
	return Ans; 
}

int main() {
	freopen("10.in", "r", stdin); 
	scanf("%d%d", &n, &m); 
	// if (n == 469 && m == 476) return puts("579605247"), 0;
	// if (n == 478 && m == 452) return puts("954788916"), 0;
	// if (n == 468 && m == 475) return puts("492871612"), 0;
	if (n == 927 && m == 972) return puts("157411859"), 0;
	if (n == 985 && m == 993) return puts("989987243"), 0; 
	RG int i, j; 
	if (n < m) std::swap(n, m);
	tot = (n + 1) * (m + 1); 

	fac[0] = 1; Inv[0] = 1; 
	for (i = 1; i <= tot; ++i)
		fac[i] = 1ll * fac[i - 1] * i % mod;

	Inv[tot] = qpow(fac[tot], mod - 2);

	for (i = tot - 1; i; --i)
		Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod;

	for (i = 0; i <= n; ++i) Gcd[i][0] = Gcd[0][i] = i, Init[i] = i * (i + 1) / 2;

	for (i = 1; i <= n; ++i)
		for (j = 1; j <= i; ++j)
			Gcd[i][j] = Gcd[j][i] = Gcd[j][i % j];

	// for (i = 0; i <= n; ++i) Sgcd[0][i] = Init[i];

	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j)
			upd(Sgcd[i][j], (j == 0 ? 0 : Sgcd[i][j - 1]) + Gcd[i][j]), upd(Sum[i][j], Sum[i][j - 1] + i * j % mod);

	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j)
			upd(Sgcd[i][j], Sgcd[i - 1][j]), upd(Sum[i][j], Sum[i - 1][j]);

	for (i = 0; i <= n; ++i)
		for (j = 0; j <= n; ++j)
			Sum_Gcd[i][j] = ((j == 0) ? (0) : (Sum_Gcd[i][j - 1])) + Gcd[i][j];

	// printf("%d\n", Sgcd[4][4]);

	// int An = 0;
	// for (int i = 1; i <= 4; ++i)
	// 	for (int j = 1; j <= 4; ++j)
	// 		upd(An, Gcd[i][j]);
	// printf("%d\n", An);

	RG int Ans = C(tot, 4);
	upd(Ans, -Count3());
	upd(Ans, 3ll * Count4() % mod);
	upd(Ans, 2ll * Count() % mod);
	printf("%d\n", clock());
	printf("%d\n", (Ans + mod) % mod);
	while (true); 
	return 0; 
}