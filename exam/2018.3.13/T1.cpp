# pragma GCC optimize("O3")
# include <bits/stdc++.h>
# define fi first
# define se second
const int MAXN = 2e5 + 5; 
int n, val[MAXN], first[MAXN], e = 1;


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
	register int x = 0, f = 1; char ch = getc;
	for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline void gmax(int &x, const int &y) {
	if (x < y) x = y;
}

struct edge {
	int u, v, next;
} a[MAXN << 1];

std::map<int, int> f[MAXN];

inline void push(int u, int v) {
	a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u, int fa) {
	for (int i = first[u], v; i; i = a[i].next) {
		if ((v = a[i].v) == fa) continue; 
		dfs(v, u);
		if (f[u].size() < f[v].size()) std::swap(f[u], f[v]);
		for (auto j:f[v]) f[u][j.fi] += j.se;
	}
	++ f[u][val[u]];
	auto it = f[u].find(val[u]);
	if (it != f[u].begin()) {
		-- it; -- it -> se; 
		if (!it -> se) f[u].erase(it);  // 这个地方实现了取 max 骚!
	}
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) val[i] = read();
    for (int i = 1; i < n; ++i) {
		register int u = read(), v = read();
		push(u, v), push(v, u); 
	} dfs(1, 0);
    for (auto i:f[1]) n -= i.se;
    printf("%d\n", n);
	return 0;
}


// T1正解  
// 我的dp是设f[i][j]为以i为根的子树中i的权值为j且i这颗子树合法的最小花费.  
// 然后转移的话就是枚举u每个儿子v, 
// f[u][j] += std::min(f[v][j...cnt]);
// 其中cnt代表离散以后的权值的范围.  
// 这样可以拿到n <= 3000 的40分, 
// 链的话其实就是一个序列, 求一个最长不下降子序列就可以了.  
// 其实把这东西拓展到树上就可以了.  
// 那么其实就是选树上的一些点使其满足小根堆的性质, 求出最大的小根堆, 用n减掉就是答案.  
// 这玩应打出来的话也是40分的暴力, 考虑转换状态, 设f[i][j]为在以i为根的子树中, 选出的小跟堆的堆顶的val大于等于j最多可以选多少个, 
// 其实就是一个后缀的最大值.
// 这时候的暴力转移已经变为了 f[u][i] += f[v][i], 再考虑一下选不选u的贡献就可以了. 
// 然后把dp值差分一下, 对每个节点开个map维护, 启发式合并之, 然后考虑自己的贡献, 就在map的对应位置减一下就可以了.  
// 然后就有一些骚操作来搞一搞了, 我想了想, 这种东西应该也可以用到我的DP上. 
// 王琦用线段树启发式合并A掉了这道题, 但是我并不会线段树启发式合并这种东西, 要抽空学一下, 这种东西可能比较像dus on tree的解法? 
// 学习到了树上DP 的新姿势...  
