#include <stdio.h>
#include <iostream>
const int MAXN = 10005;
int n,m;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    node *ch[2],*f; bool tag;
    inline void rev();
    inline void Push_down();
    inline bool get();
    inline bool isrt();
    inline void rotate();
    inline void Splay();
}null[MAXN];

inline void node::rev() {
    tag ^= 1;
    std::swap(ch[0],ch[1]);
}

inline void node::Push_down() {
    if (this == null) return;
    if (tag) {
        tag ^= 1;
        ch[0] -> rev();
        ch[1] -> rev();
    }
}

inline bool node::get() {
    return f -> ch[1] == this;
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::rotate() {
    node *fa = f,*pa = fa -> f;
    int d = get();
    if (!fa->isrt()) pa->ch[fa->get()] = this;
    if ((fa->ch[d] = ch[d^1]) != null) ch[d^1] -> f = fa;
    fa -> f = this; this -> f = pa;
    ch[d^1] = fa;
}

inline void node::Splay() {
    Push_down();
    for (node *t = f; !isrt();rotate(),t = f) {
        if (!t -> isrt()) {
            t -> f -> Push_down(); t -> Push_down(); Push_down();
            if (get() == t -> get()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(),Push_down();
    }
}

inline void Access(node *x) {
    node* y = null;
    while (x != null)
        x -> Splay(),
        x -> ch[1] = y,
        y = x,x = x -> f;
}

inline void Make_root(node *x) {
    Access(x);
    x -> Splay();
    x -> rev();
}

inline node* find_root(node *x) {
    Access(x); x -> Splay(); x -> Push_down();
    while (x -> ch[0] != null) x = x -> ch[0], x -> Push_down();
    return x;
}

inline void Link(node *x,node *y) {
    Make_root(x); x -> f = y;
}

inline void Cut(node *x,node *y) {
    Make_root(x); Access(y); y -> Splay();
    y -> ch[0] = x -> f = null;
}

int main() {
    null -> ch[0] = null -> ch[1] = null -> f = null;
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= n; i++) null[i].ch[0] = null[i].ch[1] = null[i].f = null;
    char op[10]; int x,y;
    while (m--) {
        scanf("%s",op);  x = read<int>();y = read<int>();
        if (op[0] == 'C') Link(&null[x],&null[y]);
        else if (op[0] == 'D') Cut(&null[x],&null[y]);
        else {
            if (find_root(&null[x]) == find_root(&null[y])) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
