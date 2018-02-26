#include <bits/stdc++.h>
#define int long long 
typedef long long ll;
const int MAXN = 50005;
int n,m; ll val[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    node *ch[2],*f;
    ll Lsum,Rsum,Sum,val,add,tot;
    int tag,size;
    inline void Maintain();
    inline void rev();
    inline void Push_down();
    inline void Add(ll);
    inline bool dir();
    inline bool isrt();
    inline void rotate();
    inline void Splay();
}null[MAXN];

inline void node::rev(){
    std::swap(ch[0], ch[1]);
    std::swap(Lsum,Rsum);
    tag ^= 1;
}

inline void node::Maintain(){
    size = ch[0] -> size + ch[1] -> size + 1;
    tot = ch[0] -> tot + val + ch[1] -> tot;
    Lsum = ch[0] -> Lsum + val * (ch[0] -> size + 1) + ch[1] -> Lsum + ch[1] -> tot * (ch[0] -> size + 1);
    Rsum = ch[1] -> Rsum + val * (ch[1] -> size + 1) + ch[0] -> Rsum + ch[0] -> tot * (ch[1] -> size + 1);
    Sum = ch[0] -> Sum + ch[1] -> Sum + (ch[1] -> size + 1) * ch[0] -> Lsum + (ch[0] -> size + 1) * ch[1] -> Rsum + val * (ch[0] -> size + 1) * (ch[1] -> size + 1);
}

inline void node::Push_down(){
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
    if (add) ch[0] -> Add(add), ch[1] -> Add(add), add = 0;
}

inline bool node::dir(){
    return f -> ch[1] == this;
}

inline bool node::isrt(){
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::Add(ll x){
    val += x;
    Sum += size * (size + 1) * (size + 2) / 6 * x;
    Lsum += size * (size + 1) / 2 * x;
    Rsum += size * (size + 1) / 2 * x;
    tot += size * x;
    add += x;
}

inline void node::rotate(){
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    ch[d ^ 1] = fa; fa -> f = this; this -> f = pa;
    fa -> Maintain(); Maintain();
}

inline void node::Splay(){
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()){
            t -> f -> Push_down(), t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
}

inline void Access(node *x){
    node *y = null;
    while (x != null)
        x -> Splay(),
        x -> ch[1] = y,
        x -> Maintain(),
        y = x, x = x -> f;
}

inline void Make_root(node *x){
    Access(x); x -> Splay(); x -> rev();
}

inline void Link(node *x,node *y){
    Make_root(x); x -> Splay(); x -> f = y;
}

inline void Cut(node *x,node *y){
    Make_root(x); Access(y); x -> Splay();
    x -> ch[1] = y -> f = null;
    x -> Maintain();
}

inline node* find(node *x){
    Access(x); x -> Splay(); x -> Push_down();
    while (x -> ch[0] != null)
        x = x -> ch[0], x -> Push_down();
    return x;
}

inline ll gcd(ll x,ll y){
    return !y?x:gcd(y,x%y);
}

signed main(){
    n = read<int>(); m = read<int>();
    null -> ch[0] = null -> ch[1] = null -> f = null;
    for (int i = 1; i <= n; ++i){
        val[i] = read<int>();
        null[i].ch[0] = null[i].ch[1] = null[i].f = null;
        null[i].tag = 0; null[i].size = 1;
        null[i].val = null[i].Lsum = null[i].Rsum = null[i].Sum = null[i].tot = val[i];
    }
    for (int i = 1; i < n; ++i){
        int u = read<int>(), v = read<int>();
        Link(&null[u],&null[v]);
    }
    int op,u,v,d;
    while (m --){
        op = read<int>(), u = read<int>(), v = read<int>();
        if (op == 1){
            if (find(&null[u]) == find(&null[v])) Cut(&null[u],&null[v]);
        }
        else if (op == 2){
            if (find(&null[u]) != find(&null[v])) Link(&null[u],&null[v]);
        }
        else if (op == 3){
            d = read<int>();
            if (find(&null[u]) == find(&null[v])){
                Make_root(&null[u]); Access(&null[v]);
                (&null[v]) -> Splay(); (&null[v]) -> Add(d);
            }
        }
        else {
            if (find(&null[u]) != find(&null[v])){
                puts("-1"); continue;
            }
            Make_root(&null[u]); Access(&null[v]);
            (&null[v]) -> Splay();
            ll Ans = (&null[v]) -> Sum,size = (&null[v]) -> size;
            size = size * (size + 1) / 2;
            ll g = gcd(Ans,size);
            Ans /= g; size /= g;
            printf("%lld/%lld\n",Ans,size);
        }
    }
    return 0;
}