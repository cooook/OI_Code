# pragma GCC optimize("O3")
# include <bits/stdc++.h>
const int MAXN = 200005; 
int n, Q, pre[MAXN], top[MAXN], size[MAXN], son[MAXN], deep[MAXN], fa[MAXN], dfn[MAXN], cnt, first[MAXN], e = 1;
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
}Ans;

struct node{
	node *ls, *rs;
	Basis G;
	node(){ls = rs = NULL;}
}*root;

inline void build(node *&o, int l, int r) {
	o = new node();
	for (int i = l; i <= r; ++i) o -> G.Insert(val[pre[i]]);
	if (l == r) return ;
	register int mid = l + r >> 1;
	build(o -> ls, l, mid), build(o -> rs, mid + 1, r);
}

inline void Query(node *o, int l, int r, int x, int y) {
	if (x <= l && r <= y) return Ans = Ans + o -> G, void();
	register int mid = l + r >> 1;
	if (x <= mid) Query(o -> ls, l, mid, x, y);
	if (mid < y) Query(o -> rs, mid + 1, r, x, y);
}

inline void dfs(int u, int fa) {
	::fa[u] = fa; size[u] = 1; deep[u] = deep[fa] + 1;
	for (int i = first[u]; i; i = a[i].next) {
		register int v = a[i].v;
		if (v == fa) continue;
		dfs(v, u), size[u] += size[v];
		if (size[son[u]] < size[v]) son[u] = v;
	}
}

inline void __dfs(int u, int Num) {
	top[u] = Num; pre[dfn[u] = ++ cnt] = u;
	if (son[u]) __dfs(son[u], Num);
	for (int i = first[u]; i; i = a[i].next)
		if (a[i].v != fa[u] && a[i].v != son[u])
			__dfs(a[i].v, a[i].v);
}

inline void Query(int u, int v) {
	int f1 = top[u], f2 = top[v];
	Ans.clear();
	while (f1 != f2) {
		if (deep[f1] < deep[f2]) std::swap(f1, f2), std::swap(u, v);
		Query(root, 1, n, dfn[f1], dfn[u]);
		u = fa[f1]; f1 = top[u];
	}
	if (deep[u] > deep[v]) std::swap(u, v);
	Query(root, 1, n, dfn[u], dfn[v]);
	printf("%lld\n", Ans.Max());
}

signed main() {
	//freopen("lucky7.in", "r", stdin);
	//freopen("Cooook.out", "w", stdout);
	n = read(), Q = read();
	for (int i = 1; i <= n; ++i) val[i] = read();
	for (int i = 2; i <= n; ++i) {
		register int u = read(), v = read();
		push(u, v), push(v, u);
	}
	dfs(1, 0), __dfs(1, 1);
	build(root, 1, n);
	while (Q --) {
		register int u = read(), v = read();
		Query(u, v);
	}
	return 0;
}
