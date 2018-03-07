# include <bits/stdc++.h> 
int n;


inline void Work() {
    for (int i = 1; i <= n; ++i)
        printf("%c", (rand() & 1) ? 'Y' : 'N');
    puts("");
}

int main() {
    freopen("T3.in", "w", stdout); 
    srand(time(NULL));
    n = rand() % 100 + 1;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i) Work();
    printf("%d %d\n", rand() % 100 + 1, rand() % 1000000000 + 1);
    // while (true); 
    return 0; 
}