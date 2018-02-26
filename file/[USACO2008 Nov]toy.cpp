#include <deque>
#include <stdio.h>
#define MAXN 100005
#define inf 0x3f3f3f3f
int D,N1,N2,C1,C2,Tc,sum,l,r,mid1,mid2,Ans1,Ans2,Ans = inf,T[MAXN];


template <typename _t>
inline _t read() {
    _t x = 0,f = 1; char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
    return x * f;
}

struct Node{
    int d[2];
    inline int& operator [] (const int & x) {return d[x];}
};

inline Node MK(int x,int y) {return (Node){x,y};}

std::deque<Node> Q;

inline int Calc(int Num) {
    int Ans = Num * Tc; Q.clear();
    Q.push_back(MK(-N2,Num));
    for (int i = 1; i <= D; i++) {
        if (i - N1 >= 1) Q.push_back(MK(i - N1,T[i - N1]));
        for (int Ti = T[i]; Ti;) {
            if (Q.empty()) return inf;
            Node x = Q.front();
            if (x[0] + N2 <= i && C1 > C2 * (x[0] != -N2)) {
                Q.pop_front();
                int s = std::min(Ti,x[1]);
                x[1] -= s; Ti -= s;
                Ans += C2 * s *(x[0] != -N2);
                if (x[1]) Q.push_front(x);
            }
            else {
                x = Q.back();
                Q.pop_back();
                int s = std::min(Ti,x[1]);
                x[1] -= s; Ti -= s;
                Ans += C1 * s;
                if (x[1]) Q.push_back(x);
            }
        }
    }
    return Ans;
}

int main (){
    D = read<int>(); N1 = read<int>(); 
    N2 = read<int>(); C1 = read<int>(); 
    C2 = read<int>(); Tc = read<int>();
    if (N1 > N2) std::swap(N1,N2),std::swap(C1,C2);
    for (int i = 1; i <= D; i++) T[i] = read<int>(),r += T[i],l = std::max(l,T[i]);
    while (l + 5 <= r) {
        mid1 = (l + l + r) / 3;
        mid2 = (l + r + r) / 3;
        Ans1 = Calc(mid1);
        Ans2 = Calc(mid2);
        if (Ans1 < Ans2) r = mid2;
        else l = mid1;
    }
    for (int i = l; i <= r; i++) Ans = std::min(Ans,Calc(i));
    printf("%d\n",Ans);
    return 0;
}