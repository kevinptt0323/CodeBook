struct Node {
	Node *l,*r;
	int v,delta,rev,size,minx,w;
	void up() {
		minx = v;
		size = 1;
		if(l) size += l->size, minx = min(minx, l->minx);
		if(r) size += r->size, minx = min(minx, r->minx);
	}
	void down() {
		if(delta) {
			if(l) l->delta += delta, l->v += delta, l->minx += delta;
			if(r) r->delta += delta, r->v += delta, r->minx += delta;
			delta = 0;
		}
		if(rev) {
			swap(l,r);
			if(l) l->rev ^= 1;
			if(r) r->rev ^= 1;
			rev = 0;
		}
	}
}*root = NULL, *list = NULL;
inline int sz(Node *o) { return o ? o->size : 0; }
int ran() {
	static int ranx = 123456789;
	ranx += (ranx<<2) + 1;
	return ranx;
}
void New_node(Node *&o, int val) {
	if(list == NULL) {
		Node *tt = new Node[100];
		for(int i = 0; i < 100; i ++) {
			tt[i].w = ran();
			tt[i].r = list;
			list = tt + i;
		}
	}
	o = list;
	list = o->r;
	o->l = o->r = NULL;
	o->v = o->minx = val;
	o->size = 1;
	o->delta = o->rev = 0;
}
void Reuse(Node *o) { if(o) { o->r = list; list = o; } }
void cut(Node *o, Node *&p, Node *&q, int num) {
	if(num == 0) {
		p = NULL; q = o;
	} else if(num == sz(o)) {
		p = o; q = NULL;
	} else {
		o->down();
		if(num <= sz(o->l)) {
			q = o;
			cut(o->l,p,q->l,num);
			q->up();
		} else {
			p = o;
			cut(o->r,p->r,q,num-sz(o->l)-1);
			p->up();
		}
	}
}
void merge(Node *&o, Node *p, Node *q) {
	if(!p || !q) {
		o = p ? p : q;
	} else {
		if(p->w > q->w) {
			p->down();
			o = p;
			merge(o->r,p->r,q);
		} else {
			q->down();
			o = q;
			merge(o->l,p,q->l);
		}
		o->up();
	}
}
void insert(Node *&o, int pos, int val) {
	if(o == NULL) {
		New_node(o,val);
	} else {
		Node *l , *r , *n;
		New_node( n , val );
		cut ( o , l , r , pos );
		merge( l , l , n );
		merge( root , l , r );
	}
}
void add(int l, int r, int val) {
	Node *a, *b, *c;
	cut(root,a,b,l-1);
	cut(b,b,c,r-l+1);
	b->v += val;
	b->minx += val;
	b->delta += val;
	merge(a,a,b);
	merge(root,a,c);
}
void remove(int pos) {
	Node *a, *b, *c;
	cut(root,a,b,pos-1);
	cut(b,b,c,1);
	merge(root,a,c);
	Reuse(b);
}
int query(int l, int r) {
	Node *a, *b, *c;
	cut(root,a,b,l-1);
	cut(b,b,c,r-l+1);
	int ret = b->minx;
	merge(a,a,b);
	merge(root,a,c);
	return ret;
}
void reverse(int l, int r) {
	Node *a, *b, *c;
	cut(root,a,b,l-1);
	cut(b,b,c,r-l+1);
	b->rev ^= 1;
	merge(a,a,b);
	merge(root,a,c);
}
void revolve(int l, int m, int r) {
	Node *a, *b, *c, *d;
	cut(root,a,b,l-1);
	cut(b,b,c,m-l+1);
	cut(c,c,d,r-m);
	merge(a,a,c);
	merge(a,a,b);
	merge(root,a,d);
}

