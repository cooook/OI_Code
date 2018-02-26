#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a,b,digit[15]; ll f[15][15];


inline ll DP(int x) {   
    int cnt = 0;ll Ans = 0;
    while (x) digit[++cnt] = x % 10,x /= 10;
    for (int i = 1; i < cnt; i++) for (int j = 1; j <= 9; j++) Ans += f[i][j];
    for (int i = 1; i < digit[cnt]; i++) Ans += f[cnt][i];
    for (int i = cnt - 1; i; i--) {
        for (int j = 0; j < digit[i]; j++)
            if (abs(j - digit[i+1]) >= 2) Ans += f[i][j];
        if (abs(digit[i] - digit[i+1]) < 2) break;
    }
    return Ans;
}

int main() {
    for (int i = 0; i <= 9; i++) f[1][i] = 1;
    for (int i = 2; i <= 11; i++) 
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (abs(k-j) >= 2) f[i][j] += f[i-1][k];
    scanf("%d%d",&a,&b);
    printf("%lld\n",DP(b+1) - DP(a));
    return 0;
}