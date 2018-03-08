#pragma pack(1)
#include <cstdio>
#include <cstring>
#include <algorithm>
#define diymax(a,b) ((a)>(b)?(a):(b))
#define diymin(a,b) ((a)<(b)?(a):(b))
char xB[(1<<15)+10],*xS,*xT;
#define gtc (xS==xT&&(xT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xT)?0:*xS++)
inline void read(int &x){
  register char ch=gtc;
  for(x=0;ch<'0'||ch>'9';ch=gtc);
  for(;ch>='0'&&ch<='9';x=(x<<1)+(x<<3)+ch-'0',ch=gtc);
}
const int N=1000010;
const int P=1000000007;
const int Inf=0x3f3f3f3f;
struct Ans{
  int max,sum;
  inline void update(){if(max!=0)++max;}
  inline void redef(){max=sum=0;}
  inline void print(){printf("%d %d\n",max,sum);}
}f[N];
inline Ans merge(Ans a,Ans b){
  if(a.max!=b.max)return a.max>b.max?a:b;
  a.sum=(a.sum+b.sum)%P;
  return a;
}
struct Segment_Tree{
  Segment_Tree *ch[2];
  Ans ans;
  inline void pushup(){ans=merge(ch[0]->ans,ch[1]->ans);}
}node[N<<1],*root;
int sz;
#define newnode (node+(sz++))
#define ___ ((l+r)>>1)
inline void build(Segment_Tree *&p,int l,int r){
  p=newnode,p->ch[0]=p->ch[1]=NULL,p->ans.redef();
  if(l==r)return;
  build(p->ch[0],l,___),build(p->ch[1],___+1,r);
}
inline void update(Segment_Tree *p,int l,int r,int pos,int opt){
  if(l==r){
    if(opt==-1)p->ans.redef();
    else p->ans=f[pos],p->ans.update();
    return;
  }
  if(pos<=___)update(p->ch[0],l,___,pos,opt);
  else update(p->ch[1],___+1,r,pos,opt);
  p->pushup();
}
inline void query(Segment_Tree *p,int l,int r,int z,int y,Ans &ans){
  if(z<=l&&r<=y){
    ans=merge(ans,p->ans);
    return;
  }
  if(z<=___)query(p->ch[0],l,___,z,y,ans);
  if(___<y)query(p->ch[1],___+1,r,z,y,ans);
}
int n,min[N],max[N];
struct V{int to,next,w;}c[N];
int head[N],t;
inline void add(int x,int y,int z){c[++t].to=y,c[t].next=head[x],head[x]=t,c[t].w=z;}
inline void CDQ(int l,int r){
  if(l==r)return;
  int mid=___;
  CDQ(l,mid);
  register int i,j,mini,maxi;
  sz=0,t=0;
  build(root,l,mid);
  memset(head+mid+1,0,(r-mid)<<2);
  mini=-Inf,maxi=Inf;
  for(i=mid;i>=l;--i){
    if(maxi<mini)break;
    if(maxi+i>mid&&mini+i<=r){
      if(mini+i<=mid)add(mid+1,i,1);
      else add(mini+i,i,1);
      if(maxi+i<r)add(maxi+i+1,i,-1);
    }
    maxi=diymin(maxi,max[i]);
    mini=diymax(mini,min[i]);
  }
  mini=-Inf,maxi=Inf; 
  for(i=mid+1;i<=r;++i){
    for(j=head[i];j;j=c[j].next)
      update(root,l,mid,c[j].to,c[j].w);
    maxi=diymin(maxi,max[i]);
    mini=diymax(mini,min[i]);
    if(maxi<mini)break;
    if(i-mini>=l&&i-maxi<=mid)
      query(root,l,mid,diymax(l,i-maxi),diymin(mid,i-mini),f[i]);
  }
  CDQ(mid+1,r);
}
int main(){
  freopen("Cooook.in","r",stdin);
  freopen("wq.out","w",stdout);
  read(n);
  register int i,maxi=Inf,mini=-Inf;
  for(i=1;i<=n;++i){
    read(min[i]),read(max[i]);
    maxi=diymin(maxi,max[i]);
    mini=diymax(mini,min[i]);
    if(mini<=i&&i<=maxi)f[i].max=1,f[i].sum=1;
  }
  CDQ(1,n);
  if(f[n].max==0)puts("NIE");
  else f[n].print();
  return 0;
}
