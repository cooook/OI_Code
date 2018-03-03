# include <bits/stdc++.h> 
const int inf = 0x3f3f3f3f;
int n, m; 


inline int read() {
    register int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &a, const int &b) {
    if (a > b) a = b;
}

struct node {
    node *ls, *rs; 
    int min0, min1, nmin; 
    int l, r, Sumc, tag, minc, TagC; 
    node() { 
        ls = rs = NULL; tag = 0;
        min0 = min1 = inf; minc = inf; 
        nmin = 1; Sumc = TagC = 0;
    }
    inline void Add(int x, int val) {
        min0 += x; if (min1 != inf) min1 += x;
        tag += x; TagC += val; Sumc += val;  
    }
    inline void Push_down() ; 
    inline void Maintain() {
        if (l == r) return ;
        nmin = 0;
        min0 = std::min(ls -> min0, rs -> min0);
        min1 = std::min(ls -> min1, rs -> min1);
        if (min0 == ls -> min0) nmin += ls -> nmin;
        else gmin(min1, ls -> min0);
        if (min0 == rs -> min0) nmin += rs -> nmin;
        else gmin(min1, rs -> min0);
    }
}*root;

inline void build(node *&o, int l, int r) {
    o = new node();
    o -> l = l; o -> r = r;
    int mid = l + r >> 1;
    if (l == r) return o -> min0 = read(), void();
    build(o -> ls, l, mid);
    build(o -> rs, mid + 1, r);
    o -> Maintain(); 
}

inline void Update(node *o, int l, int r, int x) {
    if (!x) return ;
    if (o -> l >= l && o -> r <= r) {
        o -> Add(x, 1);
        return ;
    }
    o -> Push_down(); 
    register int mid = o -> l + o -> r >> 1;
    if (l <= mid) Update(o -> ls, l, r, x);
    if (mid < r) Update(o -> rs, l, r, x);
    o -> Maintain(); 
}

inline void Gmax(node *o, int l, int r, int x) {
    if (x <= o -> min0) return; 
    if (l <= o -> l && o -> r <= r) {
       
        if (x > o -> min0 && x < o -> min1) {
            o -> min0 = x;
            o -> minc = x;
            ++ o -> Sumc;
        }
        else { 
			o -> Push_down();
            Gmax(o -> ls, l, r, x);
            Gmax(o -> rs, l, r, x);
            o -> Maintain();
        }
    }
    else {
        register int mid = o -> l + o -> r >> 1;
        o -> Push_down();
        if (l <= mid) Gmax(o -> ls, l, r, x);
        if (mid < r) Gmax(o -> rs, l, r, x);
        o -> Maintain(); 
    }
}

inline void node::Push_down() {
    if (l == r) return tag = 0, TagC = 0, minc = inf, void(); 
    register int mid = l + r >> 1;
    if (minc != inf) {
        Gmax(ls, l, mid, minc);
        Gmax(rs, mid + 1, r, minc);
        minc = inf; 
    }
    if (tag || TagC) {
        ls -> Add(tag, TagC); rs -> Add(tag, TagC); 
        tag = 0; TagC = 0;
    }
}

inline void Query(node *o, int x) {
    if (o -> l == o -> r) return printf("%d %d\n", o -> min0, o -> Sumc), void();
    o -> Push_down(); 
    register int mid = o -> l + o -> r >> 1;
    if (x <= mid) Query(o -> ls, x);
    else Query(o -> rs, x);
}

int main() {
	freopen("Cooook.in", "r", stdin);
    n = read();
    build(root, 1, n); 
    m = read();
    char opt; int l, r, x; 
    while (m --) {
        opt = getchar();
        for (; opt != 'A' && opt != 'M' && opt != 'Q'; opt = getchar()); 
        if (opt != 'Q') {
            l = read(), r = read(), x = read();
            if (opt == 'A') Update(root, l, r, x);
            else Gmax(root, l, r, x);
        }
        else Query(root, read());
    } 
    return 0; 
}

