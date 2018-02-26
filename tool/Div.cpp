# include <bits/stdc++.h> 


int main() {
    int n; scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
        while (n % i == 0) {
            printf("%d\n", i);
            n /= i;
        }
    if (n != 1) printf("%d\n", n);
    while (true);
}
