#include <stdio.h>
#include <iostream>
#include <cstring>
#define MAXN 305
int T,n,m;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
char s[MAXN][MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int Calc(int x,int y) {
    int Ans = 0;
    for (int i = 0; i < 4; i++) {
        int to_x = x + dx[i],to_y = y + dy[i];
        if (to_x < 1 || to_x > n || to_y < 1 || to_y > m) continue;
        if (s[to_x][to_y] == '#') Ans ++;
    }
    return Ans;
}

int main() {
    T = read<int>();
    while (T --) {
        n = read<int>(); m = read<int>();
        for (int i = 1; i <= n; i++) scanf("%s",s[i] + 1);
        int Ans = 0x3f3f3f3f,Num = 0;
        for (int i = 1; i <= n; i++)    
            for (int j = 1; j <= m; j++)
                if (s[i][j] == '#') Num ++,Ans = std::min(Ans,Calc(i,j)); 
        printf("%d\n",Num<=2?-1:Ans);
    }
    return 0;
}