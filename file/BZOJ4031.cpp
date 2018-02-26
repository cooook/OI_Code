# include <stdio.h>
# include <iostream>
# define int long long 
const int mod = (int)1e9;
char s[10005];
int n, m, a[101][101], cnt, id[11][11];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};


inline int read() {
	register int x = 0, f = 1; char ch = getchar();
	for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
	for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline void Gauss() {
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
	printf("%lld\n", (Ans + mod) % mod);
	return; 
}

signed main() {
	//freopen("Cooook.in", "r", stdin);
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; s[j]; j++)
			if (s[j] != '*') id[i][j] = ++ cnt; 
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (id[i][j]) {
				int u = id[i][j], v;
				if (i != 1 && id[i-1][j]) {
					v = id[i-1][j];
					a[u][u] ++; a[v][v] ++;
					a[u][v] --; a[v][u] --;
				}
				if (j != 1 && id[i][j-1]) {
					v = id[i][j-1];
					a[u][u] ++; a[v][v] ++;
					a[u][v] --; a[v][u] --;
				}
			}
	for (int i = 1; i < cnt; i++)
		for (int j = 1; j < cnt; j++)
			(a[i][j] += mod) %= mod;
	Gauss();
	return 0;
}
