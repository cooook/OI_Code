#include <bits/stdc++.h>
const int MAXN = 105,inf = 0x3f3f3f3f;
int n,m,val[MAXN][MAXN],Ans = -inf,now,last;


template <typename _t>
inline _t read() {
	_t x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

struct Hash_Table {
	int first[76544],e;
	struct edge{
		int u,v,next;
	}a[1<<20];
	inline void clear() {memset(first,0,sizeof first); e = 1;}
	Hash_Table() {clear();}
	inline int& New(int S) {
		a[e].u = S; a[e].v = -inf;
		a[e].next = first[S%76543]; first[S%76543] = e++;
		return a[e-1].v;
	}
	inline int& operator [] (const int &S) {
		for (int i = first[S%76543]; i; i = a[i].next) if (a[i].u == S) return a[i].v;
		return New(S);
	} 
}f[2];

inline void Set(int &S,int bit,int val) {
	bit = bit - 1 << 1;
	S |= 3 << bit;
	S ^= 3 << bit;
	S |= val << bit;
}

inline int find(int S,int pos) {
	return (S >> (pos - 1 << 1)) & 3;
}

inline int Link(int S,int pos) {
	int cnt = 0,p,d = find(S,pos) == 1?1:-1;
	for (int i = pos; i && i <= m + 1; i += d) {
		p = find(S,i);
		if (p == 1) cnt ++;
		else if (p == 2) cnt --;
		if (cnt == 0) return i;
	}
	return -1;
}

inline void Print(int S) {
	puts("Show State");
	for (int i = 1; i <= m + 1; i ++)
		printf("%d",find(S,i));
	puts("\n");
}

inline bool Judge(int S) {
	int cnt = 0,cnt1 = 0;
    for(int i = 1; i <= m+1; i++){
        int p = find(S,i);
        if (p==3)cnt++;
        else if (p == 1) cnt1++;
        else if (p == 2) cnt1--;
    }
    return cnt>2 || cnt1 != 0;
}

//#define DEBUG

inline void DP(int x,int y) {
	now ^= 1; last ^= 1;
	int p1,p2,S,val,tot = f[last].e - 1; f[now].clear(); int kong1,kong2,kong3;
	for (int i = 1; i <= tot; i++) {
		S = f[last].a[i].u;val = f[last].a[i].v;
		if (Judge(S) || S >= (1 << ((m+1)<<1)))  continue;
		p1 = find(S,y); p2 = find(S,y+1);
		kong1 = S; Set(kong1,y,0); Set(kong1,y+1,0);
		kong2 = kong1; kong3 = kong1;
		if (!p1 && !p2) {
			f[now][S] = std::max(f[now][S],val);
			if (x != n && y != m) {
				Set(S,y,1),Set(S,y+1,2);
				f[now][S] = std::max(f[now][S],val + ::val[x][y]);
			}
			if (x != n) {
				Set(S,y,3),Set(S,y+1,0);
				f[now][S] = std::max(f[now][S],val + ::val[x][y]);
			}
			if (y != m) {
				Set(S,y,0),Set(S,y+1,3);
				f[now][S] = std::max(f[now][S],val + ::val[x][y]);
			}
		}
		else if (p1 && !p2) {	
			if (x != n) {
				f[now][S] = std::max(f[now][S],val + ::val[x][y]);
			}
			if (y != m) {
				Set(kong3,y+1,p1),f[now][kong3] = std::max(f[now][kong3],val + ::val[x][y]);
			}
			if (p1 == 3) {
				if (!kong1) Ans = std::max(Ans,val + ::val[x][y]);
			}
			else Set(kong2,Link(S,y),3),f[now][kong2] = std::max(f[now][kong2],val + ::val[x][y]);
		}
		else if (!p1 && p2) {
			if (y != m) {
				f[now][S] = std::max(f[now][S],val + ::val[x][y]);
			}
			if (x != n) {
				Set(kong2,y,p2),f[now][kong2] = std::max(f[now][kong2],val + ::val[x][y]); 
			}
			if (p2 == 3) {
                if (!kong1) Ans = std::max(Ans,val + ::val[x][y]);
			}
			else Set(kong3,Link(S,y+1),3),f[now][kong3] = std::max(f[now][kong3],val + ::val[x][y]);
		}
		else if (p1 == 1 && p2 == 1) {
			Set(S,Link(S,y+1),1);
			Set(S,y,0);Set(S,y+1,0);
			f[now][S] = std::max(f[now][S],val + ::val[x][y]);
		}
		else if (p1 == 2 && p2 == 1) {
			Set(S,y,0); Set(S,y+1,0);
			f[now][S] = std::max(f[now][S],val + ::val[x][y]);
		}
		else if (p1 == 2 && p2 == 2) {
			Set(S,Link(S,y),2); Set(S,y,0); Set(S,y+1,0);
			f[now][S] = std::max(f[now][S],val + ::val[x][y]);
		}
		else if (p1 == 3 && p2 == 3) {
			if (!kong1) {
				Ans = std::max(val + ::val[x][y],Ans);
			}
		}
		else if (p1 == 3) {
			Set(S,Link(S,y+1),3),Set(S,y+1,0),Set(S,y,0),f[now][S] = std::max(f[now][S],val + ::val[x][y]);
		}
		else if (p2 == 3) {
			Set(S,Link(S,y),3),Set(S,y,0),Set(S,y+1,0),f[now][S] = std::max(f[now][S],val + ::val[x][y]);
		}
	}
}

int main() {
	n = read<int>(); m = read<int>();
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
			val[i][j] = read<int>(),Ans = std::max(Ans,val[i][j]);
	now = 0; last = 1;
	f[now][0] = 0;
	for (int i = 1; i <= n; i++)  {
		for (int j = 1; j <= m; j++) DP(i,j);
		if (i != n) 
			for (int j = 1; j < f[now].e; j++) f[now].a[j].u <<= 2;
	}
    printf("%d\n",Ans);
	return 0;
}

/*
4 4
-14484 26986 -12609 3339
7338 13733 25679 5979
20731 -20978 -5704 -30843
-14181 -15411 10519 -16039

3 3
-29122 -4516 -10444
19854 -32256 10033
-12044 24139 13108


3 3
1 -23903 -9340
-10405 -22482 1
1 1 -29984


3 3
1 1 1
1 1 1
1 1 1


4 4
-3631 -22164 -29260 -4606
16305 -27520 27335 -26081
20658 -11400 1574 30956
2172 27724 -1285 -12704
*/



































//        %%%%%%%%    %%    %%     
//        %      %  %%%%%%%%%%%%   
//        %      %    %%    %%     
//        %%%%%%%%  %%%%%%%%%%%%   
//        %      %  %          %
//        %      %  %%%%%%%%%%%%
//        %      %  %          %
//        %%%%%%%%  %%%%%%%%%%%%
//        %      %       %
//        %      %  %%%%%%%%%%%%
//        %      %     %%  %%
//        %      %   %%     %%
//        %      %  %%       %%
//        %      % %%         %%
//       %%%%%%%%%%%%%%%%%%%%%%%%%
//       %%                     %%
//       %%          %%         %%
//       %%          %%         %%
//       %%      %%%%%%%%%%%    %%
//       %%          %%         %%
//       %%   %%%%%%%%%%%%%%%%  %%
//       %%                     %%
//       %%      %%%%%%%%%%     %%
//      %%       %        %     %%
//     %%        %        %     %%
//    %%         %%%%%%%%%%     %%
//   %%                         %%
// %%                           %%
//           %%
//          %%
//         %%
//       %%
//       %%%%%%%%%%%%%%%%%%%%%%%%
//       %%                    %%
//       %%                    %%
//       %%                    %%
//       %%%%%%%%%%%%%%%%%%%%%%%%
//       %%                    %%
//       %%                    %%
//       %%                    %%
//       %%                    %%
//       %%%%%%%%%%%%%%%%%%%%%%%%
//       %%                    %%
//       %%                    %%
//       %%                    %%
//       %%%%%%%%%%%%%%%%%%%%%%%%

//     %%        %%%%%%%%%%%%%%%%%%% 
//     %%
//     %% %
//     %% %%      %%%%%%%%%%%%%%%%%
//     %%  %%     %               %
//   % %%         %               %
//  %  %%         %%%%%%%%%%%%%%%%%
// %   %%         %               %
//     %%         %               %
//     %%         %%%%%%%%%%%%%%%%%
//     %%
//     %%   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%