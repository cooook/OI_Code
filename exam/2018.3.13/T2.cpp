# include <bits/stdc++.h>
# define fi first
# define se second
# define mk std::make_pair
typedef std::pair<int, int> pii; 
typedef std::set<pii>::iterator Dit; 
const int MAXN = 2e5 + 5; 
const int mod = 1e9 + 7; 
int n, val[MAXN], Sum, Ans, last, front, back, f[MAXN], g[MAXN];
bool vis[MAXN];  
std::set<pii> S; 
pii t[MAXN]; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
	register int x = 0, f = 1;
	register char ch = getc; 	
	for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
	return x * f;
}

# define Calc(x) (1ll * (x) * ((x) + 1) / 2 % mod)

inline int Cal(int L, int R) {
	if (!L || !R) return f[L | R];
	-- L; 
	register int t = std::min(L, R), p = std::max(L, R);
	return ((Calc(L + 1) + f[p - t]) % mod + (g[L + R] - g[p - t] + mod) % mod) % mod;
}

inline void erase(pii t) {
	S.erase(t);
	if (t.fi == 1 || t.se == n) return ;
	Sum = (Sum - f[t.se - t.fi + 1] + mod) % mod;
}

inline void Insert(pii t) {
	S.insert(t);
	if (t.fi == 1 || t.se == n) return;  
	(Sum += f[t.se - t.fi + 1]) %= mod; 
}

inline void Update(int x) {
	vis[x] = true; 
	Sum = (Sum - Cal(front, back) + mod) % mod; 
	while (vis[front + 1]) ++ front;
	while (vis[n - back]) ++ back;
	(Sum += Cal(front, back)) %= mod;
	Dit it = S.insert(mk(x, x)).fi;
	Dit tmp1 = it, tmp2 = it;
	int L = x, R = x;
	if (it != S.begin() && (-- tmp1) -> se + 1 == L) L = tmp1 -> fi, erase(*tmp1);
	if ((++ tmp2) != S.end() && tmp2 -> fi == R + 1) R = tmp2 -> se, erase(*tmp2);
	S.erase(mk(x, x)); Insert(mk(L, R));
}

inline void Init() {
	for (int i = 1; i <= n; ++i) f[i] = (f[i - 1] + Calc(i)) % mod;
	for (int i = 1; i <= n; ++i) g[i] = ((i < 2 ? 0 : g[i - 2]) + Calc(i)) % mod;
}

signed main() {
	n = read();
	Init(); 
	for (int i = 1; i <= n; ++i) 
		val[i] = read(), t[i] = mk(val[i], i);
	std::sort(&t[1], &t[n + 1]);
	last = 0, Ans = 0; 
	for (int i = 1; i <= n; ++i) {
		Update(t[i].se);
		if (t[i].fi != t[i + 1].fi && i != n) 
			(Ans += 1ll * (((Sum - last) % mod + mod) % mod) * t[i].fi % mod) %= mod, last = Sum; 
	}
	(Ans += 1ll * ((((Calc(Calc(n)) - last) % mod) + mod) % mod) * t[n].fi % mod) %= mod;
	printf("%d\n", Ans);
	return 0; 
}
/**
 * 考试的时候只想出来了30分的做法, 并没有运用到另外30分的性质, 但是这30分就很能来开差距, 如果继续往下研究就可以搞出正解. 
 * 30分的做法就是先暴力模拟出来T(A), 然后再做一遍单调队列, 就求出来了最后的答案.... 
 * 另外30分只有两种权值的做法是这样的
 * 由于只有两种权值, 所以我们可以算出来有哪些区间只包含最小值, 那么这些区间的答案就是最小值啦.  
 * 然后我们又知道所有的区间数, 然后就可以愉快的求出有哪些区间是最大值了.  
 * 正解的话就是用类似的思路, 把val按升序排序, 然后维护现在有多少区间的权值是小于等于当前加的权值的, 用这次插入完权值后区间数减去
 * 原来的权值数就是对应的该权值对应的有多少区间最大值为它. 
 * 这种做法其实考虑了两种东西, 一种是在中位数、最值中很常用的离线排序处理, 另一种是本题的60分做法, 就得到了这道题的满分做法. 
 * 下面是60分做法的代码.  
*/

/*
# include <stdio.h> 
# include <iostream>
# include <algorithm> 
const int MAXN = 2e5 + 5; 
const int mod = 1e9 + 7; 
const int inf = 0x3f3f3f3f; 
int n, val[MAXN]; 
 
 
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
 
inline void gmin(int &x, const int &y) {
    if (x > y) x = y; 
}
  
namespace Solver_30 {
    const int maxn = 3e6 + 5;
    int Q[maxn], L[maxn], R[maxn], fi[maxn], cnt;
    struct node {
        int x, len, val; 
        inline bool operator < (const node &a) const {
            return len == a.len ? x < a.x : len < a.len; 
        }
    }tmp[maxn]; 
    inline void trans() {
        for (int i = 1; i <= n; ++i) {
            register int Mx = 0; 
            for (int j = i; j <= n; ++j)
                gmax(Mx, val[j]),
                tmp[++cnt].x = i,
                tmp[cnt].len = j - i + 1,
                tmp[cnt].val = Mx; 
        }
        std::sort(&tmp[1], &tmp[cnt + 1]);
        for (int i = 1; i <= cnt; ++i) fi[i] = tmp[i].val;
    }
    int Main() {
        trans();
        int top = 0;
        for (int i = 1; i <= cnt; ++i) {
            while (top && fi[Q[top]] < fi[i]) -- top;
            L[i] = Q[top]; Q[++top] = i;
        }
        Q[top = 0] = cnt + 1;
        for (int i = cnt; i; --i) {
            while (top && fi[Q[top]] <= fi[i]) -- top;
            R[i] = Q[top]; Q[++top] = i; 
        }
        register int Ans = 0;
        for (int i = 1; i <= cnt; ++i) 
            (Ans += 1ll * (R[i] - i) * (i - L[i]) % mod * fi[i] % mod) %= mod; 
        printf("%d\n", Ans);
    }
}
 
# define Calc(x) (1ll * (x) * ((x) + 1) / 2 % mod)
  
namespace _233 {
    int s[MAXN], Mn, Mx; 
    inline void Main() {
        Mn = inf, Mx = -inf; 
        for (int i = 1; i <= n; ++i) 
            s[i] = (s[i - 1] + 1ll * i * (i + 1) / 2 % mod) % mod, 
            gmin(Mn, val[i]), gmax(Mx, val[i]);
        int front = 0, back = 0, cnt = 0, Ans = 0;
        while (val[front + 1] == Mn) ++ front;
        while (val[n - back] == Mn) ++ back;
        for (int i = 1; i <= n + 1; ++i)
            if (val[i] != val[i - 1]) {
                if (val[i - 1] == Mn) (Ans += s[cnt]) %= mod;
                cnt = 1;
            }
            else ++ cnt; 
        -- front;
        while (front && back) {
            Ans = (Ans - Calc(front) + mod) % mod;
            Ans = (Ans - Calc(back) + mod) % mod; 
            Ans = (Ans + Calc(front + back)) % mod;
            -- front; -- back;
        }
        register int tmp = 1ll * n * (n + 1) / 2 % mod;
        tmp = 1ll * tmp * (tmp + 1) / 2 % mod;
        printf("%d\n", (1ll * tmp * Mx % mod + 1ll * Ans * (Mn - Mx) % mod + mod) % mod);
    }
}
  
int main() {
    n = read(); 
    for (int i = 1; i <= n; ++i) val[i] = read();
    if (n <= 2000) Solver_30::Main(); 
    else _233::Main();
    return 0; 
}
*/