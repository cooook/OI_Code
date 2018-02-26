#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100005
const double eps = 1e-7;
int n,s,L[MAXN],R[MAXN],que[MAXN]; double a[MAXN],b[MAXN],rate[MAXN],f[MAXN],Ans[MAXN],fr[MAXN];


inline bool cmp_f(int a,int b){return f[a] < f[b];}
inline bool cmp_xl(int x,int y){return a[x] / b[x] < a[y] / b[y];}
inline double K(int x,int y){return (fr[x] - fr[y]) / (f[x] - f[y]);}
inline bool Cmp(int x,int y,int z){
    if(f[x] == f[y]) return fr[x] >= fr[y];
    return K(z,x) >= K(y,x);
}

inline void CDQ(int l,int r){
    if(l == r) {fr[l] = f[l] / rate[l]; return;}
    register int mid = l + r >> 1,front = 1,back = 0; CDQ(l,mid);
    for(int i = l;i<=mid;i++) L[i] = i; std::sort(&L[l],&L[mid+1],cmp_f);
    for(int i = mid+1;i<=r;i++) R[i] = i; std::sort(&R[mid+1],&R[r+1],cmp_xl);
    for(int i = l;i<=mid;i++) {     
        while(front < back && Cmp(que[back - 1],que[back],L[i])) back --;
        que[++back] = L[i];
    }
    for(int i = mid+1;i<=r;i++) {
        while(front < back && K(que[front],que[front+1]) > -a[R[i]] / b[R[i]]) front ++;
        double now = f[que[front]] * a[R[i]] + fr[que[front]] * b[R[i]];
        Ans[R[i]] = std::max(Ans[R[i]],now);
    }
    for(int i = mid+1;i<=r;i++) Ans[i] = std::max(Ans[i-1],Ans[i]),f[i] = std::max(f[i],Ans[i] * rate[i] / (a[i] * rate[i] + b[i]));
    CDQ(mid+1,r);
}

int main(){
    scanf("%d%lf",&n,&Ans[1]);
    for(int i = 1;i<=n;i++) scanf("%lf%lf%lf",&a[i],&b[i],&rate[i]);
    f[1] = Ans[1] * rate[1] / (a[1] * rate[1] + b[1]);
    CDQ(1,n); printf("%.3f\n",Ans[n]);
    return 0;
}

//  num * a[i] + num/rate[i] * b[i] = s
//  (a[i] + 1/rate[i]*b[i]) * num = s;
//  num = s / (a[i] + 1/rate[i]*b[i]);
// Ans = s;
// for(int i = 2;i<=n;i++) {
//     for(int j = 1;j<i;j++) {
//         double now = f[j] * a[i] + f[j] / rate[j] * b[i];
//         Ans = std::max(Ans,now);
//     }
//     f[i] = Ans * rate[i] / (a[i] * rate[i] + b[i]);
// }
//  --> k > j
//  --> now[j] = f[j] * a[i] + f[j] / rate[j] * b[i]
//  --> now[k] = f[k] * a[i] + f[k] / rate[k] * b[i]
//  --> a[i] * (f[j] - f[k]) + (f[j] / rate[j] - f[k] / rate[k]) * b[i] > 0
//  --> a[i] * (f[k] - f[j]) < (f[j] / rate[j] - f[k] / rate[k]) * b[i]
//  --> (f[j] / rate[j] - f[k] / rate[k]) / (f[k] - f[j]) > a[i] / b[i]
//  --> (fr[j] - fr[k]) / (f[j] - f[k]) < - a[i] / b[i]
//  --> f[j] 不单调递增
//  --> CDQ分治,若 j 能更新 i 则 j < i && 上面辣个式子成立
//  --> 则以坐标为时间轴 进行CDQ 分治