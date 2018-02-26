#include <bits/stdc++.h>
const int inf = 1 << 30,MAXN = 50005;
int n;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct data {
    int pos,val;
    inline bool operator < (const data &x) const{
        return val > x.val;
    }
}a[MAXN];

struct node {
    node *ch[2];
    int sum;
    inline void* operator new(size_t,node *ls,node *rs,int size);
}*C,*root[MAXN],*mempool,*null;

inline void* node::operator new(size_t,node *ls,node *rs,int size) {
    if (C == mempool) C = new node[1<<15],mempool = C + (1 << 15);
    C -> ch[0] = ls; C -> ch[1] = rs; C -> sum = size;
    return C ++;
}

inline node* Update(node *o,int x,int full = inf) {
    if (!full) return new(o->ch[0],o->ch[1],o->sum + 1)node;
    if (x & full) return new(o->ch[0],Update(o->ch[1],x,full >> 1),o->sum + 1)node;
    return new(Update(o->ch[0],x,full >> 1),o->ch[1],o->sum + 1)node;
}

inline int Query(node *o,node *old,int x,int full = inf) {
    if (!full) return 0; 
    bool d = x & full; int s = o -> ch[d^1] -> sum - old -> ch[d^1] -> sum;
    if (s) return full|Query(o->ch[d^1],old->ch[d^1],x,full >> 1);
    else return Query(o->ch[d],old->ch[d],x,full>>1);
}

std::set<int> s;

int main() {
    null = new(null,null,0)node;
    null -> ch[0] = null -> ch[1] = null;
    root[0] = Update(null,0);
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i].val = read<int>();
        a[i].pos = i;
        root[i] = Update(root[i-1],a[i].val);
    }
    std::sort(&a[1],&a[n+1]);
    s.insert(-1); s.insert(-2);
    s.insert(n+1); s.insert(n+2);

    s.insert(a[1].pos);

    std::set<int>::iterator l,r;

    int Ans = 0;

    for (int i = 2; i <= n; i++) {
        r = s.lower_bound(a[i].pos);
        l = r; l--; l--; r++;
        int L = *l + 1,R = *r - 1;
        L = std::max(L,1); R = std::min(R,n);
        Ans = std::max(Ans,Query(root[R],root[L-1],a[i].val));
        s.insert(a[i].pos);
    }

    printf("%d\n",Ans);
    
    return 0;
}