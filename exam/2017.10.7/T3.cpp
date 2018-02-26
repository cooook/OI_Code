#pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define MAXN 100005

typedef long long ll;
typedef std::vector<int> Ve;

int n,m,cnt[MAXN][351],_is,q,Num,id[MAXN],qaq[MAXN];
Ve G[MAXN],Q[MAXN]; 
ll val[MAXN],sum[MAXN],add[351];
bool is[MAXN];


template<typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

int main(){
    n = read<int>(); m = read<int>();q = read<int>(); _is = sqrt(n+0.5);
    for (int i = 1; i <= n; i++) val[i] = read<ll>();
    for (int i = 1; i <= m; i++) {
        register int size = read<int>();
        if (size >= _is) is[i] = true,id[i] = ++ Num;
        else is[i] = false;
        for (int j = 1; j <= size;j ++) {
            register int v = read<int>();
            G[i].push_back(v);
            if (is[i]) Q[v].push_back(Num),sum[Num] += val[v];
        }
    }

    for (int i = 1; i <= m; i++){
        register int size = G[i].size();
        for (int j = 0; j < size; j++) {
            register int u = G[i][j],s = Q[u].size();
            for (int k = 0; k < s; k++){
                register int v = Q[u][k];
                cnt[i][v] ++;
            }
        }
    }

    while (q --) {
        register int op = read<int>(),x = read<int>();
        ll y;
        if (op == 1) {
            if (is[x]) {
                ll Ans = 0;
                Ans += sum[id[x]];
                for (int i = 1; i <= Num; i++) Ans += cnt[x][i] * add[i];
                printf("%lld\n",Ans);        
            } 
            else {
                ll Ans = 0;
                for (int i = 0; i < G[x].size(); i++) Ans += val[G[x][i]];
                for (int i = 1; i <= Num; i++) Ans += cnt[x][i] * add[i];
                printf("%lld\n",Ans);
            }
        }
        else {
            y = read<ll>();
            if (is[x]) add[id[x]] += y;
            else {
                for (int i = 0; i < G[x].size(); i++) val[G[x][i]] += y; 
                for (int i = 1; i <= Num; i++) sum[i] += cnt[x][i] * y;
            }
        }
    }
    return 0;
}