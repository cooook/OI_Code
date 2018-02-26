# include <stdio.h> 
# include <algorithm>
# define int long long 
const int MAXN = 50005;
int cnt, n;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Line {
    int k, b, id;
    Line(int K = 0, int B=0, int ID=0) {k = K; b = B; id = ID;}
    inline bool operator < (const Line &x) const { return k == x.k ? b > x.b : k > x.k; }
    inline int operator * (const Line &x) const { return k * x.b - b * x.k; }
    Line operator - (const Line &x) const { return Line(k - x.k, b - x.b, 2333); }
}t[MAXN], q[MAXN];

inline bool cmp(Line a, Line b) {
    return a.id < b.id;
}

inline bool Judge(Line a, Line b, Line c) {
    return (c - a) * (b - a) > 0; 
}

signed main() {
    n = read();
    for (int i = 1; i <= n; ++i) t[i].b = read();
    for (int i = 1; i <= n; ++i) t[i].k = read(), t[i].id = i; 
    std::sort(&t[1], &t[n + 1]);
    t[0].k = -1;
    int top = 0;
    for (int i = 1; i <= n; ++i) 
        if (t[i].k != t[i-1].k || (t[i].k == t[i - 1].k && t[i].b == t[i-1].b)) {
            while (top > 1 && Judge(q[top - 1], q[top], t[i])) -- top;
            if (t[i].k < q[top].k && t[i].b < q[top].b) continue;
            q[++top] = t[i];
        }
    std::sort(&q[1], &q[top + 1], cmp);
    printf("%d\n", top);
    for (int i = 1; i < top; ++i)
        printf("%d ", q[i].id);
    printf("%d", q[top].id);
    return 0;
}