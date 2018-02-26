#pragma GCC optimize("O3")
#include <bits/stdc++.h>
typedef long long ll;
std::vector<int> Num;
int fib[25],digit[25],c[25],cnt;
bool vis[25]; ll n,C[25][25],sum[25];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

std::map<std::vector<int>, ll> f[21];

inline ll dfs(int x,int y) {
    if (x == 10) return y?0:1;
    ll Ans = 0;
    for (int i = 1; i <= cnt; i++)
        if (fib[i] >= c[x]) {
            if (fib[i] - c[x] > y) break;
            Ans += dfs(x+1,y-fib[i]+c[x]) * C[y][fib[i] - c[x]];
        }
    return Ans;
}

inline ll Calc(int n) {
    for (int i = 0; i <= 13; i++) Num[i] = 0;
    for (int i = 0; i <= 9; i++) Num[c[i]] ++;
    if (f[n][Num]) return f[n][Num];
    return f[n][Num] = dfs(0,n);
}

inline bool Judge() {
    for (int i = 0; i <= 9; i++)
        if (!vis[c[i]]) return false;
    return true;
}

inline ll __dfs(int x,bool limit) {
    if (!x) return Judge();
    if (!limit) return Calc(x);
    ll Ans = 0; int end = limit?digit[x]:9;
    for (int i = 0; i <= end; i++) {
        c[i] ++;
        Ans += __dfs(x-1,limit & (i == end));
        c[i] --;
    }
    return Ans;
}

inline ll DP(ll x) {
    int QWQ = 0; ll Ans = 0;
    while (x) digit[++QWQ] = x % 10, x /= 10;
    for (int i = 1; i <= digit[QWQ]; i++) c[i] ++ ,Ans += __dfs(QWQ-1,i == digit[QWQ]),c[i] --;
    Ans += sum[QWQ-1];
    return Ans;
}

signed main() {
    Num.resize(14);
    fib[++cnt] = 0; fib[++cnt] = 1; fib[++cnt] = 2; fib[++cnt] = 3; fib[++cnt] = 5; fib[++cnt] = 8; fib[++cnt] = 13;
    for (int i = 1; i <= cnt; i++) vis[fib[i]] = true;
    for (int i = 0; i <= 18; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
    for (int i = 1; i <= 18; i++) {
        sum[i] = sum[i-1] + Calc(i);
        c[0] = 1;
        sum[i] -= Calc(i - 1);
        c[0] = 0;
    }
    int T = 5;
    while (T --) {
        n = read<ll>();
        ll l = 1,r = n << 2,mid,Ans;
        while (l <= r) {
            mid = l + r >> 1;
            if (DP(mid) >= n) Ans = mid,r = mid - 1;
            else l = mid + 1;
        }
        printf("%lld\n",Ans);
    }
    return 0;
}