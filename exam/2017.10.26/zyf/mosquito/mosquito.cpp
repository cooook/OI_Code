#include <stdio.h>
#define int long long 
typedef long long ll;
const int MAXN = 5000005,mod = 1e9+7;
int n ,first[MAXN],e = 1,du[MAXN],deep[MAXN],size[MAXN],d,p,q,f[MAXN],f_Num[MAXN],Num[MAXN];
ll Ans,live;


char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read() {
	int x = 0, f = 1; char ch = getc();
	for (; ch < '0' | ch > '9'; ch = getc()) if (ch == '-') f = -f;
	for (; ch <= '9' && ch >= '0'; ch = getc()) x = x * 10 + (ch ^ 48);
	return x * f;
}

struct edge{
	int v,next;
}a[MAXN<<1];

inline void push(int u,int v) {
	a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline ll qpow(ll x,ll k) {
	ll Ans = 1;
	for (; k; k >>= 1, x = x * x % mod)
		if (k & 1) Ans = Ans * x % mod;
	return Ans;
}

inline void dfs(int u,int fa) {
	if (du[u] == 1) {
		if (deep[u] <= d) f[u] = live;
		else f[u] = 1;
		size[u] = 1;
		return;
	}
	for (int i = first[u]; i; i = a[i].next) {
		register int v = a[i].v;
		if (v == fa) continue;
		deep[v] = deep[u] + 1;
		dfs(v,u); 
		if (deep[u] <= d) f[u] = (f[u] + f[v] * live % mod) % mod;
		else f[u] = (f[u] + f[v]) % mod;
		size[u] += size[v];
	}
}

inline void dp(int u,int fa) {
	for (int i = first[u]; i; i = a[i].next) {
		register int v = a[i].v;
		if (v == fa) continue;
		Num[v] = Num[u] + size[u] - size[v];
		if (deep[u] <= d) f_Num[v] = (f_Num[u] + f[u] - f[v] * live % mod + mod) % mod;
		else f_Num[v] = (f_Num[u] + f[u] - f[v] + mod) % mod;
		if (deep[v] <= d) f_Num[v] = f_Num[v] * live % mod;
		dp(v,u);
	}
}

signed main() {
	n = read();
	for (int i = 1,u,v; i < n; i++) {
		u = read(),v = read();
		push(u,v); push(v,u);
		du[u] ++; du[v] ++;
	}
	
	ll Ans = 0;
	
	d = read(); p = read(); q = read();
	
	if (p == q) p = q = 1;
	
	live = (q - p) * qpow(q,mod - 2) % mod;
	
	dfs(1,0); dp(1,0);
	
	for (int i = 1; i <= n; i++)
		if (du[i] == 1)
			(Ans += Num[i] - f_Num[i] + mod) %= mod;
	printf("%lld\n",Ans);
	return 0;
}
