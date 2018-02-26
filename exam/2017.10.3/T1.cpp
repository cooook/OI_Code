#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
typedef long long ll;
#define mod 1000000007
#define MAXN 1000005
char s[MAXN]; int n,now; 
ll f[MAXN][5][5],Ans;
 
 
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}
 
inline int id(char c) {
    if (c == '0') return 0;
    if (c == '1') return 1;
    if (c == '2') return 2;
    if (c == '*') return 3;
    return 4;
}
 
int main(){
    scanf("%s",s+1); 
    n = strlen(s + 1);
    now = id(s[1]);
    if (now == 4)
        f[1][0][0] = f[1][1][0] = f[1][3][1] = 1;
    else f[1][now][0] = 1;
    for (int i = 2;i<=n;i++) {
        now = id(s[i]);
        if (now == 0 || now == 4) {
            (f[i][0][1] += f[i-1][1][3]) %= mod;
            (f[i][0][0] += f[i-1][0][1]) %= mod;
            (f[i][0][0] += f[i-1][0][0]) %= mod;
        }
        if (now == 1 || now == 4) {
            (f[i][1][3] += f[i-1][3][1]) %= mod;
            (f[i][1][3] += f[i-1][3][3]) %= mod;
            (f[i][1][3] += f[i-1][3][2]) %= mod;
            (f[i][1][1] += f[i-1][1][3]) %= mod;
            (f[i][1][0] += f[i-1][0][1]) %= mod;
            (f[i][1][0] += f[i-1][0][0]) %= mod;
        }
        if (now == 2 || now == 4) {
            (f[i][2][3] += f[i-1][3][3]) %= mod;
            (f[i][2][3] += f[i-1][3][2]) %= mod;
            (f[i][2][3] += f[i-1][3][1]) %= mod;
        }
        if (now == 3 || now == 4) {
            (f[i][3][1] += f[i-1][1][0]) %= mod;
            (f[i][3][1] += f[i-1][1][1]) %= mod;
            (f[i][3][2] += f[i-1][2][3]) %= mod;
            (f[i][3][3] += f[i-1][3][3]) %= mod;
            (f[i][3][3] += f[i-1][3][2]) %= mod;
            (f[i][3][3] += f[i-1][3][1]) %= mod;
        }
    }
    Ans = (((f[n][1][3] + f[n][0][0])%mod + f[n][0][1]) % mod + f[n][3][1]) % mod + f[n][3][2] + f[n][3][3];
    Ans %= mod;
    printf("%lld\n",Ans);
    // getchar(); getchar();
    return 0;
}