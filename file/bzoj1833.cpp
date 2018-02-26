#include <stdio.h>
typedef long long ll;
ll f[15][15][15],a,b,Ans[15]; int digit[15];


template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline ll pw(int x) {
    ll now = 1;
    for (; x; x--, now *= 10) ;
    return now; 
}

inline void DP(ll x,int type) {
    if (!x) return;
    int cnt = 0; ll now = x;
    while (now) digit[++cnt] = now % 10,now /= 10;
    for (int i = 1; i < cnt; i++) 
        for (int j = 1; j <= 9; j++) 
            for (int k = 0; k <= 9; k++)
                Ans[k] += f[i][j][k] * type;
    for (int i = 1; i < digit[cnt]; i++) 
        for (int j = 0; j <= 9; j++) 
            Ans[j] += f[cnt][i][j] * type;
    for (int i = cnt - 1; i; i--) {
        for (int j = 0; j < digit[i]; j++) 
            for (int k = 0; k <= 9; k++)
                Ans[k] += f[i][j][k] * type;
        x %= pw(i);
        Ans[digit[i+1]] += x * type;
    }
}

int main() {
    for (int i = 0; i <= 9; i++) f[1][i][i] = 1;
    ll now = 10;
    for (int i = 2; i <= 13; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int p = 0; p <= 9; p++)
                for (int k = 0; k <= 9; k++) 
                    f[i][j][p] += f[i-1][k][p];
            f[i][j][j] += now;
        }
        now *= 10;
    }
    scanf("%lld%lld",&a,&b);
    DP(b+1,1);   DP(a,-1);
    printf("%lld",Ans[0]);
    for (int i = 1; i <= 9; i++) printf(" %lld",Ans[i]);
    return 0;
}