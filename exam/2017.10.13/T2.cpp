#include <stdio.h>
#include <iostream>
#include <algorithm>
#define MAXN 100005
#define int long long 
int a[MAXN],Hash[MAXN],n,Q,cnt,c[MAXN],L[MAXN],R[MAXN],Ans[MAXN],sum[MAXN];
int que[MAXN],l,r;
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline void read_char(char &x) {
    x = getchar();
    while (x != '>' && x != '<' && x != '=') x = getchar();
}
 
signed main() {
    // freopen(".in","r",stdin);
    // freopen("my.out","w",stdout);
    n = read<int>(); Q = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>(),Hash[i] = a[i];
    std::sort(&Hash[1],&Hash[n+1]);
    cnt = std::unique(&Hash[1],&Hash[n+1]) - Hash - 1;
    l = 1,r = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= r && a[que[r]] < a[i]) R[que[r]] = i - 1, r --;
        que[++r] = i;
    }
    for (int i = l; i <= r; i++) R[que[i]] = n;
    l = 1,r = 0;
    for (int i = n; i; i--) {
        while (l <= r && a[que[r]] <= a[i]) L[que[r]] = i + 1, r --;
        que[++r] = i;
    }
    for (int i = l; i <= r; i++) L[que[i]] = 1;
    for (int i = 1; i <= n; i++) {        
        int tmp = std::lower_bound(&Hash[1],&Hash[cnt+1],a[i]) - Hash;
        Ans[tmp] += (i - L[i] + 1) * (R[i] - i + 1);
    }
    for (int i = 1; i <= cnt; i++) sum[i] = sum[i-1] + Ans[i];
    while (Q --) {
        char op;
        read_char(op);int k = read<int>();
        if (op == '<') {
            if (k > Hash[cnt]) {printf("%lld\n",sum[cnt]);continue;}
            if (k < Hash[1]) {printf("0\n");continue;}
            int p = std::lower_bound(&Hash[1],&Hash[cnt+1],k) - Hash - 1;
            printf("%lld\n",sum[p]);
        }
        if (op == '=') {
            int p = std::lower_bound(&Hash[1],&Hash[cnt+1],k) - Hash;
            if (Hash[p] == k) printf("%lld\n",Ans[p]);
            else printf("0\n");
        }
        if (op == '>') {
            if (k > Hash[cnt]) {
                printf("0\n");
                continue;
            }
            if (k < Hash[1]) {
                printf("%lld\n",sum[cnt]);
                continue;
            }
            int p = std::upper_bound(&Hash[1],&Hash[cnt+1],k) - Hash - 1;
            printf("%lld\n",sum[cnt] - sum[p]);
        }
    }
    // getchar(); getchar();
    return 0;
}