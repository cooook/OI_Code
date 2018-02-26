#include <stdio.h>
#include <iostream>
#include <cstring>
 
#define MAXN 1000005
 
char s[MAXN]; int a[MAXN],n,num,Ans,cnt;
 
 
template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
int id(char s){
    if (s == 'B') return 0;
    else return 1;
}
 
int main(){
    freopen("line.in","r",stdin);
    freopen("line.out","w",stdout);
    scanf("%s",s + 1);
    n = strlen(s + 1);
    for (int i = n; i; i--) {
        a[i] = id(s[i]);
        if (a[i]) cnt?cnt --:0;
        else {
            num ++;
            if (n - num + 1 == i) continue; 
            Ans = std::max(n - num + 1 - i + cnt,Ans);
            cnt ++;
        }
    }
    printf("%d\n",Ans);
    return 0;
}
