struct bignum{
    int a[MAXN],len;
    bignum(){memset(a,0,sizeof a);len = 0;}
    
    inline bool operator < (const bignum & b)const{
        if(len != b.len) return len < b.len;
        for(int i  = len;i>=1;i--) if(a[i] != b.a[i]) return a[i] < b.a[i];
        return 0;
    }
    
    inline bool operator == (const bignum & b)const{
        if(len != b.len) return 0;
        for(int i = len;i>=1;i--) if(a[i] != b.a[i]) return 0;
        return 1;
    }
    
    inline bool operator != (const bignum & b)const{return *this == b ? 0:1;}
    
    inline void operator = (const char *x){
        register int tmp=strlen(x),t=1,k=0,js=0;
        for(int i=tmp-1;i>=0;--i){
            k+=t*(x[i]-'0'),t*=10;
            if(t==BASE) t=1,a[++len]=k,k=0;
        }
        if(k) a[++len]=k;
    }
    
    inline bignum operator - (const bignum &c)const{
        bignum ans; ans.len = len; bignum b = *this;
        for(register int i = 1;i<=c.len||i<=len;i++) {
            if(b.a[i] < c.a[i]) -- b.a[i+1] , b.a[i] += BASE;
            ans.a[i] = b.a[i] - c.a[i];
        }
        while(ans.a[ans.len] == 0 && ans.len > 1) -- ans.len;
        return ans;
    }
        
    inline bignum operator / (const int x){
        bignum ans = *this; 
        for(int i = len;i>=1;i--) ans.a[i-1] += (long long)ans.a[i] % x * BASE,ans.a[i] /= x;
        while(!ans.a[ans.len] && ans.len > 1) -- ans.len;
        return ans;
    }
    
    inline bignum operator * (const int x){
        bignum ans; ans.len = ++ len;
        for(register int i = 1;i<=ans.len;i++) {
            ans.a[i] += a[i] * x; ans.a[i+1] += ans.a[i]/BASE; ans.a[i] %= BASE;
        }
        while(!ans.a[ans.len] && ans.len > 1) -- ans.len;
        return ans;
    }
    
    inline bool Judge(){return a[1] & 1;}
    inline void print(){printf("%d",a[len]);for(register int i = len-1;i>=1;i--) printf("%09d",a[i]);printf("\n");}
    inline void in(){scanf("%s",s);*this=s;}
}a,b;