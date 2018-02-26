#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define Min(x,y) ((x)<(y)?(x):(y))
#define MAXN 500005
#define inf 0x3f3f3f3f3f3f3f3fll
#define ls o << 1
#define rs o << 1 | 1
typedef long long ll;
int n,k,a[MAXN],b[MAXN];
ll sum[MAXN],f[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}


struct Seg_ment_Tree{
    ll mn[MAXN<<2],tag[MAXN<<2];

    inline void build(int o,int l,int r) {
        mn[o] = inf; tag[o] = inf;
        if (l == r) return;
        register int mid = l + r >> 1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    inline void Change(int o,ll val) {
        if (tag[o] > val) tag[o] = val;
        if (mn[o] > val) mn[o] = val;
    }

    inline void Update(int o,int l,int r,int x,int y,ll val) {
        if (x > y) return;
        if (x <= l && r <= y) return Change(o,val),void();
        register int mid = l + r >> 1;
        if (tag[o] != inf) {
            Change(ls,tag[o]);
            Change(rs,tag[o]);
            tag[o] = inf;
        }
        if (x <= mid) Update(ls,l,mid,x,y,val);
        if (mid < y) Update(rs,mid+1,r,x,y,val);
        if (mn[ls] < mn[rs]) mn[o] = mn[ls];
        else mn[o] = mn[rs];
    }

    inline ll Query(int o,int l,int r,int x) {
        if (l == r) return mn[o];
        register int mid = l + r >> 1;
        if (tag[o] != inf) {
            Change(ls,tag[o]);
            Change(rs,tag[o]);
            tag[o] = inf;
        }
        if (x <= mid) return Query(ls,l,mid,x);
        else return Query(rs,mid+1,r,x);
    }
}T[2];

inline int find(int l,int r,ll val) {
    int mid,Ans;
    while (l <= r) {
        mid = l + r >> 1;
        if (sum[mid] <= val) Ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    return Ans;
}

int main() {
    n = read<int>(); k = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>(),sum[i] = sum[i-1] + a[i];
    for (int i = 0; i < n; i++) b[i] = read<int>();
    f[0] = 0; T[0].build(1,1,n); T[1].build(1,1,n);

    for (int i = 0; i < n; i++) {
        if (i) f[i] = Min(sum[i] + T[0].Query(1,1,n,i),T[1].Query(1,1,n,i));
        register int pos = find(i,Min(i+k,n),sum[i] + b[i]);
        T[1].Update(1,1,n,i + 1,pos,f[i] + b[i]);
        T[0].Update(1,1,n,pos+1,Min(i+k,n),f[i] - sum[i]);
    }
    ll Ans = 0x3f3f3f3f3f3f3f3fll;
    Ans = Min(sum[n] + T[0].Query(1,1,n,n),T[1].Query(1,1,n,n));
    printf("%lld\n",Ans);
    return 0;
}
