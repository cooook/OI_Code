#include <stdio.h>
#include <iostream>
#define int unsigned
const int mod = 51061,MAXN = 100005;
int n,q;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    node *ch[2],*f;
    int tag,size,sum,mul,add,val;
    inline void Maintain();
    inline void Push_down();
    inline void rev();
    inline void Splay();
    inline void rotate();
    inline bool isrt();
    inline bool get();
    inline void Mul(int);
    inline void Add(int);
}null[MAXN];

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline bool node::get() {
    return f -> ch[1] == this;
}

inline void node::rev() {
    if (this == null) return ;
    tag ^= 1;
    std::swap(ch[0],ch[1]);
}

inline void node::Add(int x) {
    if (this == null) return ;
    (val += x) %= mod;
    (add += x) %= mod;
    (sum += x * size % mod) %= mod;
}

inline void node::Mul(int x) {
    if (this == null) return ;
    (sum *= x) %= mod;
    (mul *= x) %= mod;
    (add *= x) %= mod;
    (val *= x) %= mod;
}

inline void node::Maintain() {
    if (this == null) return ;
    sum = (ch[0] -> sum + ch[1] -> sum + val) % mod;
    size = ch[0] -> size + ch[1] -> size + 1;
}

inline void node::Push_down() {
    if (this == null) return;
    if (mul != 1) {
        ch[0] -> Mul(mul);
        ch[1] -> Mul(mul);
        mul = 1;
    }
    if (add) {
        ch[0] -> Add(add);
        ch[1] -> Add(add);
        add = 0;
    }
    if (tag) {
        tag ^= 1;
        ch[0] -> rev();
        ch[1] -> rev();
    }
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; 
    pa -> Push_down(); fa -> Push_down(); Push_down(); int d = get();
    if (!f -> isrt()) pa -> ch[f -> get()] = this;
    if ((f -> ch[d] = ch[d^1]) != null) ch[d^1] -> f = fa;
    this -> f = pa; fa -> f = this; ch[d^1] = fa;
    fa -> Maintain(); Maintain();
}

inline void node::Splay() {
    Push_down();
    for (node *t = f; !isrt(); rotate(),t = f)
        if (!t -> isrt()) {
            t -> f -> Push_down(); t -> Push_down(); Push_down();
            if (t -> get() == get()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(),Push_down();
}

inline void Access(node *x) {
    node *y = null;
    while (x != null)
        x -> Splay(),
        x -> ch[1] = y,
        x -> Maintain(),
        y = x,x = x -> f;
}

inline void Make_root(node *x) {
    Access(x); x -> Splay(); x -> rev();
}

inline void Link(node *x,node *y) {
    Make_root(x); x -> Splay(); x -> f = y;
}

inline void Cut(node *x,node *y) {
    Make_root(x); Access(y); y -> Splay();
    y -> ch[0] = x -> f = null;
    y -> Maintain();
}

inline void Update(node *x,node *y,int c) {
    Make_root(x); Access(y); y -> Splay();
    y -> Add(c % mod);
}

inline void Mul(node *x,node *y,int c) {
    Make_root(x); Access(y); y -> Splay();
    y -> Mul(c % mod);
}

inline int Query(node *x,node *y) {
    Make_root(x); Access(y);  y -> Splay();
    return y -> sum;
}

inline int read_char() {
    char ch =getchar();
    for (; ch != '+' && ch != '-' && ch != '*' && ch != '/'; ch = getchar());
    switch (ch) {
        case '+':return 1;
        case '-':return 2;
        case '*':return 3;
        case '/':return 4;
    }
}

signed main() {
    freopen("nt2012_wym_tree.in","r",stdin);
    freopen("nt2012_wym_tree.out","w",stdout);
    n = read<int>(); q = read<int>();
    null -> ch[0] = null -> ch[1] = null -> f = null; null -> mul = 0;
    null -> size = null -> tag = null -> sum = null -> add = null -> val = 0;
    for (int i = 1; i <= n; i++) 
        null[i].ch[0] = null[i].ch[1] = null[i].f = null,
        null[i].mul = 1,null[i].val = 1,null[i].sum = 1,
        null[i].tag = 0,null[i].size = 1,null[i].add = 0;
    for (int i = 1,u,v; i < n; i++) {
        u = read<int>(),v = read<int>();
        Link(&null[u],&null[v]);
    }
    while (q--) {
        register int op = read_char(),x1,x2,x3,x4;
        if (op == 1) {
            x1 = read<int>(),x2 = read<int>(),x3 = read<int>();
            Update(&null[x1],&null[x2],x3);
        }
        if (op == 2) {
            x1 = read<int>(); x2 = read<int>(); x3 = read<int>(); x4 = read<int>();
            Cut(&null[x1],&null[x2]); Link(&null[x3],&null[x4]);
        } 
        if (op == 3) {
            x1 = read<int>(),x2 = read<int>(),x3 = read<int>();
            Mul(&null[x1],&null[x2],x3);
        }
        if (op == 4) {
            x1 = read<int>(),x2 = read<int>();
            printf("%u\n",Query(&null[x1],&null[x2]));
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}