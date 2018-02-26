#include <stdio.h>
#include <cstring>
const int MAXN = 10005,inf = 0x3f3f3f3f;
int n,first[MAXN],e = 1,k,st,f[MAXN][MAXN][2],size[MAXN];
int tmp[MAXN][2];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void gmin(int &x,int y) {
    if (x > y) x = y;
}

struct edge{
    int u,v,next,w;
}a[MAXN<<1];

inline void push(int u,int v,int w) {
    a[e].u = u; a[e].v = v; a[e].w = w;
    a[e].next = first[u]; first[u] = e++;
}

void dp(int u,int fa) {
	size[u] = 1; f[u][1][1] = 0; f[u][1][0] = 0;
	for (int i = first[u]; i; i = a[i].next) if(a[i].v != fa) {
		register int v = a[i].v; dp(v,u); 
		for (int j = 1; j <= size[u] && j <= k; j++) tmp[j][0] = f[u][j][0], tmp[j][1] = f[u][j][1];
		for (int j = 1; j <= size[v]; j++) tmp[j+size[u]][0] = tmp[j+size[u]][1]= inf;
		for (int j = 1; j <= size[u] && j <= k; j++)
			for (int o = 1; o <= size[v] && o + j <= k; o++)
				gmin(tmp[o+j][1],f[u][j][1]+f[v][o][1]+2*a[i].w),
				gmin(tmp[o+j][0],f[u][j][0]+f[v][o][1]+2*a[i].w),
				gmin(tmp[o+j][0],f[u][j][1]+a[i].w+f[v][o][0]);
		size[u] += size[v];
		for (int j = 1; j <= size[u]; j++) f[u][j][0] = tmp[j][0],f[u][j][1] = tmp[j][1];
	}
}

int main() {
	memset(f,0x3f,sizeof f);
    n = read<int>(); k = read<int>(); st = read<int>();
    for (int i = 1; i < n; i++) {
		register int u = read<int>(),v = read<int>(),w = read<int>();
		push(u,v,w); push(v,u,w);
	} dp(st,0);
	printf("%d\n",f[st][k][0]<f[st][k][1]?f[st][k][0]:f[st][k][1]);
    return 0;
}
