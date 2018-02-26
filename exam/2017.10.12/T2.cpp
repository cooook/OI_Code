#include <bits/stdc++.h>
#define ls o << 1
#define rs o << 1 | 1
#define MAXN 105000
#define inf 0x7fffffff
int n,m,x,Ans,w[MAXN],mn[MAXN<<2],tag[MAXN<<2],sum[MAXN<<2];
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
inline void Push_down(int o,int l,int r) {
    if (tag[o]) {
        if (sum[ls]) tag[ls] += tag[o],mn[ls] += tag[o];
        if (sum[rs]) tag[rs] += tag[o],mn[rs] += tag[o];
        tag[o] = 0;
    }
}
 
inline void Maintain(int o,int l,int r) {
    sum[o] = sum[ls] + sum[rs];
    mn[o] = std::min(mn[ls],mn[rs]);
}
 
inline void build(int o,int l,int r) {
    if (l == r) return sum[o] = 1,mn[o] = w[l] - l + 1,void();
    register int mid = l + r >> 1;
    build(ls,l,mid); build(rs,mid + 1,r);
    Maintain(o,l,r);
}
 
inline void Update(int o,int l,int r,int x,int y,int val) {
    if (x > y || sum[o] == 0) return;
    if (x <= l && r <= y) return tag[o] += val,mn[o] += val,void();
    Push_down(o,l,r);
    register int mid = l + r >> 1;
    if (x <= mid) Update(ls,l,mid,x,y,val);
    if (mid < y) Update(rs,mid+1,r,x,y,val);
    Maintain(o,l,r);
}
 
inline void erase(int o,int l,int r,int x) {
    if (l == r) return sum[o] = 0, mn[o] = inf, void();
    register int mid = l + r >> 1;
    Push_down(o,l,r);
    if (x <= mid) erase(ls,l,mid,x);
    else erase(rs,mid+1,r,x);
    Maintain(o,l,r);
}
 
inline int find(int o,int l,int r,int x) {
    if (l == r) return l;
    register int mid = l + r >> 1;
    Push_down(o,l,r);
    if (mn[ls] <= x) return find(ls,l,mid,x);
    else return find(rs,mid+1,r,x);
}
 
int main() {
    n = read<int>(); m = read<int>(); x = read<int>();
    for (int i = 1; i <= n; i++) w[i] = read<int>();
    for (int i = 1,a; i <= n; i++) a = read<int>(),w[i] = (x - w[i]) / a + 1;
    build(1,1,n); int Mn,now;
    for (int i = 1; i <= m; i++) {
        Mn = mn[1];
        while (Mn <= Ans) {
            now = find(1,1,n,Mn);
            erase(1,1,n,now);
            Update(1,1,n,now+1,n,1);
            Mn = mn[1];
        }
        Ans += sum[1];
    }
    return printf("%d\n",Ans), 0;
}