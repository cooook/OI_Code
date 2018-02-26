#include <stdio.h>
#define MAXN 100005
int n,m,du[MAXN],first[MAXN],e = 1,fa[MAXN],Ans,_Ans,num_block;
bool flag1[MAXN],flag2[MAXN];


template<typename _t>
inline _t read(){
    register _t x = 0,f = 1; char ch = getchar();
    for(;ch>'9'||ch<'0';ch=getchar());
    for(;ch<='9'&&ch>='0';ch=getchar()) x = x * 10 + (ch^48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u;a[e].v = v;
    a[e].next = first[u]; first[u] = e ++;
}

inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void Add(int x,int y){
    x = find(x);y = find(y);
    if(x == y) return;
    fa[x] = y;
}

int main(){
    n = read<int>(); m = read<int>();
    for(int i = 1;i<MAXN;i++) fa[i] = i;
    for(register int i = 1;i<=m;i++) {
        register int u = read<int>(),v = read<int>();
        if(!u) u = ++ n;
        if(!v) v = ++ n;
        push(u,v);push(v,u); du[u] ++;du[v] ++;
        Add(u,v);
    }
    for(int i = 1;i<=n;i++) {
        if(!du[i]) continue;
        if(du[i] & 1) _Ans ++,flag1[find(i)] = true;
        if(du[i] > 2) Ans ++,flag2[find(i)] = true;
    }
    Ans += _Ans >> 1;
    for(int i = 1;i<=n;i++) if(du[i] && i == find(i)) num_block ++;
    if(num_block > 1) {
        for(int i = 1;i<=n;i++)
            if(!flag1[i] && i == find(i) && du[i]) {
                Ans ++;
                if(!flag2[i]) Ans ++;
            }
    }
    printf("%d\n",Ans);
    return 0;
}