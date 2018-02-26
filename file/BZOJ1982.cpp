# include <stdio.h> 
# include <algorithm> 
int n, i, zzh[100005];
int main() {
    for (scanf("%d", &n), i = 1; i <= n; i++) scanf("%d", &zzh[i]);
    if (n & 1) puts("first player");
    else {
        std::sort(&zzh[1], &zzh[n + 1]);
        for (int i = 1; i <= n; i += 2) 
            if (zzh[i] != zzh[i + 1]) return puts("first player"), 0;
        puts("second player");
    }
    return 0;
}
