# include <bits/stdc++.h> 
const int N = 55; 
int n, m, mod, gcd[N][N], Ans, size[N], Inv[N], fac[N], C[N][N]; 


inline int qpow(int x, int k) {
    int Ans = 1;
    for (; k; k >>= 1, x = 1ll * x * x % mod)
        if (k & 1) Ans = 1ll * Ans * x % mod;
    return Ans; 
}

inline void dfs(int left, int last, int id, int res) {
    if (!left) { 
        size[id] = 0; -- id;
        register int tmp = 0, tot = 0;
        for (int i = 1; i <= id; ++i) tmp += size[i] >> 1;
        for (int i = 1; i <= id; ++i)
            for (int j = i + 1; j <= id; ++j)
                tmp += gcd[size[i]][size[j]];
        for (int i = 1; i <= id + 1; ++i) 
            if (size[i] != size[i - 1]) res = 1ll * res * Inv[tot] % mod, tot = 1;
            else ++ tot;
        (Ans += 1ll * res * qpow(m, tmp) % mod) %= mod;
        return; 
    }
    for (int i = last; i <= left; ++i)
        size[id] = i, dfs(left - i, i, id + 1, 1ll * res * fac[i - 1] % mod * C[left][i] % mod);
}

inline int Gcd(int x, int y) {
    return !y ? x : Gcd(y, x % y); 
}

int main() {
    scanf("%d%d%d", &n, &m, &mod); 
    fac[0] = 1; Inv[0] = 1; 
    for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod; 
    Inv[n] = qpow(fac[n], mod - 2); 
    for (int i = n - 1; i; --i)
        Inv[i] = 1ll * Inv[i + 1] * (i + 1) % mod; 
    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod, gcd[i][j] = gcd[j][i] = Gcd(i, j);
    }
    dfs(n, 1, 1, 1);
    printf("%d\n", 1LL * Ans * Inv[n] % mod);
    return 0; 
}