#include <bits/stdc++.h>
const int MAXN = 80005,inf = 1e8;
int n,Q,first[MAXN],e = 1,in[MAXN],out[MAXN],idx,deep[MAXN],f[MAXN][18],val[MAXN];
std::vector<int> add[MAXN],del[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void dfs(int u,int fa){
    in[u] = ++ idx; f[u][0] = fa; deep[u] = deep[fa] + 1;
    add[idx].push_back(val[u]);
    for (int i = 1; i <= 17; i++) f[u][i] = f[f[u][i-1]][i-1];
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa) dfs(a[i].v,u);
    out[u] = idx;
    del[idx+1].push_back(val[u]);
}

inline int lca(int u,int v){
    if (deep[u] < deep[v]) std::swap(u,v);
    int t = deep[u] - deep[v];
    for (int i = 17; ~i; i--)
        if (t & (1 << i)) u = f[u][i];
    if (u == v) return u;
    for (int i = 17; ~i; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i],v = f[v][i];
    return f[u][0]; 
}

namespace CMT{
    #define lowbit(x) ((x)&(-x))
    struct node{int l,r,sum;}tree[MAXN*200];
    int root[MAXN],S[MAXN],Use[MAXN][4],cnt;
    #define ls(i) tree[i].l
    #define rs(i) tree[i].r
    inline void Update(int &o,int old,int l,int r,int x,int val){
        o = ++ cnt; tree[o] = tree[old]; tree[o].sum += val;
        if (l == r) return;
        register int mid = l + r >> 1;
        if (x <= mid) Update(ls(o),ls(old),l,mid,x,val);
        else Update(rs(o),rs(old),mid+1,r,x,val);
    }

    inline void Tree_Update(int x,int val,int ad){
        for (; x <= n; x += lowbit(x)) Update(S[x],S[x],0,inf,val,ad);
    }

    inline int Query(int x,int op){
        int Ans = 0;
        for (; x; x -= lowbit(x)) Ans += tree[rs(Use[x][op])].sum;
        return Ans;
    }

    inline int All_Query(int x,int op){
        int Ans = 0;
        for (; x; x -= lowbit(x)) Ans += tree[Use[x][op]].sum;
        return Ans;
    }

    inline int Query(int u,int v,int k){
        int t = lca(u,v);
        int l = 0,r = inf,mid,tmp,rt[4],RT[4];
        rt[0] = in[t]; rt[1] = in[u]; rt[2] = in[v]; rt[3] = in[f[t][0]];
        for (int i = 0; i < 4; i++) RT[i] = root[rt[i]]; 
        for (int i = 0; i < 4; i++) for (int j = rt[i]; j; j -= lowbit(j)) Use[j][i] = S[j];
        tmp = All_Query(in[u],1) - All_Query(in[t],0) + All_Query(in[v],2) - All_Query(in[f[t][0]],3) + 
        tree[RT[1]].sum + tree[RT[2]].sum - tree[RT[0]].sum - tree[RT[3]].sum;
        if (tmp < k) return -1;
        while (l < r){
            mid = l + r >> 1;
            tmp = Query(in[u],1) - Query(in[t],0) + Query(in[v],2) - Query(in[f[t][0]],3) + 
            tree[rs(RT[1])].sum + tree[rs(RT[2])].sum - tree[rs(RT[0])].sum - tree[rs(RT[3])].sum;
            if (tmp >= k){
                l = mid + 1;
                for (int i = 0; i < 4; i++) for (int j = rt[i]; j; j -= lowbit(j)) Use[j][i] = rs(Use[j][i]);
                for (int i = 0; i < 4; i++) RT[i] = rs(RT[i]);
            }
            else{
                r = mid; k -= tmp;
                for (int i = 0; i < 4; i++) for (int j = rt[i]; j; j -= lowbit(j)) Use[j][i] = ls(Use[j][i]);
                for (int i = 0; i < 4; i++) RT[i] = ls(RT[i]);
            }
        }
        return l;
    }

    inline void Change(int x,int y){
        Tree_Update(in[x],val[x],-1);
        Tree_Update(out[x]+1,val[x],1);
        val[x] = y;
        Tree_Update(in[x],val[x],1);
        Tree_Update(out[x]+1,val[x],-1);
    }
}

using namespace CMT;

int main(){
    n = read<int>(); Q = read<int>();
    for (int i = 1; i <= n; i++) val[i] = read<int>();
    for (int i = 1; i < n; i++){
        register int u = read<int>(),v = read<int>();
        push(u,v), push(v,u);
    }
    dfs(1,0);
    for (int i = 1; i <= n; i++){
        root[i] = root[i-1]; S[i] = 0;
        for (int j = 0; j < add[i].size(); j++) Update(root[i],root[i],0,inf,add[i][j],1);
        for (int j = 0; j < del[i].size(); j++) Update(root[i],root[i],0,inf,del[i][j],-1);
    }
    while (Q--){
        register int k = read<int>(),x = read<int>(),y = read<int>();
        if (k > 0){
            int Ans = Query(x,y,k);
            if (Ans == -1) puts("invalid request!");
            else printf("%d\n",Ans);
        }
        else Change(x,y);
    }
    return 0;
}