# include <stdio.h>
# include <cstring>
# include <iostream>
const int MAXN = 1025;  
int n; 
double f[105][MAXN], g[105][MAXN]; // f[i][j] --> if SG[i] == j, P = f[i][j]


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

int main() {
    f[1][0] = 1.0;
    for (int i = 2; i <= 100; i++) {
        for (int j = 0; j < i; j++) f[i][j + 1] += f[i - 1][j] * 2; 
        for (int j = 1; j < i - 1; j++)
            for (int k = 0; k <= j; k++)
                for (int o = 0; o <= i - j - 1; o++)
                    f[i][(k + 1) ^ (o + 1)] += f[j][k] * f[i - j - 1][o];
    }
    for (int i = 2; i <= 100; i++) {
        double Ans = 0.0;
        for (int j = 0; j <= i; j++) Ans += f[i][j];
        for (int j = 0; j <= i; j++) f[i][j] /= Ans; 
    }
    n = read();
    g[0][0] = 1.0;
    for (int i = 1; i <= n; i++) {
        register int x = read();
        for (int j = 0; j <= 256; j++)
            for (int k = 0; k <= x; k++)
                g[i][j ^ k] += g[i - 1][j] * f[x][k];
    }
    printf("%.6f\n", 1.0 - g[n][0]);
    return 0;
}