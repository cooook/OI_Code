#include <stdio.h>
#include <cstring>
#include <iostream>
#define MAXN 100005
typedef long long ll;
int n,m,a[MAXN];


template<typename _t>
inline _t read(){
	_t x = 0,f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch == '-') f = -f;
	for(;isdigit(ch);ch=getchar()) x = x * 10 + (ch ^ 48);
	return x*f;
}

namespace solver_40{
	inline void Mod(){
		int l = read<int>(),r = read<int>(),x = read<int>();
		for(int i = l;i<=r;i++) a[i] %= x;
	}
	inline void Change(){
		int x = read<int>(),y = read<int>();
		a[x] = y;
	}
	inline void Query(){
		int x = read<int>(),y = read<int>();
		long long Ans = 0;
		for(int i = x;i<=y;i++) Ans += a[i];
		printf("%lld\n",Ans);
	}
	void Main(){
		while(m --){
			register int op = read<int>();
			if(op == 1) Query();
			if(op == 2) Mod();
			if(op == 3) Change();
		}
	}
}

namespace Segment_Tree{
	ll sum[MAXN<<2],maxn[MAXN<<2],tag[MAXN<<2];
	
	inline void Push_Up(int o,int l,int r){
		if(l == r) return;
		sum[o] = sum[o<<1] + sum[o<<1|1];
		maxn[o] = std::max(maxn[o<<1],maxn[o<<1|1]);
	}
	
	inline void Update(int o,int l,int r,int x,int y) {
		if(l == r) {sum[o] = y,maxn[o] = y;return;}
		register int mid = l + r >> 1;
		if(x<=mid) Update(o<<1,l,mid,x,y);
		else Update(o<<1|1,mid+1,r,x,y);
		Push_Up(o,l,r);
	}
	
	inline void Mod(int o,int l,int r,int x,int y,int mod) {
		if(maxn[o] < mod) return;
		if(l == r) {sum[o] %= mod,maxn[o] %= mod; return;}
		register int mid = l + r >> 1;
		if(x<=mid) Mod(o<<1,l,mid,x,y,mod);
		if(mid<y) Mod(o<<1|1,mid+1,r,x,y,mod);
		Push_Up(o,l,r);
	}
	
	inline ll Query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return sum[o];
		register int mid = l + r >> 1;ll Ans = 0;
		if(x<=mid) Ans += Query(o<<1,l,mid,x,y);
		if(mid<y) Ans += Query(o<<1|1,mid+1,r,x,y);
		return Ans;
	}
	
	inline void build(int o,int l,int r){
		if(l == r) maxn[o] = sum[o] = a[l];
		else{
			register int mid =  l + r >> 1;
			build(o<<1,l,mid);
			build(o<<1|1,mid+1,r);
			Push_Up(o,l,r);
		}
		return;
	}
	
	inline void solve(){
		build(1,1,n);
		while(m --){
			register int op = read<int>(),x,y,z;
			if(op == 1){
				x = read<int>(),y = read<int>();
				printf("%lld\n",Query(1,1,n,x,y));
			}
			if(op == 2){
				x = read<int>(),y = read<int>(),z = read<int>();
				Mod(1,1,n,x,y,z);
			}
			if(op == 3){
				x = read<int>(),y = read<int>();
				Update(1,1,n,x,y);
			}
		}
	}
}

int main(){
	freopen("mod.in","r",stdin);
	freopen("mod.out","w",stdout);
	n = read<int>(); m = read<int>();
	for(int i = 1;i<=n;i++) a[i] = read<int>();
	if(n <= 1000 && m <= 1000) {solver_40::Main(); return 0;}
	Segment_Tree::solve();
	return 0;
}
