#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long 
#define MAXN 1000005
int tot,n,m,Ans,f[MAXN],pos,val[MAXN],tree[MAXN];


template<typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct kuang{
    int a,b;
    inline bool operator < (const kuang &x)const {
        return b < x.b;
    }
    inline int& operator [] (const int x) {
        if (!x) return a;
        return b;
    }
}tmp[MAXN],a[MAXN];

inline void Update(int x,int val) {
    for (; x <= tot; x += (x) & (-x)) tree[x] = std::max(tree[x],val);
}

inline int Query(int x) {
    int Ans = -0x3f3f3f3f;
    for (; x; x -= (x) & (-x)) Ans = std::max(Ans,tree[x]);
    return Ans;
}

signed main() {
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= n; i++) tmp[i][0] = read<int>(),tmp[i][1] = read<int>();
    std::sort(&tmp[1],&tmp[n+1]);
    tot = 1;
    for (int i = 1; i <= n; i++) 
        if (tmp[i][1] != a[tot][1])  a[++tot] = tmp[i];
        else a[tot][0] += tmp[i][0];
    int last = 1;
    memset(f,0xaf,sizeof f); f[1] = 0;
    memset(tree,0xaf,sizeof tree); 
    for (int i = 2; i <= tot; i++) {
        while (a[last][1] + 19 <= a[i][1]) Update(last,f[last]),++last;
        for (int j = i - 1; j >= 1; j--) {
            if (a[i][1] - a[j][1] > 18) break;
            
            if (a[i][1] - a[j][1] == 4) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 7) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 11) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 15) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 14) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 8) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 12) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 16) f[i] = std::max(f[j],f[i]);
            
            if (a[i][1] - a[j][1] == 18) f[i] = std::max(f[j],f[i]);
        }
        f[i] = std::max(f[i],Query(i));
        f[i] += a[i][0];
        Ans = std::max(Ans,f[i]);
    }
    printf("%lld\n",Ans);
    // getchar(); getchar();
    return 0;
}