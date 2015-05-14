/*
 * merge : root = merge(x, y)
 * pop   : root = merge(root.lc, root.rc)
*/
const int MAXSIZE = 10000;

class Node {
public:
	int num, lc, rc;
	Node(int _v=0) : num(_v), lc(-1), rc(-1) {}
} tree[MAXSIZE];

int merge(int x, int y){
    if( x==-1 ) return y;
    if( y==-1 ) return x;
    if( tree[x].num<tree[y].num ) // key
        swap(x, y);
    tree[x].rc = merge(tree[x].rc, y);
    swap(tree[x].lc, tree[x].rc);
    return x;
}

