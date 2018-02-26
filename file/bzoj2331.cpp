#include <bits/stdc++.h>
const int mod = 20110520;
int n,m,now,Ans,cnt; char s[105][105],tmp[105][105];


struct Hash_Table{
    #define Key 76543
    int first[Key+1],e;
    struct edge{int u,v,next;}a[Key<<2];
    Hash_Table(){clear();}
    inline void clear(){memset(first,0,sizeof first); e = 1;}
    inline int& operator [] (const int State){
        int x = State % Key;
        for (int i = first[x]; i; i = a[i].next)
            if (a[i].u == State) return a[i].v;
        a[e].u = State; a[e].v = 0; a[e].next = first[x]; first[x] = e++;
        return a[e-1].v;
    }
}f[2];

inline void Upd(int &x,int y){(x += y) %= mod;}
inline int Get(int x,int y){return (x >> (y - 1 << 1)) & 3;}
inline void Set(int &S,int x,int val){
    x = x - 1 << 1;
    S |= 3 << x;
    S ^= 3 << x;
    S |= val << x;
}

inline int find(int S,int x){
    int d = (Get(S,x) == 1)?1:-1,plug,cnt = 0;
    for (int i = x; i && i <= m + 1; i += d){
        plug = Get(S,i);
        if (plug == 1) cnt ++;
        else if (plug == 2) cnt --;
        if (!cnt) return i;
    }
}

inline void Dp(int x,int y){
    cnt -= s[x][y] == '_';
    now ^= 1; f[now].clear();
    int val,p1,p2,S,last = now ^ 1;
    for (int i = 1; i < f[last].e; i++){
        S = f[last].a[i].u, val = f[last].a[i].v;
        p1 = Get(S,y),p2 = Get(S,y+1);
        if (s[x][y] == '*'){
            if (!p1 && !p2) Upd(f[now][S],val);
            continue;
        }
        if (!p1 && !p2){
            if (x != n) Set(S,y,1),Set(S,y+1,0),Upd(f[now][S],val);
            if (y != m) Set(S,y,0),Set(S,y+1,1),Upd(f[now][S],val);
            if (x != n && y != m) Set(S,y,2),Set(S,y+1,2),Upd(f[now][S],val);
        }
        else if (!p1 && p2){
            if (p2 == 1){
                if (x != n) Set(S,y,1),Set(S,y+1,0),Upd(f[now][S],val);
                if (y != m) Set(S,y,0),Set(S,y+1,2),Upd(f[now][S],val);
            }
            else{
                if (x != n) Set(S,y,2),Set(S,y+1,0),Upd(f[now][S],val);
                Set(S,y,0); Set(S,y+1,0); Upd(f[now][S],val);
                if (!S && !cnt) Upd(Ans,val);
            }
        }
        else if (p1 && !p2){
            if (p1 == 1){
                if (x != n) Set(S,y,2),Set(S,y+1,0),Upd(f[now][S],val);
                if (y != m) Set(S,y,0),Set(S,y+1,1),Upd(f[now][S],val);
            }
            else{
                if (y != m) Set(S,y,0),Set(S,y+1,2),Upd(f[now][S],val);
                Set(S,y+1,0); Set(S,y,0); Upd(f[now][S],val);
                if (!S && !cnt) Upd(Ans,val);
            }
        }
        else if (p1 == 1 && p2 == 1){
            Set(S,y,0),Set(S,y+1,0); Upd(f[now][S],val);
            if (!S && !cnt) Upd(Ans,val);
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++){
        scanf("%s",tmp[i] + 1);
        for (int j = 1; j <= m; j++) cnt += tmp[i][j] == '_';
    }
    if (n < m){
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                s[j][i] = tmp[i][j];
        std::swap(n,m);
    }
    else memcpy(s,tmp,sizeof tmp);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++) Dp(i,j);
        for (int j = 1; j < f[now].e; j++) f[now].a[j].u <<= 2;
    } printf("%d\n",Ans);
    return 0;
}