#include <stdio.h>
const int MAXN = 600005,inf = 1 << 24;
int n,Q,Sum[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    node *ch[2]; int size;
    inline void* operator new(size_t,node *ls,node *rs,int size);
}*null,*root[MAXN],*C,*mempool;

inline void* node::operator new(size_t,node *ls,node *rs,int size){
    if (C == mempool) C = new node[1<<15],mempool = C + (1 << 15);
    C -> ch[0] = ls; C -> ch[1] = rs; C -> size = size; 
    return C ++;
}

inline node* Update(node *o,int x,int full = inf){
    if (!full) return new(o -> ch[0], o -> ch[1],o -> size + 1) node;
    if (x & full) return new(o -> ch[0],Update(o -> ch[1], x, full >> 1), o -> size + 1) node;
    return new(Update(o -> ch[0],x, full >> 1),o -> ch[1], o -> size + 1) node;
}

inline int Query(node *o,node *old,int x,int full = inf){
    if (!full) return 0; bool d = x & full;
    if (o -> ch[d^1] -> size - old -> ch[d^1] -> size) return Query(o -> ch[d^1],old -> ch[d^1],x, full >> 1)|full;
    else return Query(o -> ch[d],old -> ch[d],x, full >> 1);
}

int main(){
    n = read<int>(); Q = read<int>();
    for (int i = 1; i <= n; i++) Sum[i] = Sum[i-1] ^ read<int>();
    null = new(null,null,0)node; null -> ch[0] = null -> ch[1] = null;
    root[0] = Update(null,0);
    for (int i = 1; i <= n; i++) root[i] = Update(root[i-1],Sum[i]);
    int l,r,x;
    while (Q--){
        char ch = getchar();
        for (; ch != 'A' && ch != 'Q'; ch = getchar());
        if (ch == 'A') Sum[n + 1] = Sum[n] ^ read<int>(), ++ n, root[n] = Update(root[n-1],Sum[n]);
        else{
            l = read<int>(),r = read<int>(),x = read<int>();
            if (l == r && l == 1){printf("%d\n",Sum[n] ^ x); continue;}
            printf("%d\n",Query(root[r-1],root[l == 1?0:l-2],Sum[n] ^ x));
        }
    }
    return 0;
}