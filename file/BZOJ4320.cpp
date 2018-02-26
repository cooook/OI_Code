#include <stdio.h>
#include <cstring>
const int len = 550,MAXN = 300005;
int f[MAXN],n,mn[555],Ans[100005],fa[MAXN];
bool vis[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int Min(int a,int b) {
    return a<b?a:b;
}

struct Cooook {
    int op,x;
}Q[MAXN];

inline int read_char() {
    char ch = getchar();
    for (; ch != 'A' && ch != 'B'; ch = getchar()) ;
    return ch == 'B';
}

int find(int x) {
    return fa[x] == x?x:fa[x] = find(fa[x]);
}

int main() {
    memset(mn,0x3f,sizeof mn);
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        Q[i].op = read_char(),Q[i].x = read<int>();
        if (!Q[i].op) {
            vis[Q[i].x] = true;
            for (int j = 1; j <= len; j++)
                mn[j] = Min(mn[j],Q[i].x%j);
        }
        else if (Q[i].x <= len) Ans[i] = mn[Q[i].x];
    }
    for (int i = 1; i <= 300000; i++) fa[i] = vis[i]?i:i+1;
    fa[0] = 1;fa[300001] = 300001;
    for (int i = n; i; i--) {
        if (!Q[i].op) fa[Q[i].x] = Q[i].x + 1;
        else {
            if (Q[i].x > len) {
                Ans[i] = 0x7f7f7f7f;
                for (int j = 0; j <= 300000; j += Q[i].x) {
                    int QWQ = 0x3f3f3f3f;
                    QWQ = find(j?j:1);
                    if (QWQ > 300000) continue;
                    Ans[i] = Min(Ans[i],QWQ % Q[i].x);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (Q[i].op) printf("%d\n", Ans[i]);
    return 0;
}
