

#include <ctime>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#define MAXN 10005
int fa[MAXN],n,cnt;


struct edge{
    int u,v,w;
    inline bool operator < (const edge &a)const{
        return w < a.w;
    }
}a[MAXN];

inline void New_Edge() {
    for (int i = 1; i <= n; i++) a[i].u = rand() % n + 1,a[i].v = rand() % n + 1,a[i].w = rand();
}

inline int find(int x) {return fa[x] == x?x:fa[x] = find(fa[x]);}
inline void Link(int x,int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    fa[x] = y;
}

inline bool Is_A_Tree() {
    std::sort(&a[1],&a[n+1]);
    for (int i = 1; i <= n; i++) {
        if (find(a[i].u) != find(a[i].v)) {
            Link(a[i].v,a[i].u);
            printf("%d %d\n",a[i].u,a[i].v);
            cnt ++;
            if (cnt == n - 1) return true;
        }
    }
    return false;
}

int main() {
    freopen("Tree.in","w",stdout);
    srand(time(NULL));
    scanf("%d",&n);
    printf("%d\n",n);
    for (int i = 1; i <= n; i++) fa[i] = i;
    do New_Edge(); while (!Is_A_Tree());
    return 0;
}
