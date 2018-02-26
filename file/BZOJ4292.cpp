#include <bits/stdc++.h>
#define int long long
int k,a,b,i,Ans,t,tmp;
signed main(){
    for (scanf("%lld%lld%lld",&k,&a,&b),i = 1; i <= b / k && i <= 1459; i++){
        if ((t = k * i) < a) continue;
        tmp = 0;
        while (t) tmp += (t % 10) * (t % 10), t /= 10;
        Ans += tmp == i;
    }
    return printf("%lld\n",Ans), 0;
}
