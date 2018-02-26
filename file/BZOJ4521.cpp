#include <stdio.h>
#define Min(x,y) ((x)<(y)?(x):(y))
typedef long long ll;
ll f[15][12][4][2][2][2],L,R; int digit[15];


inline void DP() {
    for (int i = 0; i <= 9; i ++) f[1][i][1][i == 4][i == 8][0] = 1;
    for (int i = 2; i <= 12; i ++)
	for (int j = 0; j <= 9; j ++)
    for (int k = 0; k <= 9; k ++)
    for (int flag_4 = 0; flag_4 != 2; flag_4 ++)
    for (int flag_8 = 0; flag_8 != 2; flag_8 ++)
    for (int flag = 0; flag != 2; flag ++) {    
    	if (j != k) {
    		for (int len = 1; len <= 3; len ++) 
    			f[i][j][1][flag_4|j==4][flag_8|j==8][flag] += f[i-1][k][len][flag_4][flag_8][flag];
		}
		else {
			for (int len = 1; len <= 3; len ++) {
				int Len = Min(len + 1,3);
				f[i][j][Len][flag_4|j==4][flag_8|j==8][flag|Len==3] += f[i-1][k][len][flag_4][flag_8][flag];
			}
		}
	}
}

inline ll Calc(ll x) {
    int cnt = 0; ll Ans = 0;
    while (x) digit[++cnt] = x % 10, x /= 10;
    for (int i = 1; i < cnt; i++) 
        for (int j = 1; j <= 9; j++) 
            for (int k = 1; k <= 3; k++)
                Ans += f[i][j][k][1][0][1],Ans += f[i][j][k][0][1][1],Ans += f[i][j][k][0][0][1];
    for (int i = 1; i < digit[cnt]; i++)
        for (int j = 1; j <= 3; j++)
            Ans += f[cnt][i][j][0][1][1],Ans += f[cnt][i][j][1][0][1],Ans += f[cnt][i][j][0][0][1];
    bool flag_4 = digit[cnt] == 4,flag_8 = digit[cnt] == 8,flag_3 = false;
    int suffix_len = 1,last = digit[cnt];
    for (int i = cnt - 1; i; i--) {
        for (int j = 0; j < digit[i]; j++)
            for (int k = 1; k <= 3; k++){
                Ans += f[i][j][k][0][0][1];
                if (!flag_4) Ans += f[i][j][k][0][1][1];
                if (!flag_8) Ans += f[i][j][k][1][0][1];
                if (flag_3 || (j == last && suffix_len + k >= 3)) {
                	Ans += f[i][j][k][0][0][0];
                	if (!flag_4) Ans += f[i][j][k][0][1][0];
                	if (!flag_8) Ans += f[i][j][k][1][0][0];
				}
            }
        if (last == digit[i]) suffix_len += suffix_len == 3?0:1;
        else suffix_len = 1;
        if (suffix_len == 3) flag_3 = true;
        last = digit[i]; 
        flag_4 |= (last == 4);
        flag_8 |= (last == 8);
        if (flag_4 && flag_8) break;
    }
    return Ans;
} 

int main() {
    DP();
    scanf("%lld%lld",&L,&R);
    printf("%lld\n",Calc(R + 1) - Calc(L));
    return 0;
}
