#include <bits/stdc++.h>

#define id(_) (_-null)
#define fi first
#define se second
#define mk pii

struct pii{
    int first,second;
    pii(){}
    pii(int x,int y){first = x;second = y;}
    inline bool operator < (const pii&x)const{
        return first == x.first?second < x.second:first < x.first;
    }
};

const int MAXN = 100005,MAXM = 1111115;
int n,m,Q,val[MAXM],Ans[MAXM],Query_time;


char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read() {
    int x = 0, f = 1; char ch = getc();
    for (; ch < '0' | ch > '9'; ch = getc()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getc()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{int u,v,w;}a[MAXM];
struct Operation{int op,x,y;}op[(int)1e6+5];
struct node{
    node *ch[2],*f;
    int mx,val,tag,id,pos;
    inline void Maintain();
    inline void Push_down();
    inline void rotate();
    inline void Splay();
    inline bool dir();
    inline bool isrt();
}null[MAXM];

inline int Max(register int x,register int y){return x > y?x:y;}
inline void Swap(int &x,int &y){x ^= y, y ^= x, x ^= y;}
inline void Swap1(node *&x,node *&y){node *t = x; x = y; y = t;}

inline bool node::dir(){
    return f -> ch[1] == this;
}

inline bool node::isrt(){
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::rotate(){
    node *fa = f, *pa = fa -> f; int d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    fa -> f = this; this -> f = pa; ch[d ^ 1] = fa;
    fa -> Maintain(); Maintain();
}

inline void node::Splay(){
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f) 
        if (!t -> isrt()){
            t -> f -> Push_down(), t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
}

inline void node::Push_down(){
    if (tag) {
        tag ^= 1;
        ch[0] -> tag ^= 1, Swap1(ch[0] -> ch[0],ch[0] -> ch[1]);
        ch[1] -> tag ^= 1, Swap1(ch[1] -> ch[0],ch[1] -> ch[1]);
    }
}

inline void node::Maintain(){
    mx = Max(Max(ch[0] -> mx,ch[1] -> mx),val);
    if (mx == ch[0] -> mx) pos = ch[0] -> pos;
    else if (mx == ch[1] -> mx) pos = ch[1] -> pos;
    else if (mx == val) pos = id;
}

inline void Access(node *x){
    node *y = null;
    while (x != null)
        x -> Splay(),
        x -> ch[1] = y,
        x -> Maintain(),
        y = x, x = x -> f;
}

inline void Make_root(node *x){
    Access(x); x -> Splay(); 
    Swap1(x -> ch[0],x -> ch[1]), x -> tag ^= 1;
}

inline void Link(node *x,node *y){
    Make_root(x); x -> Splay(); x -> f = y;
}

inline void Cut(node *x,node *y){
    Make_root(x); Access(y); x -> Splay();
    x -> ch[1] = y -> f = null;
}

inline node* find(node *x){
    Access(x); x -> Splay(); x -> Push_down();
    while (x -> ch[0] != null)
        x = x -> ch[0], x -> Push_down();
    return x;
}

inline int Query(node *x,node *y){
    Make_root(x);
    Access(y);
    y -> Splay();
    return y -> pos;
}

inline void Add_Edge(node *x,node *y,node *z,int w){
    if (find(x) != find(y))
        return Link(x,z), Link(y,z), void();
    else {
        int id = Query(x,y);
        if (w < val[id-n]) Cut(&null[a[id-n].u],&null[id]),Cut(&null[a[id-n].v],&null[id]),Link(x,z),Link(y,z);
    }
}

std::map<pii,int> ma;
bool vis[MAXM];

int main(){
    n = read(), m = read(), Q = read();
    for (int i = 0; i <= n + m; ++i)
        null[i].ch[0] = null[i].ch[1] = null[i].f = null,
        null[i].tag = 0, null[i].id = i, null[i].mx = 0, null[i].pos = i;
    for (int i = 1; i <= m; ++i){
        a[i].u = read(),a[i].v = read(),a[i].w = read();
        null[i+n].mx = null[i+n].val = a[i].w; val[i] = a[i].w; 
        if (a[i].u > a[i].v) Swap(a[i].u,a[i].v);
        ma[mk(a[i].u,a[i].v)] = i;
    }
    for (int i = 1; i <= Q; ++i){
        op[i].op = read(),op[i].x = read(), op[i].y = read();
        if (op[i].x > op[i].y) Swap(op[i].x,op[i].y);
        if (op[i].op == 2) vis[ma[mk(op[i].x,op[i].y)]] = true;
    }
    for (int i = 1; i <= m; ++i)
        if (!vis[i])
            Add_Edge(&null[a[i].u],&null[a[i].v],&null[n+i],a[i].w);
    for (int i = Q; i; --i){
        if (op[i].op == 1)
            Ans[++Query_time] = val[Query(&null[op[i].x],&null[op[i].y]) - n];
        else Add_Edge(&null[op[i].x],&null[op[i].y],&null[ma[mk(op[i].x,op[i].y)]+n],val[ma[mk(op[i].x,op[i].y)]]);
    }
    for (int i = Query_time; i; --i) printf("%d\n",Ans[i]);
    return 0;
}