# include <stdio.h>
# include <cstring>
# include <iostream>
# include <math.h>
const double eps = 1e-7;
const int MAXN = 1005;
const int MAXN_edge = 40400;
const double inf = 1e9;
int n,m,p;
int first[MAXN],e=2;
int S,T;
int u[MAXN],v[MAXN],w[MAXN],q[MAXN],d[MAXN];
  
  
struct edge{
    int u,v,next;
    double w;
}a[MAXN_edge];
  
void add(int u,int v,double w){
    a[e].u = u;
    a[e].v = v;
    a[e].next = first[u];
    a[e].w = w;
    first[u] = e++;
}
  
void push(int u,int v,double w){
    add(u,v,w);add(v,u,0.0);
}
  
inline bool bfs(){
    memset(d,-1,sizeof(d));
    d[S] = 1;
    int l = 0,r = 1;
    q[l] = S;
    while(l < r){
        int x = q[l++];
        if(x == T)return 1;
        for(int i = first[x]; i; i = a[i].next){
            int v = a[i].v;
            if(d[v] == -1 && a[i].w > eps){
                d[v] = d[x]+1;
                q[r++] = v;
            }
        }
    }
    return 0;
}
  
double dfs(int s,double cap){
    if (s == T || fabs(cap) < eps) return cap;
    double res = 0;
    for (int i = first[s]; i; i = a[i].next){
        int v = a[i].v;
        double w = a[i].w;
        if(d[v] == d[s] + 1 && w > eps){
            double Min = std::min(w,cap-res);
            w = dfs(v,Min);
            res += w;
            a[i].w -= w;
            a[i^1].w += w;
            if (fabs(res-cap)<eps) return res;
        }
    }
    if (fabs(res) < eps) d[s]=-1;
    return res;
}
  
inline double dinic(int S,int T){
    double Ans=0;
    while (bfs()) Ans += dfs(S,(double)inf);
    return Ans;
}
  
int main(){
    scanf("%d%d%d",&n,&m,&p);
    S=1;
    T=n;
    for (int i = 1; i <= m; i++){
        scanf("%d%d%d",&u[i],&v[i],&w[i]);
        push(u[i],v[i],(double)w[i]);
    }
    double max_flow,ret=0;
    max_flow=dinic(S,T);
    printf("%.0lf\n",max_flow);
    double l=0,r=max_flow;
    while (fabs(l-r)>eps){
        memset(first,0,sizeof(first));e=2;
        double mid=(l+r)*0.5;
        for (int i = 1; i <= m; i ++) push(u[i],v[i],std::min((double)w[i],mid));
        double res = dinic(S,T);
        if (fabs(max_flow-res)>eps)l=mid;
        else {
            ret = mid;
            r = mid;
        }
    }
    printf("%.6lf\n", ret*(double)p);
    return 0;
}