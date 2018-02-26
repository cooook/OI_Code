#include <bits/stdc++.h>
typedef long long ll;
ll L,R,f[65][9*20*20]; int k,digit[65];


inline ll __dfs(int pos,int m,bool limit) { // 这里m的含义为最后的代价为m
    if (pos == 0) return m;
    if (!limit && f[pos][m] != -1) return f[pos][m];
    int n = limit?digit[pos]:k-1; ll Ans = 0;
    for (int i = 0; i <= n; i++) Ans += __dfs(pos - 1,m + i*(pos-1),limit && i == n);
    if (!limit) f[pos][m] = Ans;
    return Ans;
}

inline ll dfs(int pos,int s,int m,bool limit) { // 注意此处的s的含义为能比原来优多少
    if (s < 0) return 0;
    if (pos == 0) return s;
    if (!limit && f[pos][s] != -1) return f[pos][s];
    int n = limit?digit[pos]:k-1; ll Ans = 0;
    for (int i = 0; i <= n; i++) {
        if (pos >= m) Ans += dfs(pos-1,s+i,m,limit && i == n);
        else Ans += dfs(pos-1,s-i,m,limit && i == n);
    }
    if (!limit) f[pos][s] = Ans;
    return Ans;
}

inline ll Calc(ll x) {
    int cnt = 0;
    while (x) digit[++cnt] = x % k, x /= k;
    memset(f,-1,sizeof f);
    ll Ans = __dfs(cnt,0,true);
    for (int i = 2; i <= cnt; i++) memset(f,-1,sizeof f),Ans -= dfs(cnt,0,i,true);
    return Ans;
}

int main() {
    scanf("%lld%lld%d",&L,&R,&k);
    return printf("%lld\n",Calc(R) - Calc(L-1)), 0;
}