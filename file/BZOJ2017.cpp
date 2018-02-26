# include <stdio.h>
int f[2005][2005], c[2005], Sum[2005], n;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(int &x, const int &y) {
    if (x < y) x = y;
}

int main() {
    n = read();
    for (int i = n; i; i--) c[i] = read();
    for (int i = 1; i <= n; i++) Sum[i] = Sum[i - 1] + c[i]; 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i][j-1];
            if (i >= (j << 1)) gmax(f[i][j], Sum[i] - f[i - (j << 1)][j << 1]);
            if (i >= (j << 1) - 1) gmax(f[i][j], Sum[i] - f[i - (j << 1) + 1][(j << 1) - 1]);
        }
    printf("%d\n", f[n][1]);
    return 0;
}