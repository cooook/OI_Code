# include <stdio.h>
# include <cstring>
const int MAXN = 1605;
char s[45][45]; 
int first[MAXN],e = 1, X, Y, black, Q, match[MAXN], color[MAXN], T, cnt, n, m, id[45][45];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
bool vis[MAXN], Del[MAXN], Ans[MAXN];


inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' | ch > '9'; ch = getchar()) ch == '-'?f = -1:0;
    for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct edge {
    int v, next; 
} a[6405];

inline void push(int u, int v) {
    a[e].v = v; a[e].next = first[u]; first[u] = e++; 
}

inline char Judge(int x, int y) {
    bool Ans = (x + y) & 1;
    return Ans == black ? 'X' : 'O';
}

inline bool find(int u) {
    if (Del[u]) return false;
    for (int i = first[u]; i; i = a[i].next) {
        register int v = a[i].v;
        if (vis[v] || Del[v]) continue;
        vis[v] = true; 
        if (!match[v] || find(match[v]))
            return match[v] = u, match[u] = v, true;
    }
    return false;
}

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1); 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] == '.') {
                X = i;
                Y = j;
                black = (i + j) & 1;
                break;
            }
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] == Judge(i, j) || s[i][j] == '.') 
                id[i][j] = ++ cnt, color[cnt] = s[i][j] == 'X';
    
    color[id[X][Y]] = true;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (!id[i][j]) continue; 
            for (int k = 0; k < 4; k++) {
                register int x = i + dx[k], y = j + dy[k];
                if (x < 1 || y < 1 || x > n || y > m) continue;
                if (id[x][y]) push(id[i][j], id[x][y]); 
            }
        }

    for (int i = 1; i <= cnt; i++) 
        if (color[i]) 
            memset(vis, false, sizeof vis), find(i); 

    Q = read();

    for (int i = 1; i <= Q << 1; i ++) {
        int Now = id[X][Y], Match = match[Now]; Del[Now] = true;
        if (Match) {
            match[Now] = match[Match] = 0;
            memset(vis, false, sizeof vis);
            Ans[i] = !find(Match);
        }
        else Ans[i] = false;
        X = read(), Y = read();
    }

    cnt = 0;

    for (int i = 1; i <= Q << 1; i += 2) if (Ans[i] & Ans[i + 1]) ++ cnt;
    
    printf("%d\n", cnt);

    for (int i = 1; i <= Q << 1; i += 2)
        if (Ans[i] & Ans[i + 1]) printf("%d\n", i + 1 >> 1);
    return 0;
}