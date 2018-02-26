# include <bits/stdc++.h>
const int MAXN = 2e5 + 5;
int n, m;
double A[20], B[20], C[20][20], fac[20];
char type[15];


struct fun {
    double val[16];
    fun() { memset(val, 0, sizeof val); }

    inline double operator ()(double x) {
        double Ans = 0.0, t = 1;
        for (int i = 0; i < 16; ++i)
            Ans += val[i] * t, t *= x;
        return Ans;
    }

    inline fun operator + (const fun &a) const {
        fun t = *this;
        for (int i = 0; i < 16; ++i) t.val[i] += a.val[i];
        return t;
    }

    inline void Init() {
        memset(val, 0, sizeof val);
        register int type; register double k, b;
        scanf("%d%lf%lf", &type, &k, &b);
        A[0] = B[0] = 1;
        if (type == 2) {
            for (int i = 1; i <= 15; ++i) A[i] = A[i - 1] * k, B[i] = B[i - 1] * b;
            for (int i = 0; i <= 15; ++i) 
                for (int j = 0; j <= i; ++j)
                    val[j] += C[i][j] * A[j] * B[i - j] / fac[i];
        }
        else if (type == 1) {
            for (int i = 1; i <= 15; ++i) A[i] = A[i - 1] * k, B[i] = B[i - 1] * b;
            for (int i = 1; i <= 15; i += 2)
                for (int j = 0; j <= i; ++j)
                    val[j] += C[i][j] * A[j] * B[i - j] / fac[i] * ((i & 2) ? -1 : 1); 
        }
        else val[0] = b, val[1] = k;
    }
};

struct node {
    node *ch[2], *f;
    bool tag; fun val, Sum;
    inline void rotate();
    inline void Splay();
    inline bool isrt();
    inline bool dir();
    inline void Maintain();
    inline void rev();
    inline void Push_down();
}null[MAXN], *tree[MAXN]; 

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
    ch[d ^ 1] = fa; fa -> f = this; f = pa;
    fa -> Maintain(); Maintain();
}

inline void node::Splay() {
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()) {
            t -> f -> Push_down(); t -> Push_down(); Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
}

inline void node::Maintain() {
    Sum = ch[0] -> Sum + ch[1] -> Sum + val;
}

inline void node::rev() {
    tag ^= 1;
    std::swap(ch[0], ch[1]);
}

inline void node::Push_down() {
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}

inline void Access(node *x) {
    node *y = null;
    while (x != null) {
        x -> Splay();
        x -> ch[1] = y;
        x -> Maintain();
        y = x; x = x -> f;
    }
}
 
inline void Make_root(node *x) {
    Access(x); x -> Splay(); x -> rev();
}

inline void Link() {
    register int x, y; scanf("%d%d", &x, &y); ++x; ++y;
    Make_root(tree[x]); tree[x] -> f = tree[y];
}

inline void Cut() {
    register int x, y; scanf("%d%d", &x, &y); ++x; ++y;
    Make_root(tree[x]); Access(tree[y]); tree[y] -> Splay(); tree[y] -> ch[0] = tree[x] -> f = null;
    tree[y] -> Maintain();
}

inline void Update() {
    register int x; scanf("%d", &x); ++ x;
    tree[x] -> Splay();
    tree[x] -> val.Init();
    tree[x] -> Maintain();
} 

inline node* find(node *x) {
    Access(x); x -> Splay();
    while (x -> ch[0] != null) x -> Push_down(), x = x -> ch[0];
    return x;
} 

inline void Query() {
    register int x, y; register double w;
    scanf("%d%d%lf", &x, &y, &w); ++ x; ++ y; 
    if (find(tree[x]) != find(tree[y])) return puts("unreachable"), void();
    Make_root(tree[x]); Access(tree[y]); tree[x] -> Splay();
    printf("%.8f\n", tree[x] -> Sum(w));
}

inline void Init() {
    C[0][0] = 1;
    for (int i = 1; i <= 19; ++i)  {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    fac[0] = 1;
    for (int i = 1; i <= 19; ++i)
        fac[i] = fac[i - 1] * i;
}

int main() {
    scanf("%d%d%*s", &n, &m);
    Init(); 
    for (int i = 0; i < MAXN; ++i)
        null[i].ch[0] = null[i].ch[1] = null[i].f = null, null[i].val = null[i].Sum = fun(), null[i].tag = 0;
    tree[0] = null;
    for (int i = 1; i <= n; ++i)
        tree[i] = &null[i], tree[i] -> val.Init(), tree[i] -> Sum = tree[i] -> val;
    while (m --) {
        scanf("%s", type + 1);
        if (type[1] == 't') Query();
        else if (type[1] == 'a') Link();
        else if (type[1] == 'd') Cut();
        else Update(); 
    }
    return 0;
}