#include <stdio.h>
const int MAXN = 500005;
int n,m; long long a[MAXN],Sum[MAXN],Ans;
bool vis[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

int main(){
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<long long>();
    for (int i = 62; ~i; i--){
        int cnt = 0;
        for (int j = 1; j <= n; j++){
            Sum[j] = Sum[j-1] ^ (a[j] >> i & 1);
            if (!Sum[j] && !vis[j]) cnt ++;
        }
        if (cnt >= m && !Sum[n]){
            for (int j = 1; j <= n; j++)
                if (Sum[j]) vis[j] = true;
        }
        else Ans |= 1ll << i;
    } printf("%lld\n",Ans);
    return 0;
}
