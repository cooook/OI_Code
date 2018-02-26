#include <stdio.h>
#include <cstring>
#define inf 0x3f3f3f3f
#define Min(x,y) ((x)<(y)?(x):(y))
int val[11][11],n,m,now,last;


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Hash{
    #define MAXN 76543
    int first[MAXN],e;
    Hash(){clear();}
    struct edge{
        int u,v,next;
    }a[MAXN<<1];
    inline void clear(){memset(first,0,sizeof first);e = 1;}
    inline int& New(int u) {
        a[e].u = u; a[e].v = inf;
        a[e].next = first[u % MAXN]; first[u % MAXN] = e++;
        return a[e-1].v;
    }
    inline int& operator [] (const int u) {
        for (int i = first[u % MAXN]; i; i = a[i].next) if (a[i].u == u) return a[i].v;
        return New(u);
    }
}f[2];

inline void Set(int &S,int bit,int val) {
    bit = bit - 1 << 1;
    S |= 3 << bit;
    S ^= 3 << bit;
    S |= val << bit;
}

inline int find(int S,int pos) {
    return (S >> ((pos - 1) << 1)) & 3;
}

inline void DP(int x,int y) {
    int val,tot = f[last].e - 1,p1,p2,S; f[now].clear();
    for (int i = 1; i <= tot; i++) {
        S = f[last].a[i].u; val = f[last].a[i].v;
        p1 = find(S,y); p2 = find(S,y+1);
        if (::val[x][y] == 1) {
            if (!p1 && !p2) f[now][S] = Min(f[now][S],val);
            continue;
        }
        if (::val[x][y] == 0) {
            if (!p1 && !p2) {
                f[now][S] = Min(f[now][S],val);
                if (x != n && y != m) {
                    Set(S,y,1),Set(S,y+1,1),f[now][S] = Min(f[now][S],val + 1);
                    Set(S,y,2),Set(S,y+1,2),f[now][S] = Min(f[now][S],val + 1);
                }
            }
            if (p1 && !p2) {
                if (x != n) f[now][S] = Min(f[now][S],val + 1);
                if (y != m) Set(S,y+1,p1),Set(S,y,0),f[now][S] = Min(f[now][S],val + 1);
            }
            if (!p1 && p2) {
                if (y != m) f[now][S] = Min(f[now][S],val + 1);
                if (x != n) Set(S,y,p2),Set(S,y+1,0),f[now][S] = Min(f[now][S],val + 1);
            }
            if (p1 == 1 && p2 == 1) {
                Set(S,y,0),Set(S,y+1,0);
                f[now][S] = Min(f[now][S],val + 1);
            }
            if (p1 == 2 && p2 == 2) {
                Set(S,y,0),Set(S,y+1,0);
                f[now][S] = Min(f[now][S],val + 1);
            }
        } 
        if (::val[x][y] == 2) {
            if (!p1 && !p2) {
                if (x != n) Set(S,y,1),Set(S,y+1,0),f[now][S] = Min(f[now][S],val + 1);
                if (y != m) Set(S,y,0),Set(S,y+1,1),f[now][S] = Min(f[now][S],val + 1);
            }
            if (p1 == 1 && !p2) {Set(S,y,0),f[now][S] = Min(f[now][S],val + 1);}
            if (!p1 && p2 == 1) {Set(S,y+1,0),f[now][S] = Min(f[now][S],val + 1);}
        }
        if (::val[x][y] == 3) {
            if (!p1 && !p2) {
                if (x != n) Set(S,y,2),Set(S,y+1,0),f[now][S] = Min(f[now][S],val + 1);
                if (y != m) Set(S,y,0),Set(S,y+1,2),f[now][S] = Min(f[now][S],val + 1);
            }
            if (p1 == 2 && !p2) {Set(S,y,0); f[now][S] = Min(f[now][S],val + 1);}
            if (!p1 && p2 == 2) {Set(S,y+1,0); f[now][S] = Min(f[now][S],val + 1);}
        }
    }
    now ^= 1;last ^= 1;
}

int main() {
    while (scanf("%d%d",&n,&m) == 2 && (n && m)) {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) val[i][j] = read<int>();
        f[0].clear(); f[0][0] = 0;last = 0;now = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) DP(i,j);
            if (i != n) for (int j = 1; j < f[last].e; j++) f[last].a[j].u <<= 2;
        }
        int Ans = f[last][0];
        if (Ans == inf) Ans = 0;
        else Ans -= 2;
        printf("%d\n",Ans);
    }
    return 0;
}