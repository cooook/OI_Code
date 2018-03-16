# include <bits/stdc++.h> 
# define RG register 
const int P = 76543; 
const int MAXN = 3e6 + 5;
const int mod = 1e9 + 7;
typedef unsigned long long ull;
char s[MAXN], tmp[MAXN]; int n, m, cnt, trans[MAXN][4], first[MAXN], e = 1, A[MAXN], B[MAXN], __Size[MAXN]; 
ull v[MAXN], Ori[MAXN], Rev[MAXN], xp[MAXN];
 
  
inline int id(char c) {
    if (c == 'A') return 0;
    else if (c == 'C') return 1;
    else if (c == 'G') return 2;
    else return 3; 
}
 
struct Hash_table {
    const int MOD = 612497;
    struct edge {
        ull u; int val, next;
    } a[MAXN]; 
    inline int& Link(ull u) {
        a[e].u = u; a[e].val = 0; a[e].next = first[u % MOD]; first[u % MOD] = e ++;
        return a[e - 1].val; 
    }
    inline bool count(ull x) {
        for (int i = first[x % MOD]; i; i = a[i].next)
            if (a[i].u == x) return true;
        return false; 
    }
    inline int& operator [] (const ull &x) {
        for (int i = first[x % MOD]; i; i = a[i].next)
            if (a[i].u == x) return a[i].val;
        return Link(x);
    }
}ma;
 
inline void Insert(char *s) {
    RG int o = 0;
    for (int i = 1; s[i]; ++i) {
        if (!trans[o][id(s[i])]) {
            trans[o][id(s[i])] = ++ cnt; 
            v[cnt] = v[o] * P + id(s[i]) + 1; 
        }
        o = trans[o][id(s[i])]; 
        ++ __Size[o]; 
    }
}
 
inline void dfs(int x) {
    for (int i = 0; i < 4; ++i)
        if (trans[x][i]) __Size[trans[x][i]] += __Size[x], dfs(trans[x][i]);
}
 
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    scanf("%d", &m);
    while (m --) {
        scanf("%s", tmp + 1);
        Insert(tmp);
    }
    for (int i = 0; i <= cnt; ++i) ma[v[i]] = i;  
    dfs(0);  xp[0] = 1;
    for (int i = 1; i <= n; ++i) xp[i] = xp[i - 1] * P; 
    for (int i = n; i; --i) Ori[i] = Ori[i + 1] * P + id(s[i]) + 1;
    for (int i = 1; i <= n; ++i) Rev[i] = Rev[i - 1] * P + id(s[i]) + 1;
    for (int i = 1; i <= n; ++i) {
        RG int l = i, r = n, mid, Ans = 0;
        while (l <= r) {
            mid = l + r >> 1;
            if (ma.count(Rev[mid] - Rev[i - 1] * xp[mid - i + 1])) Ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        if (Ans) B[i] += __Size[ma[Rev[Ans] - Rev[i - 1] * xp[Ans - i + 1]]];
    }
    for (int i = 1; i <= n; ++i) {
        RG int l = 1, r = i, mid, Ans = 0;
        while (l <= r) {
            mid = l + r >> 1;
            if (ma.count(Ori[mid] - Ori[i + 1] * xp[i - mid + 1])) Ans = mid, r = mid - 1;
            else l = mid + 1; 
        }
        if (Ans) A[i] += __Size[ma[Ori[Ans] - Ori[i + 1] * xp[i - Ans + 1]]];
    }
    RG int Ans = 0;
    for (int i = 1; i <= n; ++i)
        (Ans += 1ll * A[i] * B[i + 1] % mod) %= mod;
    printf("%d\n", Ans);
    return 0;
}