#include <bits/stdc++.h>
const int MAXN = 100005;
int T,la,lb,fail[MAXN];
char sa[MAXN],sb[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0,f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline char read_char() {
    char ch = getchar();
    for (; ch < 'a' || ch > 'z'; ch = getchar());
    return ch;
}

inline void KMP(char *s,int *fail) {
    int fix = 0;
    fail[0] = 0;
    for (int i = 1; s[i]; i++) {
        while (fix && s[fix] != s[i]) fix = fail[fix - 1];
        if (s[fix] == s[i]) fix ++;
        fail[i] = fix;
    }
} 

int main() {
    T = read<int>();
    while (T --) {
        la = read<int>(); lb = read<int>();
        scanf("%s",sa);
        bool flag = true;
        for (int i = 0; i < lb; i++) sb[i] = sa[i];
        sb[lb++] = read_char();
        for (int i = 0; i < lb; i++)
            if (sa[i] != sb[i]) {
                flag = false;
                break;
            }
        if (flag) {
            printf("%d\n",lb);
            continue;
        }
        KMP(sb,fail); 
        printf("%d\n",fail[lb-1]);
    }
    getchar(); getchar();
    return 0;
}