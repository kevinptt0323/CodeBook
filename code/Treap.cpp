class Treap{
	private:
	class Node{
		public:
			Node(  ){ }
			Node( int val ){ initVal( val ); }
			void initVal( int val ){
				pri = rand();
				this -> val = val;
				this -> maxSum = val;
				this -> maxSumLeft = val;
				this -> maxSumRight = val;
				this -> size = 1;
				this -> l = r = NULL;
				this -> reverse = false;
				this -> setValTag = false;
				this -> sum = val;
			}
			int pri, val, size, maxSum , sum;
			int maxSumLeft, maxSumRight;
			bool reverse, setValTag;
			Node *l, *r;
	};
	
	Node* root;
	Node* pool;
	Node** stk;
	int top;
	int getSize( Node *x ){
		return x ? x->size : 0;
	}
	int getMaxSumLeft( Node *x ){
		return x ? x->maxSumLeft : -INF;
	}
	int getMaxSumRight( Node *x ){
		return x ? x->maxSumRight : -INF;
	}
	int getMaxSum( Node *x ){
		return x ? x->maxSum : -INF;
	}
	int getSum( Node *x ){
		return x ? x->sum : 0;
	}

	void setVal( Node *x , int val ){
		x->val = val;
		x->maxSumLeft = x->maxSumRight = x->maxSum = val > 0 ? getSize( x ) * val : val;
		x->sum = val * getSize( x );
		x->setValTag = true;
	}
	void setReverse( Node *x  ){
		swap( x->l, x->r );
		swap( x->maxSumLeft, x->maxSumRight );
		x->reverse = !x->reverse;
	}
	void pull( Node *x ){
		x->size = getSize( x->l ) + getSize( x->r ) + 1; 
		int maxSum = max( 0 , getMaxSumRight( x->l ) ) + x->val + max( 0 , getMaxSumLeft( x->r ) );
		maxSum = max( maxSum , max( getMaxSum( x->l ) , getMaxSum( x->r ) ) );
		x->maxSum = maxSum;

		int maxSumLeft = max( getMaxSumLeft( x->l )  , getSum( x->l ) + x->val + max( 0 , getMaxSumLeft( x->r ) ) );
		x->maxSumLeft = maxSumLeft;

		int maxSumRight = max( getMaxSumRight( x->r ), getSum( x->r ) + x->val + max( 0 , getMaxSumRight( x->l ) ) );
		x->maxSumRight = maxSumRight;

		x->sum = getSum( x->l ) + x->val + getSum( x->r );
	}
	void push( Node *x ){
		if ( x->reverse ){
			if ( x->r ) setReverse( x->r );
			if ( x->l ) setReverse( x->l );
			x->reverse = false;
		}
		if ( x->setValTag ){
			if ( x->r ) setVal( x->r , x->val );
			if ( x->l ) setVal( x->l , x->val );
			x->setValTag = false;
		}
	}
	void split( Node *root, Node* &x , Node* &y , int k ){
		if ( !root ){
			x = y = NULL;
			return;
		}
		if ( getSize( root->l ) >= k ){
			y = root;
			push( y );
			split( root->l, x, y->l , k );
			pull( y );
		}
		else{
			x = root;
			push( x );
			split( root->r , x->r , y , k-getSize( root->l )-1 );
			pull( x );
		}
	}
	Node* Merge( Node *x, Node *y ){
		if ( !x || !y )
			return x ? x : y;
		
		if ( x->pri > y->pri ){
			push( x );
			x->r = Merge( x->r  , y );
			pull( x );
			return x;
		}
		else{
			push( y );
			y->l = Merge( x , y->l );
			pull( y );
			return y;
		}
	}	
	public:
	Treap(){
		root = NULL;
		pool = new Node[MAX_SIZE];
		stk = new Node*[MAX_SIZE];
		for ( top = 0 ; top < MAX_SIZE ; top++ )
			stk[top] = &pool[top];
	}
	~Treap(){
		delete[] pool;
		delete[] stk;
	}
	Node* newNode( int val ){
		Node *ret = stk[--top];
		ret -> initVal(val);
		return ret;
	}
	void release( Node *x ){
		if ( x->l )
			release( x->l );
		if ( x->r )
			release( x->r );
		stk[top++] = x;
		
	}
	void insert( int val ){
		root = Merge( root , newNode( val ) );
	}
	void insert(  int k , queue<int>& q  ){
		Node *l, *r, *newTree = NULL;
		split( root , l , r , k );
		while ( !q.empty() ){
			int a = q.front(); q.pop();
			newTree = Merge( newTree , newNode( a ) );
		}
		root = Merge( l , Merge( newTree , r ) );
	}
	void remove( int k , int sz ){
		Node *l, *m , *r;
		split( root , l , m , k-1 );
		split( m , m , r , sz );
		release( m );
		root = Merge( l , r );
	}
	void setVal( int k , int sz , int val ){
		Node *l, *m , *r;
		split( root , l , m , k-1 );
		split( m , m , r , sz );
		setVal( m , val );
		root = Merge( l , Merge( m , r ) );
	}
	void reverse( int k , int sz ){
		Node *l, *m , *r;
		split( root , l , m , k-1 );
		split( m , m , r , sz );
		setReverse( m );
		root = Merge( l , Merge( m , r ) );
	}
	int getSum( int k , int sz ){
		int ret = 0;
		Node *l, *m , *r;
		split( root , l , m , k-1 );
		split( m , m , r , sz );
		ret = getSum( m );
		root = Merge( l , Merge( m , r ) );
		return ret;
	}
	int getMaxSum(  ){
		return getMaxSum( root );
	}
};
