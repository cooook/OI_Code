#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using std::max;
using std::min;
int n,m,w[2][1333][15],nongmin,full,f[1<<11][1<<11],Ans;
 
 
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}
 
inline void __dfs__(int u,int d,int S){
    memset(f[u],0,sizeof f[u]);
    if(d == n - 1) {
        for(int i = 0;i<n-1;i++)
            if(S & (1<<i)) f[u][1] += w[1][u][i];
            else f[u][0] += w[0][u][i];
        return;
    }
    int _left = 1 << (n - d - 1);
    __dfs__(u<<1,d+1,S); 
    __dfs__(u<<1|1,d+1,S);
    for(int i = 0;i<=_left>>1;i++) for(int j = 0;j<=_left>>1;j++) f[u][i+j] = std::max(f[u][i+j],f[u<<1][i]+f[u<<1|1][j]);
    __dfs__(u<<1,d+1,S|(1<<d)); 
    __dfs__(u<<1|1,d+1,S|(1<<d));
    for(int i = 0;i<=_left>>1;i++) for(int j = 0;j<=_left>>1;j++) f[u][i+j] = std::max(f[u][i+j],f[u<<1][i]+f[u<<1|1][j]);
}

// qp765194523!` // lc's password 
 
int main(){
    n = read<int>(); m = read<int>();
    full = (1 << n) - 1; nongmin = 1 << (n-1);
    for(int i = nongmin;i<=full;i++)
        for(int j = n-2;~j;j--) w[1][i][j] = read<int>();
    for(int i = nongmin;i<=full;i++)
        for(int j = n-2;~j;j--) w[0][i][j] = read<int>();
    __dfs__(1,0,0);
    for(int i = 1;i<=m;Ans = std::max(Ans,f[1][i]),i++); 
    printf("%d\n",Ans);
    return 0;
}
