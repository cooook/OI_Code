# pragma GCC optimize("O3")
# include <bits/stdc++.h>
const int inf = 0x3f3f3f3f; 
const int mod = 1e9 + 7;
const int MAXN = 5e4 + 5; 
int n; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct value {
    int h, key, id; 
    inline bool operator < (const value &a) const {
        return key == a.key ? h < a.h : key < a.key; 
    }
} val[MAXN];

inline bool cmp1(const value &a, const value &b) {
    return a.h == b.h ? a.key < b.key : a.h < b.h;  
}

inline bool cmp2(const value &a, const value &b) {
    return a.h == b.h ? a.key < b.key : a.h > b.h;  
}

std::set<value> s; 

struct node {
    node *ls, *rs;
    int add, mn;
    node() { ls = rs = NULL; add = 0; mn = inf; }
    inline void Add(int x) {
        add += x; mn += x;
    }
    inline void Maintain() {
        mn = std::min(ls -> mn, rs -> mn);
    }
    inline void Push_down() {
        if (add) ls -> Add(add), rs -> Add(add), add = 0;
    }
}*root;

inline void build(node *&o, int l, int r) {
    o = new node();
    if (l == r) return o -> mn = val[l].key, void();
    register int mid = l + r >> 1;
    build(o -> ls, l, mid), build(o -> rs, mid + 1, r);
    o -> Maintain();
}

inline void Update(node *o, int l, int r, int x, int y, int val) {
    if (x <= l && r <= y) return o -> Add(val), void();
    o -> Push_down();
    register int mid = l + r >> 1;
    if (x <= mid) Update(o -> ls, l, mid, x, y, val);
    if (mid < y) Update(o -> rs, mid + 1, r, x, y, val);
    o -> Maintain(); 
}

inline void Set(node *o, int l, int r, int x) {
    if (l == r) return o -> mn = inf, void();
    o -> Push_down();
    register int mid = l + r >> 1;
    if (x <= mid) Set(o -> ls, l, mid, x);
    else Set(o -> rs, mid + 1, r, x);
    o -> Maintain();
}

inline void Work() {
    node *o = root;
    register int l = 1, r = n, mid;
    while (l < r) {
        o -> Push_down();
        mid = l + r >> 1;
        if (o -> ls -> mn == 1) o = o -> ls, r = mid;
        else o = o -> rs, l = mid + 1;
    }
    printf("%d %d\n", val[l].key, val[l].h);
    Update(root, 1, n, 1, l, -1);
    Set(root, 1, n, l);
    s.erase(val[l]); 
}

int main() {
    n = read(); 
    for (int i = 1; i <= n; ++i) 
        val[i].h = read(), val[i].key = read();
    std::sort(&val[1], &val[n + 1], cmp2);
    int Ans = 1, cnt, pos; val[0].h = 0x7fffffff;
    for (int i = 1; i <= n; ++i) {
        if (val[i].h != val[i - 1].h) cnt = 0, pos = i;
        else ++ cnt;  
        Ans = 1ll * Ans * (std::min(pos, val[i].key) + cnt) % mod;
    }
    printf("%d\n", Ans);

    std::sort(&val[1], &val[n + 1], cmp1); 

    build(root, 1, n); 

    for (int i = 1; i <= n; ++i) {
        val[i].id = i; 
        s.insert(val[i]);  
    } 

    for (int i = 1; i <= n; ++i) {
        if (root -> mn > 1) {
            value tmp = *s.begin();
            s.erase(tmp); 
            printf("%d %d\n", tmp.key, tmp.h);
            Update(root, 1, n, 1, tmp.id, -1);
            Set(root, 1, n, tmp.id);
        }
        else Work(); 
    }
    return 0; 
}