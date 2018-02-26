// By Cooook.
#include <stdio.h>
#include <cstring>
#include <iostream>


#define inf 0x3f3f3f3f
#define MAXN 16631

int n,m,Ans = -inf,now = 1,last,a[205][205];

template<typename _t>
inline _t read(){
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Hash{
    int first[MAXN],e;
    Hash(){clear();}
    inline void clear(){memset(first,0,sizeof first);e = 1;}
    struct edge{int u,v,next;}a[MAXN];
    inline int& New(int u) {
        a[e].u = u;a[e].v = -inf;
        a[e].next = first[u%MAXN]; first[u%MAXN] = e ++;
        return a[e-1].v;
    }
    inline int& operator [] (int u) {
        for (int i = first[u%MAXN]; i; i = a[i].next) if (a[i].u == u) return a[i].v;
        return New(u);
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

inline void DP(int x,int y){
    int val,tot = f[last].e - 1,S,p1,p2; f[now].clear();
    for (int i = 1; i <= tot; i ++) {
        S = f[last].a[i].u,p1 = find(S,y),p2 = find(S,y+1),val = f[last].a[i].v;
        if (!p1 && !p2) {
            f[now][S] = std::max(f[now][S],val);
            if (x != n && m != y) 
                Set(S,y,1),Set(S,y+1,2),f[now][S] = std::max(f[now][S],val + a[x][y]);
        }
        else if (!p1 && p2) {
            if (y != m) f[now][S] = std::max(f[now][S],val + a[x][y]);
            if (x != n) Set(S,y + 1,0),Set(S,y,p2),f[now][S] = std::max(f[now][S],val + a[x][y]); 
        } 
        else if (p1 && !p2) {
            if (x != n) f[now][S] = std::max(f[now][S],val + a[x][y]);
            if (y != m) Set(S,y,0),Set(S,y+1,p1),f[now][S] = std::max(f[now][S],val + a[x][y]);
        }
        else if (p1 == 1 && p2 == 2) {
            Set(S,y,0);Set(S,y+1,0);
            if (S) continue;
            Ans = std::max(Ans,val + a[x][y]);
        }
        else if (p1 == 1 && p2 == 1) {
            Set(S,Link(S,y+1),1); Set(S,y,0); Set(S,y+1,0);
            f[now][S] = std::max(f[now][S],val + a[x][y]);
        }
        else if (p1 == 2 && p2 == 2) {
            Set(S,Link(S,y),2); Set(S,y,0);Set(S,y+1,0);
            f[now][S] = std::max(f[now][S],val + a[x][y]);
        }
        else if (p1 == 2 && p2 == 1) {
            Set(S,y,0); Set(S,y+1,0); 
            f[now][S] = std::max(f[now][S],val + a[x][y]);
        }
    }
    now ^= 1;last ^= 1;
}

int main() {
    // freopen("park_2.in","r",stdin);
    n = read<int>(); m = read<int>();
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] = read<int>();
    f[last][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) DP(i,j);
        if (i != n) {
            int tot = f[last].e - 1;
            for (int j = 1; j <= tot; j++) f[last].a[j].u <<= 2;
        }
    }
    printf("%d\n",Ans);
    // while (true);
    // getchar(); getchar();
    return 0;
}