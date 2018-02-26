# include <stdio.h> 
const int mod = 10086;
int n, a[32], cnt, val[32], Q;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Insert(int t) {
    for (int i = 30; ~i; --i) {
        if (!(t >> i & 1)) continue;
        if (a[i]) t ^= a[i];
        else {
            for (int j = i - 1; ~j; --j) if (t >> j & 1) t ^= a[j];
            for (int j = i + 1; j <= 30; ++j) if (a[j] >> i & 1) a[j] ^= t;
            a[i] = t;
            break; 
        }
    }
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i) Insert(read());
    for (int i = 0; i <= 30; ++i) if (a[i]) val[cnt++] = i;
    Q = read();
    int Ans = 0;
    for (int i = 0; i < cnt; ++i)
        if (Q >> val[i] & 1)
            Ans |= 1 << i, Ans %= mod;
    printf("%d\n", (qpow(2, n - cnt) * Ans % mod + 1) % mod);
    return 0;
}