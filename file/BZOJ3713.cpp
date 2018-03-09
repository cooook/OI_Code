# include <stdio.h> 
int f[50], T, n; 


inline bool Judge(int n) {
    for (int i = 1; i <= 45; ++i) 
        if (f[i] == n) return true;
    return false; 
}

int main() {
    scanf("%d", &T);
    f[0] = 1; f[1] = 1;
    for (int i = 2; i <= 45; ++i) f[i] = f[i - 1] + f[i - 2];
    while (T --) {
        scanf("%d", &n); 
        if (!n) { puts("TAK"); goto here; }
        for (int i = 1; i <= 45; ++i)
            if (n % f[i] == 0 && Judge(n / f[i])) { puts("TAK"); goto here; }
        puts("NIE");
        here:;
    }
    return 0; 
}