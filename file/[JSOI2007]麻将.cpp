#include <stdio.h>
#include <cstring>
#include <algorithm>
#define MAXN 3005
int n,m,a[MAXN],Ans[MAXN],top,num[405],b[405],c[405];
bool vis[405];


template<typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline bool Judge() {
    memcpy(c,b,sizeof b);
    for (int i = 1; i <= n; i++) {
        c[i] %= 3;
        if (c[i] && c[i+1] && c[i+2]) {
            int tmp = std::min(c[i],std::min(c[i+1],c[i+2]));
            c[i] -= tmp; c[i+1] -= tmp; c[i+2] -= tmp;
        }
        if (c[i] != 0) return false;
    }
    return true;
}

inline void Work(int same) {
    memcpy(b,num,sizeof num);
    if (b[same] == 0) return;
    if (b[same] == 1) {
        if (vis[same]) return;
        b[same] = 0;
        if (Judge()) Ans[++top] = same,vis[same] = true;
    }
    else {
        b[same] -= 2;
        for (int i = 1; i <= n; i++) if (!vis[i]){
            b[i] ++;
            if (Judge()) Ans[++top] = i,vis[i] = true;
            b[i] --;
        }
    }
}

int main() {
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= 3 * m + 1; i++) a[i] = read<int>(),++num[a[i]];
    for (int i = 1; i <= n; i++) Work(i);
    if (!top) puts("NO");
    else {
        std::sort(&Ans[1],&Ans[top + 1]);
        printf("%d",Ans[1]);
        for (int i = 2; i <= top; i++) printf(" %d",Ans[i]); 
    }
    return 0;
}