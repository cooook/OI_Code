#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
const int MAXN = 200005;
int n,m,p1,p2,val[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct data{int l,r,v;};
#define ls(o) tree[o].l
#define rs(o) tree[o].r
int cnt, root[MAXN];
struct node{int l,r;ll sum,tag;}tree[MAXN*100];
inline void Update(int &o,int old,int l,int r,int x,int y,int val){
    o = ++ cnt; tree[o] = tree[old];
    tree[o].sum += 1ll * (y - x + 1) * val;
    if (x == l && r == y) return tree[o].tag += val, void();
    register int mid = l + r >> 1;
    if (y <= mid) Update(ls(o),ls(old),l,mid,x,y,val);
    else if (x > mid) Update(rs(o),rs(old),mid+1,r,x,y,val);
    else Update(ls(o),ls(old),l,mid,x,mid,val), Update(rs(o),rs(old),mid+1,r,mid+1,y,val);
}

inline ll Query(int o,int old,int l,int r,int x,int y){
    if (x == l && r == y) return tree[o].sum - tree[old].sum;
    register int mid = l + r >> 1; ll Ans = 1ll * (y - x + 1) * (tree[o].tag - tree[old].tag);
    if (y <= mid) return Query(ls(o),ls(old),l,mid,x,y) + Ans;
    else if (x > mid) return Query(rs(o),rs(old),mid+1,r,x,y) + Ans;
    else return Query(ls(o),ls(old),l,mid,x,mid) + Query(rs(o),rs(old),mid + 1,r,mid + 1,y) + Ans;
}

int Q[MAXN],top,L[MAXN],R[MAXN];
std::vector<data> G[MAXN];

int main(){
    n = read<int>(); m = read<int>(); p1 = read<int>(); p2 = read<int>();
    for (int i = 1; i <= n; i++) val[i] = read<int>();
    Q[top = 0] = 0;
    for (int i = 1; i <= n; i++){
        while (top && val[Q[top]] < val[i]) top --;
        L[i] = Q[top]; Q[++top] = i;
    }
    Q[top = 0] = n + 1;
    for (int i = n; i; i--){
        while (top && val[Q[top]] < val[i]) top --;
        R[i] = Q[top]; Q[++top] = i;
    }
    for (int i = 1; i <= n; i++){
        if (i != n) G[i].pb((data){i+1,i+1,p1});
        if (L[i] && R[i] != n + 1) G[L[i]].pb((data){R[i],R[i],p1});
        if (L[i] && i + 1 <= R[i] - 1) G[L[i]].pb((data){i+1,R[i]-1,p2});
        if (R[i] != n + 1 && L[i] + 1 <= i - 1) G[R[i]].pb((data){L[i]+1,i-1,p2});
    }
    for (int i = 1; i <= n; i++){
        root[i] = root[i-1];
        for (int j = 0; j < G[i].size(); j++)
            Update(root[i],root[i],1,n,G[i][j].l,G[i][j].r,G[i][j].v);
    }
    int l,r;
    while (m--) l = read<int>(), r = read<int>(), printf("%lld\n",Query(root[r],root[l-1],1,n,l,r));
    return 0;
}