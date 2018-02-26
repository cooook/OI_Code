# include <map> 
# include <vector>
# include <stdio.h> 
# include <cstring>
# include <iostream>
const int MAXN = 500005; 
int n, cnt;
std::map<int, int> last; 
typedef std::vector<int> Vec;
typedef std::vector<int>::iterator Dit;


inline int read() {
	register int x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

struct Value{
	int L, R, val; 
}v[MAXN], tmp[MAXN];

inline void gmax(int &x, const int &y) {
	if (x < y) x = y;
}

struct Basis{
	Basis() {memset(a, 0, sizeof a);}
	int a[35];
	
	inline void Insert(int t) {
		for (int i = 30; ~i; --i) {
			if (!(t >> i & 1)) continue; 
			if (a[i]) t ^= a[i]; 
			else {
				for (int j = 0; j < i; ++j) if (t >> j & 1) t ^= a[j];
				for (int j = i + 1; j <= 30; ++j) if (a[j] >> i & 1) a[j] ^= t;
				a[i] = t;
				break; 
			}
		}
	}
	
	inline int Get_Max() {
		int Ans = 0;
		for (int i = 30; ~i; --i) Ans ^= a[i];
		return Ans;
	}
}empty;

inline void Query(int l, int r, Basis G, int ql, int qr) {
	register int mid = l + r >> 1, st = ql, f; 
	for (int i = ql; i <= qr; ++i)
		if (v[i].L <= l && v[i].R >= r)
			G.Insert(v[i].val), std::swap(v[st++], v[i]);
	if (l == r) return printf("%d\n", G.Get_Max()), void();
	f = st; 
	for (int i = st; i <= qr; ++i)
		if (v[i].L <= mid) std::swap(v[f++], v[i]);
	Query(l, mid, G, st, f - 1);
	f = st;
	for (int i = st; i <= qr; ++i)
		if (v[i].R > mid) std::swap(v[f++], v[i]);
	Query(mid + 1, r, G, st, f - 1);
}

int main() {
	n = read(); 
	for (int i = 1; i <= n; ++i) {
		register int x = read();
		if (x > 0) v[++cnt].L = i, v[cnt].val = x, last[x] = cnt;
		else v[last[-x]].R = i - 1;
	}
	for (int i = 1; i <= cnt; ++i) if (!v[i].R) v[i].R = n;
	Query(1, n, empty, 1, cnt);
	return 0;
}
