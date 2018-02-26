# include <bits/stdc++.h>
# define int long long 
const int MAXN = 200005;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n, first[MAXN], e = 1, val[MAXN], fa[MAXN], size[MAXN], top[MAXN], f[MAXN], h[MAXN], cnt, Q, dfn[MAXN], pre[MAXN], deep[MAXN], son[MAXN]; 


inline int read() {
	register int x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline int gmin(int &x, const int &y) {
	if (x > y) x = y;
	return x;
}

struct node{
	node *ls, *rs;
	int mn, tag; 
	node(){ls = rs = NULL;}
	inline void Add(int x) {mn -= x; tag += x;}
	
	inline void Push_down() {
		if (tag) ls -> Add(tag), rs -> Add(tag), tag = 0;
	}
	
	inline void Maintain() {
		mn = inf;
		if (ls) gmin(mn, ls -> mn);
		if (rs) gmin(mn, rs -> mn);
	}
}*root;

struct edge{
	int u, v, next;	
} a[MAXN << 1];

inline void push(int u, int v) {
	a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u, int fa) {
	size[u] = 1; ::fa[u] = fa; f[u] = val[u]; deep[u] = deep[fa] + 1;
	for (int i = first[u]; i; i = a[i].next) 
		if (a[i].v != fa) {
			register int v = a[i].v;
			dfs(v, u);
			size[u] += size[v];
			h[u] += f[v];
			if (size[son[u]] < size[v]) son[u] = v;
		}
	if (size[u] == 1) h[u] = inf;
	gmin(f[u], h[u]);
}

inline void __dfs(int u, int Num) {
	pre[dfn[u] = ++cnt] = u; top[u] = Num;
	if (son[u]) __dfs(son[u], Num);
	for (int i = first[u]; i; i = a[i].next)
		if (a[i].v != fa[u] && a[i].v != son[u])
			__dfs(a[i].v, a[i].v);
}

inline node* Get(int pos) {
	node *o = root; int l = 1, r = n, mid;
	while (l < r) {
		o -> Push_down();
		mid = l + r >> 1;
		if (pos <= mid) r = mid, o = o -> ls;
		else l = mid + 1, o = o -> rs;
	}
	return o;
}

inline void Query(int u) {
	node *t = Get(dfn[u]);
	printf("%lld\n", val[u] - (t -> mn > 0 ? t -> mn : 0)); 
}

inline void build(node *&o, int l, int r) {
	o = new node();
	if (l == r) return o -> mn = val[pre[l]] - h[pre[l]], o -> tag = 0, void();
	register int mid = l + r >> 1;
	build(o -> ls, l, mid); build(o -> rs, mid + 1, r);
	o -> Maintain();
}

inline int Update(node *o, int l, int r, int x, int y, int delta) {
	if (l == r) return o -> Add(delta), o -> mn <= 0 ? pre[l] : 0;
	o -> Push_down();
	if (x == l && r == y && o -> mn > delta) return o -> Add(delta), 0;
	register int mid = l + r >> 1, t = 0;
	if (y <= mid) t = Update(o -> ls, l, mid, x, y, delta);
	else if (x > mid) t = Update(o -> rs, mid + 1, r, x, y, delta);
	else {
		t = Update(o -> rs, mid + 1, r, mid + 1, y, delta);
		if (!t) t = Update(o -> ls, l, mid, x, mid, delta);
	}
	o -> Maintain();
	return t;
}

inline void Change(int u, int delta) {
	if (!u || delta <= 0) return;
	while (u) {
		register int t = Update(root, 1, n, dfn[top[u]], dfn[u], delta);
		if (!t) u = fa[top[u]];
		else return Change(fa[t], delta + Get(dfn[t]) -> mn), void();
	}
}

signed main() {
	freopen("Cooook.in", "r", stdin);
	freopen("Cooook.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; ++i) val[i] = read();
	for (int i = 1; i < n; ++i) {
		register int u = read(), v = read();
		push(u, v), push(v, u);
	}
	dfs(1, 0); __dfs(1, 1);
	build(root, 1, n);
	Q = read(); 
	while (Q --) {
		char ch = getchar();
		for (; ch != 'Q' && ch != 'C'; ch = getchar());
		int rt = read(); 
		if (ch == 'Q') Query(rt);
		else {
			register int delta = read(), s;
			if (!delta) continue;
			Update(root, 1, n, dfn[rt], dfn[rt], -delta);
			val[rt] += delta;
			s = val[rt] - Get(dfn[rt]) -> mn;
			f[rt] = std::min(s, val[rt]);
			Change(fa[rt], f[rt] - val[rt] + delta);
		}
	}
	return 0;
}

