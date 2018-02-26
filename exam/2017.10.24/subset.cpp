#include <stdio.h>
const int MAXN = 200005;
int n,Sum[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int read_char() {
    char s[10];
    scanf("%s",s + 1);
    if (s[1] == 'a') return 0;
    else if (s[1] == 'd') return 1;
    else return 2;
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        int op = read_char(),x = read<int>();
        if (op == 0) Sum[x] ++;
        if (op == 1) Sum[x] --;
        if (op == 2) {
            int Ans = Sum[0];
            for (int j = x; j; j = (j-1) & x)
                Ans += Sum[j];
            printf("%d\n",Ans);
        }
    }
    return 0;
}
