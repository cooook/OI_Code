#include <stdio.h>
#include <math.h>
#include <cstring>
#include <algorithm>
typedef double ll;
typedef std::pair<int,ll> pa;
#define MAXN 50005
#define lowbit(x) ((x)&(-x))
int n,tree[MAXN],Mark[MAXN],T,sz,Ans,Hash[MAXN];
pa f[MAXN][2]; ll Sum,num[MAXN];


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

struct Operation{
    int d[2],t;
    inline int& operator [] (const int &x){return d[x];}
}a[MAXN],tmp[MAXN],b[MAXN];

inline bool cmp(Operation a,Operation b){
    if(a[0] == b[0]) {
        if(a[1] == b[1]) return a.t < b.t;
        return a[1] > b[1];
    }return a[0] > b[0];
}

inline bool __cmp(Operation a,Operation b){
    if(a[0] == b[0]) {
        if(a[1] == b[1]) return a.t > b.t;
        return a[1] < b[1];
    }return a[0] < b[0];
}

inline void Update_l(int x,int val,ll cnt){
    for(;x<=sz;x+=lowbit(x)) {
        if(Mark[x] != T) tree[x] = 0,num[x] = 0,Mark[x] = T;
        if(tree[x] < val) tree[x] = val,num[x] = cnt;
        else if(tree[x] == val) num[x] += cnt;
    }
    return;
}

inline pa Query_l(int x){
    pa Ans;Ans.first = 0;Ans.second = 0;
    for(;x;x-=lowbit(x)) {
        if(Mark[x] != T) tree[x] = 0,num[x] = 0,Mark[x] = T;
        if(tree[x] == Ans.first) Ans.second += num[x];
        else if(tree[x] > Ans.first) Ans.first = tree[x],Ans.second = num[x];
    }
    return Ans; 
}

inline void Update_r(int x,int val,ll cnt){
    for(;x;x-=lowbit(x)) {
        if(Mark[x] != T) tree[x] = 0,num[x] = 0,Mark[x] = T;
        if(tree[x] < val) tree[x] = val,num[x] = cnt;
        else if(tree[x] == val) num[x] += cnt;
    }
}

inline pa Query_r(int x){
    pa Ans;Ans.first = 0;Ans.second = 0;
    for(;x<=sz;x+=lowbit(x)) {
        if(Mark[x] != T) tree[x] = 0,num[x] = 0,Mark[x] = T;
        if(tree[x] == Ans.first) Ans.second += num[x];
        else if(tree[x] > Ans.first) Ans.first = tree[x],Ans.second = num[x];
    }
    return Ans; 
}

inline void CDQ(int l,int r){
    if(l == r) return;
    register int mid = l + r >> 1,L = l,R = mid + 1;
    for(int i = l;i<=r;i++) 
        if(a[i].t <= mid) tmp[L++] = a[i];
        else tmp[R++] = a[i];
    for(int i = l;i<=r;i++) a[i] = tmp[i];
    CDQ(l,mid);
    int j = l; T ++;
    for(int i = mid + 1;i<=r;i++) {
        for(;a[j][0] >= a[i][0] && j <= mid;j++) Update_r(a[j][1],f[a[j].t][0].first + 1,f[a[j].t][0].second);
        pa Tmp = Query_r(a[i][1]);
        if(f[a[i].t][0].first == Tmp.first) f[a[i].t][0].second += Tmp.second;
        else if(f[a[i].t][0].first < Tmp.first) f[a[i].t][0] = Tmp;
    }
    CDQ(mid+1,r);
    std::sort(&a[l],&a[r+1],cmp);
}

inline void __CDQ(int l,int r){
    if(l == r) return;
    register int mid = l + r >> 1,L = l,R = mid + 1;
    for(int i = l;i<=r;i++)
        if(b[i].t <= mid) tmp[L++] = b[i];
        else tmp[R++] = b[i];
    for(int i = l;i<=r;i++) b[i] = tmp[i];
    __CDQ(l,mid);
    int j = l; T ++;
    for(int i = mid+1;i<=r;i++) {
        for(;j<=mid && b[j][0] <= b[i][0];j++) Update_l(b[j][1],f[b[j].t][1].first+1,f[b[j].t][1].second);
        pa Tmp = Query_l(b[i][1]);
        if(f[b[i].t][1].first == Tmp.first) f[b[i].t][1].second += Tmp.second;
        else if(f[b[i].t][1].first < Tmp.first) f[b[i].t][1] = Tmp;
    }
    __CDQ(mid+1,r);
    std::sort(&b[l],&b[r+1],__cmp);
}

int main(){
    n = read<int>();
    for(int i = 1;i<=n;i++) {
        a[i][0] = read<int>();a[i][1] = read<int>();
        a[i].t = i; Hash[i] = a[i][1];
    }
    std::sort(&Hash[1],&Hash[n+1]); 
    sz = std::unique(&Hash[1],&Hash[n+1]) - Hash - 1;
    for(int i = 1;i<=n;i++) a[i][1] = std::lower_bound(&Hash[1],&Hash[sz+1],a[i][1]) - Hash;
    for(int i = 1;i<=n;i++) b[i] = a[n-i+1],b[i].t = i;
    for(int i = 1;i<=n;i++) f[i][0] = f[i][1] = std::make_pair(1,1);
    std::sort(&a[1],&a[n+1],cmp); CDQ(1,n);   
    std::sort(&b[1],&b[n+1],__cmp); __CDQ(1,n);
    for(int i = 1;i<=n;i++) Ans = std::max(Ans,f[i][0].first+f[n-i+1][1].first-1);
    for(int i = 1;i<=n;i++) if(f[i][0].first == Ans) Sum += f[i][0].second;
    printf("%d\n",Ans);
    for(int i = 1;i<=n;i++) {
        if(f[i][0].first + f[n-i+1][1].first - 1 != Ans) printf("%.8f ",0.0);
        else printf("%.8f ",(f[i][0].second * f[n-i+1][1].second)/Sum);
    }
    return 0;
}