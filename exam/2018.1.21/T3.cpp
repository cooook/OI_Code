// # pragma GCC optimize("O3")
# include <bits/stdc++.h>
const int MAXN = 5e6 + 5; 
const int N = 5e6;
typedef long long ll; 
int n, m, k, mu[MAXN], prime[MAXN], cnt, Sum[MAXN], f[2005];
bool _prime[MAXN];


std::map<int, int> QAQ[2005];

inline ll F(int n) {
    return 1ll * (n / k) * f[k] + f[n % k];
}

inline void Init() {
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!_prime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i <= N; j++) {
            _prime[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= N; i++) Sum[i] = Sum[i - 1] + mu[i];
    for (int i = 1; i <= k; i++) f[i] = f[i - 1] + (std::__gcd(i, k) == 1);
}

struct Hash_table{
    # define Key 76543
    int first[Key + 1], e;
    Hash_table() {e = 1;}

    struct edge{
        int u, v, next;
    }a[Key + 1];
    
    inline bool count(int x) {
        for (int i = first[x % Key]; i; i = a[i].next) if (a[i].u == x) return true;
        return false;
    }

    inline int& New(int u) {
        a[e].u = u; a[e].next = first[u % Key]; first[u % Key] = e ++;
        return a[e - 1].v;
    }

    inline int& operator [] (const int &x) {
        for (int i = first[x % Key]; i; i = a[i].next) if (a[i].u == x) return a[i].v;
        return New(x);
    }
}ma;

inline int Mu(int n) {
    if (n <= N) return Sum[n];
    if (ma.count(n)) return ma[n];
    int Ans = 1, last;
    for (int i = 2; i <= n; i = last + 1) {
        last = n / (n / i);
        Ans -= (last - i + 1) * Mu(n / i); 
    }
    ma[n] = Ans;
    return Ans;
}

inline ll G(int x, int k) {
    if (k == 1) return Mu(x);
    if (x == 0) return 0;
    if (QAQ[k].count(x)) return QAQ[k][x];
    ll Ans = 0;
    for (int i = 1; i * i <= k; i++)
        if (k % i == 0) {
            if (mu[i]) Ans += mu[i] * mu[i] * G(x / i, i);
            if (i * i != k && mu[k / i]) Ans += mu[k / i] * mu[k / i] * G(x / (k / i), k / i);
        }
    return QAQ[k][x] = Ans;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    Init();
    ll Ans = 0; int last;
    for (int i = 1; i <= n && i <= m; i = last + 1) {
        last = std::min(n / (n / i), m / (m / i));
        Ans += (G(last, k) - G(i - 1, k)) * (n / i) * F(m / i);
    }
    printf("%lld\n", Ans);
    return 0;
}