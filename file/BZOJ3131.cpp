#pragma GCC optimize("O2")
#include <stdio.h>
#include <queue>
#include <algorithm>
#define mod 1000000007
typedef long long ll;
ll n,k,f[15][12][10005],pre[1000005],Ans[10005]; 
int cnt,N,digit[15];
bool vis[10005][10005];


inline void dfs(int len,int last,ll p) {
    if (len == N + 1) return;
    pre[++cnt] = p;
    for (; last <= 9; last++) dfs(len + 1,last,p * last);
}

inline void dp(ll x) {
    int tot = 0;
    while (x) digit[++tot] = x % 10,x /= 10;
    for (int i = 1; i < tot; ++i) 
        for (int j = 1; j <= 9; ++j) 
            for (int k = 1; k <= cnt; ++k) 
                (Ans[k] += f[i][j][k]) %= mod;
                
    ll QWQ = 1;
            
    for (int i = tot; i; --i) {
        for (int j = 1; j < digit[i]; ++j) { 
            for (int k = 1; k <= cnt; ++k)
                if (pre[k] * QWQ <= n && QWQ)
                    (Ans[std::lower_bound(&pre[1],&pre[cnt+1],pre[k] * QWQ) - pre] += f[i][j][k]) %= mod;
        }
        QWQ *= digit[i];
    }
}

inline void DP() {
    std::sort(&pre[1],&pre[cnt + 1]);
    cnt = std::unique(&pre[1],&pre[cnt+1]) - pre - 1;
    for (int i = 1; i <= 9; ++i) f[1][i][std::lower_bound(&pre[1],&pre[cnt+1],i) - pre] = 1;
    for (int i = 2; i <= 12; ++i)   
        for (int j = 1; j <= 9; ++j)
            for (int k = 1; k <= 9; ++k)
                for (int p = 1; p <= cnt; ++p)
                    if (pre[p] * j <= n)
                        (f[i][j][std::lower_bound(&pre[1],&pre[cnt+1],pre[p] * j) - pre] += f[i-1][k][p]) %= mod; 
    dp(n + 1); 
}

struct Node{
    int d[2]; ll val;
    inline int& operator [] (const int &a){
        return d[a];
    }
    inline bool operator < (const Node & a)const {
        if (val == a.val) {
            if (d[0] == a.d[0]) return d[1] > a.d[1];
            return d[0] > a.d[0];
        }
        return val < a.val;
    }
};

inline void G_Ans() {
    std::priority_queue<Node> Q;
    std::sort(&Ans[1],&Ans[cnt+1]);
    Q.push((Node){cnt,cnt,Ans[cnt]*Ans[cnt]});
    ll Final_Ans = 0;
    while (!Q.empty() && k) {
        k --;
        Node now;
        do 
            now = Q.top(),Q.pop(); 
        while((!Q.empty()) && vis[now[0]][now[1]]);
        if (vis[now[0]][now[1]]) break;
        (Final_Ans += now.val) %= mod;
        vis[now[0]][now[1]] = true;
        if (now[0] > 2) Q.push((Node){now[0] - 1,now[1],Ans[now[0]-1] * Ans[now[1]]});
        if (now[1] > 2) Q.push((Node){now[0],now[1] - 1,Ans[now[0]] * Ans[now[1]-1]});
    }
    printf("%lld\n",Final_Ans);
}

int main() {
    scanf("%lld%lld",&n,&k);
    ll x = n;  N = 12;
    dfs(0,2,1ll);
    DP(); G_Ans();
    // getchar(); getchar();
    return 0;
}
