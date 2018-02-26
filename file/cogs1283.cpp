#include <stdio.h>
#include <cstring>
#include <iostream>


#define BASE 1000000000
#define MAXN 2601

typedef long long ll;

int n,m;


template<typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct bignum{
    int a[6],len;
    bignum(){memset(a,0,sizeof a);len = 0;}
    inline bignum operator = (ll x) {
        len = 0;
        memset(a,0,sizeof a);
        while (x) a[++len] = x % BASE,x /= BASE;
        return *this;
    }
    inline bignum operator + (bignum x){
        bignum Ans; Ans.len = std::max(len,x.len) + 1;
        for (int i = 1; i <= Ans.len; i++) Ans.a[i] += a[i] + x.a[i],Ans.a[i+1] += Ans.a[i] / BASE,Ans.a[i] %= BASE;
        while(Ans.len > 1 && Ans.a[Ans.len] == 0) -- Ans.len;
        return Ans;
    }
    inline bignum operator += (const bignum &x){*this = *this + x;return *this;}
    inline void out(){printf("%d",a[len]);for(int i = len - 1; i > 0; i--) printf("%09d",a[i]);puts("");}
    
}Ans;

struct Hash{
    Hash() {clear();}
    int first[MAXN],e;
    struct edge{int u,next;bignum v;}a[MAXN];
    inline void clear(){memset(first,0,sizeof first); e = 1;}
    inline bignum& New(int u) {
        a[e].u = u; a[e].v = 0;
        a[e].next = first[u%MAXN]; first[u%MAXN] = e ++;
        return a[e - 1].v;
    }
    inline bignum& operator [] (int state) {
        for (int i = first[state%MAXN]; i; i = a[i].next) if (a[i].u == state) return a[i].v;
        return New(state);
    }
}f[2];

inline void Set(int &S,int bit,int val) {
    bit = (bit - 1) << 1;
    S |= 3 << bit;
    S ^= 3 << bit;
    S |= val << bit;
}

inline int find(int S,int pos) {
    return (S >> ((pos - 1) << 1)) & 3;
}

inline int Link(int S,int pos) {
    int d = (find(S,pos) == 1)?1:-1,cnt = 0,p;
    for (int i = pos; i && i <= m + 1; i += d) {
        p = find(S,i);
        if (p == 1) cnt ++;
        else if (p == 2) cnt --;
        if (cnt == 0) return i;
    }
    return -1;
}

inline void DP(int x,int y) {
    int now = ((x - 1) * m + y)&1,last = now ^ 1,tot = f[last].e - 1,S,p1,p2; f[now].clear(); bignum val;
    for (int i = 1; i <= tot; i ++) {
        S = f[last].a[i].u; val = f[last].a[i].v; p1 = find(S,y),p2 = find(S,y+1);
        if (!p1 && !p2) {if(x != n && y != m) Set(S,y,1),Set(S,y+1,2),f[now][S] += val;}
        else if (p1 && !p2) {if (x != n) f[now][S] += val; if(y != m) Set(S,y,0),Set(S,y+1,p1),f[now][S] += val;} 
        else if (!p1 && p2) {if (y != m) f[now][S] += val; if(x != n) Set(S,y+1,0),Set(S,y,p2),f[now][S] += val;}
        else if (p1 == 1 && p2 == 2) {if(x == n && y == m) Ans += val;}
        else if (p1 == 2 && p2 == 2) {Set(S,Link(S,y),2);Set(S,y,0);Set(S,y+1,0);f[now][S] += val;}
        else if (p1 == 2 && p2 == 1) {Set(S,y,0);Set(S,y+1,0); f[now][S] += val;}
        else if (p1 == 1 && p2 == 1) {Set(S,Link(S,y+1),1);Set(S,y,0); Set(S,y+1,0); f[now][S] += val;}
    }
}

int main() {
    // freopen("postman.in","r",stdin);
    // freopen("postman.out","w",stdout);
    n = read<int>(); m = read<int>();
    if (n == 1 || m == 1) { puts("1\n"); return 0;}
    if (n < m) std::swap(n,m);
    f[0].clear(); f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)  DP(i,j);
        if (i != n) {
            int now = (i * m) & 1,tot = f[now].e - 1;
            for (int j = 1; j <= tot; j++) f[now].a[j].u <<= 2;
        }
    }
    Ans += Ans; Ans.out();
    getchar(); getchar();
    return 0;
}