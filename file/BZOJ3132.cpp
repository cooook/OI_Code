#include <stdio.h>
const int MAXN = 1 << 11 | 5;
int n,m;


template <typename _t>
inline _t read(){
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' | ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct BIT{
    #define lowbit(_) ((_)&(-_))
    int tree[MAXN][MAXN];
    inline void Update(int x,int y,int val){
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
                tree[i][j] += val;
    }

    inline int Query(int x,int y){
        int Ans = 0;
        for (int i = x; i; i -= lowbit(i))
            for (int j = y; j; j -= lowbit(j))
                Ans += tree[i][j];
        return Ans;
    }
}T[4];

inline void Update(int x,int y,int z){
    T[0].Update(x,y,z); T[1].Update(x,y,x*z); T[2].Update(x,y,y*z); T[3].Update(x,y,x*y*z);
}

inline int Query(int x,int y){
    return T[0].Query(x,y) * (x*y+x+y+1) - T[1].Query(x,y) * (y + 1) - T[2].Query(x,y) * (x + 1) + T[3].Query(x,y);
}

int main(){
    n = read<int>(); m = read<int>();
    char s[3]; int a,b,c,d,e;
    while (scanf("%s",s) != EOF){
        a = read<int>(),b = read<int>(),c = read<int>(),d = read<int>();
        if (s[0] == 'L'){
            e = read<int>();
            Update(c+1,d+1,e); Update(a,b,e); Update(c+1,b,-e); Update(a,d+1,-e);
        }
        else printf("%d\n",Query(c,d)-Query(c,b-1)-Query(a-1,d)+Query(a-1,b-1));
    }
    return 0;
}
