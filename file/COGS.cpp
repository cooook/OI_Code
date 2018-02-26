#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#define MAXN 10005
int n,m,root[133333],cnt,QWQ;


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct node{
    int l,r,mx;
    inline void Update(int val){
        mx = std::max(mx,val);
    }
}tree[133333*20];

#define ls tree[o].l
#define rs tree[o].r

inline void Update(int &o,int old,int l,int r,int x,int val){
    o = ++ cnt; tree[o] = tree[old];
    if (l == r) {tree[o].mx = val;return;}
    register int mid = l + r >> 1;
    if (x<=mid) Update(tree[o].l,tree[old].l,l,mid,x,val);
    else Update(tree[o].r,tree[old].r,mid+1,r,x,val);
    tree[o].mx = std::max(tree[ls].mx,tree[rs].mx);
}

inline int Query(int o,int l,int r,int x,int y) {
    if (x<=l&&r<=y) return tree[o].mx;
    register int mid = l + r >> 1,Ans = -0x3f3f3f3f;
    if (x<=mid) Ans = std::max(Query(tree[o].l,l,mid,x,y),Ans);
    if (mid<y) Ans = std::max(Query(tree[o].r,mid+1,r,x,y),Ans);
    return Ans;
}

inline void build(int &o,int l,int r){
    o = ++ cnt;
    if (l == r) {
        tree[o].mx = read<int>();
        return ;
    }
    register int mid = l + r >> 1;
    build(tree[o].l,l,mid); 
    build(tree[o].r,mid+1,r);
    tree[o].mx = std::max(tree[ls].mx,tree[rs].mx);
}

int main() {
    freopen("longterm_segtree.in","r",stdin);
    freopen("longterm_segtree.out","w",stdout);
    n = read<int>(); m = read<int>();
    build(root[1],1,n); QWQ = 1;
    for (int i = 1; i <= m; i++) {
        register int op = read<int>(),l = read<int>(),r = read<int>(),y = read<int>();
        if (op == 0) printf("%d\n",Query(root[l],1,n,r,y));
        else Update(root[++QWQ],root[l],1,n,r,y);
    }
    return 0;
}