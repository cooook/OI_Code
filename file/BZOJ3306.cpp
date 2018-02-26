#include <bits/stdc++.h>
#define id(_) (_-null)
const int MAXN = 1e5+5, inf = 0x3f3f3f3f;
int val[MAXN],first[MAXN],e = 1,n,m;


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge{
    int u,v,next;
}a[MAXN<<1];

inline void push(int u,int v){
    a[e].u = u; a[e].v = v;
    a[e].next = first[u]; first[u] = e++;
}

inline int Min(int a,int b){
    return a < b? a:b;
}

struct Heap{
    std::priority_queue<int,std::vector<int>,std::greater<int> > G,del;
    inline void push(int x){G.push(x);}
    inline void erase(int x){del.push(x);}
    inline int top(){
        while (!del.empty() && del.top() == G.top()) del.pop(), G.pop();
        return G.empty()?inf:G.top();
    }
};

struct node{
    Heap val; int mn,tag;
    node *ch[2],*f;
    inline void Maintain();
    inline void rotate();
    inline void Splay();
    inline void rev();
    inline void Push_down();
    inline bool dir();
    inline bool isrt();
}null[MAXN];

inline void node::Maintain(){
    mn = Min(val.top(),Min(ch[0] -> mn,ch[1] -> mn));
}

inline void node::rev(){
    std::swap(ch[0],ch[1]); tag ^= 1;
}

inline void node::rotate(){
    node *fa = f, *pa = fa -> f; bool d = dir();
    if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
    if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
    this -> f = pa; fa -> f = this; ch[d ^ 1] = fa;
    fa -> Maintain(), Maintain();
}

inline void node::Splay(){
    Push_down();
    for (node *t = f; !isrt(); rotate(), t = f)
        if (!t -> isrt()){
            t -> f -> Push_down(),t -> Push_down(), Push_down();
            if (t -> dir() == dir()) t -> rotate();
            else rotate();
        }
        else t -> Push_down(), Push_down();
}

inline bool node::isrt(){
    return f -> ch[0] != this && f -> ch[1] != this;
}

inline bool node::dir(){
    return f -> ch[1] == this;
}

inline void node::Push_down(){
    if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}

inline void Access(node *x){
    node *y = null;
    while (x != null){
        x -> Splay();
        if (x -> ch[1] != null) 
            x -> val.push(x -> ch[1] -> mn);
        if (y != null) 
            x -> val.erase(y -> mn);
        x -> ch[1] = y;
        x -> Maintain();
        y = x, x = x -> f;
    }
}

inline void Make_root(node *x){
    Access(x), x -> Splay(), x -> rev();
}

inline void dfs(int u,int fa){
    for (int i = first[u]; i; i = a[i].next){
        register int v = a[i].v;
        if (v == fa) continue;
        dfs(v,u);
        (&null[u]) -> val.push((&null[v]) -> mn);
        (&null[v]) -> f = &null[u];
    }
    (&null[u]) -> Maintain();
}

int main(){
    using std::cout;
    using std::endl;
    n = read<int>(); m = read<int>();
    null -> ch[0] = null -> ch[1] = null -> f = null;
    null -> mn = inf;
    for (int i = 1; i <= n; i++){
        int fa = read<int>(); val[i] = read<int>();
        null[i].ch[0] = null[i].ch[1] = null[i].f = null;
        null[i].mn = val[i]; null[i].val.push(val[i]);
        if (fa) push(fa,i);
    } dfs(1,0);
    char s[5]; int x;
    while (m --){
        scanf("%s",s); x = read<int>();
        if (s[0] == 'V'){
            Access(&null[x]);
            (&null[x]) -> Splay();
            (&null[x]) -> val.erase(val[x]);
            (&null[x]) -> val.push(val[x] = read<int>());
            (&null[x]) -> Maintain();
        }
        else if (s[0] == 'E') Make_root(&null[x]);
        else{
            Access(&null[x]); (&null[x]) -> Splay();
            printf("%d\n", (&null[x]) -> val.top());
        }
    }
    return 0;
}