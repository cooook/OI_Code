# pragma GCC optimize("O3")
# include <bits/stdc++.h> 
# define mid (l + r >> 1)
const int MAXN = 1e5 + 5;
const int inf = 0x3f3f3f3f; 
int cnt = -1, tot, n, m;


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline bool gmax(int &a, const int &b) {
    return a < b ? a = b, true : false; 
}

inline bool gmin(int &a, const int &b) {
    return a > b ? a = b, true : false; 
}

struct qujian {
    int l, r;
} st[MAXN]; 

struct node {
    node *ls, *rs;
    int mx, mn, lmn, lmx, rmn, rmx, l_mn_pos, l_mx_pos, r_mn_pos, r_mx_pos, lmaxn, rmaxn, lminn, rminn, Sum;
    bool tag;
    inline void rev() {
        Sum = -Sum; tag ^= 1;
        std::swap(mx, mn);
        std::swap(lmn, lmx);
        std::swap(rmn, rmx);
        std::swap(l_mn_pos, l_mx_pos);
        std::swap(r_mn_pos, r_mx_pos);
        std::swap(lmaxn, lminn);
        std::swap(rmaxn, rminn);
        mx = -mx; mn = -mn; lmn = -lmn; rmn = -rmn; lmx = -lmx; rmx = -rmx; 
    }
    inline void Push_down() {
        if (tag) {
            if (ls) ls -> rev();
            if (rs) rs -> rev();
            tag ^= 1;
        }
    }
    inline void Maintain() {
        Sum = ls -> Sum + rs -> Sum;

        lmn = ls -> lmn; l_mn_pos = ls -> l_mn_pos; 
        if (gmin(lmn, ls -> Sum + rs -> lmn)) l_mn_pos = rs -> l_mn_pos;

        rmn = rs -> rmn; r_mn_pos = rs -> r_mn_pos;
        if (gmin(rmn, rs -> Sum + ls -> rmn)) r_mn_pos = ls -> r_mn_pos;

        lmx = ls -> lmx; l_mx_pos = ls -> l_mx_pos;
        if (gmax(lmx, ls -> Sum + rs -> lmx)) l_mx_pos = rs -> l_mx_pos;

        rmx = rs -> rmx; r_mx_pos = rs -> r_mx_pos;
        if (gmax(rmx, rs -> Sum + ls -> rmx)) r_mx_pos = ls -> r_mx_pos;

        mx = ls -> mx; gmax(mx, rs -> mx); gmax(mx, ls -> rmx + rs -> lmx);
        if (mx == ls -> mx) lmaxn = ls -> lmaxn, rmaxn = ls -> rmaxn;
        else if (mx == rs -> mx) lmaxn = rs -> lmaxn, rmaxn = rs -> rmaxn;
        else lmaxn = ls -> r_mx_pos, rmaxn = rs -> l_mx_pos;

        mn = ls -> mn; gmin(mn, rs -> mn); gmin(mn, ls -> rmn + rs -> lmn);
        if (mn == ls -> mn) lminn = ls -> lminn, rminn = ls -> rminn;
        else if (mn == rs -> mn) lminn = rs -> lminn, rminn = rs -> rminn;
        else lminn = ls -> r_mn_pos, rminn = rs -> l_mn_pos;
    }

    inline void get(int pos, int val) {
        if (val > 0) {
            lmx = rmx = mx = val;
            lmn = rmn = mn = 0;
            l_mn_pos = pos - 1; r_mn_pos = pos + 1; lminn = rminn = pos; 
            l_mx_pos = r_mx_pos = lmaxn = rmaxn = pos; 
        }
        else {
            lmx = rmx = mx = 0;
            lmn = rmn = mn = val;
            l_mn_pos = r_mn_pos = lminn = rminn = pos;
            l_mx_pos = pos - 1; r_mx_pos = pos + 1; lmaxn = rmaxn = pos; 
        }
        Sum = val; 
    }
}*root, mempool[MAXN << 2];

inline node* newnode() {
    return &mempool[++cnt];
}

inline void build(node *&o, int l, int r) {
    o = newnode();
    if (l == r) {
        o -> get(l, read());
        o -> l_mn_pos = o -> r_mn_pos = o -> l_mx_pos = o -> r_mx_pos
         = o -> lmaxn = o -> rmaxn = o -> lminn = o -> rminn = l;
        return; 
    }
    build(o -> ls, l, mid); build(o -> rs, mid + 1, r);
    o -> Maintain(); 
}

inline void Update(node *o, int l, int r, int x, int y) {
    if (l == r) return o -> get(x, y), void();
    o -> Push_down();
    if (x <= mid) Update(o -> ls, l, mid, x, y);
    else Update(o -> rs, mid + 1, r, x, y);
    o -> Maintain(); 
}

inline void Filp(node *o, int l, int r, int x, int y) {
    if (x == l && r == y) return o -> rev(), void();
    o -> Push_down();
    if (y <= mid) Filp(o -> ls, l, mid, x, y);
    else if (x > mid) Filp(o -> rs, mid + 1, r, x, y);
    else Filp(o -> ls, l, mid, x, mid), Filp(o -> rs, mid + 1, r, mid + 1, y);
    o -> Maintain(); 
}

inline node* Query(node *o, int l, int r, int x, int y) {
    if (x == l && r == y) return o;
    o -> Push_down(); 
    if (y <= mid) return Query(o -> ls, l, mid, x, y);
    else if (x > mid) return Query(o -> rs, mid + 1, r, x, y);
    else {
        node *t = newnode(); t -> ls = Query(o -> ls, l, mid, x, mid);
        t -> rs = Query(o -> rs, mid + 1, r, mid + 1, y); 
        t -> Maintain();
        return t; 
    }
}

int main() {
    n = read(); m = read();
    build(root, 1, n); tot = cnt;
    register int opt, l, r, x, top = 0, Ans; register node *t; 
    while (m --) {
        opt = read(); l = read(), r = read();
        if (!opt) Update(root, 1, n, l, r); 
        else {
            x = read();
            cnt = tot; Ans = 0;
            while (x --) {
                t = Query(root, 1, n, l, r);
                if (t -> mx == 0) break; 
                Ans += t -> mx;
                st[++top] = (qujian){t -> lmaxn, t -> rmaxn};
                Filp(root, 1, n, t -> lmaxn, t -> rmaxn);
            }
            for (; top; --top) Filp(root, 1, n, st[top].l, st[top].r);
            printf("%d\n", Ans);
        }
    }
    return 0; 
}