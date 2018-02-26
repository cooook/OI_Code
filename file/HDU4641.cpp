# include <stdio.h> 
# include <cstring>
const int MAXN = 3e5 + 5;
int n, m, k, trans[MAXN][26], fa[MAXN], Mx[MAXN], size[MAXN], cnt, last; char s[MAXN];
long long Ans = 0;


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

inline void Add(int c){
    int np = ++ cnt, p = last; Mx[np] = Mx[p] + 1;
    for (; p && !trans[p][c]; p = fa[p]) trans[p][c] = np;
    if (!p) fa[np] = 1;
    else {
        int q = trans[p][c];
        if (Mx[q] == Mx[p] + 1) fa[np] = q;
        else {
            int nq = ++ cnt; Mx[nq] = Mx[p] + 1; size[nq] = size[q];
            fa[nq] = fa[q]; fa[np] = fa[q] = nq;
            memcpy(trans[nq], trans[q], sizeof trans[q]);
            for (; trans[p][c] == q; p = fa[p]) trans[p][c] = nq;
        }
    } last = np;
    for (int x = np; x && size[x] < k; x = fa[x]) {
        size[x] ++;
        if (size[x] >= k) Ans += Mx[x] - Mx[fa[x]];
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) { 
        cnt = 0; Ans = 0;
        memset(size, 0, sizeof size); 
        memset(trans, 0, sizeof trans);
        scanf("%s", s); last = ++ cnt;
        for (char *c = s; *c; c++) Add(*c - 'a');
        while (m --) {
            register int t = read();
            if (t == 2) printf("%lld\n", Ans);
            else {
                char ch = getchar();
                for (; ch < 'a' || ch > 'z'; ch = getchar());
                Add(ch - 'a');
            }
        }
    }
    return 0;
}