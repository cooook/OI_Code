#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 50005*2;
int cnt=0,use[MAXN],root[MAXN],sz,hhhh[MAXN],a[MAXN],n,T,m,num,S[MAXN];
 
 
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}
 
struct node{int l,r,sum;}tree[MAXN*80];
void insert(int &o,int old,int l,int r,int x,int val){
    o=++cnt;
    tree[o]=tree[old];
    tree[o].sum+=val;
    if(l==r)return;
    int m=l+r>>1;
    if(x<=m)insert(tree[o].l,tree[old].l,l,m,x,val);
    else insert(tree[o].r,tree[old].r,m+1,r,x,val);
    return;
}
 
inline int lowbit(int x){return (x)&(-x);}
inline void add(int x,int pos,int val){for(;x<=n;x+=lowbit(x))insert(S[x],S[x],1,sz,pos,val);}
 
void build(int &o,int l,int r){
    o=++cnt;
	tree[o].sum=0;
    if(l==r)return;
    int m=l+r>>1;
    build(tree[o].l,l,m);
    build(tree[o].r,m+1,r);
}
 
inline int qsum(int x){
    int ans=0;
    for(;x;x-=lowbit(x))ans+=tree[tree[use[x]].l].sum;
    return ans;
}
 
int query(int l,int r,int k){
    for(int i=l-1;i;i-=lowbit(i))use[i]=S[i];
    for(int i=r;i;i-=lowbit(i))use[i]=S[i];
    int L=1,R=sz,lrt=root[l-1],rrt=root[r];
    while(L<R){
        int tmp = qsum(r)-qsum(l-1)+tree[tree[rrt].l].sum-tree[tree[lrt].l].sum;
        int m=L+R>>1;
        if(tmp>=k){
            for(int i=l-1;i;i-=lowbit(i))use[i]=tree[use[i]].l;
            for(int i=r;i;i-=lowbit(i))use[i]=tree[use[i]].l;
            lrt=tree[lrt].l;rrt=tree[rrt].l;
            R=m;
        }
        else{
            for(int i=l-1;i;i-=lowbit(i))use[i]=tree[use[i]].r;
            for(int i=r;i;i-=lowbit(i))use[i]=tree[use[i]].r;
            lrt=tree[lrt].r;rrt=tree[rrt].r;
            L=m+1;k-=tmp;
        }
    }
    return L;
}
 
inline int Init(){sort(&hhhh[1],&hhhh[num+1]);sz=unique(&hhhh[1],&hhhh[num+1])-hhhh-1;}
inline int Hash(int x){return lower_bound(&hhhh[1],&hhhh[sz+1],x)-hhhh;}
struct operation{int l,r,op,k;}op[MAXN];
 
int main(){
    freopen("dynrank.in","r",stdin);
    freopen("dynrank.out","w",stdout);
    T=read<int>();
    while(T--){
        cnt=0;num=0;
        n=read<int>();m=read<int>();
        for(int i=1;i<=n;i++)a[i]=read<int>(),hhhh[++num]=a[i];
        for(int i=1;i<=m;i++){
            char ch=getchar();
            for(;ch!='Q'&&ch!='C';ch=getchar());
            op[i].op=(ch=='Q');
            op[i].l=read<int>();
            op[i].r=read<int>();
            if(ch=='Q')op[i].k=read<int>();
            else hhhh[++num]=op[i].r;
        }
        Init();
        build(root[0],1,sz);
        for(int i=1;i<=n;i++)insert(root[i],root[i-1],1,sz,Hash(a[i]),1);
        for(int i=1;i<=n;i++)S[i]=root[0];
        for(int o=1;o<=m;o++){
            if(op[o].op==0){
                add(op[o].l,Hash(a[op[o].l]),-1);
                add(op[o].l,Hash(op[o].r),1);
                a[op[o].l]=op[o].r;
            }
            else printf("%d\n",hhhh[query(op[o].l,op[o].r,op[o].k)]);
        }
    }
}