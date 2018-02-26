#include <iostream>
#include <stdio.h>
#define Min(x,y) ((x)<(y)?(x):(y))
typedef long long ll;
int T,n,digit[20]; ll f[18][10][4][2];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Pre_Work() {
    for (int i = 0; i <= 9; i++) f[1][i][1][0] = 1;
    for (int i = 2; i <= 18; i++) 
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                for (int flag = 0; flag != 2; flag ++) {
                    if (j != k) {
                        for (int len = 1; len <= 3; len ++) 
                            f[i][j][1][flag] += f[i-1][k][len][flag];
                    }
                    else {
                        for (int len = 1; len <= 3; len ++) {
                            int Len = Min(len + 1,3);
                            f[i][j][Len][flag|(Len==3&&j==6)] += f[i-1][k][len][flag];
                        }
                    }
                }
}

inline ll DP(ll x) {
    ll Ans = 0; int cnt = 0;
    while (x) digit[++cnt] = x % 10,x /= 10;
    for (int i = 1; i < cnt; i++) 
        for (int j = 1; j <= 9; j++) 
            for (int len = 1; len <= 3; len++) 
                Ans += f[i][j][len][1];
    for (int i = 1; i < digit[cnt]; i++)
        for (int len = 1; len <= 3; len++)
            Ans += f[cnt][i][len][1];
    int last = digit[cnt],suffix_len = 1; bool flag = false;
    for (int i = cnt - 1; i; i--) {
        for (int j = 0; j < digit[i]; j++) 
            for (int len = 1; len <= 3; len++) {
                Ans += f[i][j][len][1];
                if (flag) Ans += f[i][j][len][0];
                else {
                    if (j == last)
                        if (j == 6 && suffix_len + len >= 3) 
                            Ans += f[i][j][len][0];
                }
            }
        last = digit[i];
        if (last == digit[i+1]) suffix_len = Min(3,suffix_len + 1);
        else suffix_len = 1;
        if (last == 6 && suffix_len >= 3) flag = true;
    }
    return Ans;
}

int main() {
    Pre_Work();
    T = read<int>();
    while (T --) {
        n = read<int>();
        ll l = 1,r = 1e18,Ans;
        while (l <= r) {
            register ll mid = l + r >> 1;
            if (DP(mid + 1) >= n) Ans = mid,r = mid - 1;
            else l = mid + 1;
        }
        printf("%lld\n",Ans);
    }
    // getchar(); getchar();
    return 0;
}