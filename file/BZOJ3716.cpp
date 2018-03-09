# include <bits/stdc++.h> 
# define int long long 
const int MAXN = 2e5 + 5;
int n, m, w, h; 


char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Point {
    int x, y, v; 
    inline bool operator < (const Point &a) const {
        return x == a.x ? y < a.y : x < a.x; 
    }
} pt[MAXN << 1];

struct Data {
    int y, v;
    inline bool operator < (const Data &x) const { return y < x.y;  }
} ; 

std::multiset<Data> S;
std::multiset<Data>::iterator it;

signed main() {
    n = read(), m = read();
    w = read(), h = read(); 
    register int x, y; 
    for (int i = 1; i <= n; ++i) x = read() * h, y = read() * w, pt[i].x = x + y, pt[i].y = y - x, pt[i].v = read();
    for (int i = 1; i <= m; ++i) x = read() * h, y = read() * w, pt[i + n].x = x + y, pt[i + n].y = y - x, pt[i + n].v = -read();
    std::sort(&pt[1], &pt[n + m + 1]);
    register int Ans = 0, v;
    for (int i = 1; i <= n + m; ++i)
        for (y = pt[i].y, v = pt[i].v; v; Ans -= it -> v, v += it -> v, S.erase(it)) {
            it = S.upper_bound((Data){y,0});
			if (v > 0) { S.insert((Data){y,v}); Ans += v; break; }
			else if (it == S.begin()) break;
			else y = (--it) -> y;
        }
    printf("%lld\n", Ans);
    return 0;   
}
