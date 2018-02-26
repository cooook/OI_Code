#include <stdio.h>
#include <iostream>
#include <math.h>
typedef long long ll;
 
const ll inf = 0x3f3f3f3f3f3f3f3fll;
ll n;int d,a,b;
 
 
template<typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline bool Judge(ll mid) {
    register ll Ans = 0;
    Ans += (mid - a - 1) / d + 1;
    Ans += (mid - b - 1) / d + 1;
    return Ans <= n;
}
 
int main() {
    n = read<ll>() - 1; d = read<int>(); a = read<int>(); b = read<int>();
    ll l = std::max(b,a),r = inf,mid,Ans = std::max(a,b);
    while (l <= r) {
        mid = l + r >> 1;
        if (Judge(mid)) Ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    printf("%lld\n",Ans);
    // getchar(); getchar();
    return 0;
}