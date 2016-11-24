#include <cstdio>
#include <cstring>
#include <list>
#include <algorithm>
#define clear(x,y) memset(x, y, sizeof(x))
using namespace std;
const int N=100005;
class zkw_seg_tree {
public:
	struct node {
		node() {add=sum=0, len=1;}
		int len, add, sum; 
	};
	zkw_seg_tree(int size) { // [1,size]
		dep=lg2(size-1)+1;
		delta=(1<<dep)-1;
		arr=new node[1<<(dep+1)];
		for(int i=delta; i>0; --i) arr[i].len=arr[i+i].len<<1;
	}
	~zkw_seg_tree() {
		delete[] arr;
	}
	inline void update(int l, int r, int num=1) {
		l+=delta-1, r+=delta+1;
		int l0=l, r0=r;
		while( r-l>1 ) {
			if( (l&1)^1 ) ++l, arr[l].add+=num, arr[l].sum+=arr[l].len*num;
			if( (r&1)^0 ) --r, arr[r].add+=num, arr[r].sum+=arr[r].len*num;
			l>>=1, r>>=1;
		}
		__update(l0), __update(r0);
	}
	inline int query(int l, int r) {
		__down(l+delta), __down(r+delta);
		l+=delta-1, r+=delta+1;
		int res=0;
		while( r-l>1 ) {
			if( (l&1)^1 ) res+=arr[l+1].sum;
			if( (r&1)^0 ) res+=arr[r-1].sum;
			l>>=1, r>>=1;
		}
		return res;
	}
private:
	node *arr;
	int dep;
	int delta;
	inline int lg2(int x) {int r;for(r=-1; x; x>>=1, ++r);return r;}
	inline void __update(int x) {
		while( x>1 ) x>>=1, arr[x].sum=arr[x+x].sum+arr[x+x+1].sum+arr[x].len+arr[x].add;
	}
	inline void __down(int x) {
		for(int i=dep, tmp; i>0; --i) {
			tmp=x>>i;
			arr[tmp<<1].add+=arr[tmp].add, arr[(tmp<<1)+1].add+=arr[tmp].add;
			arr[tmp<<1].sum+=arr[tmp].add*arr[tmp<<1].len, arr[(tmp<<1)+1].sum+=arr[tmp].add*arr[tmp<<1].len;
			arr[tmp].add=0;
		}
	}
} segtree(N);
list<int> all[N];
int dep[N];
int chn[N], son[N], fat[N], anc[N];
int flag;
int seg_pos[N];
void dfs1(int now) {
	chn[now]=0;
	son[now]=-1;
	for(list<int>::iterator ee=all[now].begin(); ee!=all[now].end(); ++ee) {
		if( !~dep[*ee] ) {
			dep[*ee]=dep[now]+1, fat[*ee]=now;
			dfs1(*ee);
			chn[now]+=chn[*ee];
			if( !~son[now] || chn[*ee]>chn[son[now]] ) son[now]=*ee;
		}
	chn[now]++;
	}
}
void dfs2(int now, int now_anc) {
	anc[now]=now_anc;
	seg_pos[now]=flag++;
	if( ~son[now] ) dfs2(son[now], now_anc);
	for(list<int>::iterator ee=all[now].begin(); ee!=all[now].end(); ++ee)
		if( fat[*ee]==now && son[now]!=*ee )
			dfs2(*ee, *ee);
}
inline int cmd(int ch, int v1, int v2) {
	int res=0;
	while( anc[v1]!=anc[v2] ) {
		if( dep[anc[v1]]>dep[anc[v2]] ) swap(v1, v2); // anc[v2] is deeper
		if( ch==1 ) {
			if( anc[v2]^v2 ) segtree.update(seg_pos[son[anc[v2]]], seg_pos[v2]);
			segtree.update(seg_pos[anc[v2]], seg_pos[anc[v2]]);
		}
		else {
			if( anc[v2]^v2 ) res+=segtree.query(seg_pos[son[anc[v2]]], seg_pos[v2]);
			res+=segtree.query(seg_pos[anc[v2]], seg_pos[anc[v2]]);
		}
		v2=fat[anc[v2]];
	}
	if( v1!=v2 ) {
		if( dep[v1]>dep[v2] ) swap(v1, v2); // v2 is deeper
		if( ch==1 ) segtree.update(seg_pos[son[v1]], seg_pos[v2]);
		else res+=segtree.query(seg_pos[son[v1]], seg_pos[v2]);
	}
	return res;
}
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i=0, v1, v2; i<n-1; ++i){
		scanf("%d%d", &v1, &v2);
		all[v1].push_back(v2), all[v2].push_back(v1);
	}
	clear(dep, -1);
	dep[1]=0, fat[1]=0, flag=0;
	dfs1(1);
	dfs2(1, 1);
	char ch[5];
	int v1, v2;
	for(int i=0; i<q; ++i) {
		scanf("%s %d %d", ch, &v1, &v2);
		if( ch[0]=='P' ) cmd(1, v1, v2);
		else printf("%d\n", cmd(2, v1, v2));
	}
}
