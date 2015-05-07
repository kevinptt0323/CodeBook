int tree[size+1][size+1]={{0}};
inline int lowbit(const int &x) {return x&(-x);}
inline void add(int x, int y, int z) {
	for(int i; x<=n; x+=lowbit(x))
		for(i=y; i<=n; i+=lowbit(i)) tree[x][i]+=z;
}
inline int query(short x, short y) {
	int res=0;
	for(int i; x; x-=lowbit(x))
		for(i=y; i; i-=lowbit(i))
			res+=tree[x][i];
	return res;
}

