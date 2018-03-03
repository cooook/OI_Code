# pragma GCC optimize("O3")
# include <stdio.h>
# define C2(_) (1ll * (_) * (_ - 1) % mod * Inv2 % mod)
# define C3(_) (1ll * (_) * (_ - 1) % mod * (_ - 2) % mod * Inv6 % mod)
# define C4(_) (1ll * (_) * (_ - 1) % mod * (_ - 2) % mod * (_ - 3) % mod * Inv24 % mod)
const int mod = 1e9 + 7; 
const int Inv2 = 500000004;
const int Inv6 = 166666668;
const int Inv24 = 41666667;
int f[505], n; 

inline int sum(int x, int y) {
    return (x + y) % mod; 
}

inline void upd(int &x, const int &y) {
    x += y; if (x >= mod) x -= mod; 
}

int main() {
    scanf("%d", &n);
    f[0] = 1, f[1] = 1;
    register int i, j, k, l, Ans = 0;
    for (i = 2; i <= n / 2; ++i)
        for (j = 0; j < i; ++j)
            for (k = 0; k <= j; ++k)
                if (j + k < i) {
                    l = i - 1 - j - k;
                    if (l < j) break; 
                    if (l == k) upd(f[i], sum(f[l], sum(C2(f[l]) * 2 % mod, C3(f[l]))));
                    else if (l == j) upd(f[i], 1ll * f[k] * sum(f[l], C2(f[l])) % mod);
                    else if (j == k) upd(f[i], 1ll * f[l] * sum(f[k], C2(f[k])) % mod);
                    else upd(f[i], 1ll * f[j] * f[k] % mod * f[l] % mod);
                }
                else break;
    for (i = 0; i <= (n - 1) / 2; ++i) 
        for (j = 0; j <= i; ++j)
            for (k = 0; k <= j; ++k)
                if (i + j + k < n) {
                    l = n - i - j - k - 1;
                    if (l < i || l > (n - 1) / 2) continue; 
                    if (l == k) upd(Ans, sum(f[l], sum(3ll * C2(f[l]) % mod, sum(3ll * C3(f[l]) % mod, C4(f[l]))))); 
                    else if (l == j) upd(Ans, 1ll * f[k] * sum(f[l], sum(2 * C2(f[l]) % mod, C3(f[l]))) % mod);
                    else if (l == i && j == k) upd(Ans, 1ll * sum(f[l], C2(f[l])) * sum(f[j], C2(f[j])) % mod);
                    else if (i == k) upd(Ans, 1ll * f[l] * sum(f[i], sum(2 * C2(f[i]) % mod, C3(f[i]))) % mod);
                    else if (i == j) upd(Ans, 1ll * f[k] * f[l] % mod * sum(f[i], C2(f[i])) % mod);
                    else if (j == k) upd(Ans, 1ll * f[i] * f[l] % mod * sum(f[j], C2(f[j])) % mod);
                    else if (i == l) upd(Ans, 1ll * f[j] * f[k] % mod * sum(f[i], C2(f[i])) % mod);
                    else upd(Ans, 1ll * f[i] % mod * f[j] % mod * f[k] % mod * f[l] % mod);
                }
    if (!(n & 1)) upd(Ans, sum(C2(f[n / 2]), f[n / 2]));
    printf("%d\n", Ans);
    return 0;
}
