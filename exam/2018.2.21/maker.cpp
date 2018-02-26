# include <bits/stdc++.h> 
int n, L, R;


int main() {
    srand(time(NULL));
    freopen("T3.in", "w", stdout);
    int n = 1000;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i)
        printf("%d%c", rand() % 2, " \n"[i == n]);
    printf("%d\n", 1000);
    for (int i = 1; i <= n; ++i) {
        int l = rand() % n + 1, r = rand() % n + 1;
        if (l > r) std::swap(l, r);
        printf("%d %d\n", l, r);
    }
    return 0;
}