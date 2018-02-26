# pragma GCC optimize("O3")
# include <bits/stdc++.h>
const int MAXN = 20005;
int n, Q, first[MAXN], e = 1, f[MAXN][18], deep[MAXN]; 
long long val[MAXN];


char sb[1 << 15], *S = sb, *T = sb;
# define gc (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T)?0:*S++)

inline long long read() {
	register long long x = 0, f = 1; char ch = gc;
	for (; !isdigit(ch); ch = gc) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = gc) x = x * 10 + (ch ^ 48);
	return x * f;
}

struct edge{
	int u, v, next;
}a[MAXN << 1];

inline void push(int u, int v) {
	a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}


struct Basis{
	long long a[65];
	inline Basis() {clear();}
	inline void clear(){memset(a, 0, sizeof a);}
	inline void Insert(long long t) {
		for (int i = 60; ~i; --i) 
			if (t >> i & 1) {
				if (!a[i]) { a[i] = t; break; }
				t ^= a[i];
			}
	}
	inline Basis operator + (const Basis &x) {
		Basis t = *this;
		for (int i = 0; i <= 60; ++i) if (x.a[i]) t.Insert(x.a[i]);
		return t;
	}
	inline long long Max() {
		long long Ans = 0;
		for (int i = 60; ~i; --i) if ((Ans ^ a[i]) > Ans) Ans ^= a[i]; 
		return Ans;
	} 
}Ans, g[MAXN][18];

inline void dfs(int u, int fa) {
	for (int i = 1; i <= 17; ++i) f[u][i] = f[f[u][i-1]][i-1], g[u][i] = g[u][i-1] + g[f[u][i-1]][i-1];
	for (int i = first[u]; i; i = a[i].next) {
		register int v = a[i].v;
		if (v == fa) continue;
		f[v][0] = u; g[v][0].Insert(val[u]);
		deep[v] = deep[u] + 1;
		dfs(v, u);
	}
}

inline void Query() {
	int u = read(), v = read();
	if (deep[u] < deep[v]) std::swap(u, v);
	Ans.clear();
	Ans.Insert(val[u]);
	Ans.Insert(val[v]);
	register int t = deep[u] - deep[v];
	for (int i = 17; ~i; --i) if (t >> i & 1) Ans = Ans + g[u][i], u = f[u][i];
	if (u == v) return printf("%lld\n", Ans.Max()), void();
	for (int i = 17; ~i; --i)
		if (f[u][i] != f[v][i])
			Ans = Ans + g[u][i], Ans = Ans + g[v][i], u = f[u][i], v = f[v][i];
	Ans = Ans + g[u][0];
	printf("%lld\n", Ans.Max());
}

signed main() {
	n = read(); Q = read();
	for (int i = 1; i <= n; ++i) val[i] = read();
	for (int i = 1; i < n; ++i) {
		register int u = read(), v = read();
		push(u, v), push(v, u);
	}
	dfs(1, 0);
	while (Q --) Query();
	return 0;
}
