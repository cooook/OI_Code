#include <bits/stdc++.h>
#define int long long 
int T,n,N,Num_R; char s[2000005];


template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int Calc() {
    int Ans = 0,L_Sum_R = 0,R_Sum_R = 0,L_Sum_B = 0,R_Sum_B = 0,mid = 0,now = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'B') now += L_Sum_R,L_Sum_B ++;
        else  ++ L_Sum_R;
        if (L_Sum_R << 1 > Num_R) {mid = i; break;}
    }
    for (int i = n; i > mid; i--)
        if (s[i] == 'B') now += R_Sum_R,R_Sum_B ++;
        else ++ R_Sum_R;
    Ans = now;
    for (int i = n + 1; i <= N; i++)
        if (s[i] == 'B') L_Sum_B --,R_Sum_B ++;
        else {
            L_Sum_R --; R_Sum_R ++;
            now += R_Sum_B - L_Sum_B; 
            while (L_Sum_R << 1 <= Num_R) {
                if (s[mid + 1] == 'B')  now += L_Sum_R - R_Sum_R,++L_Sum_B,--R_Sum_B;
                else ++ L_Sum_R, -- R_Sum_R;  ++ mid;
            }
            Ans = std::min(Ans,now);
        }
    return Ans;
}

signed main() {
    T = read<int>();
    while (T --) {
        Num_R = 0;
        scanf("%s",s+1); n = strlen(s + 1); N = n << 1;
        for (int i = n + 1; i <= N; i++) s[i] = s[i-n],Num_R += s[i-n] == 'R';
        printf("%lld\n",Calc());
    }
    return 0;
}