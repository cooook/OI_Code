#include <stdio.h>
#include <iostream>
const int MAXN = 200005;
int n,m,fa[MAXN];
 
 
template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
struct node{
    node *ch[2],*f;
    int tag,size;
    inline void rev();
    inline void Push_down();
    inline void Maintain();
    inline bool isrt();
    inline bool get();
    inline void rotate();
    inline void Splay();
}null[MAXN];
 
inline void node::rev() {
    if (this == null) return;
    tag ^= 1;
    std::swap(ch[0],ch[1]);
}
 
inline void node::Push_down() {
    if (this == null) return;
    if (tag) {
        ch[0] -> rev();
        ch[1] -> rev();
        tag ^= 1;
    }
}
 
inline void node::Maintain() {
    size = ch[0] -> size + ch[1] -> size + 1;
}
 
inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}
 
inline bool node::get() {
    return f -> ch[1] == this;
}
 
inline void node::rotate() {
    node *fa = f,*pa = fa -> f; int d = get();
    if (!fa -> isrt()) pa -> ch[fa->get()] = this;
    if ((fa -> ch[d] = ch[d^1]) != null) ch[d^1] -> f = fa;
    fa -> f = this; this -> f = pa; ch[d^1] = fa;
    fa -> Maintain(); Maintain();
}
 
inline void node::Splay() {
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f) {
        if (!t -> isrt()) {
            t -> f -> Push_down(); t -> Push_down(); Push_down();
            if (get() == t -> get()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(),Push_down();
    }
}
 
inline void Access(node *x) {
    node *y = null;
    while (x != null)
        x -> Splay(), 
		x -> ch[1] = y, 
		x -> Maintain(), 
		y = x, x = x -> f;
}
 
inline void Make_root(node *x) {
    Access(x); x -> Splay(); x -> rev();
}
 
inline void Link(node *x,node *y) {
    Make_root(x); x -> f = y;
}
 
inline void Cut(node *x,node *y) {
    Make_root(x); Access(y); y -> Splay();
    y -> ch[0] = x -> f = null;
    y -> Maintain();
}
 
inline int Query(node *x) {
	Make_root(&null[n+1]);  // ÏÈ»»³ÉÊ÷¸ù... 
    Access(x); x -> Splay();
    return x -> size - 1;
}
 
#define waiting_to_debug true
#include <time.h>
 
int main() {
    freopen("bzoj_2002.in","r",stdin);
    freopen("bzoj_2002.out","w",stdout);
    null -> ch[0] = null -> ch[1] = null -> f = null;
    null -> size = 0;
    n = read<int>();
    for (int i = 1; i <= n + 1; i++)
        null[i].ch[0] = null[i].ch[1] = null[i].f = null,null[i].size = 1,null[i].tag = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i + read<int>(); fa[i] = std::min(fa[i],n+1);
        Link(&null[i],&null[fa[i]]);
    } 
	m = read<int>();
    while (m --) {
        register int op = read<int>(),x = read<int>() + 1,y;
        if (op == 1) printf("%d\n",Query(&null[x]));
        else {
            y = read<int>();
            Cut(&null[x],&null[fa[x]]);
            fa[x] = x+y<=n+1?x+y:n+1;
        	Link(&null[x],&null[fa[x]]);
        }
    }
    return 0;
}
