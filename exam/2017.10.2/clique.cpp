#include <stdio.h>
#include <iostream>
#include <algorithm>
#define MAXN 200005
#define lowbit(x) ((x)&(-x))
typedef long long ll;
ll Hash[MAXN<<1],cnt,tree[MAXN<<1];
int n,sz,Ans;


template<typename _t>
inline _t read(){
	_t x = 0,f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch == '-') f = -f;
	for(;isdigit(ch);ch=getchar()) x = x * 10 + (ch ^ 48);
	return x*f;
}

struct Point{
	ll d[2],x,y;
	inline ll& operator [] (const int & x){return d[x];}
	inline void in(){
		x = read<ll>(),y = read<ll>();
		d[0] = x + y; Hash[++cnt] = d[0];
		d[1] = x - y; Hash[++cnt] = d[1];
	}
	inline bool operator < (const Point & a)const{return x < a.x;}
}pt[MAXN];

inline void Update(int x,int val) {
	for(;x<=sz;x+=lowbit(x)) tree[x] = std::max((ll)val,tree[x]);
}

inline int Query(int x){
	int Ans = 0;
	for(;x;x-=lowbit(x)) Ans = std::max((ll)Ans,tree[x]);
	return Ans;
}

int main(){
	freopen("clique.in","r",stdin);
	freopen("clique.out","w",stdout);
	n = read<int>();
	for(int i = 1;i<=n;i++) pt[i].in();
	std::sort(&Hash[1],&Hash[cnt+1]);
	sz = std::unique(&Hash[1],&Hash[cnt+1]) - Hash - 1;
	for(int i = 1;i<=n;i++) 
		pt[i][0] = std::lower_bound(&Hash[1],&Hash[sz+1],pt[i][0]) - Hash,
		pt[i][1] = std::lower_bound(&Hash[1],&Hash[sz+1],pt[i][1]) - Hash;
	std::sort(&pt[1],&pt[n+1]);
	for(int i = 1;i<=n;i++) {
		int now = Query(pt[i][1]) + 1;
		Ans = std::max(Ans,now);
		Update(pt[i][0],now);
	}
	printf("%d\n",Ans);
	return 0;
}
