#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef unsigned long long ll;
ll C[65][65],n,m,T,Ans;


template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}

inline int G_bit(int x){
    int Ans = 0;
    for(;x;x-=x&(-x)) Ans ++;
    return Ans;
}

inline void Get_C(){
    for(int i = 0;i<=64;i++) {
        C[i][0] = 1;
        for(int j = 1;j<=i;j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
}

inline bool Judge(ll mid,ll x){
	ll Ans = 0; int k = 0;
    for(ll i = 63;~i;i--)
        if(mid & (1ll<<i)) {
        	k ++;
            Ans += C[i][m-k];
        }
    return Ans >= x;
}

inline ll Calc(ll x){
    ll l = 1,r = 1ll<<62,mid,Ans;
    while(l<=r){
        mid = (l + r) >> 1;
        if(Judge(mid,x)) Ans = mid,r = mid - 1;
        else l = mid + 1;
    }
    return Ans;
}

int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
    Get_C(); T = read<int>();
    while(T --) {
        n = read<ll>(); m = read<int>();
        if(m==1){printf("1 -1\n");continue;}
        if(m==64){printf("1 9223372036854775807\n");continue;}
        if(m==63){printf("1 4611686018427387903\n");continue;}
        ll l = Calc(n),r = Calc(n + 1);
        cout << l << " " << r - l<< endl;
    }
    return 0;
}
