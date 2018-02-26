#include <bits/stdc++.h>
#define MAXN 100005
#define int long long 
typedef long long ll;
int n,L[MAXN][2],R[MAXN][2],now,sum[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int d[2],id;
    inline int& operator []  (const int &x) {return d[x];}
    inline bool operator < (const Point &x) {
        return d[now] == x.d[now]?d[now ^ 1] < x.d[now ^ 1]:d[now] < x.d[now];
    }
}pt[MAXN];

inline void Work(bool type) {
	now = type;
	std::sort(&pt[1],&pt[n+1]);
	memset(sum,0,sizeof sum);
	for (int i = 1; i <= n; i++) sum[i] = sum[i-1] + (i - 1) * (pt[i][type] - pt[i-1][type]),L[pt[i].id][type] = sum[i];
	memset(sum,0,sizeof sum);
	for (int i = n; i >= 1; i--) sum[i] = sum[i+1] + (n - i) * (pt[i+1][type] - pt[i][type]),R[pt[i].id][type] = sum[i];
 	return;
}

signed main() {
	n = read<int>();
	for (int i = 1; i <= n; i++) {
		register int x = read<int>(),y = read<int>();
		pt[i][0] = x + y;
		pt[i][1] = x - y;
		pt[i].id = i;
	}
	Work(false); Work(true);
	ll Ans = 1e18;
	for (int i = 1; i <= n; i++) Ans = std::min(Ans,L[i][0] + L[i][1] + R[i][0] + R[i][1]);
	printf("%lld\n",Ans >> 1);
	getchar(); getchar();
    return 0;
}
