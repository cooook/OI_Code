#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>


#define pb push_back
#define fi first
#define se second
#define mk std::make_pair
#define int long long 


typedef long long ll;
typedef std::pair<int,ll> pii;
typedef std::vector<pii> Vec;
typedef std::vector<pii>::iterator D;


const int MAXN = 150005;
int n,Q,A,val[MAXN],first[MAXN],e = 1,root,Num,size[MAXN],g[MAXN],pre[MAXN],f[MAXN],deep[MAXN],st[MAXN << 1][18];
int dfn[MAXN],idx,Log[MAXN << 1],bin[18],Last_Ans;
bool vis[MAXN]; Vec Sum[MAXN],Up_Sum[MAXN],num[MAXN];


char xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read() {
    int x = 0, f = 1; char ch = getc();
    for (; ch < '0' | ch > '9'; ch = getc()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getc()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
	int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w){
	a[e].u = u; a[e].v = v; a[e].w = w;
	a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int fa){
	st[dfn[u] = ++ idx][0] = deep[u];
	for (int i = first[u]; i; i = a[i].next){
		register int v = a[i].v;
		if (v == fa) continue;
		deep[v] = deep[u] + a[i].w;
		dfs(v,u);
        st[++idx][0] = deep[u];
	}
}

inline void build_st(){
	Log[1] = 0; bin[0] = 1;
	for (int i = 2; i <= idx; i++) Log[i] = Log[i >> 1] + 1;
	for (int i = 1; i <= 17; i++) bin[i] = bin[i-1] << 1;
	for (int j = 1; j <= 17; j++)
		for (int i = 1; i + bin[j] - 1 <= idx; i++)
			st[i][j] = std::min(st[i][j-1],st[i+bin[j-1]][j-1]);
}

inline int lca(int u,int v){
	int x = dfn[u], y = dfn[v];
	if (x > y) std::swap(x,y);
	int len = Log[y - x + 1];
	return std::min(st[x][len],st[y-bin[len]+1][len]) << 1; 
}

inline int dis(int u,int v){
	return deep[u] + deep[v] - lca(u,v);
}

inline void G_size(int u,int fa){
	size[u] = 1;
	for (int i = first[u]; i; i = a[i].next)
		if (a[i].v != fa && !vis[a[i].v])
			G_size(a[i].v,u), size[u] += size[a[i].v];
}

inline void G_root(int u,int fa){
	g[u] = 0;
	for (int i = first[u]; i; i = a[i].next){
		register int v = a[i].v;
		if (v == fa || vis[v]) continue;
		g[u] = std::max(g[u],size[v]);
		G_root(v,u);
	}
	g[u] = std::max(g[u],Num - g[u]);
	if (g[u] < g[root]) root = u;
}

inline void G_Vec(int u,int fa,int last,Vec &Sum,Vec &Up_Sum){
	Sum.pb(mk(val[u],dis(u,last)));
	Up_Sum.pb(mk(val[u],dis(u,pre[last])));
	for (int i = first[u]; i; i = a[i].next){
		register int v = a[i].v;
		if (v == fa || vis[v]) continue;
		G_Vec(v,u,last,Sum,Up_Sum);
	}
}

Vec tmp1,tmp2,tmp3;

inline void Div(int u){
	vis[u] = true; G_size(u,0);
	G_Vec(u,0,u,Sum[u],Up_Sum[u]);
	Sum[u].pb(mk(-1,0)); Up_Sum[u].pb(mk(-1,0));
	std::sort(Sum[u].begin(),Sum[u].end());
	std::sort(Up_Sum[u].begin(),Up_Sum[u].end());
	for (int i = 1; i < Sum[u].size(); i++) Sum[u][i].se += Sum[u][i-1].se;
	for (int i = 1; i < Up_Sum[u].size(); i++) Up_Sum[u][i].se += Up_Sum[u][i-1].se;
	for (int i = first[u]; i; i = a[i].next){
		register int v = a[i].v;
		if (vis[v]) continue;
		Num = size[v]; root = 0; G_root(v,0), pre[root] = u, Div(root);
	}
}

inline pii Query(int l,int r,Vec &Sum){
	pii L = mk(l,0),R = mk(r+1,0);
	D it1 = std::lower_bound(Sum.begin(),Sum.end(),L); -- it1;
	D it = std::lower_bound(Sum.begin(),Sum.end(),R); -- it;
	return mk(it -> se - it1 -> se,it - it1);
}

int T_Sum[MAXN],T_Up_Sum[MAXN],T_num[MAXN];

inline int Query(int x,int L,int R){
	int Ans = 0; pii tmp1, tmp2;
	for (int u = x; u; u = pre[u]){
		tmp1 = Query(L,R,Sum[u]);
		tmp2 = Query(L,R,Up_Sum[u]);
		T_Sum[u] = tmp1.fi;
		T_num[u] = tmp1.se;
		T_Up_Sum[u] = tmp2.fi;
	}
	for (int u = x; u; u = pre[u]){
		Ans += T_Sum[u];
		if (pre[u]) Ans += -T_Up_Sum[u] + (T_num[pre[u]] - T_num[u]) * dis(x,pre[u]); 
	} return Ans;
}

signed main(){
//	freopen("4012.in","r",stdin);
//	freopen("4012.out","w",stdout);
	n = read(); Q = read(); A = read();
	for (int i = 1; i <= n; i++) val[i] = read();
	for (int i = 1; i < n; i++){
		register int u = read(),v = read(), w = read();
		push(u,v,w), push(v,u,w);
	} dfs(1,0); build_st(); G_size(1,0);
	Num = n; g[0] = n; root = 0; G_root(1,0); Div(root);
	while (Q--){
		register int u = read(),l = read(),r = read();
		(l += Last_Ans) %= A;
		(r += Last_Ans) %= A;
		if (l > r) std::swap(l,r);
		printf("%lld\n",Last_Ans = Query(u,l,r));
	}
    return 0;
}
