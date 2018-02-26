# include <stdio.h>
# include <iostream> 
//# define int unsigned long long 
typedef unsigned long long ull;
const int MAXN = 1e5 + 5;
int n, k, cnt, a[35], b[35];


inline long long read() {
	register long long x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f= -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

inline void Insert(int t) {
	for (int i = 30; ~i; --i) {
		if (!(t >> i & 1)) continue;
		if (a[i]) t ^= a[i];
		else {
			for (int j = i - 1; j >= 0; --j) if (t >> j & 1) t ^= a[j];
			for (int j = i + 1; j <= 30; ++j) if (a[j] >> i & 1) a[j] ^= t;
			a[i] = t; break;
		}
	}
}

inline void Work_1(){
	ull Ans = 0;
	for (int i = 1; i <= n; ++i) Ans |= read();
	printf("%llu", Ans >> 1);
	if (Ans & 1) puts(".5");
	else puts(""); 
}

inline void Work_2(){
	static bool bit[65];
	static int val[MAXN];
	for (int i = 1; i <= n; ++i) {
		register int t = read(); val[i] = t;
		for (int j = 0; j <= 31; ++j) bit[j] |= (t >> j & 1);
	}
	
	ull Ans = 0, res = 0;
	
	for (int i = 0; i <= 31; ++i)
		for (int j = 0; j <= 31; ++j) {
			if (!(bit[i] & bit[j])) continue;
			bool flag = false; 
			for (int k = 1; k <= n; ++k) if ((val[k] >> i & 1) != (val[k] >> j & 1)) { flag = true; break; }
			if (i + j - 1 - flag < 0) ++ res;
			else  Ans += 1ll << (i + j - 1 - flag);
		}
	Ans += res >> 1;
	printf("%llu", Ans);
	if (res & 1) puts(".5");
	else puts("");
}

inline void Work_3() {
	for (int i = 1; i <= n; ++i) Insert((int)read());
	for (int i = 0; i <= 30; ++i) if (a[i]) b[cnt++] = i;
	int Total = 1 << cnt, full = Total - 1, val;
	ull Ans = 0, lef = 0, All, A = 0, B = 1;
	for (int i = 1; i <= full; ++i) {
		val = 0; All = 1;
		for (int j = 0; j < cnt; ++j)
			if (i >> j & 1) val ^= a[b[j]];
			
		A = 0; B = 1;

		for (int j = 1; j <= k; ++j) 
			A *= val, B *= val, A += B >> cnt, B &= full;
			
		Ans += A; lef += B;
		Ans += lef >> cnt; lef &= full;
	}
	printf("%llu", Ans);
	if (lef) puts(".5");
	else puts("");
}

int main() {
	n = read(), k = read();
	if (k == 1) Work_1();
	else if (k == 2) Work_2();
	else Work_3();
	return 0;
}
