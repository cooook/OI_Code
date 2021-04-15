// # pragma GCC optimize("O3")
# include <bits/stdc++.h>
const int MAXN = 5e6 + 5; 
const int N = 5e6;
typedef long long ll; 
int n, m, k, mu[MAXN], prime[MAXN], cnt, Sum[MAXN], f[2005];
bool _prime[MAXN];


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
        // u ∈ S
        // v ∈ T
        a[e].u = u; a[e].next = first[u % Key]; first[u % Key] = e ++;
        return a[e - 1].v;
    }

    inline int& operator [] (const int &x) {
        // x % Key = y; 
        for (int i = first[x % Key]; i; i = a[i].next) if (a[i].u == x) return a[i].v;
        return New(x);
    }
}ma;

int main() {
    int Hash = 123456789;
    ma[Hash] = 1; 
    return 0;
}