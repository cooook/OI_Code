# include <stdio.h>
# include <algorithm> 
int T, n, Ans, val[1005]; 
int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%d", &n); Ans = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
        if (n & 1) val[++n] = 0;
        std::sort(&val[1], &val[n + 1]);
        for (int i = 2; i <= n; i += 2) Ans ^= val[i] - val[i - 1] - 1;  
        puts(!Ans ? "Bob will win" : "Georgia will win");
    }
    return 0;
}