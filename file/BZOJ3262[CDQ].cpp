#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#define MAXN 100005
int n,m,Ans[MAXN],tot;


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct Operation{
    int cnt,x,y,t,Ans;
    inline bool operator != (const Operation & a)const{
        return x != a.x || y != a.y || t != a.t;
    }
    inline bool operator < (const Operation & a)const{
        if(x == a.x) {
            if(y == a.y) return t < a.t;
            return y < a.y;
        }
        return x < a.x;
    } 
}a[MAXN],tmp[MAXN];
inline bool cmp_y (Operation x,Operation y){ // 一定要讨论　 !!! 
    if(x.y == y.y) { 
		if(x.t == y.t)
			return x.x<y.x;
		return x.t<y.t;
	}
	return x.y<y.y;
}

int tree[MAXN<<1];
#define lowbit(x) ((x)&(-x))
inline void Update(int x,int val){for(;x<=m;x+=lowbit(x)) tree[x] += val;}
inline int Query(int x){int Ans = 0;for(;x;x-=lowbit(x)) Ans += tree[x];return Ans;}

inline void CDQ(int l,int r) {
    if(l == r) return;
    register int mid = l + r >> 1,L = l,R = mid + 1;
    for(int i = l;i<=r;i++) 
        if(a[i].x <= mid) Update(a[i].t,a[i].cnt);
        else a[i].Ans += Query(a[i].t);
    for(int i = l;i<=r;i++) if(a[i].x <= mid) Update(a[i].t,-a[i].cnt);
    for(int i = l;i<=r;i++)
        if(a[i].x <= mid) tmp[L++] = a[i];
        else tmp[R++] = a[i];
    for(int i = l;i<=r;i++) a[i] = tmp[i]; 
    CDQ(l,mid);CDQ(mid+1,r);
}

int main(){
    n = read<int>(); m = read<int>();
    for(int i = 1;i<=n;i++) 
        a[i].x = read<int>(),a[i].y = read<int>(),
        a[i].t = read<int>(),a[i].cnt = 1;
    std::sort(&a[1],&a[n+1]); 
    for(int i = 1;i<=n;i++) {
        if(i == 1 || a[i-1] != a[i]) a[++tot] = a[i];
        else a[tot].cnt ++;
    }
    for(int i = 1;i<=tot;i++) a[i].x = i;
    std::sort(&a[1],&a[tot+1],cmp_y); CDQ(1,tot);
    for(int i = 1;i<=tot;i++) Ans[a[i].Ans + a[i].cnt - 1] += a[i].cnt;
    for(int i = 0;i<n;i++) printf("%d\n",Ans[i]);
    return 0;
}