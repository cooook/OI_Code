#include <stdio.h>
#include <iostream>
const int MAXN = 100005;
typedef long long ll;
ll n,k,a[MAXN],Ans,last[MAXN],Last;
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline void Update(int x,int id) {
    if (x < 0) return;
    if (!x) return last[0] = id,void();
    for (int i = 1; i * i <= x; i++)
        if (x % i == 0) {
            last[i] = id;
            if (i *i != x)  last[x/i] = id;
        }
}
 
int main() {
    n = read<int>(); k = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        if (a[i] > k) Last = std::max(std::max(last[a[i]],last[0]),Last);
        Ans += i - Last;
        Update(a[i] - k,i);
    }
    printf("%lld\n",Ans);
    return 0;
}