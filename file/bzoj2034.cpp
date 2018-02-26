#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#define MAXN 5005
int n,m,pos[MAXN],match[MAXN]; long long Ans = 0;


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct QWQ{
    int s,v,x,y;
}a[MAXN];

inline bool cmp1(const QWQ & a,const QWQ & b){
    return a.x < b.x;
}

inline bool cmp2(const QWQ & a,const QWQ & b){
    return a.v > b.v;
}

inline bool Check(int x,int y) {
    if (pos[y] > a[x].y) return false;
    if (!match[y]) {
        match[y] = x;
        return true;
    }
    else {
        if (a[match[y]].y < a[x].y) return Check(x,y + 1);
        else if (Check(match[y],y + 1)) {
            match[y] = x;
            return true;
        }
        else return false;
    }
}

int main(){
    n = read<int>();
    for (int i = 1;i<=n;i++) 
        a[i].x = read<int>(),a[i].y = read<int>(),a[i].v = read<int>();
    std::sort(&a[1],&a[n+1],cmp1);
    for (int i = 1;i<=n;i++) pos[i] = std::max(pos[i-1] + 1,a[i].x);
    a[1].s = 1;
    for (int i = 2;i<=n;i++) {
        a[i].s = a[i-1].s;
        while (pos[a[i].s] < a[i].x && a[i].s < n) ++ a[i].s;
    }
    std::sort(&a[1],&a[n+1],cmp2);
    for (int i = 1;i<=n;i++) if (Check(i,a[i].s)) Ans += a[i].v;
    printf("%lld\n",Ans);
    // getchar(); getchar();
    return 0;
}