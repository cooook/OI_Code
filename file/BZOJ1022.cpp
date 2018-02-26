# include <stdio.h> 
int T, n; 
int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%d", &n);
        bool zzh = true; int Ans = 0;
        for (int i = 1; i <= n; i++) {
            int val; scanf("%d", &val);
            if (val > 1) zzh = false;
            Ans ^= val;
        }
        printf("%s\n", ((zzh && Ans) || (!zzh && !Ans)) ? "Brother" : "John");
    }
    return 0;
}