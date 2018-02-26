# include <bits/stdc++.h> 


int main() {
    freopen("T3.in", "w", stdout);
    srand(time(NULL));
    int n = 8, m;
    printf("%d\n", n);
    for (int i = 2; i <= n; ++i)
        printf("%d %d\n", rand() % (i - 1) + 1, i);
    printf("%d\n", m = 8);
    while (m --) {
        int opt = rand() & 1, x = rand() % n + 1, y = rand() % n + 1;
        while (x == y) y = rand() % n + 1;
        // if (opt) printf("Q %d %d\n", x, y);
        // else printf("L %d %d\n", x, y);
        printf("Q %d %d\n", x, y);
    }
    return 0;
}