#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define fi first
#define se second
#define int long long 
#define mk(x,y) std::make_pair(x,y)
typedef std::pair<int,int> pa;
typedef std::vector<pa> Vec;


int T,k,m,prime[305],cnt,Max[305];
bool _prime[305]; Vec Ans;

template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Update(int p) {
    int x = k;
    while (Max[x - 1] < p && x) x--;
    for (int i = k; i > x; i--) Max[i] = Max[i - 1];
    Max[x] = p;
}

Vec expend(Vec a,int p) {
    Vec Ans; Ans.clear();
    for (std::vector<pa>::iterator it = a.begin(); it != a.end(); ++ it) {
        int now = 1,P = 1;
        while (m / P >= it -> fi) {
            Ans.push_back(mk(it->fi * P,it->se * now));
            now ++; P *= p;
        }
    }
    std::sort(Ans.begin(),Ans.end());
    std::unique(Ans.begin(),Ans.end());
    return Ans;
}

Vec change(Vec a) {
    memset(Max,0,sizeof Max);
    Vec Ans; Ans.clear();
    for (std::vector<pa>::iterator it = a.begin(); it != a.end(); ++ it) {
        if (it -> se >= Max[k]) {
            Update(it -> se);
            Ans.push_back(*it);
        }
    }
    return Ans;
}

inline void Prime() {
    for (int i = 2; i <= 293; i++) {
        if (!_prime[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= 293; j++) {
            _prime[i*prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

inline void Get_Ans() {
    Ans.push_back(mk(1,1));
    for (int i = 1; i <= cnt; i++) {
        Ans = expend(Ans,prime[i]);
        Ans = change(Ans);
    }
}

signed main() {
    Prime();
    T = read<int>(); k = read<int>(); m = read<int>();
    Get_Ans();
    while (T --) printf("%lld\n",Ans[read<int>()-1].fi);
    return 0;
}