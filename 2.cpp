# include <bits/stdc++.h>
typedef unsigned long long ull; 
const int P = 23;
const int mod1 = 1e9 + 9; 
const int mod2 = 1e9 + 7;
const int MAXN = 200005; 
ull L1[MAXN], L2[MAXN], xp[MAXN]; 
char s1[MAXN], s2[MAXN]; 
int len1, len2; 



ull Get_Hash(ull Hash[], int l, int r) {
    return Hash[r] - Hash[l - 1] * xp[r - l + 1]; 
}

bool Judge(int x) {
    return Get_Hash(L1, 1, x) == Get_Hash(L2, 1, x);
}

int main() {
    // freopen("1.in", "r", stdin); 
    scanf("%s%s", s1 + 1, s2 + 1);
    len1 = strlen(s1 + 1);
    len2 = strlen(s2 + 1); 
    xp[0] = 1; 
    for (int i = 1; i <= len1 || i <= len2; ++i) xp[i] = xp[i - 1] * P;
    for (int i = 1; s1[i]; ++i)
        L1[i] = L1[i - 1] * P + s1[i] - 'a';
    for (int i = 1; s2[i]; ++i)
        L2[i] = L2[i - 1] * P + s2[i] - 'a';
    int l = 1, r = std::min(len1, len2), mid, Ans;
    while (l <= r) {
        mid = l + r >> 1;
        if (Judge(mid)) Ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return 0; 
}