#include <bits/stdc++.h>
typedef long long ll;
const int mod = 10000007;
ll n,f[65][2][65],size[65];
int digit[65];


inline ll qpow(ll x, ll k) {
    ll Ans = 1;
    for (; k; k >>= 1,x = x * x % mod) if (k & 1) Ans = Ans * x % mod;
    return Ans;
}

inline void dp(ll n) {
    int cnt = 0;
    while (n) digit[++cnt] = n & 1,n >>= 1;
    for (int i = 1; i < cnt; i++)
        for (int j = 0; j <= 62; j++)
            size[j] += f[i][1][j];
    ll Num = 1;
    for (int i = cnt - 1; i; i--) {
        for (int j = 0; j < digit[i]; j++) 
            for (int k = 0; k <= 62; k++)
                size[Num+k] += f[i][j][k];
        Num += digit[i];
    }
}

inline void Work() {
    for (int i = 0; i <= 1; i++) f[1][i][i] = 1;
    for (int i = 2; i <= 62; i++)
        for (int j = 0; j <= 1; j++)
            for (int k = 0; k <= 1; k++)
                for (int p = 0; p <= 62 && p + j <= 62; p++)
                    f[i][j][p+j] += f[i-1][k][p];
    dp(n + 1); ll Ans = 1;
    for (int i = 2; i <= 62; i++) Ans = Ans * qpow(i,size[i]) % mod;
    printf("%lld\n",Ans);
}

int main() {
    scanf("%lld",&n);
    Work();
    return 0;
}