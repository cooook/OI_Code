#include <bits/stdc++.h>
typedef long long ll;
ll n, m, k, s;
ll qpow(ll x, ll k)
{
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % s)
        if (k & 1)
            Ans = Ans * x % s;
    return Ans;
}
int main()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    s = n + m;
    n = n * qpow(2, k) % s;
    printf("%lld", std::min(n, s - n));
}