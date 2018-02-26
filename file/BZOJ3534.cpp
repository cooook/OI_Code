# include <iostream> 
const int MAXN = 55;
const long double eps = 1e-8;
int n; 
long double a[MAXN][MAXN];


inline double Gauss() {
	long double Ans = 1.0;
	for (int i = 1; i < n; i++) {
		int u = i;
		for (int j = i + 1; j < n; j++) 
			if (a[j][i] > a[u][i]) u = j;
		if (a[u][i] < eps) { Ans = 0.0; break; }
		if (u != i) {
			Ans *= -1;
			for (int j = i; j < n; j++) std::swap(a[i][j], a[u][j]);
		}
		for (int j = i + 1; j < n; j++) {
			long double t = a[j][i] / a[i][i];
			for (int k = i; k < n; k++)
				a[j][k] -= t * a[i][k];
		}
		Ans *= a[i][i];
	}
	return Ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	long double Ans = 1.0;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++){
			register long double f; std::cin >> f; 
			if (i >= j) continue;
			if (f == 1.0) f -= eps;
			a[i][i] += f / (1 - f); a[j][j] += f / (1 - f);
			a[i][j] -= f / (1 - f); a[j][i] -= f / (1 - f);
			Ans *= 1 - f;
		}
	std::cout << Gauss() * Ans;
	return 0;
}
