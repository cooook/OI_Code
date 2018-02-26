#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1000000007,MAXL = 75,MAXN = 100005;
int m,cnt,in[MAXN],out[MAXN],f[MAXN],first[MAXN],e = 1; 
string A,B;
std::map<string,int> ma;


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN];

inline void push(int u,int v) {
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline void tuopu() {
    std::queue<int> Q;
    for (int i = 1; i <= cnt; i++) if (!in[i]) Q.push(i),f[i] = 1;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = first[u]; i; i = a[i].next) {
            (f[a[i].v] += f[u]) %= mod;
            in[a[i].v] --;
            if (!in[a[i].v]) Q.push(a[i].v);
        }
    }
    int Ans = 0;
    for (int i = 1; i <= cnt; i++)
        if (!out[i]) (Ans += f[i]) %= mod;
    printf("%lld\n",Ans);
}

signed main() {
    m = read<int>();
    for (int i = 1; i <= m; i++) {
        cin >> A >> B;
        if (!ma.count(A)) ma[A] = ++ cnt;
        if (!ma.count(B)) ma[B] = ++ cnt;
        push(ma[B],ma[A]);
        in[ma[A]] ++; out[ma[B]] ++;
    }
    tuopu();
    // getchar(); getchar();
    return 0;
}