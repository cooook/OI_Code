#pragma GCC optimize("O3")
#include <stdio.h>
#include <algorithm>
typedef long long ll;
const int MAXN = 205;
ll n,m,f,Ans,cnt;


template<typename _t>
inline _t read(){
    _t x = 0,f = 1;
    char ch = getchar();
    for (;ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (;ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Food{
    ll p,s;
    inline bool operator < (const Food & a)const{
        return p < a.p;
    }
}use[MAXN],tmp[MAXN];

inline ll Calc(ll x){
    ll left = m - f * x,d = 0,QWQ,Ans = 0;
    if (left < 0) return 0;
    for (int i = 1; i <= n; i++) {
        if (d <= use[i].s) {
            QWQ = std::min(use[i].s - d + 1,left / (use[i].p * x));
            Ans += QWQ * x;
            left -= QWQ * x * use[i].p;
            d += QWQ;
        }
        if (d <= use[i].s) {
            QWQ = std::min(x,left / use[i].p);
            Ans += QWQ;
            left -= QWQ * use[i].p;
            d ++;
        }
    }
    return Ans;
}

int main(){
    while(scanf("%lld%lld%lld", &m, &f, &n) == 3) {
        cnt = 0; Ans = 0;
        for (int i = 1; i <= n; i++) tmp[i].p = read<ll>(),tmp[i].s = read<ll>();
        if (m < f) {
            printf("0\n");
            return 0;
        }
        std::sort(&tmp[1],&tmp[n+1]);
        use[++cnt] = tmp[1];
        for (int i = 1;i<=n;i++) 
            if (tmp[i].s > use[cnt].s)
                use[++cnt] = tmp[i];
        n = cnt;
        ll l = 1,r = m / (f + use[1].p);
        while (l + 5 <= r) {
            register ll mid1 = (l + l + r) / 3,mid2 = (l + r + r) / 3,Ans1 = Calc(mid1),Ans2 = Calc(mid2);
            if (Ans1 > Ans2) r = mid2; 
            else l = mid1;
        }
        for (ll i = l; i <= r; i++) Ans = std::max(Ans,Calc(i));
        printf("%lld\n",Ans);
    }
    return 0;
}