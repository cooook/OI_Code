#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN = 1005;
const int inf = 0x3f3f3f3f;
const int MAXN_edge = 100005;
int c[MAXN],first[MAXN],e=2,dis[MAXN],pre[MAXN],n,m,k,S,T,ans;
bool vis[MAXN];
 
 
struct edge{
    int u,v,next,w,c;
}a[MAXN_edge];
 
void add(int u,int v,int w,int c){
    a[e].u=u;a[e].w=w;
    a[e].v=v;a[e].c=c;
    a[e].next=first[u];
    first[u]=e++;
}
 
void push(int u,int v,int w,int c){
    add(u,v,w,c);add(v,u,0,-c);
}
 
inline bool bfs(){
    memset(dis,0xef,sizeof(dis));
    memset(pre,0,sizeof(pre));
    dis[S]=0;
    vis[S]=1;
    queue<int>q;
    q.push(S);
    while(!q.empty()){
        int k=q.front();
        q.pop();
        vis[k]=0;
        for(int i=first[k];i;i=a[i].next){
            int v=a[i].v;
            if(dis[v]<dis[k]+a[i].c && a[i].w){
                pre[v]=i;
                dis[v]=dis[k]+a[i].c;
                if(!vis[v])vis[v]=1,q.push(v);
            }
        }
    }
    if(dis[T]==0xefefefef) return false;  
    int x=inf;
    for(int i=pre[T];i;i=pre[a[i].u])
        x=min(x,a[i].w);
    ans+=x*dis[T];
    for(int i=pre[T];i;i=pre[a[i].u]){
        a[i].w-=x;
        a[i^1].w+=x;
    }
    return true;
}
 
int main(){
     
     
     
    scanf("%d%d%d",&n,&m,&k);
 
    T=1001;
 
    for(int i=1;i<=n;i++)scanf("%d",&c[i]);
    for(int i=1;i<=n;i++)push(i-1,i,k,0);
    for(int i=1;i<=n;i++){
        if(i+m<=n)push(i,i+m,1,c[i]);
        else push(i,T,1,c[i]);
    }
    push(n,T,k,0);
 
    while(bfs());
 
    printf("%d\n",ans);
}