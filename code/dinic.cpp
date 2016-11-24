class Flow {
public:
	int ncnt;
	void reset() {
		for(int i=0; i<3605; ++i)
			edge[i].clear();
	}
	void AddEdge(int s, int t){
		edge[s].emplace_back(t, 1, edge[t].size());
		edge[t].emplace_back(s, 0, edge[s].size()-1); //
	}
	int MaxFlow(int s, int t){ // Dinic
		int f = 0, df;
		while (BFS(s, t)!=-1){
			while (true){
				memset(vst, 0, sizeof(vst));
				df = DFS(s, 1<<30, t);
				if (!df) break;
				f += df;
			}
		}
		return f;
	}

private:
	int d[3605]; // Dicic distance
	bool vst[3605];

	struct Edge {
		Edge(const int& t, const int& c, const int& r) : tar(t), cap(c), rev(r) {}
		int tar;
		int cap;
		int rev;
		operator tuple<int&,int&,int&>() { return tuple<int&,int&,int&>{tar, cap, rev}; }
	};
	vector<Edge> edge[3605];

	int DFS(int now, int df, int t){
		if (now==t) return df;
		if (vst[now]) return 0;
		vst[now] = true;
		int nxt, re;
		int cap;
		for(auto& edg: edge[now]) {
			tie(nxt, cap, re) = edg;
			if (cap>0 && d[nxt]==d[now]+1){
				int f = DFS(nxt, min(df, cap), t);
				if (f){
					edg.cap -= f;
					edge[nxt][re].cap += f;
					return f;
				}
			}
		}
		return 0;
	}

	int BFS(int s, int t){
		memset(d, -1, sizeof(d));
		memset(vst, false, sizeof(vst));
		d[s] = 0;
		vst[s] = true;
		queue<int> qq;
		qq.push(s);
		int now, nxt, re;
		int cap;
		while (!qq.empty()) {
			now = qq.front();
			qq.pop();
			for(auto& edg: edge[now]) {
				tie(nxt, cap, re) = edg;
				if (!vst[nxt] && cap) {
					vst[nxt] = true;
					d[nxt] = d[now] + 1;
					if (nxt==t) return d[nxt];
					qq.push(nxt);
				}
			}
		}
		return d[t];
	}
};

Flow flow;
