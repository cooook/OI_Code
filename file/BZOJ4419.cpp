#include <bits/stdc++.h>
#define MAXN 200005
int n,m,Ans[MAXN];


template <typename _t>
inline _t read() {
	_t x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}																					

inline char read_char() {
	char ch = getchar();
	for (; ch != '!' && ch != '+' && ch != '-'; ch = getchar()); 
	return ch;
}

struct node{
	node *ch[2]; int v,r,tag;
	inline int cmp(int x) const {
		if (x == v) return -1;
		return x < v?0:1;
	}
	
	inline void Update_Ans(int val) {
		Ans[v] += val;
		tag += val;
		return ;
	}
	
	inline void Push_down() {
		if (tag) {
			if (ch[0]) ch[0] -> Update_Ans(tag);
			if (ch[1]) ch[1] -> Update_Ans(tag);
			tag = 0;
		}
	}
	
	node(){}
	node(int x) {
		v = x; r = rand(); tag = 0;
	}
	inline void* operator new(size_t);
}*root[MAXN],*C,*mempool;

inline void* node::operator new(size_t) {
	if (C == mempool) {
        C = new node[1<<15];
        mempool = C + (1 << 15);
    }
	return C++;
}

inline void rotate(node *&o,int d) {
	node *k = o -> ch[d^1];
	o -> Push_down(); k -> Push_down();
	o -> ch[d^1] = k -> ch[d];
	k -> ch[d] = o;
	o = k;
}

inline void Insert(node *&o,int x) {
	if (!o) o = new node(x);
	else {
		o -> Push_down();
		register int d = o -> cmp(x);
		Insert(o->ch[d],x);
		if (o -> ch[d] -> r < o -> r) rotate(o,d^1);
	}
}

inline void erase(node *&o,int x) {
    int d = o -> cmp(x);
	o -> Push_down();
	if (d == -1) {
        node *tmp = o;
		if (o -> ch[0] != NULL && o -> ch[1] != NULL) {
			int k = o -> ch[0] -> r < o -> ch[1] -> r?0:1;
			rotate(o,k); erase(o->ch[k],x);
		}
		else {
			if (o -> ch[1] == NULL) o = o -> ch[0];
            else o = o -> ch[1];
            tmp = NULL;
		}
	}
	else erase(o -> ch[d],x);
}

inline void dfs(node *&o) {
	if (!o) return;
	o -> Push_down();
	dfs(o -> ch[0]);
	dfs(o -> ch[1]);
}

int main() {
	n = read<int>(); m = read<int>();
	while (m --) {
		char op = read_char();
		if (op == '!') {
			register int u = read<int>();
			if (root[u]) root[u] -> Update_Ans(1);
		}
		else if (op == '+') {
			register int u = read<int>(),v = read<int>();
			Insert(root[u],v); Insert(root[v],u);
		}
		else if (op == '-'){
			register int u = read<int>(),v = read<int>();
            erase(root[u],v); erase(root[v],u);
		}
	}
	for (int i = 1; i <= n; i++) dfs(root[i]);
	printf("%d",Ans[1]);
	for (int i = 2; i <= n; i++) printf(" %d",Ans[i]);
	return 0;
}
