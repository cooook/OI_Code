#include <set>
#include <stdio.h>
#define fi first
#define se second
#define mk std::make_pair
#define ls (o << 1)
#define rs (o << 1 | 1)
typedef std::pair<int,int> pa;
typedef std::set<pa>::iterator D;
const int MAXN = 2005;
std::set<pa> s; D it;
int n,a[MAXN],w[MAXN],cnt,Q,mx[MAXN<<2];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int Max(int x,int y) {
    return x > y?x:y;
}

inline void Upd(int x) {
    pa p = mk(a[x],x);
    s.insert(p);
    if (p < *it) cnt --;
    else cnt++;
}

void build(int o,int l,int r) {
    if (l == r) return mx[o] = w[l],void();
    register int mid = l + r >> 1;
    build(ls,l,mid); build(rs,mid+1,r);
    mx[o] = Max(mx[ls],mx[rs]);
}

int Query(int o,int l,int r,int x,int y) {
    if (x <= l && r <= y) return mx[o];
    register int mid = l + r >> 1,Ans = 0;
    if (x <= mid) Ans = Max(Ans,Query(ls,l,mid,x,y));
    if (mid < y) Ans = Max(Ans,Query(rs,mid+1,r,x,y));
    return Ans;
}

int main() {
    // freopen("beautiful.in","r",stdin);
    // freopen("beautiful.out","w",stdout);
    n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>(),w[i] = 1;
    for (int i = 1; i <= n; i++) {
        s.clear();
        s.insert(mk(a[i],i));
        it = s.begin();
        for (int j = i + 2; j <= n; j += 2) {
            Upd(j-1); Upd(j);
            if (cnt < 0) it --;
            if (cnt > 0) it ++; cnt = 0;
            w[it -> se] = Max(w[it -> se],j - i + 1);
        }
    }
    build(1,1,n);
    Q = read<int>();
    while (Q--) {
        register int l = read<int>(),r = read<int>();
        printf("%d\n",Query(1,1,n,l,r));
    }
    return 0;
}
