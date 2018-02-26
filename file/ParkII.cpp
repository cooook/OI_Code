#include <bits/stdc++.h>
const int inf = 0x3f3f3f3f;
int n,m,now,Ans,w[105][9];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Hash_Table{
    #define key 76543
    int first[key+1],e;
    Hash_Table(){clear();}
    inline void clear(){memset(first,0,sizeof first); e = 1;}
    struct edge{int u,v,next;}a[key<<1];
    inline int& operator [] (const int &State){
        register int x = State % key;
        for (int i = first[x]; i; i = a[i].next)
            if (a[i].u == State) return a[i].v;
        a[e].u = State; a[e].v = -inf; a[e].next = first[x]; first[x] = e++;
        return a[e-1].v;
    }
}f[2];

inline void Upd(int &x,int y){
    if (x < y) x = y;
}

inline int Get(int S,int x){
    return (S >> (x - 1 << 1)) & 3;
}

inline void Set(int &S,int x,int y){
    (-- x) <<= 1;
    S |= 3 << x;
    S ^= 3 << x;
    S |= y << x;
}

inline int find(int S,int x){
    int d = (Get(S,x) == 1)?1:-1,plug,cnt = 0;
    for (int i = x; i && i <= m + 1; i += d){
        plug = Get(S,i);
        if (plug == 1) cnt ++;
        if (plug == 2) cnt --;
        if (!cnt) return i;
    }
}

inline void Dp(int x,int y){
    now ^= 1; f[now].clear();
    int S,val,p1,p2,last = now ^ 1;
    for (int i = 1; i < f[last].e; i++){
        S = f[last].a[i].u, val = f[last].a[i].v + w[x][y];
        p1 = Get(S,y), p2 = Get(S,y+1);
        if (!p1 && !p2){
            Upd(f[now][S],f[last].a[i].v);
            if (x != n && y != m) Set(S,y,1),Set(S,y+1,2),Upd(f[now][S],val);
            if (x != n) Set(S,y,3),Set(S,y+1,0),Upd(f[now][S],val);
            if (y != m) Set(S,y,0),Set(S,y+1,3),Upd(f[now][S],val);
        }
        else if (!p1 && p2){
            if (p2 == 3){
                Set(S,y+1,0);
                if (!S) Upd(Ans,val);
                if (x != n) Set(S,y,3),Set(S,y+1,0),Upd(f[now][S],val);
                if (y != m) Set(S,y,0),Set(S,y+1,3),Upd(f[now][S],val);
            }
            else{
                if (x != n) Set(S,y,p2),Set(S,y+1,0),Upd(f[now][S],val);
                if (y != m) Set(S,y,0),Set(S,y+1,p2),Upd(f[now][S],val);
                Set(S,y,0),Set(S,y+1,p2),Set(S,find(S,y+1),3), Set(S,y,0), Set(S,y+1,0); Upd(f[now][S],val);
            }
        }
        else if (p1 && !p2){
            if (p1 == 3){
                Set(S,y,0);
                if (!S) Upd(Ans,val);
                if (x != n) Set(S,y,3),Set(S,y+1,0),Upd(f[now][S],val);
                if (y != m) Set(S,y,0),Set(S,y+1,3),Upd(f[now][S],val);
            }
            else{
                if (y != m) Set(S,y,0),Set(S,y+1,p1),Upd(f[now][S],val);
                if (x != n) Set(S,y,p1),Set(S,y+1,0),Upd(f[now][S],val);
                Set(S,y,p1),Set(S,y+1,0),Set(S,find(S,y),3), Set(S,y,0), Set(S,y+1,0); Upd(f[now][S],val);
            }
        }
        else if (p1 == 1 && p2 == 1){
            Set(S,find(S,y+1),1), Set(S,y,0), Set(S,y+1,0); Upd(f[now][S],val);
        }
        else if (p1 == 2 && p2 == 2){
            Set(S,find(S,y),2), Set(S,y,0), Set(S,y+1,0); Upd(f[now][S],val);
        }
        else if (p1 == 2 && p2 == 1){
            Set(S,y,0), Set(S,y+1,0), Upd(f[now][S],val);
        }
        else if (p1 == 3 && p2 == 3){
            Set(S,y,0), Set(S,y+1,0);
            if (!S) Upd(Ans,val);
        }
        else if (p1 == 3){
            Set(S,find(S,y+1),3), Set(S,y,0), Set(S,y+1,0);
            Upd(f[now][S],val);
        }
        else if (p2 == 3){
            Set(S,find(S,y),3), Set(S,y,0), Set(S,y+1,0);
            Upd(f[now][S],val);
        }
    }
}

int main(){
    n = read<int>(), m = read<int>();
    f[0][0] = 0; Ans = -inf;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            w[i][j] = read<int>(), Upd(w[i][j],Ans);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++) Dp(i,j);
        for (int j = 1; j < f[now].e; j++) f[now].a[j].u <<= 2;
    }
    printf("%d\n",Ans);
    return 0;
}