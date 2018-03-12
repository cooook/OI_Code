# include <bits/stdc++.h>
# define RG register 
const int MAXN = 1e5 + 5;
const int P = 66191; 
typedef unsigned long long ull; 
int n, cnt1 = 1, cnt2 = 1, ch[MAXN][26], f[MAXN][18], opt[MAXN][2], w[MAXN], cnt = 1, deep[MAXN], fa[MAXN], id[MAXN], in[MAXN], out[MAXN], L[MAXN], R[MAXN], idx;
ull d[MAXN][18], t[MAXN], power[18];  
int id1[MAXN], id2[MAXN], rk[MAXN]; 
long long Ans; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; RG char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct BIT {
    int tree[MAXN], n;
    inline void Update(RG int x, RG int val) { for (; x <= n; x += x & (-x)) tree[x] += val; }
    inline int Sum(RG int x) { 
        RG int Ans = 0; 
        for (; x; x -= x & (-x)) Ans += tree[x]; 
        return Ans; 
    }
}T1, T2;

inline int Link1(const RG int &x, const RG int &c) {
    if (!ch[x][c]) {
        ch[x][c] = ++cnt1;
        w[cnt1] = c + 1; 
        deep[cnt1] = deep[x] + 1; 
        t[cnt1] = t[x] * P + w[cnt1]; 
        fa[cnt1] = x;
    } 
    return id[++ cnt] = ch[x][c]; 
}

inline int Link2(RG int x, RG int c) {
    // printf("x = %d cnt2 = %d\n", x, cnt2);
    f[++cnt2][0] = x; d[cnt2][0] = c + 1;
    for (int i = 1; i <= 17; ++i)
        f[cnt2][i] = f[f[cnt2][i  - 1]][i - 1], 
        d[cnt2][i] = d[cnt2][i - 1] * power[i - 1] + d[f[cnt2][i - 1]][i - 1];
    return cnt2; 
}

inline void dfs(RG int u, RG int fa) {
    in[u] = ++idx;
    for (RG int i = 0; i < 26; ++i)
        if (ch[u][i]) dfs(ch[u][i], u);
    out[u] = ++idx; 
}

inline bool cmp_1(const int &x, const int &y) {
    return t[x] < t[y]; 
}

inline bool cmp_2(int x, int y) {
    for (int i = 17; ~i; --i) if (d[x][i] == d[y][i]) x = f[x][i], y = f[y][i];
    return d[x][0] < d[y][0]; 
}

inline ull Get_Kth(RG int u, RG int k) {
    -- k;
    for (int i = 17; ~i; --i)
        if (k >> i & 1) u = f[u][i];
    return d[u][0]; 
}

inline void Calc(const int &x) {
    RG int father_L = L[fa[x]], father_R = R[fa[x]], l, r, mid, dep = deep[x], W = w[x]; L[x] = father_R + 1, R[x] = father_L - 1; 
    l = father_L, r = father_R;
    while (l <= r) 
        if (Get_Kth(id2[mid = l + r >> 1], dep) >= W) L[x] = mid, r = mid - 1;
        else l = mid + 1; 
    l = father_L, r = father_R;
    while (l <= r)
        if (Get_Kth(id2[mid = l + r >> 1], dep) <= W) R[x] = mid, l = mid + 1; 
        else r = mid - 1;  
}

inline int Trie_ID(const ull &x) {
    RG int l = 1, r = cnt1, mid;
    while (l <= r) {
        mid = l + r >> 1;
        if (t[id1[mid]] == x) return id1[mid]; 
        else if (t[id1[mid]] < x) l = mid + 1;
        else r = mid - 1;
    }
    return 0; 
}

inline void Update1(const int &x) {
    T1.Update(in[x], 1); T1.Update(out[x] + 1, -1); 
    if (L[x] <= R[x]) Ans += T2.Sum(R[x]) - T2.Sum(L[x] - 1);
}

inline void Update2(RG int x) {
    T2.Update(rk[x], 1);
    RG int Now_ID = 1, Tmp_ID, i; 
    RG ull now = 0, last = 0; 
    for (i = 17; ~i; --i)
        if (Tmp_ID = Trie_ID(now = last * power[i] + d[x][i])) 
            Now_ID = Tmp_ID, last = now, x = f[x][i]; 
    Ans += T1.Sum(in[Now_ID]);
}

int main() {
    n = read();
    power[0] = P; id[1] = 1;  Ans = 1;
    RG int i; RG char c; 
    for (i = 1; i <= 17; ++i) power[i] = power[i - 1] * power[i - 1];
    for (i = 1; i <= n; ++i) {
        opt[i][0] = read() - 1, opt[i][1] = read();
        c = getc; 
        while (c < 'a' | c > 'z') c = getc;
        opt[i][1] = opt[i][0] ? Link2(opt[i][1], c - 'a') : Link1(id[opt[i][1]], c - 'a');
    }
    dfs(1, 0);
    for (i = 1; i <= cnt1; ++i) id1[i] = i; 
    for (i = 1; i <= cnt2; ++i) id2[i] = i; 
    std::sort(&id1[1], &id1[cnt1 + 1], cmp_1);
    std::sort(&id2[1], &id2[cnt2 + 1], cmp_2);
    for (i = 1; i <= cnt2; ++i) rk[id2[i]] = i;
    L[1] = 1; R[1] = cnt2; 
    for (i = 2; i <= cnt1; ++i) Calc(i);
    T1.n = idx; T2.n = cnt2; 
    T1.Update(1, 1); T2.Update(1, 1);
    for (i = 1; i <= n; ++i) {
        if (opt[i][0]) Update2(opt[i][1]);
        else Update1(opt[i][1]);
        printf("%lld\n", Ans);
    }
    return 0; 
}