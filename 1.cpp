# include <bits/stdc++.h>
typedef unsigned long long ull; 
const int P = 23;
const int mod1 = 1e9 + 9; 
const int mod2 = 1e9 + 7;
const int MAXN = 200005; 
ull L1[MAXN], L2[MAXN], xp[MAXN]; 
char s1[MAXN], s2[MAXN]; 
int len1, len2; 



ull Get_Hash(ull *Hash, int l, int r) {
    return Hash[r] - Hash[l - 1] * xp[r - l + 1]; 
}

long long mul(long long a, long long b, long long mod) {
    long long Ans = 0;
    for (; b; b >>= 1, a += a)
        if (b & 1)
            Ans += a;
    return Ans; 
}

long long ex(long long a, long long b, long long mod) {
    long long Ans = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            (Ans *= a) %= mod;
    return Ans; 
}

int main() {
    // freopen("1.in", "r", stdin); 
    scanf("%s%s", s1 + 1, s2 + 1);
    len1 = strlen(s1 + 1);
    len2 = strlen(s2 + 1); 
    xp[0] = 1; 
    for (int i = 1; i <= len1 || i <= len2; ++i) xp[i] = xp[i - 1] * P;
    for (int i = 1; s1[i]; ++i)
        L1[i] = L1[i - 1] * P + s1[i] - 'a';
    for (int i = 1; s2[i]; ++i)
        L2[i] = L2[i - 1] * P + s2[i] - 'a';
    int l1, l2, r1, r2;
    while (true) {
        std::cin >> l1 >> r1 >> l2 >> r2;
        // std :: cin >> l1 >> r1;
        // std :: cout << mul(l1, r1, mod1) << std::endl; 
        if (Get_Hash(L1, l1, r1) == Get_Hash(L2, l2, r2))
            puts("True");
        else puts("False");
    }
    // while (true); 
    return 0; 
}