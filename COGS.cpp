#include <fstream>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
//
ifstream fin ("redbag.in");
ofstream fout ("redbag.out");
const int INF=0x7fffffff;
//
class point {//This class is the type of the Segment Tree
public://If the ID of this point is x, so (x<<1) and (x<<1^1) is left-child and right-child of this point (AKA (x*2) & (x*2+1))
	int l, r;
	int sum;
	int max0, max1, nmax;//max_number in this Segment: max1<max0, number of max0
	int min0, min1, nmin;//min_number in this Segment: min0<min1, number of min0
	int maxc, minc, mc;
	bool cg;
};
class mnn {
public:
	int m0, nm;
};
//
point tree[1<<18];
//
void maketree(int x, int l, int r);
void updata(int x);
void downdata(int x);
void Cadd(int x, int l, int r, int a);
void Cchange(int x, int l, int r, int a);
void Cbmax(int x, int l, int r, int a);
void Cbmin(int x, int l, int r, int a);
int Qsum(int x, int l, int r);
int Qwmax(int x, int l, int r);
int Qwmin(int x, int l, int r);
mnn Qnmax(int x, int l, int r);
mnn Qnmin(int x, int l, int r);
//
int main() {
	int n, m;
	fin >>n;
	maketree(1, 1, n);
	string s;
	int l, r, a;
	fin >>m;
	while (m--) {
		fin >>s >>l >>r;
		if (s=="Cadd") {
			fin >>a;
			Cadd(1, l, r, a);
		} else if (s=="Cchange") {
			fin >>a;
			Cchange(1, l, r, a);
		} else if (s=="Cbmax") {
			fin >>a;
			Cbmax(1, l, r, a);
		} else if (s=="Cbmin") {
			fin >>a;
			Cbmin(1, l, r, a);
		} else if (s=="Qsum") {
			fout <<Qsum(1, l, r) <<endl;
		} else if (s=="Qwmax") {
			fout <<Qwmax(1, l, r) <<endl;
		} else if (s=="Qwmin") {
			fout <<Qwmin(1, l, r) <<endl;
		} else if (s=="Qnmax") {
			mnn uu=Qnmax(1, l, r);
			fout <<uu.nm <<endl;
		} else if (s=="Qnmin") {
			mnn uu=Qnmin(1, l, r);
			fout <<uu.nm <<endl;
		}
	}
	return 0;
}
//
void maketree(int x, int l, int r) {
	point &u=tree[x];
	u.l=l;
	u.r=r;
	u.maxc=0;
	u.minc=0;
	u.mc=0;
	u.cg=false;
	if (l==r) {
		fin >>u.sum;
		u.max0=u.sum;
		u.max1=-INF;
		u.nmax=1;
		u.min0=u.sum;
		u.min1=INF;
		u.nmin=1;
	}
	else {
		maketree(x<<1, l, l+r>>1);
		maketree(x<<1^1, (l+r>>1)+1, r);
		updata(x);
	}
}
void updata(int x) {
	point &u=tree[x], &lc=tree[x<<1], &rc=tree[x<<1^1];
	u.sum=lc.sum+rc.sum;
	//max
	u.nmax=0;
	u.max0=max(lc.max0, rc.max0);
	u.max1=max(lc.max1, rc.max1);
	if (u.max0==lc.max0)
		u.nmax+=lc.nmax;
	else
		u.max1=max(u.max1, lc.max0);
	if (u.max0==rc.max0)
		u.nmax+=rc.nmax;
	else
		u.max1=max(u.max1, rc.max0);
	//min
	u.nmin=0;
	u.min0=min(lc.min0, rc.min0);
	u.min1=min(lc.min1, rc.min1);
	if (u.min0==lc.min0)
		u.nmin+=lc.nmin;
	else
		u.min1=min(u.min1, lc.min0);
	if (u.min0==rc.min0)
		u.nmin+=rc.nmin;
	else
		u.min1=min(u.min1, rc.min0);
}
void downdata(int x) {
	point &u=tree[x];
	if (u.l==u.r) {
		u.maxc=0;
		u.minc=0;
		u.mc=0;
		u.cg=false;
		return;
	}
	point &lc=tree[x<<1], &rc=tree[x<<1^1];
	if (u.cg==true) {
		Cchange(x<<1, u.l, u.r, u.max0);
		Cchange(x<<1^1, u.l, u.r, u.max0);
		u.cg=false;
		return;
	}
	if (!(u.maxc||u.minc||u.mc))
		return;
	if (u.max0==u.min0) {
		Cchange(x<<1, u.l, u.r, u.max0);
		Cchange(x<<1^1, u.l, u.r, u.max0);
		u.maxc=0;
		u.minc=0;
		u.mc=0;
		return;
	}
	Cadd(x<<1, u.l, u.r, u.mc);
	Cadd(x<<1^1, u.l, u.r, u.mc);
	int nm;
	nm=u.max0-u.maxc;
	if (lc.max0==nm)
		Cbmin(x<<1, u.l, u.r, u.max0);
	if (rc.max0==nm)
		Cbmin(x<<1^1, u.l, u.r, u.max0);
	nm=u.min0-u.minc;
	if (lc.min0==nm)
		Cbmax(x<<1, u.l, u.r, u.min0);
	if (rc.min0==nm)
		Cbmax(x<<1^1, u.l, u.r, u.min0);
	u.mc=0;
	u.maxc=0;
	u.minc=0;
}
void Cadd(int x, int l, int r, int a) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r) {
		if (u.cg==true)
			downdata(x);
		u.mc+=a;
		u.sum+=a*(u.r-u.l+1);
		u.max0+=a;
		if (u.max1!=-INF)
			u.max1+=a;
		u.min0+=a;
		if (u.min1!=INF)
			u.min1+=a;
	} else {
		downdata(x);
		if (l<tree[x<<1^1].l)
			Cadd(x<<1, l, r, a);
		if (tree[x<<1].r<r)
			Cadd(x<<1^1, l, r, a);
		updata(x);
	}
}
void Cchange(int x, int l, int r, int a) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r) {
		u.cg=true;
		u.mc=0;
		u.maxc=0;
		u.minc=0;
		u.sum=a*(u.r-u.l+1);
		//max
		u.max0=a;
		u.max1=-INF;
		u.nmax=u.r-u.l+1;
		//min
		u.min0=a;
		u.min1=INF;
		u.nmin=u.r-u.l+1;
	} else {
		downdata(x);
		if (l<tree[x<<1^1].l)
			Cchange(x<<1, l, r, a);
		if (tree[x<<1].r<r)
			Cchange(x<<1^1, l, r, a);
		updata(x);
	}
}
void Cbmax(int x, int l, int r, int a) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r) {
		if (a<=u.min0)
			return;
		else if (u.min0<a&&a<u.min1) {
			if (u.cg==true)
				downdata(x);
			u.sum+=(a-u.min0)*u.nmin;
			if (u.max0==u.min0) {
				u.max0=a;
				u.mc+=a-u.min0;
				u.min0=a;
			}
			else if (u.max1==u.min0) {
				u.max1=a;
				u.minc+=a-u.min0;
				u.min0=a;
			}
			else {
				u.minc+=a-u.min0;
				u.min0=a;
			}
		}
		else {
			downdata(x);
			Cbmax(x<<1, l, r, a);
			Cbmax(x<<1^1, l, r, a);
			updata(x);
		}
	} else {
		downdata(x);
		if (l<tree[x<<1^1].l)
			Cbmax(x<<1, l, r, a);
		if (tree[x<<1].r<r)
			Cbmax(x<<1^1, l, r, a);
		updata(x);
	}
}
void Cbmin(int x, int l, int r, int a) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r) {
		if (a>=u.max0)
			return;
		else if (u.max0>a&&a>u.max1) {
			if (u.cg==true)
				downdata(x);
			u.sum+=(a-u.max0)*u.nmax;
			if (u.min0==u.max0) {
				u.min0=a;
				u.mc+=a-u.max0;
				u.max0=a;
			}
			else if (u.min1==u.max0) {
				u.min1=a;
				u.maxc+=a-u.max0;
				u.max0=a;
			}
			else {
				u.maxc+=a-u.max0;
				u.max0=a;
			}
		}
		else {
			downdata(x);
			Cbmin(x<<1, l, r, a);
			Cbmin(x<<1^1, l, r, a);
			updata(x);
		}
	} else {
		downdata(x);
		if (l<tree[x<<1^1].l)
			Cbmin(x<<1, l, r, a);
		if (tree[x<<1].r<r)
			Cbmin(x<<1^1, l, r, a);
		updata(x);
	}
}
int Qsum(int x, int l, int r) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r)
		return u.sum;
	int sum=0;
	downdata(x);
	if (l<tree[x<<1^1].l)
		sum+=Qsum(x<<1, l, r);
	if (tree[x<<1].r<r)
		sum+=Qsum(x<<1^1, l, r);
	return sum;
}
int Qwmax(int x, int l, int r) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r)
		return u.max0;
	int maax=-INF, uu;
	downdata(x);
	if (l<tree[x<<1^1].l) {
		uu=Qwmax(x<<1, l, r);
		maax=max(maax, uu);
	}
	if (tree[x<<1].r<r){
		uu=Qwmax(x<<1^1, l, r);
		maax=max(maax, uu);
	}
	return maax;
}
int Qwmin(int x, int l, int r) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r)
		return u.min0;
	int miin=INF, uu;
	downdata(x);
	if (l<tree[x<<1^1].l) {
		uu=Qwmin(x<<1, l, r);
		miin=min(miin, uu);
	}
	if (tree[x<<1].r<r) {
		uu=Qwmin(x<<1^1, l, r);
		miin=min(miin, uu);
	}
	return miin;
}
mnn Qnmax(int x, int l, int r) {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r) {
		mnn ed;
		ed.m0=u.max0;
		ed.nm=u.nmax;
		return ed;
	}
	downdata(x);
	mnn ed;
	ed.m0=-INF;
	ed.nm=0;
	if (l<tree[x<<1^1].l) {
		mnn uu=Qnmax(x<<1, l, r);
		if (ed.m0<uu.m0) {
			ed=uu;
		} else if (ed.m0==uu.m0) {
			ed.nm+=uu.nm;
		}
	}
	if (tree[x<<1].r<r) {
		mnn uu=Qnmax(x<<1^1, l, r);
		if (ed.m0<uu.m0) {
			ed=uu;
		} else if (ed.m0==uu.m0) {
			ed.nm+=uu.nm;
		}
	}
	return ed;
}
mnn Qnmin(int x, int l, int r)  {
	point &u=tree[x];
	if (l<=u.l&&u.r<=r) {
		mnn ed;
		ed.m0=u.min0;
		ed.nm=u.nmin;
		return ed;
	}
	downdata(x);
	mnn ed;
	ed.m0=INF;
	ed.nm=0;
	if (l<tree[x<<1^1].l) {
		mnn uu=Qnmin(x<<1, l, r);
		if (uu.m0<ed.m0) {
			ed=uu;
		} else if (uu.m0==ed.m0) {
			ed.nm+=uu.nm;
		}
	}
	if (tree[x<<1].r<r) {
		mnn uu=Qnmin(x<<1^1, l, r);
		if (uu.m0<ed.m0) {
			ed=uu;
		} else if (uu.m0==ed.m0) {
			ed.nm+=uu.nm;
		}
	}
	return ed;
}