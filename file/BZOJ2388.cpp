# pragma GCC optimize("O3")
# include <math.h> 
# include <stdio.h> 
# include <iostream> 
# define int long long 
typedef long long ll; 
const int MAXN = 155555;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n, len, bl[MAXN], val[MAXN], cnt[450], Q, Top[450];


char sb[1 << 15], *S = sb, *T = sb; 

# define gc() (((S == T) && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T))?0 : *S++)

inline int read() {
    int x = 0, f = 1; char ch = gc();
    for (; !isdigit(ch); ch = gc()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ 48);
    return x * f;
}

// inline int read() {
//     int x = 0, f = 1; char ch = getchar();
//     for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
//     for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
//     return x * f;
// }

inline int gmax(int &x, const int &y) {
    if (x < y) x = y;
    return x ;
}

struct Point {
    int d[2];
    inline int& operator [] (const int &x) {return d[x];}
    inline int operator * (const Point &x) const {return d[0] * x.d[1] - d[1] * x.d[0];}
    inline Point operator + (const Point &x) const {return (Point){d[0] + x.d[0], d[1] + x.d[1]};}
    inline Point operator - (const Point &x) const {return (Point){d[0] - x.d[0], d[1] - x.d[1]};}
}st[450][450], Add1[450];

int Add2[450], Ans[450][450];

inline void Work(Point *a, int len, int *Ans, int &top) {
    Ans[top=1] = 1;
    Ans[++top] = 2;
    for (int i = 3; i <= len; Ans[++top] = i, ++i)
        while (top > 1 && (a[Ans[top]] - a[Ans[top - 1]]) * (a[i] - a[Ans[top - 1]]) > 0) -- top; 
}

inline int Calc(int pos) {
    return Add2[bl[pos]] + val[pos] + Add1[bl[pos]][0] + Add1[bl[pos]][1] * (pos - (bl[pos] - 1) * len - 1);
}

inline void Push_down(int x) {
    for (int i = (x - 1) * len + 1; i <= x * len && i <= n; ++i) 
        val[i] = Calc(i), st[x][i - (x - 1) * len] = (Point){i, val[i]};
    Add2[x] = 0; Add1[x] = (Point){0, 0};
}

inline void Update(int l, int r, int delta) {
    int St = bl[l] + 1, end = bl[r] - 1, Sum = delta;
    
    // printf("l=%lld r=%lld delta=%lld\n", l, r, delta);

    if (bl[l] == bl[r]) {
        Push_down(bl[l]);

        for (int i = l; i <= r; ++i) 
            st[bl[l]][i - (bl[l] - 1) * len] = (Point){i, val[i] += Sum}, Sum += delta;
        Sum -= delta; 
        
        for (int i = r + 1; i <= bl[l] * len; ++i) 
            st[bl[l]][i - (bl[l] - 1) * len] = (Point){i, val[i] += Sum};
        
        Work(st[bl[l]], cnt[bl[l]], Ans[bl[l]], Top[bl[l]]);
        
        for (int i = bl[l] + 1; i <= bl[n]; ++i) Add2[i] += Sum; 
        return ;
    }
    
    Push_down(bl[l]); Push_down(bl[r]);
    
    // printf("%lld %lld\n", l, bl[l] * len);

    for (int i = l; i <= bl[l] * len; ++i) 
        st[bl[l]][i - (bl[l] - 1) * len] = (Point){i, val[i] += Sum}, Sum += delta;

    // block add dengcha

    for (int i = St; i <= end; ++i) 
        Add1[i] = Add1[i] + (Point){Sum, delta}, Sum += delta * len;

    // printf("%lld %lld\n", end * len + 1, r);

    for (int i = end * len + 1; i <= r; ++i) 
        st[bl[r]][i - end * len] = (Point){i, val[i] += Sum}, Sum += delta;
    
    // last block add

    Sum -= delta;

    for (int i = r + 1; i <= bl[r] * len; ++i) 
        st[bl[r]][i - (bl[r] - 1) * len] = (Point){i, val[i] += Sum};

    Work(st[bl[l]], cnt[bl[l]], Ans[bl[l]], Top[bl[l]]);
    Work(st[bl[r]], cnt[bl[r]], Ans[bl[r]], Top[bl[r]]); 

    for (int i = bl[r] + 1; i <= bl[n]; ++i) Add2[i] += Sum;

    // for (int i = 1; i <= bl[n]; ++i)
    //     printf("%lld %lld %lld\n", Add1[i][0], Add1[i][1], Add2[i]);
}

inline int Query_Block(int x) {
    int l = 1, r = Top[x], mid1, mid2, res = -inf, wtf = (x - 1) * len;
    while (l + 3 <= r) {
        mid1 = (l + l + r) / 3;
        mid2 = (l + r + r) / 3;
        if (Calc(Ans[x][mid1] + wtf) > Calc(Ans[x][mid2] + wtf)) r = mid2;
        else l = mid1;
    }
    for (int i = l; i <= r; ++i) gmax(res, Calc(Ans[x][i] + wtf));
    

    // int res = -inf;
    // for (int i = 1; i <= cnt[x]; ++i) gmax(res, Calc(i + (x - 1) * len));
    return res;
}

inline int Query(int l, int r) {
    int Ans = -inf;
    if (bl[l] == bl[r]) {
        for (int i = l; i <= r; ++i) gmax(Ans, Calc(i));
        return Ans;
    }

    else {
        int st = bl[l] + 1, end = bl[r] - 1;
        for (int i = st; i <= end; ++i) gmax(Ans, Query_Block(i));
        for (int i = l; i <= bl[l] * len; ++i) gmax(Ans, Calc(i));
        for (int i = end * len + 1; i <= r; ++i) gmax(Ans, Calc(i));
        return Ans;
    }
}

signed main() {
    n = read();
    len = sqrt(n + 0.5);
    for (int i = 1; i <= n; ++i) {
        val[i] = read() + val[i - 1], bl[i] = (i - 1) / len + 1;
        st[bl[i]][++cnt[bl[i]]] = (Point){i, val[i]};
    }
    for (int i = 1; i <= bl[n]; ++i) Work(st[i], cnt[i], Ans[i], Top[i]);
    Q = read(); 
    while (Q --) {
        register int op = read(), x = read(), y = read(), z;
        if (op == 0) z = read(), Update(x, y, z);
        else printf("%lld\n", Query(x, y));
    }
    return 0;
}