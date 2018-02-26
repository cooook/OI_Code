# include <bits/stdc++.h>
const int MAXN = 1e5 + 5;


int n, first[MAXN], e = 2, m, Q;
bool vis[MAXN], intree[500005]; int Xor[MAXN], edge_val[500005];


inline int read() {
	register int x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

struct Basis{
	int a[31];
	inline void clear(){memset(a, 0, sizeof a);}
	inline bool Insert(int t) {
		for (int i = 30; ~i; --i)
			if (t >> i & 1) {
				if (!a[i]) return a[i] = t, false;
				else t ^= a[i];
			}
		return t == 0;
	}
}T;

struct edge{
	int u, v, next;
} a[1000005];

inline void push(int u, int v) {
	a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u) {
	vis[u] = true;
	for (int i = first[u]; i; i = a[i].next) {
		register int v = a[i].v;
		if (vis[v]) continue;
		intree[i >> 1] = true;
		dfs(v);
	}
}

inline void __dfs(int u, int fa) {
	for (int i = first[u]; i; i = a[i].next) {
		register int v = a[i].v;
		if (v == fa || !intree[i >> 1]) continue;
		__dfs(v, u);
		Xor[u] ^= Xor[v];
		edge_val[i >> 1] = Xor[v];
	}
}

int main() {
	srand(20020305);
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		push(u, v), push(v, u);
	}
	dfs(1);

	for (int i = 2; i < e; i += 2)
		if (!intree[i >> 1]) Xor[a[i].u] ^= (edge_val[i >> 1] = rand()), Xor[a[i].v] ^= edge_val[i >> 1];
		
	__dfs(1, 0);
	Q = read();
	int Ans = 0, k = 0;
	while (Q --) {
		k = read(); bool flag = true;
		T.clear();
		for (int i = 1; i <= k; ++i) 
			if (T.Insert(edge_val[read() ^ Ans])) {flag = false;}
		Ans += flag;
		puts(flag ? "Connected" : "Disconnected");
	}
	return 0;
}
