# include <stdio.h>
# include <iostream> 
typedef long long ll; 
int n, mod, T, tree[100005], cnt; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Update(register int x, register int val) {
    if (!x) return cnt += val, void();
    for (; x < mod; x += x&(-x)) tree[x] += val; 
}

inline int Sum(register int x) {
    if (x < 0) return 0; 
    register int Ans = 0;
    for (; x; x -= x&(-x)) Ans += tree[x];
    return Ans + cnt; 
}

# define Query(l, r) (Sum(r) - Sum(l - 1))

int main() {
    T = read(); 
    for (int Case = 1; Case <= T; ++ Case) {
        n = read(), mod = read(); 
        ll Ans = 0;
        for (register int i = 1; i <= n; ++i) Update(1ll * i * i * i % mod, 1);
        for (register int i = 1; i <= n; ++i) {
            register int t = 1ll * i * i % mod, st = (t + 1) % mod, l, r;
            if (mod - st > i) Ans += Query(st, (t + i) % mod);
            else {
                Ans += Query(st, mod - 1), l = mod - st + 1, r = i;
                Ans += 1ll * (r - l + 1) / mod * Query(0, mod - 1);
                if ((r - l + 1) % mod) Ans += Query(0, (t + i) % mod);
            }
            Update(1ll * i * i * i % mod, -1);
        }   
        printf("Case %d: %lld\n", Case, Ans);
    }
    return 0; 
}