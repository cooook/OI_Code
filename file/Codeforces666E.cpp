# include <stdio.h>
# include <cstring>
# include <iostream> 
# define RG register
const int inf = 0x3f3f3f3f; 
const int MAXN = 1.5e6 + 5; 
int first[MAXN], e = 1, n, Q, f[MAXN][21], deep[MAXN], id[MAXN]; 
char s[MAXN]; 


inline int read() {
	RG int x = 0, f = 1; RG char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

template <typename _t>
inline void gmin(_t &x, const _t &y) {
	if (x > y) x = y;
}

template <typename _t>
inline void gmax(_t &x, const _t &y) {
	if (x < y) x = y; 
}

namespace Segment_Tree {
	struct val {
		int fi, se;  
		val(int fi = 0, int se = 0):fi(fi), se(se) {  }
		inline bool operator < (const val &x) const { return fi == x.fi ? se > x.se : fi < x.fi; }
		inline bool operator > (const val &x) const { return fi == x.fi ? se < x.se : fi > x.fi; }
	};
	struct node {
		node *ls, *rs;
		val mx; 
		node() { ls = rs = NULL; }
		inline void Maintain() {
			mx = val();
			if (ls) gmax(mx, ls -> mx);
			if (rs) gmax(mx, rs -> mx);
		}
		inline void* operator new (size_t) ;
	}*root[MAXN << 1], *C, *mempool;
	inline void* node::operator new(size_t) {
		if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
		return C ++; 
	}

	inline void Update(node *&o, int l, int r, int x) {
		if (!o) o = new node(); 
		if (l == r) return o -> mx.se = l, ++ o -> mx.fi, void(); 
		register int mid = l + r >> 1;
		if (x <= mid) Update(o -> ls, l, mid, x);
		else Update(o -> rs, mid + 1, r, x); 
		o -> Maintain(); 
	}
	
	inline node* Merge(node *x, node *y, int l, int r) {
		if (!x || !y) return !x ? y : x;
		node *o = new node();
		if (l == r) {
			o -> mx = x -> mx;
			o -> mx.fi += y -> mx.fi;
			return o; 
		}
		register int mid = l + r >> 1; 
		o -> ls = Merge(x -> ls, y -> ls, l, mid);
		o -> rs = Merge(x -> rs, y -> rs, mid + 1, r);
		o -> Maintain();
		return o; 
	}
	
	inline val Query(node *o, int l, int r, int x, int y) {
		if (!o) return val(); 
		if (x == l && r == y) return o -> mx;
		register int mid = l + r >> 1;
		if (y <= mid) return Query(o -> ls, l, mid, x, y);
		else if (x > mid) return Query(o -> rs, mid + 1, r, x, y);
		else return std::max(Query(o -> ls, l, mid, x, mid), Query(o -> rs, mid + 1, r, mid + 1, y));
	}
}

namespace Tree {
	struct edge {
		int u, v, next; 
	} a[MAXN << 1];

	inline void push(int u, int v) {
		a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
	}

	inline void dfs(int u, int fa) {
		using namespace Segment_Tree; 
		f[u][0] = fa; deep[u] = deep[fa] + 1;
		for (RG int i = 1; i <= 19; ++i) f[u][i] = f[f[u][i - 1]][i - 1]; 
		for (RG int i = first[u]; i; i = a[i].next) 
			if (a[i].v != fa) dfs(a[i].v, u), root[u] = Merge(root[u], root[a[i].v], 1, n);
	}
}

namespace Suffix_Automata {
	const int Automata_NODE = MAXN << 1;
	int trans[Automata_NODE][26], last, cnt, fa[Automata_NODE], Mx[Automata_NODE];
	inline void Init() {
		last = ++ cnt; 
	}
	inline int Extend(int c) {
		RG int np = ++ cnt, p = last; Mx[np] = Mx[last] + 1;
		for (; !trans[p][c]; p = fa[p]) trans[p][c] = np;  
		if (!p) fa[np] = 1;
		else {
			RG int q = trans[p][c];
			if (Mx[q] == Mx[p] + 1) fa[np] = q;
			else {
				RG int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
				fa[nq] = fa[q]; fa[q] = fa[np] = nq; 
				memcpy(trans[nq], trans[q], sizeof trans[q]);
				for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq; 
			}
		}
		return last = np;
	}

	inline void build() {
		using namespace Tree; 
		for (int i = 2; i <= cnt; ++i) push(fa[i], i);
		dfs(1, 0); 
	}
}

int main() {
	// freopen("Cooook.in", "r", stdin);
	// freopen("Cooook.out", "w", stdout);
	using namespace Suffix_Automata;
	using namespace Segment_Tree; 
	scanf("%s", s + 1); 
	Init();
	RG int len = strlen(s + 1);
	for (RG int i = len; i; --i) 
		id[i] = Extend(s[i] - 'a');
	n = read(); 
	for (RG int i = 1, x; i <= n; ++i) {
		scanf("%s", s + 1);
		len = strlen(s + 1);
		last = 1;
		for (RG int j = len; j; --j)
			x = Extend(s[j] - 'a'), Update(root[x], 1, n, i);
	}
	build();
	Q = read(); 
	while (Q --) {
		register int L = read(), R = read(), l = read(), r = read(); 
		register int o = id[l], Len = r - l + 1;
		for (int i = 19; ~i; --i)
			if (Mx[f[o][i]] >= Len) o = f[o][i];
		RG val Ans = Query(root[o], 1, n, L, R);
		if (!Ans.fi) printf("%d %d\n", L, Ans.fi);
		else printf("%d %d\n", Ans.se, Ans.fi);
	}
	return 0; 
}