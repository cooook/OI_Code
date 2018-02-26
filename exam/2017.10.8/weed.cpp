#pragma GCC optimize("O3")
#include <stdio.h>

#define MAXN 200005
#define ls o << 1
#define rs o << 1 | 1
int del[MAXN<<2],add[MAXN<<2],sum[MAXN<<2],__sum[MAXN<<2],m,q;
struct Q{int k,w;}a[MAXN];


template<typename _t>
inline _t read(){
    register _t x = 0, f = 1; char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int Query(int o,int l,int r,int val) {
    if (add[o] <= val) return 0;
    if (l == r) return sum[o];
    register int mid = l + r >> 1;
    if (add[rs] >= val) return __sum[o] + Query(rs,mid+1,r,val);
    else return Query(ls,l,mid,val - add[rs] + del[rs]);
}

inline void Maintain(int o,int l,int r) {
    if (l == r) return;
    register int mid = l + r >> 1;
    sum[o] = sum[rs]; add[o] = add[rs]; del[o] = del[ls];
    if (add[ls] < del[rs]) del[o] += del[rs] - add[ls],__sum[o] = 0;
    else sum[o] += (__sum[o] = Query(ls,l,mid,del[rs])),add[o] += add[ls] - del[rs];
}

inline void Update(int o,int l,int r,int x,int k,int w) {
    if (l == r) {
        if (!k) del[o] = w,__sum[o] = 0,add[o] = 0,sum[o] = 0;
        else sum[o] = w,add[o] = 1,__sum[o] = 0,del[o] = 0;
        return;
    }
    register int mid = l + r >> 1;
    if (x <= mid) Update(ls,l,mid,x,k,w);
    else Update(rs,mid+1,r,x,k,w);
    Maintain(o,l,r);
}

inline void build(int o,int l,int r) {
    if (l == r) {
        if (!a[l].k) del[o] = a[l].w,add[o] = 0,sum[o] = 0,__sum[o] = 0;
        else sum[o] = a[l].w,add[o] = 1,del[o] = 0,__sum[o] = 0;
        return;
    }
    register int mid = l + r >> 1;
    build(ls,l,mid); build(rs,mid+1,r);
    Maintain(o,l,r);
}

int main () {
    m = read<int>(); q = read<int>();
    for (int i = 1; i <= m; i++) a[i].k = read<int>() ^ 1,a[i].w = read<int>();
    build(1,1,m);
    for (int i = 1; i <= q; i++) {
        register int c = read<int>(),k = read<int>() ^ 1,w = read<int>();
        Update(1,1,m,c,k,w);
        printf("%d\n",sum[1]);
    }
    return 0;
}