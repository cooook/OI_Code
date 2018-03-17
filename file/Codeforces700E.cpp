# include <bits/stdc++.h> 
# define RG register 
const int MAXN = 4e5 + 5; 
int trans[MAXN][26], fa[MAXN], Mx[MAXN], id[MAXN], last, cnt, n, g[MAXN], f[MAXN], first[MAXN], e = 1, Ans;  
char s[MAXN]; 


inline void gmax(int &x, const int &y) {
    if (x < y) x = y; 
}

struct edge {
    int u, v, next;
} a[MAXN];

inline void push(int u, int v) {
    a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
}

struct node {
    node *ls, *rs;
    node() { ls = rs = NULL; }
    inline void* operator new (size_t);
} *root[MAXN], *C, *mempool;

inline void* node::operator new (size_t) {
    if (C == mempool) C = new node[1 << 15], mempool = C + (1 << 15);
    return C ++;
} 

inline void Update(node *&o, int l, int r, int x) {
    if (!x) return ;
    if (!o) o = new node();
    if (l == r) return ;
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x);
    else Update(o -> rs, mid + 1, r, x);
}

inline node* merge(node *x, node *y) {
    if (!x || !y) return !x ? y : x;
    node *o = new node();
    o -> ls = merge(x -> ls, y -> ls);
    o -> rs = merge(x -> rs, y -> rs);
    return o;
}

inline bool Query(node *o, int l, int r, int x, int y) {
    if (!o) return false; 
    if (x <= l && r <= y) return true;
    register int mid = l + r >> 1;
    if (x <= mid && Query(o -> ls, l, mid, x, y)) return true;
    if (mid < y && Query(o -> rs, mid + 1, r, x, y)) return true;
    return false;   
}

inline void Extend(int x, int c) {
    RG int np = ++ cnt, p = last; Mx[np] = Mx[last] + 1; id[np] = x; 
    for (; !trans[p][c]; p = fa[p]) trans[p][c] = np;  
    if (!p) fa[np] = 1;
    else {
        RG int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            RG int nq = ++ cnt; Mx[nq] = Mx[p] + 1; id[nq] = x; 
            fa[nq] = fa[q]; fa[q] = fa[np] = nq; 
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq; 
        }
    } last = np;
}

inline void dfs(int u) {
    Update(root[u], 1, n, id[u]);
    for (RG int i = first[u], v; i; i = a[i].next) 
        dfs(a[i].v), root[u] = merge(root[u], root[a[i].v]);
}

inline void dp(int u) {
    for (int i = first[u], v; i; i = a[i].next) {
        v = a[i].v;
        if (u == 1) f[v] = 1, g[v] = v; 
        else if (Query(root[g[u]], 1, n, id[v] - Mx[v] + Mx[g[u]], id[v] - 1)) f[v] = f[u] + 1, g[v] = v;
        else f[v] = f[u], g[v] = g[u]; 
        dp(v); 
    }
    gmax(Ans, f[u]);
}

int main() {
    scanf("%d%s", &n, s + 1);
    last = ++ cnt; 
    for (int i = 1; s[i]; ++i) Extend(i, s[i] - 'a');
    for (int i = 2; i <= cnt; ++i) push(fa[i], i);
    dfs(1); dp(1); 
    printf("%d\n", Ans);
    return 0; 
}