#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 505
#define lowbit(x) ((x)&(-x))
int n,m,top,tree[MAXN][MAXN],Ans[60005];


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct Op{
    int val,x,y;
    inline bool operator < (const Op & a)const{
        return val < a.val;
    }
}a[MAXN*MAXN];
struct Qu{int x,y,x1,y1,k,id;}Q[60005],L[60005],R[60005];

inline void Update(int x,int y,int val) {
    for(int i = x;i<=n;i+=lowbit(i))
        for(int j = y;j<=n;j+=lowbit(j))
            tree[i][j] += val;
}

inline int Query(int x,int y){
    if(!x || !y) return 0;
    int Ans = 0;
    for(int i = x;i;i-=lowbit(i))
        for(int j = y;j;j-=lowbit(j))
            Ans += tree[i][j];
    return Ans;
}

inline int Query(int a,int b,int c,int d){
    return Query(c,d) + Query(a-1,b-1) - Query(a-1,d) - Query(c,b-1);
}

inline void solve(int ql,int qr,int l,int r) {
    if(ql>qr) return;
    if(l == r) {
        for(;ql<=qr;ql++) Ans[Q[ql].id] = l;
        return ;
    }
    register int mid = l + r >> 1,Lnum = 0,Rnum = 0;
    while(a[top+1].val <= mid && top < n * n) Update(a[top+1].x,a[top+1].y,1),top ++;
    while(a[top].val > mid && top >= 1) Update(a[top].x,a[top].y,-1),top --;
    for(int i = ql;i<=qr;i++) {
        register int now = Query(Q[i].x,Q[i].y,Q[i].x1,Q[i].y1);
        if(now >= Q[i].k) L[++Lnum] = Q[i];
        else R[++Rnum] = Q[i];
    }
    for(int i = 1;i<=Lnum;i++) Q[ql + i - 1] = L[i];
    for(int i = 1;i<=Rnum;i++) Q[qr - Rnum + i] = R[i];
    solve(ql,ql + Lnum - 1,l,mid);solve(ql + Lnum,qr,mid+1,r);
}

int main(){
    n = read<int>(); m = read<int>();
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=n;j++) {
            a[(i-1)*n+j].val = read<int>();
            a[(i-1)*n+j].x = i;
            a[(i-1)*n+j].y = j;
        }
    std::sort(&a[1],&a[n*n+1]);
    for(int i = 1;i<=m;i++) 
        Q[i].id = i,Q[i].x = read<int>(),Q[i].y = read<int>(),
        Q[i].x1 = read<int>(),Q[i].y1 = read<int>(),Q[i].k = read<int>();
    solve(1,m,1,1e9); 
    for(int i = 1;i<=m;i++) printf("%d\n",Ans[i]);
    // getchar(); getchar();
    return 0;
}