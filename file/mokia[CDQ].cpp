#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 2000005
#define MAXM 210005
int tot,n,Query_time,Ans[10005];


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct operation{
    int pos,val,x,y,op,id;
    inline bool operator < (const operation &a) const{return x == a.x?op<a.op:x<a.x;}
}a[MAXM],tmp[MAXM];

int tree[MAXN];
#define lowbit(x) ((x)&(-x))
inline void Update(int x,int val){for(;x<=n;x+=lowbit(x)) tree[x] += val;}
inline int Query(int x){int Ans = 0;for(;x;x-=lowbit(x)) Ans += tree[x];return Ans;}

inline void CDQ(int l,int r){
    if(l == r) return;
    register int mid = l + r >> 1,num_l = l,num_r = mid + 1;
    for(int i = l;i<=r;i++) {
        if(a[i].id <= mid && !a[i].op) Update(a[i].y,a[i].val);
        if(a[i].id > mid && a[i].op) Ans[a[i].pos] += a[i].val * Query(a[i].y);
    }
    for(int i = l;i<=r;i++) if(a[i].id <= mid && !a[i].op) Update(a[i].y,-a[i].val);
    for(int i = l;i<=r;i++) 
        if(a[i].id <= mid) tmp[num_l++] = a[i]; 
        else tmp[num_r++] = a[i];
    for(int i = l;i<=r;i++) a[i] = tmp[i];
    CDQ(l,mid);CDQ(mid+1,r);
}

int main(){
    // freopen("mokia.in","r",stdin); 
    // freopen("mokia.out","w",stdout);
    read<int>(); n = read<int>();
    while(true) {
        register int op = read<int>();
        if(op == 1) {
            a[++tot].op = 0;
            a[tot].x = read<int>();
            a[tot].y = read<int>();
            a[tot].val = read<int>();
        }
        else if(op == 2) {
            ++ Query_time; int x = read<int>(),y = read<int>(),x1 = read<int>(),y1 = read<int>();
            a[++tot].pos = Query_time; a[tot].x = x-1;a[tot].y = y-1;a[tot].val =  1; a[tot].op = 1;
            a[++tot].pos = Query_time; a[tot].x = x1 ;a[tot].y = y1 ;a[tot].val =  1; a[tot].op = 1;
            a[++tot].pos = Query_time; a[tot].x = x-1;a[tot].y = y1 ;a[tot].val = -1; a[tot].op = 1;
            a[++tot].pos = Query_time; a[tot].x = x1 ;a[tot].y = y-1;a[tot].val = -1; a[tot].op = 1;
        }
        else break;
    }
    for(int i = 1;i<=tot;i++) a[i].id = i;
    std::sort(&a[1],&a[tot+1]); CDQ(1,tot);
    for(int i = 1;i<=Query_time;i++) printf("%d\n",Ans[i]);
    return 0;
}