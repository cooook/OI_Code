#include <bits/stdc++.h>
#define MAXM 10000005
const int mod = 1e9+7;
typedef unsigned long long ull;
int m,c[20],n,a[20];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Hash_Table {
    int first[76545],e;
    struct edge{
        ull u; int v,next;
    }a[MAXM];
    Hash_Table() {memset(first,0,sizeof first); e = 1;}
    inline int& New(ull Hash) {
        a[e].u = Hash;a[e].v = 0;
        a[e].next = first[Hash % 76543];
        first[Hash % 76543] = e++;
        return a[e-1].v;
    }
    inline int& operator [] (ull x) {
        for (int i = first[x%76543]; i; i = a[i].next) if (a[i].u == x) return a[i].v;
        return New(x);
    }
    inline bool count(ull x) {
        for (int i = first[x % 76543]; i; i = a[i].next) if (a[i].u == x) return true;
        return false;
    }
}ma;

#define P 9091

inline int dfs(int x,int last) {
    if (x == n + 1) return 1;  
    int cnt = 0;
    for (int i = 1; i <= m; i++) if (i != last) a[++cnt] = c[i];
    std::sort(&a[1],&a[cnt+1]); a[++cnt] = c[last];
    ull Hash = 0;
    for (int i = 1; i <= cnt; i++) Hash = Hash * P + a[i];
    if (ma.count(Hash)) return ma[Hash];
    int Ans = 0;
    for (int i = 1; i <= m; i++)
        if (c[i] && last != i) {
            c[i] --;
            (Ans += dfs(x+1,i)) %= mod;
            c[i] ++;
        }
    return ma[Hash] = Ans;
}

int main() {
    m = read<int>();
    for (int i = 1; i <= m; i++) c[i] = read<int>(), n += c[i];
    printf("%d\n",dfs(1,0));
    return 0;
}