#include <stdio.h>
#include <iostream>
#define MAXN 100005
#define inf (0x3f3f3f3f)
#define ls (o << 1)
#define rs (o << 1 | 1)
int n,y,z,yn[MAXN],ym[MAXN],zn[MAXN],zm[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int d[4];
    inline int& operator [] (const int & x) {
        return d[x];
    }
}t[MAXN<<2],Ans;

inline void Maintain(int o) {
    t[o][0] = std::max(t[ls][0],t[rs][0]);
    t[o][1] = std::min(t[ls][1],t[rs][1]);
    t[o][2] = std::max(t[ls][2],t[rs][2]);
    t[o][3] = std::min(t[ls][3],t[rs][3]);
}

inline void build(int o,int l,int r) {
    if (l == r) {
        t[o][0] = yn[l];
        t[o][1] = ym[l];
        t[o][2] = zn[l];
        t[o][3] = zm[l];
        return;       
    }
    register int mid = l + r >> 1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    Maintain(o);
}

inline void Query(int o,int l,int r,int x,int y) {
    if (x <= l && r <= y) {
        Ans[0] = std::max(Ans[0],t[o][0]);
        Ans[1] = std::min(Ans[1],t[o][1]);
        Ans[2] = std::max(Ans[2],t[o][2]);
        Ans[3] = std::min(Ans[3],t[o][3]);
        return;
    }
    register int mid = l + r >> 1;
    if (x <= mid) Query(ls,l,mid,x,y);
    if (mid < y) Query(rs,mid+1,r,x,y);
    return;
}

inline int Query(int x,int y) {
    Ans[0] = Ans[2] = -inf;
    Ans[1] = Ans[3] = inf;
    Query(1,1,n,x,y);
    return std::min(Ans[1] - Ans[0],Ans[3] - Ans[2]) + 1;
}

inline bool Judge(int len) {
    for (int i = 1; i <= n - len + 1; i++)
        if (Query(i,i+len-1) >= len) return true;
    return false;
}

int main() {
    n = read<int>(); y = read<int>(); z = read<int>();
    for (int i = 1; i <= n; i++) yn[i] = read<int>(),zn[i] = read<int>(),ym[i] = read<int>(),zm[i] = read<int>();
    int l = 1,r = std::min(n,std::min(y,z)),Ans,mid;
    build(1,1,n);
    while (l <= r) {
        if (Judge(mid = l + r >> 1)) Ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n",Ans);
    getchar(); getchar();
    return 0;
}