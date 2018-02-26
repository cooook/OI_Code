# include <stdio.h> 
# include <cstring> 
# include <iostream>
const int MAXN = 25; 
int T, n, val[MAXN], SG[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int GET_SG(int x) {
    static bool vis[10005];
    memset(vis, false, sizeof vis);
    for (int i = x + 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            vis[SG[i] ^ SG[j]] = true;
    for (int i = 0; ; i++) 
        if (!vis[i]) return i;
}

int main() {
    T = read();
    while (T --) {   
        memset(SG, 0, sizeof SG);
        n = read(); int Ans = 0, cnt = 0; bool flag = false; 
        for (int i = 1; i <= n; i++) val[i] = read();
        for (int i = n - 1; i; i--) SG[i] = GET_SG(i);
        for (int i = 1; i <= n; i++) 
            Ans ^= (val[i] & 1) ? SG[i] : 0;
        if (!Ans) { puts("-1 -1 -1"); puts("0"); continue; }
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                for (int k = j; k <= n; k++)
                    if ((Ans ^ SG[i] ^ SG[j] ^ SG[k]) == 0 && val[i]){
                        ++ cnt; 
                        if (!flag) { flag = true; printf("%d %d %d\n", i - 1, j - 1, k - 1); }
                    }
        printf("%d\n", cnt);
    }
    return 0;
}