#include <bits/stdc++.h>
#define fi first
#define se second
typedef std::pair<int,int> pa;
const int MAXN = 100005;
int a[MAXN],b[MAXN],opt[MAXN],Ans[MAXN],n,m,c; char s[15]; 
bool f[MAXN][32]; pa g[MAXN][32];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int bit(int x) {
    int cnt = 0;
    for (; x; x -= (x) & (-x)) ++ cnt;
    return cnt;
}

int main() {
    n = read<int>(); m = read<int>(); c = read<int>();
    for (int i = 1; i < n; i++) {
        scanf("%s",s);
        if (s[0] == 'X') opt[i] = 0;
        else if (s[0] == 'A') opt[i] = 1;
        else if (s[0] == 'O') opt[i] = 2;
    }
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    f[1][a[1]] = true;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++) if (f[i][j]) {
            for (int k = 0; k <= j && k <= a[i+1]; k++) if (j + a[i+1] - k <= m) {
                if (opt[i] == 0) f[i+1][j+a[i+1]-k*2] |= 1,g[i+1][j+a[i+1]-k*2] = (pa){j,k};
                if (opt[i] == 2) f[i+1][j+a[i+1]-k] |= 1,g[i+1][j+a[i+1]-k] = (pa){j,k};
                if (opt[i] == 1) f[i+1][k] |= 1,g[i+1][k] = (pa){j,k};
            }
        } 
    }
    if (!f[n][bit(c)]) return puts("OvO"), 0;
    int Num = bit(c);
    for (int i = n; i > 1; i--) {
        pa p = g[i][Num]; int pre = 0,res = 0,last = p.fi,xj = p.se,now = a[i];
        last -= xj; now -= xj;
        for (int len = 0; len <= m; len++) {
            if (opt[i-1] == 0) {
                if (c & (1 << len)) {
                    if (last) last --,pre |= 1 << len;
                    else if (now) now --, res |= 1 << len;
                }
                else if (xj) xj --,res |= 1 << len,pre |= 1 << len;
            }
            if (opt[i-1] == 2) {
                if (c & (1 << len)) {
                    if (xj) xj --, res |= 1 << len,pre |= 1 << len;
                    else if (last) last --, pre |= 1 << len;
                    else if (now) now --, res |= 1 << len;
                }
            }
            if (opt[i-1] == 1) {
                if (c & (1 << len)) {if (xj) xj --, res |= 1 << len, pre |= 1 << len;}
                else {
                    if (last) last --,pre |= 1 << len;
                    else if(now) now --,res |= 1 << len;
                }
            }
        } 
        Ans[i] = res; Num = p.fi; c = pre;
    }  
    Ans[1] = c;
    for (int i = 1; i <= n; i++) printf("%d ",Ans[i]);
    return 0;
}