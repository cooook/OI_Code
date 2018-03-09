# include <bits/stdc++.h> 
const int MAXN = 1e5 + 5; 
# define int long long 
int n, z, cnt1, cnt2, Ans[MAXN], cnt; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct mk {
    int fi, se, id; 
    mk() {  }
    mk(int fi, int se, int id = 0):fi(fi), se(se), id(id) {  }  
    inline bool operator < (const mk &a) const {
        return a.fi == fi ? se < a.se : fi < a.fi; 
    }
} val[MAXN], h[MAXN], l[MAXN];

inline bool cmp(const mk &a, const mk &b) {
    return a.fi > b.fi; 
}

signed main() {
    // freopen("Cooook.in","r",stdin);
    // freopen("Cooook.out","w",stdout);?
    n = read(), z = read(); 
    for (int i = 1; i <= n; ++i) {
        val[i].fi = read(), val[i].se = read();
        if (val[i].fi - val[i].se <= 0) h[++cnt1] = mk(val[i].fi, val[i].se - val[i].fi, i);
        else l[++cnt2] = mk(val[i].se, val[i].fi - val[i].se, i); 
    }
    std::sort(&h[1], &h[cnt1 + 1]);
    for (int i = 1; i <= cnt1; ++i)
        if (z <= h[i].fi) return puts("NIE"), 0;
        else z += h[i].se, Ans[++cnt] = h[i].id;  
    std::sort(&l[1], &l[cnt2 + 1], cmp);
    for (int i = 1; i <= cnt2; ++i) 
        if (z <= l[i].fi + l[i].se) return puts("NIE"), 0;
        else z -= l[i].se, Ans[++cnt] = l[i].id; 
    puts("TAK");
    for (int i = 1; i <= cnt; ++i) printf("%lld%c", Ans[i], " \n"[i == cnt]); 
    // while (true); 
    return 0;
}

// d + 1, d - a, 