# include <stdio.h> 
# include <iostream>
const int MAXN = 50005;
int n, m, val[MAXN];
 
 
char sb[1 << 15], *S = sb, *T = sb;
# define Getc (S == T && (T = (S = sb) + fread(sb, 1, 1 << 15, stdin), S == T) ? 0 : * S++)
inline int read() {
    register int x = 0, f = 1; char ch = Getc;
    for (; !isdigit(ch); ch = Getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = Getc) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) val[i] = read();
    register char ch; register int l, r, x;
    while (m --) {
        ch = Getc;
        while (ch != 'Q' && ch != 'A') ch = Getc;
        l = read(), r = read();
        if (ch == 'Q') {
            long long Ans = 0, f = 0;
            for (register int i = l; i <= r; ++i) {
                f = f > 0 ? f + val[i] : val[i];
                Ans = Ans < f ? f : Ans;
            }
            printf("%lld\n", Ans);
        }
        else {
            x = read();
            while (l + 3 <= r)
                val[l] += x, val[l + 1] += x, val[l + 2] += x, val[l + 3] += x, l += 4;
            for (int i = l; i <= r; ++i) val[i] += x;
        }
    }
    return 0;
}