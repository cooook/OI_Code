#include <bits/stdc++.h>
typedef long long ll;
int n,r,q,id[25][25],N; ll S;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar())
        x = x * 10 + (ch ^ 48);
    return x * f;
}

struct matrix {
	double a[111][111];
	matrix() {memset(a,0,sizeof a);}
	inline double* operator [] (const int x) {
		return a[x];
	}
	inline void print() {
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				printf("%f%c",a[i][j]," \n"[j==N]);
	}
}mul;

inline matrix operator * (matrix a,matrix b) {
	matrix Ans;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (a[i][j] > 1e-15)
				for (int k = 1; k <= N; k++)
					Ans[i][k] += a[i][j] * b[j][k];
	return Ans;
}

inline matrix operator ^ (matrix a,int k) {
	matrix Ans; for (int i = 1; i <= N; i++) Ans[i][i] = 1.0;
	for (; k; k >>= 1, a = a * a)
		if (k & 1) Ans = Ans * a;
	return Ans;
}

inline double DP(double p) {
	memset(mul.a,0,sizeof mul.a);
	mul[N][N] = 1.0;
	for (int i = 1; i <= q; i++)
		for (int j = 1; j <= r; j++) {	
			mul[N][id[i][j]] += p * j;
			mul[id[std::min(i+1,q)][std::min(j+1,r)]][id[i][j]] += p;
			if (i > 1) mul[id[i-1][1]][id[i][j]] += 1 - p;
		}
	mul = mul ^ n;
	return mul[N][id[q][1]];
}

int main() {
	n = read<int>(); r = read<int>(); q = read<int>(); S = read<ll>();
	for (int i = 1; i <= q; i++) for (int j = 1; j <= r; j++) id[i][j] = ++ N;
	N ++;
	if (DP(1.0) <= S) return puts("Impossible."), 0;
	double l = 0.0,r = 1.0,mid;
	while (l + 1e-8 < r) {
		mid = (l + r) / 2.0;
		if (DP(mid) > S) r = mid;
		else l = mid; 
	}
	printf("%.6lf\n",mid); // mid 比 Ans 更精准QAQ....
    return 0;
}
