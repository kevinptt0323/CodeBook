#include <vector>
#include <algorithm>
using namespace std;

template<int DEGREE>
struct SuffixAutomaton {
	struct node {
		int green, edge[DEGREE];
		int max_len;
		vector<int> rgreen, id;
		node(const int ml=0) : green(0), max_len(ml) {
			fill(edge, edge+DEGREE, 0);
		}
	};
	vector<node> pool; // 0=NULL, 1=root
	void init() {
		pool.resize(2);
		pool[1] = node(0);
	}
	// extend from last
	void extend(int last, const int c) {
		int idx = last;
		last = pool.size();
		pool.emplace_back(pool[idx].max_len+1);
		for (; idx && !pool[idx].edge[c]; idx=pool[idx].green)
			pool[idx].edge[c] = last;
		if (!idx) pool[last].green = 1; // root
		else {
			int pot_green = pool[idx].edge[c];
			if (pool[pot_green].max_len==pool[idx].max_len+1)
				pool[last].green = pot_green;
			else {
				int wish = pool.size();
				pool.emplace_back(pool[idx].max_len+1);
				for(; idx && pool[idx].edge[c]==pot_green; idx=pool[idx].green)
					pool[idx].edge[c] = wish;
				copy(pool[pot_green].edge, pool[pot_green].edge+DEGREE, pool[wish].edge);
				pool[wish].green = pool[pot_green].green;
				pool[pot_green].green = pool[last].green = wish;
			}
		}
	}
	void build_rg() {
		for(size_t i=2; i<pool.size(); i++)
			pool[i].rgreen.clear();
		for(size_t i=2; i<pool.size(); i++)
			if(pool[i].green)
				pool[pool[i].green].rgreen.push_back(i);
	}
};
SuffixAutomaton<26> SAM;
void travel(int cur, vector<int> &vec) {
	for(int id: SAM.pool[cur].id)
		vec.push_back(id);
	for(int child: SAM.pool[cur].rgreen)
		travel(child, vec);
}

