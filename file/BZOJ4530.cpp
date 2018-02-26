#include <stdio.h>
#include <iostream>
const int MAXN = 100005;
int n,Q;


inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	for (; ch < '0' | ch > '9'; ch = getchar()) if (ch == '-') f = -f;
	for (; ch >= '0' & ch <= '9'; ch = getchar()) x = x * 10 + (ch ^ 48);
	return x * f;
}

struct node{
	node *ch[2], *f;
	bool tag; int size, Vsize;
	inline void Maintain();
	inline void rotate();
	inline void Splay();
	inline bool dir();
	inline bool isrt();
	inline void rev();
	inline void Push_down();
}*null,*tree[MAXN];

inline void node::Maintain(){
	if (this == null) return;
	size = ch[0] -> size + ch[1] -> size + Vsize + 1;
}

inline void node::rotate(){
	node *fa = f, *pa = fa -> f; bool d = dir();
	if (!fa -> isrt()) pa -> ch[fa -> dir()] = this;
	if ((fa -> ch[d] = ch[d ^ 1]) != null) ch[d ^ 1] -> f = fa;
	this -> f = pa; fa -> f = this; ch[d ^ 1] = fa;
	fa -> Maintain(); Maintain();
}

inline void node::Splay(){
	Push_down();
	for (node *t = f; !isrt(); rotate(), t = f)
		if (!t -> isrt()){
			t -> f -> Push_down(), t -> Push_down(), Push_down();
			if (t -> dir() == dir()) t -> rotate();
			else rotate();
		}
		else t -> Push_down(), Push_down();
}

inline bool node::dir(){
	return f -> ch[1] == this;
}

inline bool node::isrt(){
	return f -> ch[0] != this && f -> ch[1] != this;
}

inline void node::rev(){
	std::swap(ch[0], ch[1]);
	tag ^= 1;
}

inline void node::Push_down(){
	if (tag) ch[0] -> rev(), ch[1] -> rev(), tag ^= 1;
}

inline void Access(node *x){
	node *y = null;
	while (x != null)
		x -> Splay(),
	 	x -> Vsize += x -> ch[1] -> size,
	 	x -> Vsize -= y -> size,
	 	x -> ch[1] = y,
	 	x -> Maintain(),
	 	y = x, x = x -> f;
}

inline void Make_root(node *x){
	Access(x);
	x -> Splay(); 
	x -> rev();
}

inline void Link(node *x,node *y){
	Make_root(x); Make_root(y);
	x -> f = y; y -> Vsize += x -> size;
	y -> Maintain();
}

int main(){
	n = read(); Q = read();
	null = new node;
	null -> ch[0] = null -> ch[1] = null -> f = null; 
	null -> Vsize = null -> size = 0; null -> tag = false;
	for (int i = 1; i <= n; i++){
		tree[i] = new node;
		tree[i] -> ch[0] = null;
		tree[i] -> ch[1] = null;
		tree[i] -> f = null;
		tree[i] -> size = 1;
		tree[i] -> Vsize = 0;
		tree[i] -> tag = false;
	}
	int x,y;
	while (Q--){
		char ch = getchar();
		while (ch != 'A' && ch != 'Q') ch = getchar();
		x = read(), y = read();
		if (ch == 'A') Link(tree[x], tree[y]);
		else {
			Make_root(tree[x]); 
			Access(tree[y]);
			tree[x] -> Splay();
			printf("%lld\n",1ll * (tree[y] -> Vsize + 1) * (tree[x] -> size - tree[y] -> Vsize - 1));
		}
	}
	return 0;
}