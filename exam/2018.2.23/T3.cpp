# include <bits/stdc++.h> 
# define Debug
const int MAXN = 50005;
const int inf = 0x3f3f3f3f;
int n, m, first[MAXN], e = 1, f[MAXN];


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS ++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmax(int &a, const int &b) {
    if (a < b) a = b;
}

struct My_Queue {
    std::priority_queue<int> Q, D;
    inline void push(int x) { Q.push(x); }
    inline void pop(int x) { D.push(x); }
    inline int size() { return Q.size() - D.size(); }
    inline int top() {
        while (!D.empty() && Q.top() == D.top()) Q.pop(), D.pop();
        return Q.empty() ? -inf : Q.top();
    }
}; 

struct edge {
    int u, v, next;
} a[MAXN << 1];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

struct node {
    node *ch[2], *f;
    int tag, size, mx, wtf;  My_Queue val;
# ifdef Debug
    int id;
# endif
    inline void Maintain(); 
    inline void rotate();
    inline void Push_down();
    inline void rev();
    inline bool isrt();
    inline bool dir();
    inline void Splay();
}null[MAXN], *tree[MAXN];

inline void Print() {
    puts("---------------------------------------------------");
    for (int i = 1; i <= n; ++i)
        printf("i = %d mx = %d vch = %d Visual_Size = %d\n", i, tree[i] -> mx, tree[i] -> val.top(), tree[i] -> val.size() - 1);
    puts("---------------------------------------------------");
}

inline void node::Maintain() {
    if (this == null) return ;
    size = ch[0] -> size + ch[1] -> size + 1;
    mx = 0; wtf = 0;
    gmax(mx, val.top() + ch[0] -> size);
    gmax(mx, ch[0] -> mx);
    gmax(mx, ch[1] -> mx + ch[0] -> size + 1);
    gmax(wtf, val.top() + ch[1] -> size);
    gmax(wtf, ch[0] -> wtf + ch[1] -> size + 1);
    gmax(wtf, ch[1] -> wtf);
}

inline bool node::isrt() {
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline bool node::dir() {
    return f -> ch[1] == this;
}

inline void node::rev() {
    tag ^= 1; std::swap(ch[0], ch[1]); std::swap(wtf, mx);
}

inline void node::rotate() {
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    this -> f = pa; fa -> f = this; ch[d ^ 1] = fa;
    fa -> Maintain(), Maintain();
}

inline void node::Push_down() {
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}

inline void Down(node *x) {
    if (!x -> isrt()) Down(x -> f);
    x -> Push_down();
}

inline void node::Splay() {
    Down(this);
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()) {
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
}

inline void Access(node *x) {
    node *y = null;
    while (x != null) {
        x -> Splay();
# ifdef Son
        printf("%d hvae real son %d\n", x -> id, y -> id);
# endif 
        if (x -> ch[1] != null) {
            x -> val.push(x -> ch[1] -> mx + 1);
# ifdef Son
            printf("%d have son %d val = %d\n", x -> id, x -> ch[1] -> id, x -> ch[1] -> mx + 1);
# endif 
        }
        if (y != null) {
            x -> val.pop(y -> mx + 1);
# ifdef Son
            printf("%d lose son %d val = %d\n", x -> id, y -> id, y -> mx + 1);
# endif 
        }
        // printf("%d %d %d %d\n", x -> id, x -> ch[0] -> id, y -> mx + 1, y -> size);
        x -> ch[1] = y;
        x -> Maintain();
        // printf("null -> mx = %d %d\n", null -> mx, x -> ch[1] -> mx + x -> ch[0] -> size + 1);
        // printf("x = %d %d\n", x -> id, x -> mx);
        y = x; x = x -> f;
    }
}

inline void Make_root(node *x) {
    Access(x); x -> Splay(); x -> rev();
}

inline void Cut(node *x, node *y) {
    Make_root(x); 
    // printf("id = %d %d\n", x -> id, y -> id);
    // Print(); 
    Access(y); 
    // Print();
    y -> Splay(); 
    y -> ch[0] = null; x -> f = null;
    y -> Maintain();
}

inline void Cut(node *x) {
    Access(x); x -> Splay();
    x -> ch[0] -> f = null;
    x -> ch[0] = null;
    x -> Maintain();
}

inline void Link(node *x, node *y) {
    Make_root(x); y -> Splay(); x -> f = y; 
    y -> val.push(x -> mx + 1); y -> Maintain();
# ifdef Son
    printf("%d have son %d val = %d\n", y -> id, x -> id, x -> mx + 1);
# endif 
}

inline void dfs(int u, int fa) {
    f[u] = 0;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v, u);
        gmax(f[u], f[v] + 1);
        tree[v] -> f = tree[u];
# ifdef Son
        printf("%d have son %d val = %d\n", tree[u] -> id, tree[v] -> id, f[v] + 1);
# endif 
        tree[u] -> val.push(f[v] + 1);
    }
    tree[u] -> Maintain();
}

inline node* find(node *o, int k) {
    while (true) {
        o -> Push_down();
        if (o -> ch[0] -> size + 1 == k) return o;
        if (k > o -> ch[0] -> size) k -= o -> ch[0] -> size + 1, o = o -> ch[1];
        else o = o -> ch[0];
    }
    return 0x0;
} 

inline void dfs__(node *x) {
    if (x == null) return;
    // x -> Push_down();
    dfs__(x -> ch[0]);
# ifdef Debug
    printf("%d\n", x -> id);
# endif 
    dfs__(x -> ch[1]);
}

int main() {
    // freopen("T3.in","r",stdin);
    // freopen("Cooook.out","w",stdout);
    n = read();
    null -> ch[0] = null -> ch[1] = null -> f = null; null -> mx = -inf; null -> wtf = -inf;
    null -> tag = false; null -> size = 0;
    for (int i = 1; i <= n; ++i)
        tree[i] = &null[i], tree[i] -> ch[0] = tree[i] -> ch[1] = tree[i] -> f = null, 
        tree[i] -> tag = false, tree[i] -> size = 1, tree[i] -> val.push(0);

# ifdef Debug
    for (int i = 1; i <= n; ++i) tree[i] -> id = i;
# endif 

    for (int i = 1; i < n; ++i) {
        register int u = read(), v = read();
        push(u, v), push(v, u);
    }
    dfs(1, 0);

    m = read();
    int x, y;
    while (m --) {
        register char ch = getc;
        for (; ch != 'L' && ch != 'Q'; ) ch = getc;
        x = read(), y = read();
        if (ch == 'L') {
            Make_root(tree[y]);
            Cut(tree[x]);
            Link(tree[x], tree[y]);
        }
        else {
            int Ans = 0;
            Make_root(tree[x]); 
            // Access(tree[2]); tree[x] -> Splay();
            // puts("2333333333");
            // dfs__(tree[y]);
            // puts("2333333333");
            Access(tree[y]); 
            // tree[y] -> Splay();
            // puts("2333333333");
            // dfs__(tree[y]);
            // puts("2333333333");
            tree[x] -> Splay(); 
            int size = tree[x] -> size >> 1;
            // printf("size = %d\n", size);
            node *f1 = find(tree[x], size), *f2 = find(tree[x], size + 1);
            // printf("f1 = %d f2 = %d\n", f1 -> id, f2 -> id);

            // Print();

            Cut(f1, f2);

            // Print();

            Make_root(tree[x]); Access(f1);  tree[x] -> Splay();
            gmax(Ans, tree[x] -> mx);
            // printf("size = %d\n", tree[x] -> size);
            // printf("mx = %d\n", tree[x] -> mx);

            

            Make_root(tree[y]); 
            // Print(); 
            Access(f2); tree[y] -> Splay();
            gmax(Ans, tree[y] -> mx);
            // Print();
            // printf("size = %d\n", tree[y] -> size);
            // printf("mx = %d\n", tree[y] -> mx);
            
            printf("%d\n", Ans);

            Link(f1, f2);
        }
        // Make_root(tree[6]); Access(tree[2]); tree[6] -> Splay();
        // puts("233333333");
        // dfs__(tree[6]);
        // puts("233333333");
    }
    // while (true);
    return 0;
}