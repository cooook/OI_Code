#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
using std::max;
using std::min;
const int MAXN = 200010;
int tot,Ans,now,n,len;
 
 
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-f;
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return x*f;
}
 
struct Point{
    int d[3];
    inline int& operator [] (int x){return d[x];}
    inline bool operator < (const Point &a)const{
        return d[now]==a.d[now]?d[now^1]<a.d[now^1]:d[now]<a.d[now];
    }
}pt[MAXN],in;
 
struct node{
    node *ls,*rs;
    Point point;
    int mn[2],mx[2],sum;
    inline void Update(node *p){
        if(!p)return;
        for(int i=0;i<=1;i++)mn[i]=min(mn[i],p->mn[i]);
        for(int i=0;i<=1;i++)mx[i]=max(mx[i],p->mx[i]);
    }
 
    inline void Maintain(){
        sum = point[2];
        if(ls)Update(ls),sum+=ls->sum;
        if(rs)Update(rs),sum+=rs->sum;
    }
 
    inline bool in(node *cur){
        return mn[0]>=cur->mn[0]
        && mx[0]<=cur->mx[0]
        && mn[1]>=cur->mn[1]
        && mx[1]<=cur->mx[1];
    }
 
    inline bool out(node *cur){
        return mn[0]>cur->mx[0]
        || mx[0]<cur->mn[0]
        || mn[1]>cur->mx[1]
        || mx[1]<cur->mn[1];
    }
 
    inline bool self(node *cur){
        return point[0]>=cur->mn[0]
        && point[0]<=cur->mx[0]
        && point[1]>=cur->mn[1]
        && point[1]<=cur->mx[1];
    }
 
    node(Point x){
        ls = rs = NULL;
        point = x;
        mn[0]=mx[0]=x[0];
        mn[1]=mx[1]=x[1];
        sum = x[2];
    }
    node(){}
}*root,*cur=new node();
 
void build(node *&o,int l,int r,int d=0){
    if(l>r)return;
    now = d;int mid = l+r>>1;
    std::nth_element(&pt[l],&pt[mid],&pt[r+1]);
    o = new node(pt[mid]);
    build(o->ls,l,mid-1,d^1);
    build(o->rs,mid+1,r,d^1);
    o->Maintain();
}
 
void dfs(node *o){
    if(!o)return;
    dfs(o->ls);
    pt[++len]=o->point;
    dfs(o->rs);
    delete o;
}
 
void Query(node *o){
    if(!o)return;
    if(o->in(cur)){Ans+=o->sum;return;}
    if(o->out(cur))return;
    if(o->self(cur))Ans+=o->point[2];
    Query(o->ls);Query(o->rs);
}
 
void insert(node *&o,int d=0){
    if(!o){o=new node(in);return;}
    if(o->point[d]>in[d])insert(o->ls,d^1);
    else insert(o->rs,d^1);
    o->Maintain();
}
 
inline void rebuild(){
    len = 0;
    dfs(root);
    build(root,1,len);
}
 
void Up(){
    in[0]=read<int>()^Ans,in[1]=read<int>()^Ans,in[2]=read<int>()^Ans;
    insert(root);tot++;
    if(tot == 6666)tot=0,rebuild();
}
 
void Query(){
    cur->mn[0]=read<int>()^Ans,
    cur->mn[1]=read<int>()^Ans,
    cur->mx[0]=read<int>()^Ans;
    cur->mx[1]=read<int>()^Ans;
    Ans = 0;Query(root);
    printf("%d\n",Ans);
}
 
int main(){
    n=read<int>();
    while(1){
        register int op = read<int>();
        if(op==3)break;
        if(op==1)Up();
        if(op==2)Query();
    }
}