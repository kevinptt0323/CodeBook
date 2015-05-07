#define MAXSLEN 5000
#define MAXNUM 5000
#define MAXPLEN 50
class Node {
public:
	Node *fail; // transition when undefined next character encountered
	map<char,Node*> _next; // transition to next node corresponding to a character
	bool marked; // whether the prefix is "matched" sometime
	Node() { fail=NULL; marked=0; }
	~Node() {
		for(map<char,Node*>::iterator it=_next.begin();it!=_next.end();it++)
		delete it->second;
	}
	Node* build(char ch) {
		if(_next.find(ch)==_next.end()) _next[ch]=new Node;
		return _next[ch];
	}
	Node* next(char ch) {
		if(_next.find(ch)==_next.end()) return NULL;
		else return _next[ch];
	}
};
int pn; // number of pattern
char s[MAXSLEN]; // string to be matched
char p[MAXNUM][MAXPLEN]; // patterns
Node* pre[MAXNUM]; // its corresponding node on ac-prefix-tree
int ql,qr;
Node* que[MAXNUM*MAXPLEN];
bool appear[MAXNUM];
inline Node* construct(Node *v,char *p) { // append a prefix to the tree
	while(*p) { v=v->build(*p); p++; }
	return v;
}
inline void construct_all(Node *ac) { // construct the prefix tree
	for(int i=0;i<pn;i++) pre[i]=construct(ac,p[i]);
}
inline void find_fail(Node *ac) { // find fail function
	Node *v,*u,*f;
	char ch;
	map<char,Node*>::iterator it;
	ql=qr=0;
	ac->fail=ac;
	for(it=ac->_next.begin();it!=ac->_next.end();it++) {
		que[qr]=it->second;
		que[qr]->fail=ac;
		qr++;
	}
	while(ql<qr) {
		v=que[ql++];
		for(it=v->_next.begin();it!=v->_next.end();it++) {
			ch=it->first; u=it->second;
			que[qr++]=u;
			f=v->fail;
			while(f!=ac&&f->next(ch)==NULL) f=f->fail;
			if(f->next(ch)) u->fail=f->next(ch);
			else u->fail=ac;
		}
	}
}
inline void trace(Node *v) { // marked all contained prefixes
	while(!v->marked) { v->marked=1; v=v->fail; }
}
inline void ac_match(Node *ac,char *s) { // match a string s
	Node *v=ac;
	while(*s) {
		while(v!=ac&&v->next(*s)==NULL) v=v->fail;
		if(v->next(*s)!=NULL) v=v->next(*s);
		trace(v);
		s++;
	}
}
inline void aho_corasick() {
	Node ac;
	construct_all(&ac);
	find_fail(&ac);
	ac_match(&ac,s);
	for(int i=0;i<pn;i++) {
		if(pre[i]->marked) printf("prefix %d is matched\n",i);
		else printf("prefix %d not matched\n",i);
	}
}

