#include <stdio.h>
#include <iostream>
#include <cstring>
#define ls o << 1
#define rs o << 1 | 1
#define MAXN 100005
int n,Q,val[MAXN],sum[MAXN<<2][8],_sum[8],tag[MAXN<<2];
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
} 
 
inline void build(int o,int l,int r) {
    if (l == r) return sum[o][val[l]] = 1,void();
    register int mid = l + r >> 1;
    build(ls,l,mid); build(rs,mid+1,r);
    if (l == r) return;
    sum[o][1] = sum[ls][1] + sum[rs][1];
    sum[o][2] = sum[ls][2] + sum[rs][2];
    sum[o][3] = sum[ls][3] + sum[rs][3];
    sum[o][4] = sum[ls][4] + sum[rs][4];
    sum[o][5] = sum[ls][5] + sum[rs][5];
    sum[o][6] = sum[ls][6] + sum[rs][6];
    sum[o][7] = sum[ls][7] + sum[rs][7];
}
 
inline void Push_down(int o,int l,int r) {
    if (l == r) return tag[o] = 0,void();
    if (tag[o]) {
        register int mid = l + r >> 1;
        memset(sum[ls],0,sizeof sum[ls]);
        memset(sum[rs],0,sizeof sum[rs]);
        sum[ls][tag[o]] = mid - l + 1;
        sum[rs][tag[o]] = r - mid;
        tag[ls] = tag[o];
        tag[rs] = tag[o];
        tag[o] = 0;
    }
}
 
inline void Update(int o,int l,int r,int x,int y,int val) {
    if (x > y) return;
    if (x <= l && r <= y) {
        memset(sum[o],0,sizeof sum[o]);
        tag[o] = val;
        sum[o][val] = r - l + 1;
        return;
    }
    Push_down(o,l,r);
    register int mid = l + r >> 1;
    if (x <= mid) Update(ls,l,mid,x,y,val);
    if (mid < y) Update(rs,mid+1,r,x,y,val);
    if (l == r) return;
    sum[o][1] = sum[ls][1] + sum[rs][1];
    sum[o][2] = sum[ls][2] + sum[rs][2];
    sum[o][3] = sum[ls][3] + sum[rs][3];
    sum[o][4] = sum[ls][4] + sum[rs][4];
    sum[o][5] = sum[ls][5] + sum[rs][5];
    sum[o][6] = sum[ls][6] + sum[rs][6];
    sum[o][7] = sum[ls][7] + sum[rs][7];
}
 
inline void Query(int o,int l,int r,int x,int y) {
    if (x > y) return;
    if (x <= l && r <= y) {
        _sum[1] += sum[o][1];
        _sum[2] += sum[o][2];
        _sum[3] += sum[o][3];
        _sum[4] += sum[o][4];
        _sum[5] += sum[o][5];
        _sum[6] += sum[o][6];
        _sum[7] += sum[o][7];
        return;
    }
    Push_down(o,l,r);
    register int mid = l + r >> 1;
    if (x <= mid) Query(ls,l,mid,x,y);
    if (mid < y) Query(rs,mid+1,r,x,y);
}
 
inline void Mark_down(int o,int l,int r) {
    if (l == r)  for (int i = 1; i <= 7; i++) if (sum[o][i]) return printf("%d ",i),void();
    register int mid = l + r >> 1;
    Push_down(o,l,r);
    Mark_down(ls,l,mid); Mark_down(rs,mid+1,r);
}
 
int main() {
    n = read<int>(); Q = read<int>();
    for (int i = 1 ; i <= n; i++) val[i] = read<int>();
    build(1,1,n);
    while (Q --) {
        register int l = read<int>(),r = read<int>(),op = read<int>();
        memset(_sum,0,sizeof _sum);
        Query(1,1,n,l,r);
        if (!op) {
            int last = l;
            for (int i = 1; i <= 7; i++) Update(1,1,n,last,last + _sum[i] - 1,i),last += _sum[i];
        }
        else {
            int last = r;
            for (int i = 1; i <= 7; i++) Update(1,1,n,last-_sum[i]+1,last,i),last -= _sum[i];
        }
    }
    Mark_down(1,1,n);
    // while (true);
    return 0;
}