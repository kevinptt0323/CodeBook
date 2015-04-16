// AC automaton
#include <cstdio>
#include <queue>
using namespace std;

template<int NodeSZ>
class AhoCorasick {
public:
	AhoCorasick() { clear(); }
	void clear() {
		all[0] = Node();
		ncnt = 1;
	}
	void push(char *s) {
		Node *curr = &all[0], *next;
		for(int i=0; s[i]; ++i) {
			next = curr->next[idx(s[i])];
			if( next == NULL )
				next = &all[ncnt], all[ncnt++] = Node();
			curr = curr->next[idx(s[i])] = next;
		}
		curr->val++;
	}
	void build() {
		queue<Node*> qq;
		qq.push(&all[0]);
		while( !qq.empty() ) {
			Node *curr = qq.front(), *fail;
			qq.pop();
			for(int i=0; i<NodeSZ; ++i) {
				if( !curr->next[i] ) continue;
				qq.push(curr->next[i]);
				fail = curr->fail;
				while( fail && !fail->next[i] )
					fail = fail->fail;
				curr->next[i]->fail = fail ? fail->next[i] : &all[0];
				//printf("%p %p %p\n", curr->next[i], curr->next[i]->fail, all[0].next[i]);
			}
		}
	}
	int count(char *s) {
		build();
		int cnt = 0;
		Node *curr = &all[0], *tmp;
		for(int i=0, ch; s[i]; ++i) {
			ch = idx(s[i]);
			while( curr && !curr->next[ch] )
				curr = curr->fail;
			curr = curr ? curr->next[ch] : all[0].next[ch];
			tmp = curr;
			while( tmp && tmp->val ) {
				cnt += tmp->val;
				tmp->val = 0;
				tmp = tmp->fail;
			}
		}
		return cnt;
	}
	
private:
	struct Node {
		Node() : val(0), fail(NULL) {
			for(int i=0; i<NodeSZ; ++i) next[i] = NULL;
		}
		int val;
		Node *fail, *next[NodeSZ];
	};
	Node all[250005];
	int ncnt;
	inline int idx(char c) { return c-'a'; }
};
AhoCorasick<26> AC;
char pat[55], str[1000005];

int main() {
	int T, n;
	scanf("%d", &T);
	while( T-- ) {
		scanf("%d", &n);
		AC.clear();
		while( n-- ) {
			scanf("%s", pat);
			AC.push(pat);
		}
		scanf("%s", str);
		printf("%d\n", AC.count(str));
	}
	return 0;
}

