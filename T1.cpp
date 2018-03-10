# include <bits/stdc++.h> 


struct bignum {
    int a[1005]; int cnt;
    bignum() { memset(a, 0, sizeof a); cnt = 0; }
    inline bignum operator << (const bignum &x, int k) {
        bignum Ans; Ans.cnt = x.cnt + k;
        for (int i = Ans.cnt - 1; i >= k; --i)
            Ans.a[i] = x.a[i - k];
        return Ans; 
    }
    inline bignum operator + (const bignum &x) const {
        bignum Ans;  Ans.cnt = std::max(cnt, x.cnt) + 1;
        for (int i = 0; i < Ans.cnt; ++i) {
            Ans.a[i] += (a[i] + x.a[i]);
            Ans.a[i + 1] += Ans.a[i] >> 1;
            Ans.a[i] &= 1; 
        }
        while (!Ans.a[Ans.cnt - 1]) -- Ans.cnt;
        return Ans; 
    }

    inline void Print() {
        for (int i = cnt - 1; ~i; --i)
            printf("%d", a[i]);
    }
}_10[151];

std::vector<bignum> f[150]; 

int main() {
    n = read(); 
    bignum tmp; 
    _10[0].a[0] = 1;
    _10[0].cnt = 1;
    f[0].push(tmp);
    for (int i = 1; i <= 150; ++i) _10[i] = (_10[i - 1] << 3) + (_10[i - 1] << 1), f[i].push(_10[i]);
    for (int i = 0; i <= 150; ++i)
        for (auto j:f[i])
            for (int k = i + 1; k <= 150; ++k)
                if (j.a[k]) break;
                else f[k].push(j + _10[k]);
    for (int i = 0; i <= 150; ++i) {
        if (n > f[i].size()) n -= f[i].size();
        else return f[i][n - 1].Print(), 0; 
    }
    return 0; 
}