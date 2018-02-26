#include <stdio.h>
#include <math.h>
const int MAXN = 1005;
const double eps = 1e-7;
int fa[MAXN],n,m;
double w[MAXN];


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' | ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int find(int x){
    if (x == fa[x]) return x;
    register int rt = fa[x];
    fa[x] = find(fa[x]);
    w[x] *= w[rt];
    return fa[x];
}

inline void Link(int x,int y,double p){
    int fa_x = find(x),fa_y = find(y);
    fa[fa_x] = fa_y;
    w[fa_x] = w[y] * p / w[x];
}

inline bool Judge(int x,int y,double p){
    return fabs(w[x] / w[y] - p) < eps;
}

int main(){
    for (int Case = 1,T = read<int>(); Case <= T; Case++){
        n = read<int>(); m = read<int>();
        for (int i = 1; i <= n; i++) fa[i] = i,w[i] = 1.0;
        int u,v,x,y; bool flag = true;
        for (int i = 1; i <= m; i++){
            u = read<int>(),v = read<int>();
            x = read<int>(),y = read<int>();
            if (find(u) != find(v)) Link(u,v,x/1.0/y);
            else if (!Judge(u,v,x/1.0/y)){
                flag = false; break;
            }
        }
        printf("Case #%d: %s\n",Case,flag?"Yes":"No");
    }
    return 0;
}
