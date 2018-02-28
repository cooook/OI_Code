# include <stdio.h> 
# include <cstring>
# include <iostream> 

# define INF { puts("Infinity"); exit(0); }

const int MAXN = 1e6 + 5; 

char s[105][100005];
int f[MAXN][2], id[105][100005][2], st[MAXN], end[MAXN], from[MAXN], last, first[MAXN], e = 1, n;
bool vis[MAXN][2], used[MAXN][2]; 

inline void gmax(int &a, const int &b) {
    if (a < b) a = b;
}

namespace Suffix {
    const int MAXM = MAXN;
    int fa[MAXM], trans[MAXM][26], Mx[MAXM], cnt, st[MAXM << 1][20], bin[20], Log[MAXM], dfn[MAXM], idx; 
    inline void Init() { last = ++ cnt; }
    inline int Extend(int c) {
        int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1;
        for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
        if (!p) fa[np] = 1;
        else {
            int q = trans[p][c];
            if (Mx[q] == Mx[p] + 1) fa[np] = q;
            else {
                register int nq = ++ cnt; Mx[nq] = Mx[p] + 1;
                fa[nq] = fa[q]; fa[q] = fa[np] = nq;
                memcpy(trans[nq], trans[q], sizeof trans[q]);
                for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
            }
        }
        return last = np;
    }

    struct edge {
        int u, v, next;
    } a[MAXM];

    inline void push(int u, int v) {
        a[e].u = u; a[e].v = v; a[e].next = first[u]; first[u] = e++;
    }

    inline void dfs(int u) {
        st[dfn[u] = ++idx][0] = Mx[u];
        for (int i = first[u]; i; i = a[i].next) {
            register int v = a[i].v; 
            dfs(v), st[++idx][0] = Mx[u]; 
        }
    }

    inline void Build() {
        for (int i = 2; i <= cnt; ++i) push(fa[i], i);
        dfs(1); bin[0] = 1; Log[1] = 0;
        for (int i = 1; i <= 18; ++i) bin[i] = bin[i - 1] << 1;
        for (int i = 2; i <= idx; ++i) Log[i] = Log[i >> 1] + 1; 
        for (int j = 1; j <= 18; ++j)
            for (int i = 1; i + bin[j - 1] - 1 <= idx; ++i)
                st[i][j] = std::min(st[i][j - 1], st[i + bin[j - 1]][j - 1]);
    }

    inline int Query(int x, int y) {
        x = dfn[x], y = dfn[y];
        if (x > y) std::swap(x, y);
        int lg = Log[y - x + 1];
        return std::min(st[x][lg], st[y - bin[lg] + 1][lg]);
    }
}

inline int find(int u, int op) { // 
    using Suffix::Query;
    if (vis[u][op]) INF
    if (used[u][op]) return f[u][op];
    vis[u][op] = true; used[u][op] = true; 
    int len, l, r;
    if (op) {
        for (int i = 1; i <= n; ++i) {
            len = Query(id[from[u]][u - st[from[u]] + 1][0], id[i][end[i] - st[i] + 1][1]);
            // printf("from = %d u = %d i = %d len = %d\n", from[u], u - st[from[u]] + 1, i, len);
            l = end[i] - len + 1, r = u + len - 1; 
            if (l == st[i] && r == end[from[u]]) INF //////////////////////////////
            else if (l != st[i] && r != end[from[u]]) gmax(f[u][op], len << 1);
            else if (l == st[i]) gmax(f[u][op], len * 2 + find(r + 1, 1));
            else gmax(f[u][op], len * 2 + find(l - 1, 0));
        }
    }
    else {
        for (int i = 1; i <= n; ++i) {
            len = Query(id[from[u]][u - st[from[u]] + 1][1], id[i][1][0]);
            l = u - len + 1, r = st[i] + len - 1; 
            if (l == st[from[u]] && r == end[i]) INF  //////////////////////////////
            else if (l != st[from[u]] && r != end[i]) gmax(f[u][op], len << 1);
            else if (l == st[from[u]]) gmax(f[u][op], len * 2 + find(r + 1, 1));
            else if (r == end[i]) gmax(f[u][op], len * 2 + find(l - 1, 0));
        }
    }

    vis[u][op] = false; 
    return f[u][op]; 
}

int main() {
    // freopen("T3.in","r",stdin);
    // freopen("T3.out","w",stdout);
    using Suffix::Extend;
    using Suffix::Query;
    scanf("%d", &n);  Suffix::Init();  
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
        int len = strlen(s[i] + 1);
        st[i] = end[i - 1] + 1;
        end[i] = end[i - 1]; 
        last = 1;
        for (int j = 1; s[i][j]; ++j) ++ end[i], from[end[i]] = i, id[i][j][1] = Extend(s[i][j] - 'a');
        last = 1;
        for (int j = len; j; --j) id[i][j][0] = Extend(s[i][j] - 'a');
    }

    Suffix::Build(); 

    register int Ans = 0;

    for (int i = 1; i <= n; ++i) {
        int len, l, r; 
        for (int j = st[i]; j <= end[i]; ++j) {
            len = Query(id[i][j - st[i] + 1][0], id[i][j - st[i] + 1][1]);
            l = j - len + 1, r = j + len - 1; 
            if (l == st[i] && r == end[i]) INF
            else if (l != st[i] && r != end[i]) gmax(Ans, len * 2 - 1);
            else if (l == st[i]) gmax(Ans, len * 2 - 1 + find(r + 1, 1));
            else gmax(Ans, len * 2 - 1 + find(l - 1, 0));


            len = Query(id[i][j - st[i] + 2][0], id[i][j - st[i] + 1][1]);
            l = j - len + 1; r = j + len;
            if (l == st[i] && r == end[i]) INF
            else if (l != st[i] && r != end[i]) gmax(Ans, len * 2);
            else if (l == st[i]) gmax(Ans, len * 2 + find(r + 1, 1));
            else gmax(Ans, len * 2 + find(l - 1, 0));
        }
    } 

    for (int i = 1; i <= n; ++i) gmax(Ans, find(st[i], 1)), gmax(Ans, find(end[i], 0));
    printf("%d\n", Ans);
    // while (true); 
    return 0;
}