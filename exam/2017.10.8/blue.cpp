#pragma GCC optimize("O3")
#include <set>
#include <stdio.h>
#include <iostream>
std::set<int> G;
std::set<int>::iterator it;
int T,n,m,a,D,L,Ans,now;


inline void read(int& x){
    x = 0; register char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) ;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
}

int main() {
    read(T);
    while (T --) {
        G.clear(); G.insert(0);
        read(n); read(m); read(D); read(L);
        for (register int i = 1; i <= n; i++) read(a),G.insert(a); Ans = 0;
        for (; Ans < m; Ans ++) {
            now = 0;
            while (now + D < L) {
                it = G.upper_bound(now + D); -- it;
                if (*it == now) break;
                if (now != 0) G.erase(now);
                now = *it;
            }
            if (now + D < L) break;
            if (now != 0) G.erase(now);
        }
        if (Ans == m) puts("Excited");
        else printf("%d\n", Ans);
    }
    return 0;
}