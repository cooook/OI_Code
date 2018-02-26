# include <bits/stdc++.h> 
const int mod = 998244353;
const int maxn = 1 << 21;
int n, val, Inv2 = 499122177, f[maxn], Mx, N, power[maxn];


inline int read() {
	register int x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline void fwt(int *f, int n) {
	int x, y;
	for (int k = 2; k <= n; k <<= 1)
		for (int i = 0; i < n; i += k)
			for (int j = 0; j < k >> 1; ++j)
				x = f[i + j], y = f[i + j + (k >> 1)],
				f[i + j] = x + y, f[i + j + (k >> 1)] = x - y;
}

inline void dfwt(int *f, int n) {
	int x, y;
	for (int k = 2; k <= n; k <<= 1)
		for (int i = 0; i < n; i += k)
			for (int j = 0; j < (k >> 1); ++j) {
				x = f[i + j], y = f[i + j + (k >> 1)]; 
				f[i + j] = 1ll * (x + y) * Inv2 % mod;
				f[i + j + (k >> 1)] = 1ll * ((x - y + mod) % mod) * Inv2 % mod;			
			}
}

inline void gmax(int &x, const int &y) {
	if (x < y) x = y;
}

int main() {
	n = read();
	
	power[0] = 1;
	for (int i = 1; i <= n; ++i) power[i] = 1ll * power[i - 1] * 3 % mod;
	
	
	for (int i = 1; i <= n; ++i)  f[val = read()] += 2, ++ f[0], gmax(Mx, val);
	for (N = 1; N <= Mx; N <<= 1); 
	fwt(f, N);
	for (int i = 0; i < N; ++i) {
		int x = (3 * n - f[i]) / 4;
		f[i] = ((x & 1)? -1 : 1) * power[n - x];
	}
	dfwt(f, N);
	printf("%d\n", (f[0] - 1 + mod) % mod);
	return 0;
}
