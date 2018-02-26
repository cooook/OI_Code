#pragma GCC optimize("O3")
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#define fi first
#define se second
#define mk std::make_pair
#define int long long

typedef long long ll;
typedef std::pair<ll,ll> pa;
typedef std::map<pa,ll> Hash;
std::vector<int> G[30];

int n,prime[35] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101},size[35],Num,cnt;

Hash ma[26];


inline void div(int x) {
    for (int i = 1; prime[i] <= x; i++)
        while (x % prime[i] == 0) size[i]++,x /= prime[i];
}

template <typename _t>
inline _t gcd(_t x,_t y) {
    return !y?x:gcd(y,x%y);
}

inline ll dfs(ll x1,ll x2,int id) {
    if (id == cnt + 1) return (x1 == x2);
    ll Ans = 0; pa p;
    if (x1 > x2) p = mk(x2,x1);
    else p = mk(x1,x2);
    if (id >= 4 && id <= 20)
        if (ma[id].count(p)) return ma[id][p];
    for (register int i = 0; i <= size[id]; i++) {
        register ll X1 = x1 * (i + 1),X2 = x2 * (size[id] - i + 1);
        register ll g = std::__gcd(X1,X2); X1 /= g; X2 /= g;
        register bool flag = true;
        register int Size = G[id].size();
        for (register int j = 0; j < Size; j++) if (X1 % G[id][j] == 0 || X2 % G[id][j] == 0) {flag = false; break;}
        if (!flag) continue;
        Ans += dfs(X1,X2,id+1);
    }
    if (id >= 4 && id <= 20)
    ma[id][p] = Ans;
    return Ans;
}

int C[30][30];

inline void Work() {
    for (int i = 0; i <= 25; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
    scanf("%d",&n);
    if (n == 1) return puts("1"), void();
    for (int i = 2; i <= n; i++) div(i);
    for (int i = 2; i <= 25; i++)
        for (int j = 1; j <= 25; j++)
            if (size[j] + 1 < prime[i]) {
                G[j].push_back(prime[i]);
                break;
            }
    cnt = 25; ll Ans = 0;
    for (; cnt && size[cnt] <= 1; cnt--) Num += (size[cnt] == 1);
    for (int i = 0; i <= Num; i++)
        Ans += dfs(1ll<<i,1ll<<(Num-i),1) * C[Num][i];
    printf("%lld\n",Ans>>1);
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("euler.in","r",stdin);
    freopen("euler.out","w",stdout);
#endif
    Work();
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
