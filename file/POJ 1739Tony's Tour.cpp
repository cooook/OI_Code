#include <stdio.h>
#include <cstring>
typedef long long ll;
int n,m,w[15][15],now,cnt; char s[15]; ll Ans;


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Hash_Table{
    #define Key 76543
    int first[Key+5],e;
    Hash_Table(){clear();}
    struct edge{int u,next; ll v;}a[1<<20];
    inline void clear(){memset(first,0,sizeof first); e = 1;}
    inline ll& New(int u){
        a[e].u = u; a[e].v = 0; 
        a[e].next = first[u % Key]; first[u % Key] = e++;
        return a[e - 1].v;
    }
    inline ll& operator [] (const int State){
        for (int i = first[State % Key]; i; i = a[i].next)
            if (a[i].u == State) return a[i].v;
        return New(State);
    }
}f[2];

inline int Get(int S,int x){
    return (S >> (x - 1 << 1)) & 3;
}

inline void Set(int &S,int x,int val){
    x = x - 1 << 1;
    S |= 3 << x;
    S ^= 3 << x;
    S |= val << x;
}

inline int find(int S,int x){
    int d = (Get(S,x) == 1)?1:-1,cnt = 0, plug;
    for (int i = x; i && i <= m + 1; i += d){
        plug = Get(S,i);
        if (plug == 1) cnt ++;
        else if (plug == 2) cnt --;
        if (!cnt) return i;
    }
}

inline void DP(int x,int y){
    now ^= 1; ll val; int last = now ^ 1,S,plug1,plug2; f[now].clear();
    for (int i = 1; i < f[last].e; i++){
        S = f[last].a[i].u; val = f[last].a[i].v;
        plug1 = Get(S,y), plug2 = Get(S,y+1);
        if (w[x][y]){
            if (!plug1 && !plug2) f[now][S] = val;
            continue;
        }
        if (!plug1 && !plug2){if (x != n && y != m) Set(S,y,1),Set(S,y+1,2),f[now][S] += val;}
        else if (!plug1 && plug2){if (y != m) f[now][S] += val; if (x != n) Set(S,y,plug2),Set(S,y+1,0),f[now][S] += val;}
        else if (plug1 && !plug2){if (x != n) f[now][S] += val; if (y != m) Set(S,y,0),Set(S,y+1,plug1),f[now][S] += val;}
        else if (plug1 == 1 && plug2 == 2){if (x == n && y == m) Ans = val;}
        else if (plug1 == 1 && plug2 == 1){Set(S,find(S,y+1),1),Set(S,y,0),Set(S,y+1,0); f[now][S] += val;}
        else if (plug1 == 2 && plug2 == 2){Set(S,find(S,y),2),Set(S,y,0),Set(S,y+1,0); f[now][S] += val;}
        else if (plug1 == 2 && plug2 == 1){Set(S,y,0),Set(S,y+1,0); f[now][S] += val;}
    }
}

int main(){
    while (scanf("%d%d",&n,&m) == 2 && n && m){
        Ans = 0;
        for (int i = 1; i <= n; i++){
            scanf("%s", s + 1);
            for (int j = 1; j <= m; j++)
                if (s[j] == '#') w[i][j] = true;
                else w[i][j] =false;
        }
        ++ n; 
        for (int i = 1; i <= m; i++) w[n][i] = true;
        w[n][1] = w[n][m] = false;
        ++ n;
        for (int i = 1; i <= m; i++) w[n][i] = false;
        f[0].clear(); now = 0;
        f[0][0] = 1;
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++) DP(i,j);
            if (i != n) for (int j = 1; j < f[now].e; j++) f[now].a[j].u <<= 2;
        }
        printf("%lld\n",Ans);
    }
    return 0;
}