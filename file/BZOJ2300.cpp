# include <time.h>
# include <math.h> 
# include <stdio.h> 
# include <stdlib.h>
# include <iostream> 


# define fi first
# define se second
# define mk std::make_pair
# define sqr(_) ((_) * (_)) 
# define __Size(_) ((_)?(_)->Size:(0))


const int MAXN = 1e5 + 5; 

int n, x, y, m, Q;
bool vis[MAXN]; double Ans[MAXN << 1];


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Operation {
    int op, val;
    inline void in() {
        op = read();
        if (op == 1) val = read(), vis[val] = true; 
    }
}op[MAXN << 1];

struct Point {
    int d[2];
    inline int& operator [] (const int& x) {return d[x];}
    inline int operator * (const Point &a) const {return d[0] * a.d[1] - d[1] * a.d[0];}
    inline Point operator + (const Point &x) const {return (Point){d[0] + x.d[0], d[1] + x.d[1]};}
    inline Point operator - (const Point &x) const {return (Point){d[0] - x.d[0], d[1] - x.d[1]};}
}pt[MAXN];

inline double dis(Point a, Point b) {
    return sqrt(sqr(a[0] - b[0]) + sqr(a[1] - b[1]));
}

struct node{
    node *ch[2]; int Size, fix;
 
    Point val, L, R; double Sum;

    inline void Maintain() {
        L = R = val;  Size = 1; Sum = 0;
        if (ch[0] != NULL) Sum += ch[0] -> Sum + dis(val, ch[0] -> R), L = ch[0] -> L, Size += ch[0] -> Size;
        if (ch[1] != NULL) Sum += ch[1] -> Sum + dis(val, ch[1] -> L), R = ch[1] -> R, Size += ch[1] -> Size; 
    }

    node();

    node(Point);

    inline void* operator new (size_t); 
}*root, *C, *mempool;

inline void* node::operator new(size_t) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
    return C ++; 
}

typedef std::pair<node*, node*> pii; 

node::node() {
    ch[0] = ch[1] = NULL;
    Size = 0; fix = rand();
}

node::node(Point val) {
    ch[0] = ch[1] = NULL;
    Size = 1; fix = rand();
    this -> val = L = R = val;
    Sum = 0;
}

inline int Rank(node *o, int x) {
    int Ans = 0;
    while (o)
        if (x > o -> val[0]) Ans += __Size(o -> ch[0]) + 1, o = o -> ch[1];
        else o = o -> ch[0];
    return Ans + 1;
}

inline node* Kth(node *o, int k) {
    while (o) {
        if (k == __Size(o -> ch[0]) + 1) return o;
        if (__Size(o -> ch[0]) + 1 < k) k -= __Size(o -> ch[0]) + 1, o = o -> ch[1];
        else o = o -> ch[0]; 
    }
    return NULL;
}

inline pii Split(node *o, int k) {
    if (!o) return mk((node*)NULL, (node*)NULL);

    if (k >= __Size(o -> ch[0]) + 1) {
        k -= __Size(o -> ch[0]) + 1;
        pii y = Split(o -> ch[1], k);
        o -> ch[1] = y.fi;
        o -> Maintain();
        y.fi = o;
        return y;
    }

    else {
        pii y = Split(o -> ch[0], k);
        o -> ch[0] = y.se;
        o -> Maintain();
        y.se = o;
        return y;
    }
}

inline node* merge(node *x, node *y) {
    if (!x || !y) return x != NULL ? x : y;

    if (x -> fix > y -> fix) {
        x -> ch[1] = merge(x -> ch[1], y);
        x -> Maintain();
        return x;
    }

    else {
        y -> ch[0] = merge(x, y -> ch[0]);
        y -> Maintain();
        return y;
    }
}

inline void Insert(Point val) {
    int __Rank = Rank(root, val[0]) - 1;
    node *x = Kth(root, __Rank), *y = Kth(root, __Rank + 1);
    if ((y -> val - val) * (x -> val - val) > 0) return;
    pii Ans = Split(root, __Rank);
    int L = Ans.fi -> Size, R = 0;
    node *xx = Kth(Ans.fi, Ans.fi -> Size - 1), *yy = Kth(Ans.se, 2);
    while (xx && (x -> val - xx -> val) * (val - xx -> val) >= 0) -- L, x = xx, xx = Kth(Ans.fi, L - 1);
    while (yy && (y -> val - yy -> val) * (val - yy -> val) <= 0) ++ R, y = yy, yy = Kth(Ans.se, R + 2);
    root = merge(merge(Split(Ans.fi, L).fi, new node(val)), Split(Ans.se, R).se);
}

int main() {
    n = read(), x = read(), y = read();
    root = new node((Point){x, y});
    root -> ch[0] = new node((Point){0, 0});
    root -> ch[1] = new node((Point){n, 0});
    root -> Maintain();  
    m = read();
    for (int i = 1; i <= m; ++i) pt[i][0] = read(), pt[i][1] = read(); 
    Q = read(); int tot = 0; 
    for (int i = 1; i <= Q; ++i) op[i].in();
    for (int i = 1; i <= m; ++i) if (!vis[i]) Insert(pt[i]);
    for (int i = Q; i; --i) {
        if (op[i].op == 2) Ans[++tot] = root -> Sum;
        else Insert(pt[op[i].val]);
    }
    for (int i = tot; i; --i) printf("%.2f\n", Ans[i]);
    return 0;
}