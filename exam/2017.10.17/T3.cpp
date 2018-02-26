#pragma GCC optimize("O3")
#include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 300005, mod = 1e9 + 7;

int n, size[MAXN], first[MAXN], b[MAXN], e = 1, son[MAXN], len;
int du[MAXN], tree[MAXN], back[MAXN], id[MAXN];
bool flag = false;

ll fac[MAXN], f[MAXN], Ans;

std::set<int> G[MAXN];

template <typename _t>
inline _t read()
{
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -f;
    for (; isdigit(ch); ch = getchar())
        x = x * 10 + (ch ^ 48);
    return x * f;
}

#define lowbit(x) ((x) & (-x))

inline void Update(int x, int val)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += val;
}

inline int Query(int x)
{
    int Ans = 0;
    for (; x; x -= lowbit(x))
        Ans += tree[x];
    return Ans;
}

struct edge
{
    int u, v, next;
} a[MAXN << 1];

inline void push(int u, int v)
{
    a[e].u = u;
    a[e].v = v;
    a[e].next = first[u];
    first[u] = e++;
}

inline ll qpow(ll x, ll k)
{
    ll Ans = 1;
    for (; k; k >>= 1, x = x * x % mod)
        if (k & 1)
            Ans = Ans * x % mod;
    return Ans;
}

inline void dfs(int u, int fa)
{
    son[u] = 0;
    size[u] = 1;
    f[u] = 1;
    for (int i = first[u]; i; i = a[i].next)
        if (a[i].v != fa)
        {
            dfs(a[i].v, u);
            f[u] = f[u] * f[a[i].v] % mod;
            G[u].insert(a[i].v);
            son[u]++;
            size[u] += size[a[i].v];
        }
    f[u] = f[u] * fac[son[u]] % mod;
    if (size[u] == 1)
        return;
    std::set<int>::iterator it = G[u].begin();
    while (it != G[u].end())
        id[*it] = ++len, Update(len, 1), ++it;
    Update(len + 1, -G[u].size());
    back[u] = len + 1;
}

inline void dp(int u, ll last, int x)
{
    if (flag)
        return;
    ll tmp = 1;
    std::set<int>::iterator it = G[u].begin();
    while (it != G[u].end())
        tmp = tmp * f[*it] % mod, ++it;
    while (!G[u].empty())
    {
        if (flag)
            return;
        it = G[u].lower_bound(b[x]);
        if (it == G[u].end())
        {
            (Ans += tmp * fac[G[u].size()] % mod * last % mod) %= mod;
            return flag = true, void();
        }
        if (*it > b[x])
        {
            (Ans += tmp * fac[G[u].size() - 1] % mod * last % mod * (Query(id[*it]) - 1) % mod) %= mod;
            return flag = true, void();
        }
        (Ans += tmp * fac[G[u].size() - 1] % mod * last % mod * (Query(id[*it]) - 1) % mod) %= mod;
        tmp = tmp * qpow(f[*it], mod - 2) % mod;
        dp(*it, tmp * fac[G[u].size() - 1] % mod * last % mod, x + 1);
        if (flag)
            return;
        x += size[*it];
        Update(id[*it], -1);
        Update(back[u], 1);
        G[u].erase(it);
    }
}

int main()
{
    n = read<int>();
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % mod;
    for (int i = 1; i <= n; i++)
        b[i] = read<int>();
    for (int i = 1; i < n; i++)
    {
        register int u = read<int>(), v = read<int>();
        push(u, v);
        push(v, u);
        du[u]++;
        du[v]++;
    }
    ll Pre_Ans = 1;
    for (int i = 1; i <= n; i++)
        Pre_Ans = Pre_Ans * fac[du[i] - 1] % mod;
    for (int i = 1; i < b[1]; i++)
        (Ans += Pre_Ans * du[i] % mod) %= mod;
    dfs(b[1], 0);
    dp(b[1], 1, 2);
    printf("%lld\n", Ans);
    // for (;;);
    return 0;
}