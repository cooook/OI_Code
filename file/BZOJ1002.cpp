# include <stdio.h>
# include <math.h> 
# include <iostream> 
const double eps = 1e-8; 
int n; 
double a[105][105]; 


inline void Link(int x, int y) {
	a[x][x] ++; a[y][y] ++;
	a[x][y] --; a[y][x] --;
}

inline double Gauss() {
	double Ans = 1.0; 
	for (int i = 1; i <= n; i++) {
		int u = i;
		for (int j = i + 1; j <= n; j++)
			if (a[u][i] < a[j][i]) u = j;
		if (fabs(a[u][i]) < eps) { Ans = 0.0; break; }
		if (u != i) {
			Ans = -Ans;
			for (int j = i; j <= n; j++) std::swap(a[u][j], a[i][j]);
		}
		for (int j = i + 1; j <= n; j++) {
			double t = a[j][i] / a[i][i];
			for (int k = i; k <= n; k++)
				a[j][k] -= t * a[i][k];
		}
		Ans *= a[i][i];
	}
	return Ans;
}

int main() {
//	f[1] = 1; f[2] = 5; f[3] = 16; f[4] = 45; f[5] = 121;
//  f[i] = f[i-1] * 3 - f[i-2] + 2; 
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		Link(i, i == n ? 1 : i + 1), Link(i, n + 1);
	printf("%.0f\n", Gauss());
	return 0;
}
