#pragma GCC optimize ("O3")
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 1005
int f[MAXN][MAXN],n,m,num[MAXN][MAXN],cnt,my_cnt,Ans;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
bool full[MAXN*MAXN];
 
 
template<typename _t>
inline _t read(){
    register _t x=0,f=1;
    register char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+(ch^48);
    return x*f;
}
 
int fa[MAXN*MAXN];
 
inline int find(int x){
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
 
inline void link(int x,int y){
    x = find(x),y = find(y);
    if(x == y) return;
    fa[x] = y; full[y] |= full[x];
    return;
}
 
struct node{
    int d[2],w;
    inline bool operator < (const node &a) const {return w<a.w;}
    inline int& operator [] (int x){return d[x];}
}my[MAXN*MAXN],all[MAXN*MAXN];
 
inline void add(node now){
    register int x , y;
    for(register int i = 0;i<4;i++){
        x = now[0] + dx[i] , y = now[1] + dy[i];
        if(x<1||x>n||y<1||y>m) continue;
        if(f[x][y] > now.w) continue;
        link(num[now[0]][now[1]],num[x][y]);
    }
    return;
}
 
int main(){
    n = read<int>() , m = read<int>();
    for(register int i = 1;i<=n;i++)
        for(register int j = 1;j<=m;j++){
            num[i][j] = ++cnt;
            all[cnt][0] = i; all[cnt][1] = j;
            all[cnt].w = read<int>();
            f[i][j] = all[cnt].w; 
            if(all[cnt].w > 0) my[++my_cnt] = all[cnt];
            else all[cnt].w = -all[cnt].w , f[i][j] = - f[i][j];
        }
    for(register int i = 1;i<=cnt;i++) fa[i] = i; 
    register int now = 1;
    std::sort(&my[1],&my[my_cnt+1]);std::sort(&all[1],&all[n*m+1]);
 
    for(register int i = 1;i<=my_cnt;i++){
        while(now <= cnt&&all[now].w <= my[i].w) add(all[now++]);
        if(!full[find(num[my[i][0]][my[i][1]])]) ++ Ans,full[find(num[my[i][0]][my[i][1]])] = 1;
    }
 
    printf("%d\n",Ans);
    return 0;
}