#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ls o << 1
#define rs o << 1 | 1
const int MAXN = 200005,inf = 0x3f3f3f3f;
int f[MAXN],n,h[MAXN],c[MAXN],mx[MAXN<<2],val[MAXN<<2],mn[MAXN<<2],id[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^48);
    return x * f;
}

inline int Calc(int o,int l,int r,int x) {
    // 当前的Update是更新对后面答案的影响
    // 如果当前的值大于这段区间的最大值则这一段区间的贡献为inf
    // 因为对后面的答案造成影响的条件是大于当前的高度
    // 解释不清了QAQ...
    if (mx[o] < x) return inf;
    if (l == r) return mn[o];
    register int mid = l + r >> 1;
    if (x <= mx[rs]) return std::min(val[o],Calc(rs,mid+1,r,x));
    return Calc(ls,l,mid,x);
}

inline void Update(int o,int l,int r,int x,int H,int V) {
    if (l == r) return mx[o] = H,mn[o] = V,void();
    register int mid = l + r >> 1;
    if (x <= mid) Update(ls,l,mid,x,H,V);
    else Update(rs,mid+1,r,x,H,V);
    mx[o] = std::max(mx[ls],mx[rs]);
    mn[o] = std::min(mn[rs],val[o] = Calc(ls,l,mid,mx[rs]));
}

inline void Query(int o,int l,int r,int x,int y,int &Ans,int &Max) {
    if (x <= l && r <= y) return Ans = std::min(Ans,Calc(o,l,r,Max)),Max = std::max(Max,mx[o]),void(); // 每段区间更新Ans值
    register int mid = l + r >> 1;
    if (mid < y) Query(rs,mid+1,r,x,y,Ans,Max); // 应该先查询右儿子，根据右儿子的max来查询左儿子
    if (x <= mid) Query(ls,l,mid,x,y,Ans,Max);
}

inline void build(int o,int l,int r) {
    mx[o] = -inf; mn[o] = inf; // 初始化线段树
    if (l == r) return;
    register int mid = l + r >> 1;
    build(ls,l,mid); build(rs,mid+1,r);
}

bool cmp_h(const int &x,const int &y) {
    return h[x] < h[y];
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) h[i] = read<int>(),id[i] = i;
    for (int i = 1; i <= n; i++) c[i] = read<int>();
    std::sort(&id[1],&id[n+1],cmp_h);
    build(1,1,n);
    for (int i = 1; i <= n; i++) {
        int Ans = inf,Max = 0;
        Query(1,1,n,1,id[i],Ans,Max);
        if (Ans == inf) Ans = 0;
        f[id[i]] = Ans + c[id[i]];
        Update(1,1,n,id[i],i,f[id[i]]);
    }
    int Ans = inf,last = 0;
    for (int i = n; i; i--) {
        if (last > h[i]) continue;
        last = h[i],Ans = std::min(Ans,f[i]);
    }
    printf("%d\n",Ans);
    return 0;
}
