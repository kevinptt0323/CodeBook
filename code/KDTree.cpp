struct NODE{
	int x , y;
	int x1 , x2 , y1 , y2;
	NODE *L , *R;
};
bool cmpx( const NODE& a , const NODE& b ){
	return a.x < b.x;
}
bool cmpy( const NODE& a , const NODE& b ){
	return a.y < b.y;
}
NODE* KDTree( int L , int R , int depth ){
	if ( L > R ) return 0;
	int M = ( L + R ) >> 1;
	node[M].f = depth % 2;
	nth_element( node+L , node+M , node+R+1 , node[M].f ? cmpy : cmpx );
	node[M].L = KDTree( L , M-1 , depth+1 );
	node[M].R = KDTree( M+1 , R , depth+1 );
	node[M].x1 = node[M].x2 = node[M].x;
	node[M].y1 = node[M].y2 = node[M].y;
	if ( node[M].L ){
		node[M].x1 = min( node[M].x1 , node[M].L->x1 );
		node[M].y1 = min( node[M].y1 , node[M].L->y1 );
	}
	if ( node[M].R ){
		node[M].x2 = max( node[M].x2 , node[M].L->x2 );
		node[M].y2 = max( node[M].y2 , node[M].L->y2 );
	}
	return node+M;
} 
inline int mayTouchRectangle( NODE* r , int x , int y , long long d2 ){
	long long d = ( long long )( sqrt(d2) + 1 );
	return x >= r->x1 - d && x <= r->x2 +d && y >= r->y1 - d && y <= r->y2 + d;
}
// find the nearest point near p
// r is tree node
void nearest( NODE* r , NODE* p , long long &dmin ){
	if ( !r || !mayTouchRectangle( r , p->x , p->y , dmin ) ) return;
	if ( p->i != r->i ) dmin = min( dmin , dis( *r , *p ) );  // dis returns the dis^2
	int whichFirst = r->f ? p->y < r->y: p->x < r->x;
	if ( whichFirst ){
		nearest( r->L , p , dmin );
		nearest( r->R , p , dmin );
	}
	else{
		nearest( r->R , p , dmin );
		nearest( r->L , p , dmin );
	}
}

