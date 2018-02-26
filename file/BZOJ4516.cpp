# include <stdio.h>
# include <cstring>
# include <map>
#define int long long 
typedef long long ll;
const int MAXN = 200005;
int n, last, fa[MAXN], Mx[MAXN], cnt; ll Ans; char s[MAXN];
std::map<int,int> trans[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int expend(int p, int c) {
    int np = ++ cnt; Mx[np] = Mx[p] + 1;
    for (; p && !trans[p].count(c); p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1, Ans += Mx[np];
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q, Ans += Mx[np] - Mx[q];
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1; 
            Ans -= Mx[q] - Mx[fa[q]];
            fa[nq] = fa[q];
            trans[nq] = trans[q];
            fa[np] = fa[q] = nq;
            Ans += Mx[nq] - Mx[fa[nq]] + Mx[q] - Mx[fa[q]] + Mx[np] - Mx[fa[np]];
            for (; p && trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    }
    return np;
}

signed main() {
    n = read();
    last = ++ cnt;
    for (int i = 1; i <= n; i++) 
        last = expend(last, read()), printf("%lld\n", Ans);
    return 0;
}