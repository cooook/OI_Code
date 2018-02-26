# include <stdio.h>
# include <iostream> 
const int mod = 2007;
char s[10005];
int n, m, a[505][505], cnt;


inline int read() {
	register int x = 0, f = 1; char ch = getchar();
	for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
	for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline void Gauss() {
	for (int i = 1; i < cnt; i++)
		for (int j = 1; j < cnt; j++)
			(a[i][j] += mod) %= mod;
	int Ans = 1;
	for (int i = 1; i < cnt; i++) {
		register int u = i;
		for (; u < cnt; ++u) if (a[u][i]) break; 
		if (u == cnt) { Ans = 0; break; }
		if (u != i) {
			Ans = - Ans;
			for (int j = i; j < cnt; j++) std::swap(a[i][j], a[u][j]);
		}
		for (int j = i + 1; j < cnt; j++)
			while (a[j][i]) {
				int t = a[j][i] / a[i][i];
				for (int k = i; k < cnt; k++) a[j][k] = (a[j][k] - t * a[i][k] % mod + mod) % mod;
				if (!a[j][i]) break;
				Ans = -Ans;
				for (int k = i; k < cnt; k++) std::swap(a[j][k], a[i][k]); 
			}
		Ans = 1ll * Ans * a[i][i] % mod; 
	}
	printf("%d\n", (Ans + mod) % mod);
	return; 
}

signed main() {
	return 0;
}
