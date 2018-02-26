#include <stdio.h>
#include <algorithm>
#define int long long 
const int MAXN = 100005,inf = 2e9;
int n,Q,val[2][MAXN],Hash[2][MAXN],sz[2];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

class CMT{
public:
    struct node{int l,r,size,sum;}tree[MAXN*20];
    int root[MAXN],cnt,tot,op;
    #define ls(o) tree[o].l
    #define rs(o) tree[o].r
    inline void Update(int &o,int old,int l,int r,int x){
        o = ++ cnt; tree[o] = tree[old]; tree[o].sum += Hash[op][x]; tree[o].size ++;
        if (l == r) return;
        register int mid = l + r >> 1;
        if (x <= mid) Update(ls(o),ls(old),l,mid,x);
        else Update(rs(o),rs(old),mid+1,r,x);
    }
    inline int Kth(int o,int old,int l,int r,int k){
        if (l == r) return l;
        register int mid = l + r >> 1, tmp = tree[ls(o)].size - tree[ls(old)].size;
        if (k <= tmp) return Kth(ls(o),ls(old),l,mid,k);
        else return Kth(rs(o),rs(old),mid+1,r,k - tmp);
    }
    inline void Query_Sum(int o,int old,int l,int r,int x,int y,int &Sum,int &Size){
        if (x <= l && r <= y) return Sum += tree[o].sum - tree[old].sum, Size += tree[o].size - tree[old].size, void();
        register int mid = l + r >> 1, Ans = 0;
        if (x <= mid) Query_Sum(ls(o),ls(old),l,mid,x,y,Sum,Size);
        if (mid < y) Query_Sum(rs(o),rs(old),mid+1,r,x,y,Sum,Size);
    }
    inline int Query(int l,int r){
        int k = tree[root[r]].size - tree[root[l-1]].size, tmp, Ans = 0;k = k + 1 >> 1;
        tmp = Kth(root[r],root[l-1],1,tot,k);
        int Size[2],Sum[2]; Size[0] = Size[1] = Sum[0] = Sum[1] = 0;
        Query_Sum(root[r],root[l-1],1,tot,1,tmp,Sum[0],Size[0]);
        Query_Sum(root[r],root[l-1],1,tot,tmp+1,tot,Sum[1],Size[1]);
        return Sum[1] - Size[1] * Hash[op][tmp] + Size[0] * Hash[op][tmp] - Sum[0];
    }
    inline void build(int *a){
        for (int i = 1; i <= n; i++) Update(root[i],root[i-1],1,tot,a[i]);
    }
}chair_man_tree[2];

inline void Hash_Init(){
    for (int j = 0; j <= 1; j++){
        for (int i = 1; i <= n; i++) Hash[j][i] = val[j][i];
        std::sort(&Hash[j][1],&Hash[j][n+1]);
        sz[j] = std::unique(&Hash[j][1],&Hash[j][n+1]) - Hash[j] - 1;
        for (int i = 1; i <= n; i++) val[j][i] = std::lower_bound(&Hash[j][1],&Hash[j][sz[j]+1],val[j][i]) - Hash[j];
    }
}

signed main(){
    n = read<int>(); Q = read<int>();
    for (int i = 1; i <= n; i++) val[0][i] = read<int>();
    for (int i = 1; i <= n; i++) val[1][i] = read<int>();
    for (int i = 1, x, y; i <= n; i++) 
        x = val[0][i],y = val[1][i],val[0][i] = x + y, val[1][i] = x - y;
    Hash_Init();
    chair_man_tree[0].tot = sz[0];
    chair_man_tree[0].op = 0;
    chair_man_tree[1].tot = sz[1];
    chair_man_tree[1].op = 1;
    chair_man_tree[0].build(val[0]);
    chair_man_tree[1].build(val[1]);
    while (Q--){
        register int l = read<int>(),r = read<int>();
        printf("%.2f\n",(chair_man_tree[0].Query(l,r) + chair_man_tree[1].Query(l,r)) / 2.0);
    }
    return 0;
}