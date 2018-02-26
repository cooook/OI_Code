#include <bits/stdc++.h>
using std::cout;
using std::endl;
const int MAXN = 1e5+5;
int n,cnt,id[MAXN],edge_id[MAXN];
char s[15];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct node{
    node *ch[2],*f;
    int mx,rev,tag,val,mn,have_val;
    inline void Maintain();
    inline void rotate();
    inline void Rev();
    inline void Tag();
    inline void Splay();
    inline void Push_down();
    inline bool isrt();
    inline bool dir();
}null[MAXN];

inline void node::Push_down(){
    if (this == null) return;
    if (rev){
        ch[0] -> Rev();
        ch[1] -> Rev();
        rev ^= 1;
    }
    if (tag){
        ch[0] -> Tag();
        ch[1] -> Tag();
        tag ^= 1;
    }
}

inline void node::rotate(){
    node *fa = f, *pa = fa -> f; int d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    fa -> f = this; this -> f = pa; ch[d ^ 1] = fa;
    fa -> Maintain(); Maintain();
}

inline void node::Maintain(){
    if (this == null) return;
    mx = std::max(ch[0] -> mx,ch[1] -> mx);
    mn = std::min(ch[0] -> mn,ch[1] -> mn);
    if (!have_val) return;
    if (mx < val) mx = val;
    if (mn > val) mn = val;
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

inline void node::Rev(){
    rev ^= 1;
    std::swap(ch[0],ch[1]);
}

inline void node::Tag(){
    val = -val;
    std::swap(mx,mn);
    mx = -mx; mn = -mn;
    tag ^= 1;
}

inline bool node::isrt(){
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline bool node::dir(){
    return f -> ch[1] == this;
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
    Access(x); x -> Splay(); x -> Rev();
}

inline void Link(node *x,node *y){
    Make_root(x); x -> f = y;
}

inline void Change(node *x,int y){
    x -> Splay(); x -> val = y;
    x -> Maintain();
}

inline void Negate(node *x,node *y){
    Make_root(x); Access(y); y -> Splay(); y -> Tag();
}

inline int Query(node *x,node *y){
    Make_root(x); Access(y); y -> Splay();
    return y -> mx;
}

int main(){
    n = read<int>();
    for (int i = 0; i < MAXN; i++)
        null[i].ch[0] = null, null[i].ch[1] = null, null[i].f = null,
        null[i].tag = 0, null[i].mx = -0x3f3f3f3f,null[i].have_val = 0,
        null[i].mn = 0x3f3f3f3f, null[i].rev = 0;
    for (int i = 1; i <= n; i++) id[i] = ++ cnt;
    for (int i = 1; i < n; i++){
        int u = read<int>(),v = read<int>(), w = read<int>();
        edge_id[i] = ++ cnt;
        null[cnt].mn = null[cnt].mx = null[cnt].val = w; 
        null[cnt].have_val = true;
        Link(&null[id[u]],&null[cnt]);
        Link(&null[id[v]],&null[cnt]);
    }
    while (true){
        scanf("%s",s);
        if (s[0] == 'D') break;
        int x = read<int>(),y = read<int>();
        if (s[0] == 'C') Change(&null[edge_id[x]],y);
        else if (s[0] == 'N') Negate(&null[id[x]],&null[id[y]]);
        else printf("%d\n",Query(&null[id[x]],&null[id[y]]));
    }  
    return 0;
}