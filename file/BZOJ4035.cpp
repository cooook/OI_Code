# include <stdio.h>
# include <iostream> 
# include <algorithm>
int n, k, w, f[100005], Ans, i, b[100005], cnt;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch <= '9' & ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline int find(int x) {
    int l = 1, r = cnt, mid; 
    while (l <= r) {
        mid = l + r >> 1;
        if (b[mid] == x) return mid; 
        if (b[mid] < x) l = mid + 1;
        else r = mid - 1;
    } 
    return l; 
}

inline void Pre_Work() {
    static int vis[100005], Time, Last;
    for (int i = 1; i <= n; i = Last + 1) b[++ cnt] = Last = n / (n / i);
    for (int i = cnt; i; --i) {
        int Ans = 1, x = b[i], Xor = 0, last, Next = i; ++ Time; 
        for (int j = 2; j * x <= n; j = last + 1) {
            while (Next < cnt && j * x > b[Next]) ++ Next;
            last = b[Next] / x; 
            vis[Xor ^ f[Next]] = Time; 
            if ((last - j + 1) & 1) Xor ^= f[Next];
        }
        while (vis[Ans] == Time) ++ Ans; 
        f[i] = Ans;
    }
}

int main() {
    for (n = read(), k = read(), Pre_Work(); k; --k) {
        Ans = 0;
        for (w = read(), i = 1; i <= w; ++i) Ans ^= f[find(n / (n / read()))];
        puts(Ans ? "Yes" : "No");
    }
    return 0;
}