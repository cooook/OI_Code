#include <bits/stdc++.h>
int n,m,T;
int main() {
    for (scanf("%d",&T); T; T--) {
        scanf("%d%d",&n,&m);
        if (m == 1 || m == 10 || m == 100 || m == 1000) {
            if (n == m << 1) puts("1");
            else puts("2");
        }else puts("1");
    }
    return 0;
}