# include <bits/stdc++.h>
const int mod = 1e9 + 7; 
const int MAXN = 1e6 + 5; 
int f[MAXN], n, trans[MAXN][26], fail[MAXN], diff[MAXN], nxt[MAXN], last, len[MAXN], tot, S[MAXN], g[MAXN];
char s[MAXN];

inline void upd(int &x, const int &y) {
	(x += y) %= mod; 
}

inline int newnode(int x) {
	return len[tot] = x, tot ++; 
}

inline int get_fail(int x, int n) {
	while (S[n - len[x] - 1] != S[n]) x = fail[x];
	return x; 
}

inline void insert(int c, int n) {
	register int rt = get_fail(last, n); 
	if (!trans[rt][c]) {
		register int nw = newnode(len[rt] + 2);
		fail[nw] = trans[get_fail(fail[rt], n)][c];
		diff[nw] = len[nw] - len[fail[nw]];
		if (diff[nw] == diff[fail[nw]]) nxt[nw] = nxt[fail[nw]];
		else nxt[nw] = fail[nw]; 
		trans[rt][c] = nw;
	} last = trans[rt][c]; 
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	S[0] = -1; 
	newnode(0); newnode(-1); 
	fail[0] = 1; f[0] = 1; 
	for (int i = 1; i <= n; ++i) 
		if (i & 1) S[i] = s[i + 1 >> 1] - 'a';
		else S[i] = s[n - (i >> 1) + 1] - 'a';
	for (int i = 1; i <= n; ++i) {
		insert(S[i], i);
		for (int p = last; p; p = nxt[p]) {
			g[p] = f[i - len[nxt[p]] - diff[p]];
			if (diff[p] == diff[fail[p]]) upd(g[p], g[fail[p]]);
			if (!(i & 1)) upd(f[i], g[p]);
		}
	}
	return printf("%d\n", f[n]), 0;
}
