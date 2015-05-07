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
		RotateTo(l-1, null);
		RotateTo(r+1, root);
		root->rc->lc->inc += val;
		root->rc->lc->up();
	}
	ll query(int l, int r) {
		if( l>r ) swap(l, r);
		RotateTo(l-1, null);
		RotateTo(r+1, root);
		TNode<T> *now = root->rc->lc;
		now->up();
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
			if( now->lc->sz > x ) now = now->lc;
			else x -= now->lc->sz+1, now = now->rc;
		}
		splay(now, aim);
	}
	void splay(TNode<T> *now, TNode<T> *aim) {
		// make now become aim's child
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
		now->down();
		fa->c[!fl] = now->c[fl];
		if( now->c[fl] != null ) now->c[fl]->fa = fa;
		now->fa = fa->fa;
		if( fa->fa != null ) fa->fa->c[ fa->fa->c[1]==fa ] = now;
		now->c[fl] = fa, fa->fa = now;
		now->inc = fa->inc, fa->inc = 0;
		fa->up();
	}
};
SplayTree<ll> tree;

