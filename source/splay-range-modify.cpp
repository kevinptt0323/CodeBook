/* 
 * poj 3468
 * splay - range modify
 */
// Template.cpp by kevinptt 20140714
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <cmath>

#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <set>

#include <iostream>
using namespace std;

#define REP(I, N) for(int I=0; I<(N); ++I)
#define REP1(I, N) for(int I=1; I<=(N); ++I)
#define REPP(I, A, B) for(int I=(A); I<(B); ++I)
#define REPR(I, N) for(int I=N-1; I>=0; --I)
#define RI(X) scanf("%d", &(X))
#define RII(X, Y) scanf("%d%d", &(X), &(Y))
#define RIII(X, Y, Z) scanf("%d%d%d", &(X), &(Y), &(Z))
#define DRI(X) int X; scanf("%d", &X)
#define DRII(X, Y) int X, Y; scanf("%d%d", &X, &Y)
#define DRIII(X, Y, Z) int X, Y, Z; scanf("%d%d%d", &X, &Y, &Z)
#define MP make_pair
#define PB push_back
#define MSET(x, y) memset(x, y, sizeof(x))
#define F first
#define S second
typedef long long ll;
typedef pair<int,int> pii;

/***************************************************************/

#define lc c[0]
#define rc c[1]
#define MAXN 200005
#define INF 2147483647

int all[MAXN];

template<class T>
struct TNode {
	TNode<T> *c[2], *fa;
	T val, inc, sum;
	int sz;
	void down() {
		val += inc;
		if( lc->fa ) lc->inc += inc;
		if( rc->fa ) rc->inc += inc;
		inc = 0;
	}
	void up() {
		sz = lc->sz + rc->sz + 1;
		sum = val;
		if( lc->fa ) sum += lc->sum + lc->inc*lc->sz;
		if( rc->fa ) sum += rc->sum + rc->inc*rc->sz;
	}
};
template<class T>
class SplayTree {
public:
	void init(const int& n) {
		null = &node[0];
		null->fa = NULL;
		null->val = null->inc = null->sum = null->sz = 0;
		ncnt = 0;
		root = newnode(-1, null);
		root->rc = newnode(-1, root);
		root->rc->lc = build(1, n, root->rc);
		root->rc->up(), root->up();
	}
	void update(int l, int r, T val) {
		//cout << "update " << root->rc->lc->val << " -> " << root->rc->lc->lc->val << " , " << root->rc->lc->rc->val << endl;
		RotateTo(l-1, null);
		RotateTo(r+1, root);
		//cout << "update " << root->rc->lc->val << " -> " << root->rc->lc->lc->val << " , " << root->rc->lc->rc->val << endl;
		root->rc->lc->inc += val;
		root->rc->lc->up();
	}
	ll query(int l, int r) {
		if( l>r ) swap(l, r);
		//cout << "query " << root->rc->lc->val << " -> " << root->rc->lc->lc->val << " , " << root->rc->lc->rc->val << endl;
		RotateTo(l-1, null);
		//cout << "query " << root->rc->lc->val << " -> " << root->rc->lc->lc->val << " , " << root->rc->lc->rc->val << endl;
		RotateTo(r+1, root);
		TNode<T> *now = root->rc->lc;
		now->up();
		//cout << "query " << root->rc->lc->val << " -> " << root->rc->lc->lc->val << " , " << root->rc->lc->rc->val << endl;
		return now->sum + now->inc*now->sz;
	}
private:
	TNode<T> *root, *null;
	TNode<T> node[MAXN];
	int ncnt;
	TNode<T>* newnode(T val, TNode<T> *fa) {
		TNode<T> *x = &node[++ncnt];
		x->lc = x->rc = null;
		x->fa = fa;
		x->val = x->sum = val, x->inc = 0, x->sz = 1;
		return x;
	}
	TNode<T>* build(int l, int r, TNode<T> *fa) {
		if( l>r ) return null;
		int md = (l+r)>>1;
		TNode<T> *now = newnode(all[md], fa);
		now->lc = build(l, md-1, now);
		now->rc = build(md+1, r, now);
		now->up();
		return now;
	}
	void RotateTo(int x, TNode<T> *aim) {
		// find k-th element
		TNode<T> *now = root;
		while( now->lc->sz != x ) {
			//cout << "RTO : " << now->val << "(" << now->inc << ") -> " << now->lc->val << "(" << now->lc->inc << ") , " << now->rc->val << "(" << now->rc->inc << ")" << endl;
			if( now->lc->sz > x ) now = now->lc;
			else x -= now->lc->sz+1, now = now->rc;
		}
		splay(now, aim);
	}
	void splay(TNode<T> *now, TNode<T> *aim) {
		// make now become aim's child
		//cout << "splay : " << now->val << "(" << now->inc << ") -> " << now->lc->val << "(" << now->lc->inc << ") , " << now->rc->val << "(" << now->rc->inc << ")" << endl;
		TNode<T> *fa, *fafa;
		while( now->fa != aim ) {
			if( now->fa->fa == aim ) Rotate(now, now->fa->lc==now);
			else {
				fa = now->fa, fafa = fa->fa;
				int pos = ( fafa->c[1] == fa );
				if( fa->c[pos] == now ) Rotate(fa, !pos);
				else Rotate(now, pos);
				Rotate(now, !pos);
			}
		}
		now->up();
		if( aim == null ) root = now;
	}
	void Rotate(TNode<T> *now, int fl) {
		// fl : 0 - L-Rotate
		//      1 - R-Rotate
		TNode<T> *fa = now->fa;
		//cout << "Rot : " << now->val << " " << now->sum << "(" << now->inc << ") -> " << fa->val << " " << fa->sum << "(" << fa->inc << ")" << endl;
		now->down();
		fa->c[!fl] = now->c[fl];
		if( now->c[fl] != null ) now->c[fl]->fa = fa;
		now->fa = fa->fa;
		if( fa->fa != null ) fa->fa->c[ fa->fa->c[1]==fa ] = now;
		now->c[fl] = fa, fa->fa = now;
		now->inc = fa->inc, fa->inc = 0;
		fa->up();
		//cout << "Rot : " << now->val << " " << now->sum << "(" << now->inc << ") -> " << fa->val << " " << fa->sum << "(" << fa->inc << ")" << endl << endl;
	}
};
SplayTree<ll> tree;
inline int input() {
	int res=0, tmp=getchar(), neg=1;
	for(; (tmp<'0'||tmp>'9') && tmp!='-'; tmp=getchar());
	if( tmp=='-' ) neg=-1, tmp=getchar();
	for(; tmp>='0'&&tmp<='9'; tmp=getchar()) res=res*10+tmp-48;
	return res*neg;
}
int main() {
	int n, q;
	char cmd[5];
	int l, r, c;
	while( ~RII(n, q) ) {
		REP1(i, n) all[i] = input();
		tree.init(n);
		while( q-- ) {
			scanf("%s", cmd);
			l = input(), r = input();
			if( cmd[0]=='Q' ) printf("%lld\n", tree.query(l, r));
			else {
				c = input();
				tree.update(l, r, c);
			}
		}
	}
	return 0;
}

