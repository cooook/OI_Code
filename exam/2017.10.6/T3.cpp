#pragma GCC optimize("O3")
#include <bits/stdc++.h>


#define MAXN 200005
#define fi first
#define se second
#define ls o << 1
#define rs o << 1 | 1


typedef std::pair<int,int> pa;


int n,Hash[MAXN<<1],cnt,mx[MAXN<<2],mp[MAXN<<2],vl[MAXN<<2],vr[MAXN<<2],v[MAXN];


template<typename _t>
inline void read(_t &o) {
    _t x = 0,f = 1;      
    char ch = getchar();   
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -f;   
    for (; ch <= '9' && ch >= '0'; ch = getchar()) x = x * 10 + (ch ^ 48); 
    o = x * f;
}

struct DATA{int k,w,op;}Q[MAXN];
inline int id(int x){return std::lower_bound(&Hash[1],&Hash[cnt+1],x) - Hash;}
inline void In(){
    read(n);
    for (int i = 1; i <= n; i++) {
        read(Q[i].op);
        if (Q[i].op == 0) read(Q[i].k),read(Q[i].w),Hash[++cnt] = Q[i].k;
        if (Q[i].op == 1) read(Q[i].k);
        if (Q[i].op == 2) read(Q[i].k),read(Q[i].w),Hash[++cnt] = Q[i].k,Hash[++cnt] = Q[i].w;
    }
    std::sort(&Hash[1],&Hash[cnt+1]);
    cnt = std::unique(&Hash[1],&Hash[cnt+1]) - Hash - 1;
    for (int i = 1; i <= n; i++) {
        if (Q[i].op == 0) Q[i].k = id(Q[i].k);
        else if (Q[i].op == 1) Q[i].k = id(Q[i].k);
        else Q[i].k = id(Q[i].k),Q[i].w = id(Q[i].w);
    }
}

inline int Queryl(int o,int l,int r,int x) {
    if (x > mx[o]) return 0;
    if (l == r) return 1;
    register int mid = l + r >> 1;
    if (x > mx[rs]) return Queryl(ls,l,mid,x);
    else return vl[ls] + Queryl(rs,mid+1,r,x);
}

inline int Queryr(int o,int l,int r,int x) {
    if (x > mx[o]) return 0;
    if (l == r) return 1;
    register int mid = l + r >> 1;
    if (x > mx[ls]) return Queryr(rs,mid+1,r,x);
    else return vr[rs] + Queryr(ls,l,mid,x);
}

inline void Maintain(int o,int l,int r) {
    mx[o] = mx[ls];
    mp[o] = mp[ls];
    if (mx[o] < mx[rs]) mx[o] = mx[rs],mp[o] = mp[rs];
    register int mid = l + r >> 1;
    vl[ls] = Queryl(ls, l, mid, mx[rs]);
    vr[rs] = Queryr(rs, mid + 1, r, mx[ls]);
}

inline pa Ql(int o,int l,int r,int x,int y,int val) {
    if (x == l && r == y) return (pa) {Queryl(o,l,r,val),std::max(val,mx[o])};
    register int mid = l + r >> 1;
    if (y <= mid) return Ql(ls,l,mid,x,y,val);
    else if (x > mid) return Ql(rs,mid+1,r,x,y,val);
    else {
        pa QWQ = Ql(rs,mid+1,r,mid+1,y,val);
        pa QAQ = Ql(ls,l,mid,x,mid,QWQ.se);
        return (pa){QWQ.fi + QAQ.fi,std::max(QWQ.se,QAQ.se)};
    }
}

inline pa Qr(int o,int l,int r,int x,int y,int val) {
    if (x == l && r == y) return (pa) {Queryr(o,l,r,val),std::max(val,mx[o])};
    register int mid = l + r >> 1;
    if (y <= mid) return Qr(ls,l,mid,x,y,val);
    else if (x > mid) return Qr(rs,mid+1,r,x,y,val);
    else {
        pa QWQ = Qr(ls,l,mid,x,mid,val);
        pa QAQ = Qr(rs,mid+1,r,mid+1,y,QWQ.se);
        return (pa) {QWQ.fi + QAQ.fi,std::max(QWQ.se,QAQ.se)};
    }
}

inline pa Qp(int o,int l,int r,int x,int y) {
    if (x == l && r == y) return (pa) {mx[o],mp[o]};
    register int mid = l + r >> 1;
    if (y <= mid) return Qp(ls,l,mid,x,y);
    else if (x > mid) return Qp(rs,mid+1,r,x,y);
    else return std::max(Qp(ls,l,mid,x,mid),Qp(rs,mid+1,r,mid+1,y));
}

inline void Update(int o,int l,int r,int x,int val) {
    if (l == r) {vl[o] = vr[o] = 1,mx[o] = val,mp[o] = l;return;}
    register int mid = l + r >> 1;
    if (x <= mid) Update(ls,l,mid,x,val);
    else Update(rs,mid+1,r,x,val);
    Maintain(o,l,r);
}

inline void erase(int o,int l,int r,int x) {
    if (l == r) {vl[o] = vr[o] = 0;mx[o] = 0;return;}
    register int mid = l + r >> 1;
    if (x <= mid) erase(ls,l,mid,x);
    else erase(rs,mid+1,r,x);
    Maintain(o,l,r);
}

inline int Calc(int x) {
    int Ans = 0;
    if (x != 1) Ans += Ql(1,1,cnt,1,x - 1,v[x]).fi;
    if (x != cnt) Ans += Qr(1,1,cnt,x + 1,cnt,v[x]).fi;
    return Ans;
}

inline void Work(){
    for (int i = 1; i <= n; i++)  {
        if (Q[i].op == 0) Update(1,1,cnt,Q[i].k,Q[i].w),v[Q[i].k] = Q[i].w;
        else if (Q[i].op == 1) erase(1,1,cnt,Q[i].k);
        else {
            if (Q[i].w > Q[i].k) std::swap(Q[i].w,Q[i].k);
            int LCA = Qp(1,1,cnt,Q[i].w,Q[i].k).se;
            printf("%d\n",Calc(Q[i].w) + Calc(Q[i].k) - 2 * Calc(LCA));
        }
    }
}

int main() {
    In();
    Work();
    return 0;
}