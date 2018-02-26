# include <bits/stdc++.h> 
const int MAXN = 1e6 + 5;
int n, cnt, Ans[MAXN], Qc, id[MAXN], Node, L[MAXN], R[MAXN], Last, m; 


char sb[1 << 15], *S = sb, *T = sb;
# define gc (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
inline int read() {
    register int x = 0, f = 1; char ch = gc;
    for (; !isdigit(ch); ch = gc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = gc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct WTF {
    int Num, id, x, y;
    WTF(int Num = 0, int id = 0, int x = 0, int y = 0) : Num(Num), id(id), x(x), y(y) {  }
    inline bool operator < (const WTF &a) const {
        return Num == a.Num ? id < a.id : Num < a.Num;
    }
}Q[MAXN];

struct node {
    node *ch[2], *f; 
    int val, size; bool tag; 
    inline void Maintain();
    inline void rev();
    inline void Push_down();
    inline void rotate();
    inline void Splay();
    inline bool isrt();
    inline bool dir();
} null[MAXN], *tree[MAXN]; 

inline void New(bool type) {
    ++ cnt; null[cnt].ch[0] = null[cnt].ch[1] = null[cnt].f = null;
    null[cnt].val = null[cnt].size = type; null[cnt].tag = false;
    tree[cnt] = &null[cnt];
}

inline void node::Maintain() {
    size = val + ch[0] -> size + ch[1] -> size;
}

inline bool node::dir() {
    return f -> ch[1] == this;
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    fa -> f = this; f = pa; ch[d ^ 1] = fa;
    fa -> Maintain(); Maintain();
}

inline void node::rev() {
    std::swap(ch[0], ch[1]);
    tag ^= 1;
}

inline void node::Push_down() {
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}

inline void node::Splay() {
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()) {
            t -> f -> Push_down(), t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
}

inline node* Access(node *x) {
    node *y = null; 
    while (x != null) {
        x -> Splay();
        x -> ch[1] = y; 
        x -> Maintain();
        y = x; x = x -> f;
    }
    return y;
}

inline void Cut(node *x) {
    Access(x); x -> Splay(); 
    x -> ch[0] = x -> ch[0] -> f = null;
    x -> Maintain();
}

inline void Link(node *x, node *y) {
    Access(x); x -> Splay(); x -> rev(); x -> f = y;
}

int main() { 
    n = read(), m = read(); 
    null -> ch[0] = null -> ch[1] = null -> f = null; 
    null -> tag = false; null -> val = null -> size = 0;
    Node = 1;
    L[Node] = id[Node] = 1; R[Node] = n;
    New(1); New(0); Last = cnt; Link(tree[2], tree[1]);
    for (int i = 1; i <= m; ++i) {
        Ans[i] = -1;
        int opt = read(), x, y, z; 
        if (opt == 0) {
            New(1); L[++ Node] = read(), R[Node] = read(); id[Node] = cnt;
            Q[++Qc] = WTF(L[Node], i - m, cnt, Last);
        }
        else if (opt == 1) {
            x = read(), y = read(), z = read();
            x = std::max(x, L[z]), y = std::min(y, R[z]);
            if (x <= y) { 
                New(0);  Link(tree[cnt], tree[Last]);
                Q[++Qc] = WTF(x, i - m, cnt, id[z]);
                Q[++Qc] = WTF(y + 1, i - m, cnt, Last);
                Last = cnt;
            }
        }
        else {
            x = read(), y = read(), z = read();
            Q[++Qc] = WTF(x, i, id[y], id[z]);
        }
    }
    std::sort(&Q[1], &Q[Qc + 1]);
    int zzh = 1;
    for (int i = 1; i <= n; ++i) {
        for (; zzh <= Qc && Q[zzh].Num == i; ++zzh) {
            if (Q[zzh].id > 0) {
                Access(tree[Q[zzh].x]), tree[Q[zzh].x] -> Splay(); Ans[Q[zzh].id] = tree[Q[zzh].x] -> size;
                node *p = Access(tree[Q[zzh].y]); tree[Q[zzh].y] -> Splay(); Ans[Q[zzh].id] += tree[Q[zzh].y] -> size;
                Access(p); p -> Splay(); Ans[Q[zzh].id] -= 2 * p -> size;
            }
            else Cut(tree[Q[zzh].x]), Link(tree[Q[zzh].x], tree[Q[zzh].y]);
        }
    }
    for (int i = 1; i <= m; ++i)
        if (Ans[i] != -1) printf("%d\n", Ans[i]);
    return 0;
}