#pragma GCC optimize("O3")
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using namespace std;
int n,m,BASE = 10000;
 
 
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}
 
struct bignum{
    int a[10000],len;
    inline int& operator [] (const int & x){return a[x];}
    bignum(){
        memset(a,0,sizeof a); len = 0;
    }

    inline bignum operator + (const bignum & x)const{
        bignum Ans; Ans.len = max(x.len,len) + 1;
        for(int i = 1;i<=Ans.len;i++) {
            Ans.a[i] += x.a[i] + a[i];
            Ans.a[i+1] += Ans.a[i] / BASE;
            Ans.a[i] %= BASE;
        }
        while(Ans.a[Ans.len] == 0) --Ans.len;
        return Ans;
    }

    inline bignum operator - (const bignum & c)const{
        bignum Ans; Ans.len = len; bignum b = *this;
        for(register int i = 1;i<=c.len||i<=len;i++) {
            if(b.a[i] < c.a[i]) -- b.a[i+1] , b.a[i] += BASE;
            Ans.a[i] = b.a[i] - c.a[i];
        }
        while(Ans.a[Ans.len] == 0 && Ans.len > 1) -- Ans.len;
        return Ans;
    }

    inline bignum operator * (const int b){
        bignum c;int tmp = 0;
        c.len = len;
        for(int i=1;i<=len;++i){
            c[i] = (a[i]*b+tmp)%BASE;
            tmp = (a[i]*b+tmp)/BASE;
        }
        while(tmp)c[++c.len] = tmp % BASE , tmp /= BASE;
        return c;
    }
  
    inline bignum operator / (const int k){
        bignum c;c.len = len;int tmp = 0;
        for(int i = len;i>=1;i--){
            c[i]=(a[i]+tmp)/k;
            tmp = (tmp+a[i])%k*BASE;
        }
        while(!c[c.len])c.len--;
        return c;
    }

    inline void print(){
        printf("%d",a[len]);
        for(int i = len-1;i>=1;i--) printf("%04d",a[i]);
    }
}Ans;

inline bignum C(int n,int m){
    int A = n,B = m; bignum Ans;Ans[1] = 1;Ans.len = 1;
    for(int i = 1;i<=m;i++) Ans = Ans * (n-i+1);
    for(int i = 1;i<=m;i++) Ans = Ans / i;
    return Ans;
}
 
int main(){
    n = read<int>(); m = read<int>();
    (C(n+m,m) - C(n+m,m-1)).print();
    return 0;
}