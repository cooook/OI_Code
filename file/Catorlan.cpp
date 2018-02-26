#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
typedef long long ll;
#define QAQ 10000
int n;
  
  
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}
  
struct bignum{
    int a[1005],len;
    inline int& operator [] (int x){return a[x];}
    bignum(){
        len=0;memset(a,0,sizeof a);
    }
  
    inline bignum operator = (ll k){
        while(k)a[++len]=k%QAQ,k/=QAQ;
        if(len==0) ++ len;
        return *this;
    }
  
    inline bignum operator * (const int b){
        bignum c;int tmp = 0;
        c.len = len;
        for(int i=1;i<=len;++i){
            c[i] = (a[i]*b+tmp)%QAQ;
            tmp = (a[i]*b+tmp)/QAQ;
        }
        while(tmp)c[++c.len] = tmp % QAQ , tmp /= QAQ;
        return c;
    }
  
    inline bignum operator / (const int k){
        bignum c;c.len = len;int tmp = 0;
        for(int i = len;i>=1;i--){
            c[i]=(a[i]+tmp)/k;
            tmp = (tmp+a[i])%k*QAQ;
        }
        while(!c[c.len])c.len--;
        return c;
    }
}Ans;
  
inline void print(bignum c){
    printf("%d",c[c.len]);
    for(int i=c.len-1;i>=1;i--)printf("%04d",c[i]);
    printf("\n");
}
  
int main(){
    n = read<int>();
    Ans = 1;
    for(int i=2;i<=n;i++)Ans = Ans * (4*i-2) / (i+1);
    print(Ans);
    getchar(); getchar();
}