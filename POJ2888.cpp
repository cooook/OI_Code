# include <stdio.h> 
# include <cstring>
# include <iostream> 
const int MAXN = 1e5 + 5;
const int mod = 9973; 
int T, n, m, k, prime[MAXN], cnt;
bool _prime[MAXN];


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1) Ans = Ans * x % mod;
    return Ans; 
}

inline void Init(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!_prime[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && prime[j] * i <= n; ++j) {
            _prime[i * prime[j]] = true;
            if (!(i % prime[j])) break; 
        }
    }
}

struct matrix {
    int a[11][11]; 
    matrix() { clear(); }
    inline void clear() { memset(a, 0, sizeof a); }
    inline matrix operator * (const matrix &x) const {
        matrix Ans ; register int i, j, k; 
        for (i = 1; i <= m; ++i) 
            for (k = 1; k <= m; ++k) if (a[i][k])
                for (j = 1; j <= m; ++j) if (x.a[k][j])
                    (Ans.a[i][j] += a[i][k] * x.a[k][j] % mod) %= mod;
        return Ans; 
    }
}mul, t[40];

inline int phi(int x) {
    int Ans = 1;
    for (int i = 1; prime[i] * prime[i] <= x && i <= cnt; ++i)
        if (x % prime[i] == 0) {
            Ans *= prime[i] - 1;
            x /= prime[i];
            while (x % prime[i] == 0) Ans *= prime[i], x /= prime[i];
        }
    if (x != 1) Ans *= x - 1;
    return Ans % mod; 
}

inline matrix qpow(int k) {
    matrix Ans; for (int i = 1; i <= m; ++i) Ans.a[i][i] = 1;
    int cnt = 0;
    while (k) {
        if (k & 1) Ans = Ans * t[cnt];
        k >>= 1; ++ cnt;
    }
    return Ans; 
}

inline int Calc(int n) { 
    matrix t = qpow(n);
    int Ans = 0; 
    for (int i = 1; i <= m; ++i) 
        Ans += t.a[i][i];
    return Ans; 
}

int main() {
    Init(100000);
    T = read(); 
    while (T --) {
        n = read(), m = read(), k = read(); 
        mul.clear(); 
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j)
                mul.a[i][j] = 1;

        for (int i = 1; i <= k; ++i) {
            register int x = read(), y = read();
            mul.a[x][y] = mul.a[y][x] = false; 
        }

        memcpy(t[0].a, mul.a, sizeof mul.a);

        for (int i = 1; i <= 30; ++i) t[i] = t[i - 1] * t[i - 1];

        int Ans = 0;

        for (int i = 1; i * i <= n; ++i)
            if (n % i == 0) {
                (Ans += Calc(i) * phi(n / i) % mod) %= mod;
                if (i * i != n) (Ans += Calc(n / i) * phi(i) % mod) %= mod; 
            }
        printf("%d\n", Ans * qpow(n % mod, mod - 2) % mod);
    }
    return 0;
}