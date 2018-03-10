# include <bits/stdc++.h>
const int MAXN = 3e4 + 5;  
int fa[MAXN], n; 


inline int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]); 
}

int main() {
    freopen("T3.in" ,"w", stdout);
    srand(time(NULL)); 
    n = 100;
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i) fa[i] = i; 
    for (int i = 1; i < n; ++i) {
        register int x = rand() % n + 1, y = rand() % n + 1;
        while (find(x) == find(y)) x = rand() % n + 1, y = rand() % n + 1;
        fa[find(x)] = find(y);
        printf("%d %d %d\n", x, y, rand());
    }
    return 0; 
}