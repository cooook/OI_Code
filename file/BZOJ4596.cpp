# include <stdio.h> 
# include <cstring> 
# include <iostream> 
# define fi val[x][i].first
# define se val[x][i].second
# define mk std::make_pair
# define clear memset(a, 0, sizeof a), type = 0


const int mod = 1e9 + 7;


typedef long long ll;
typedef std::pair<int, int> pii; 


int n, cnt[50]; 
ll a[50][50];  
pii val[50][105]; 


inline int read() {
	int x = 0, f = 1; char ch = getchar(); 
	for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-' ? f = -f : 0;
	for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

template <typename __Type>
inline void Swap(__Type &x, __Type &y) {
	register __Type t = x; x = y; y = t;
}

inline ll Gauss(int n) {
	ll Ans = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = (a[i][j] + mod) % mod;
	for (int i = 1; i <= n; i++) {
		int u = i;
		for (; u <= n; u++) if (a[u][i]) break;
		if (!a[u][i]) { Ans = 0; break; }
		if (u != i) {
			Ans = -Ans;
			for (int j = i; j <= n; j++) Swap(a[u][j], a[i][j]);
		}
		for (int j = i + 1; j <= n; j++) 	
			while (a[j][i]) {
				ll t = a[j][i] / a[i][i];
				for (int k = i; k <= n; k++)
					a[j][k] = (a[j][k] - t * a[i][k] % mod + mod) % mod;
				if (!a[j][i]) break;
				Ans = - Ans;
				for (int k = i; k <= n; k++)
					Swap(a[i][k], a[j][k]);
			}
		(Ans *= a[i][i]) %= mod;
	}
	return (Ans + mod) % mod;
}

inline void Add(int x) {
	for (int i = 1; i <= cnt[x]; i++)
		a[fi][fi] ++, a[se][se] ++, a[fi][se] --, a[se][fi] --;
}

int main() {
	n = read() - 1;
	for (int i = 1; i <= n; i++) {
		cnt[i] = read();
		for (int j = 1, x, y; j <= cnt[i]; j++) 
			x = read(), y = read(), val[i][j] = mk(x, y);
	}
	int full = 1 << n; 
	ll Ans = 0; int type;
	for (int i = 1; i < full; i++) {
		clear;
		for (int j = 1; j <= n; j++)
			if ((i >> j - 1) & 1) Add(j);
			else type ^= 1;
		Ans += (type == 1?-1 : 1) * Gauss(n);
		Ans %= mod;
	}
	printf("%lld\n", (Ans + mod) % mod);
	return 0;
}
