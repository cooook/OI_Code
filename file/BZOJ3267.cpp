#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
#define int long long
int n,m,val[MAXN],cnt,now[MAXN],Ans,pre[MAXN],nxt[MAXN],tot;
 
 
char xB[1 << 15], *xS = xB, *xT = xB;
# define getc (xS == xT && (xT = (xS = xB) + fread(xB, 1, 1 << 15, stdin), xS == xT) ? 0 : *xS++)
inline int read() {
    register int x = 0, f = 1; char ch = getc;
    for (; !isdigit(ch); ch = getc) if (ch == '-') f = -f;
    for (; isdigit(ch); ch = getc) x = x * 10 + (ch ^ 48);
    return x * f;
}
 
struct data{
    int val,id;
    inline bool operator < (const data & a)const{return val == a.val?id<a.id:val<a.val;}
}; set<data>s;
 
signed main(){ 
    n = read(); m = read();
    for(int i = 1;i<=n;i++) val[i] = read() ;
    int pos = 1,limit = n;
    while(pos<n&&val[pos]<=0) pos ++;
    while(limit>0&&val[limit]<=0) limit --;
    while(pos<=limit) {
        if(val[pos] < 0) {
            if(now[cnt] > 0 || !cnt) cnt ++;
            while(pos<=limit&&val[pos]<0) now[cnt] += val[pos],pos ++;
            continue;
        }
 
        if(val[pos] > 0) {
            if(now[cnt] < 0 || !cnt) cnt ++;
            while(pos<=limit&&val[pos]>0) now[cnt] += val[pos],pos ++;
            continue;
        }
 
        pos ++;
    }
    for(int i = 1;i<=cnt;i++) {
        if(now[i] > 0) tot ++ , Ans += now[i]; 
        now[i] = abs(now[i]);
        s.insert((data){abs(now[i]),i});
        pre[i] = i-1;nxt[i] = i + 1;
    } now[0] = 0x3f3f3f3f3f3f3f3fll;now[cnt+1] = 0x3f3f3f3f3f3f3f3fll;  tot -= m;
    if(tot <= 0) {printf("%lld\n",Ans);return 0;}
    while(tot --) {
        int QWQ = s.begin()->id;
        Ans -= now[QWQ];
        now[QWQ] = now[pre[QWQ]] + now[nxt[QWQ]] - now[QWQ]; 
        s.erase(s.begin());
        s.erase((data){now[pre[QWQ]],pre[QWQ]});
        s.erase((data){now[nxt[QWQ]],nxt[QWQ]});
        s.insert((data){now[QWQ],QWQ});
        if(nxt[nxt[QWQ]]) pre[nxt[nxt[QWQ]]] = QWQ;
        if(pre[pre[QWQ]]) nxt[pre[pre[QWQ]]] = QWQ;
        if(pre[QWQ]) pre[QWQ] = pre[pre[QWQ]];
        if(nxt[QWQ]) nxt[QWQ] = nxt[nxt[QWQ]];
    } printf("%lld\n",max(Ans,0ll));
    return 0;
}