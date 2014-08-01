/*
 * hdu 1754
 * splay - single modify
 */
#include <cstdio>
#include <algorithm>
using namespace std;

#define lc c[0]
#define rc c[1]
#define MAXN 200005
#define INF 2147483647

int all[MAXN];

struct TNode {
	TNode *c[2], *fa;
	int val, maxx, sz;
	void up() {
		maxx = val;
		sz = lc->sz + rc->sz + 1;
		if( lc->fa ) maxx = max(maxx, lc->maxx);
		if( rc->fa ) maxx = max(maxx, rc->maxx);
	}
};
class SplayTree {
public:
	void init(const int& n) {
		null = &node[0];
		null->fa = NULL;
		null->val = null->maxx = null->sz = 0;
		ncnt = 0;
		root = newnode(-INF, null);
		root->rc = newnode(-INF, root);
		root->rc->lc = build(1, n, root->rc);
		root->rc->up(), root->up();
	}
	void update(int x, int val) {
		RotateTo(x, null);
		root->val = val;
	}
	int query(int l, int r) {
		if( l>r ) swap(l, r);
		RotateTo(l-1, null);
		RotateTo(r+1, root);
		return root->rc->lc->maxx;
	}
private:
	TNode *root, *null;
	TNode node[MAXN];
	int ncnt;
	TNode* newnode(int val, TNode* fa) {
		TNode *x = &node[++ncnt];
		x->lc = x->rc = null;
		x->fa = fa;
		x->val = x->maxx = val, x->sz = 1;
		return x;
	}
	TNode* build(int l, int r, TNode* fa) {
		if( l>r ) return null;
		int md = (l+r)>>1;
		TNode *now = newnode(all[md], fa);
		now->lc = build(l, md-1, now);
		now->rc = build(md+1, r, now);
		now->up();
		return now;
	}
	void RotateTo(int x, TNode *aim) {
		// find k-th element
		TNode *now = root;
		while( now->lc->sz != x )
			if( now->lc->sz > x ) now = now->lc;
			else x -= now->lc->sz+1, now = now->rc;
		splay(now, aim);
	}
	void splay(TNode *now, TNode *aim) {
		// make now become aim's child
		TNode *fa, *fafa;
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
	void Rotate(TNode *now, int fl) {
		// fl : 0 - L-Rotate
		//      1 - R-Rotate
		TNode *fa = now->fa;
		fa->c[!fl] = now->c[fl];
		if( now->c[fl] != null ) now->c[fl]->fa = fa;
		now->fa = fa->fa;
		if( fa->fa != null ) fa->fa->c[ fa->fa->c[1]==fa ] = now;
		now->c[fl] = fa, fa->fa = now;
		fa->up();
	}
} tree;
int main() {
	int n, q;
	char cmd[5];
	int x, y;
	while( ~scanf("%d %d", &n, &q) ) {
		for(int i=1; i<=n; ++i) scanf("%d", &all[i]);
		tree.init(n);
		while( q-- ) {
			scanf("%s %d %d", cmd, &x, &y);
			if( cmd[0]=='U' ) tree.update(x, y);
			else printf("%d\n", tree.query(x, y));
		}
	}
}
