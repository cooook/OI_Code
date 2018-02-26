#include <bits/stdc++.h>
#define MAXN 55
int T,len;
char s[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

bool f[55][55];

inline bool Judge(int l,int r) {
    for (int i = l; i <= r; i++) if (!isdigit(s[i])) return false;
    return true; 
}

inline bool Work() {
    memset(f,false,sizeof f);
    for (int i = 1; i <= len; i++)
        for (int j = i; j <= len; j++)
            if (Judge(i,j)) f[i][j] = true;
            else break;
    for (int i = 0; i <= len; i++)
        for (int j = 0; j < i; j++)
            f[i][j] = false;
    for (int l = 1; l <= len; l++) {
        for (int i = 1; i <= len - l + 1; i++) {
            int j = i + l - 1;
            for (int k = i; k <= j; k++) {
                if (f[i][k-1] && f[k+1][j]) {
                    if (s[k] == '-' || s[k] == '+' || s[k] == '/' || s[k] == '*')
                        f[i][j] = true;
                }
            }
            if (f[i][j]) {
                if (s[i-1] == '(' && s[j+1] == ')') f[i-1][j+1] = true;
                if (s[i-1] == ' ') f[i-1][j] = true;
                if (s[j+1] == ' ') f[i][j+1] = true;
                continue;
            }
        }
    }
    return f[1][len];
}

int main() {
    T = read<int>();
    while (T --) {
        gets(s + 1);
        len = strlen(s + 1);
        if (Work()) puts("Yes");
        else puts("No");
    }
}
