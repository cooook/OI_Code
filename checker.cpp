# include <bits/stdc++.h> 


inline void gmax(int &x, const int &y) {
    if (x < y) x = y;
}

int main() {
    int cnt = 0, Ans = 0; 
    while (cnt <= 1000) {
        system("T3_maker");
        system("T3");
        FILE *f = fopen("T3.out", "r");
        int x;
        fscanf(f, "%d", &x); 
        gmax(Ans, x);
        ++ cnt; 
        fclose(f);
        printf("cnt = %d\n", cnt);
    }
    printf("%d\n", Ans);
    while (true); 
    return 0;
}