#include <stdio.h>
int c[1005], n,i,s; double Ans;
int main() {
    for (scanf("%d",&n),i = 1; i <= n; i++) scanf("%d",&s),c[s]++; n++;
    for (i = 1,s = 0; i <= 1000; i++) if (c[i]) Ans += c[i] * 1.0 * n / (n - s),s += c[i];
    return printf("%.2f\n",Ans),0;
}
