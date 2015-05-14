class Flow {
public:
	Flow(int _ncnt) :ncnt(_ncnt), ecnt(1), path(new int[_ncnt + 2]), d(new int[_ncnt + 2]), visited(new bool[_ncnt + 2]){
		memset(path, 0, sizeof(int)*(_ncnt + 1));
	}
	~Flow(){
		delete[](path);
		delete[](d);
		delete[](visited);
	}
	void Reset(){
		memset(path, 0, sizeof(int)*(ncnt + 1));
		ecnt = 1;
	}
	void AddEdge(int s, int t, int cap){
		edge[++ecnt].tar = t, edge[ecnt].cap = cap, edge[ecnt].next = path[s], path[s] = ecnt;
		edge[++ecnt].tar = s, edge[ecnt].cap = 0, edge[ecnt].next = path[t], path[t] = ecnt;
	}
	int MaxFlow(int s, int t){ // Dinic
		int f = 0, df;
		while (BFS(s, t) < ncnt){
			while (true){
				memset(visited, 0, sizeof(bool)*(ncnt + 1));
				df = DFS(s, INF, t);
				if (!df) break;
				f += df;
			}
		}
		return f;
	}

private:
	static const int eMaxSize = 40002, INF = (int) 1e9;
	int ecnt, ncnt;
	int *path, *d; // d for Dicic distance
	bool *visited;

	struct Edge{
		int tar, cap, next;
	}edge[eMaxSize];

	int DFS(int a, int df, int t){
		if (a == t) return df;
		if (visited[a]) return 0;
		visited[a] = true;
		for (int i = path[a]; i; i = edge[i].next){
			int b = edge[i].tar;
			if (edge[i].cap > 0 && d[b] == d[a] + 1){
				int f = DFS(b, std::min(df, edge[i].cap), t);
				if (f){
					edge[i].cap -= f, edge[i ^ 1].cap += f;
					return f;
				}
			}
		}
		return 0;
	}

	int BFS(int s, int t){
		memset(d, 0x7f, sizeof(int)*(ncnt + 1));
		memset(visited, 0, sizeof(bool)*(ncnt + 1));
		d[s] = 0; visited[s] = true;
		std::queue<int> Q;
		Q.push(s);
		while (!Q.empty()){
			int a = Q.front(); Q.pop();
			for (int i = path[a]; i; i = edge[i].next){
				int b = edge[i].tar;
				if (visited[b] || edge[i].cap == 0) continue;
				visited[b] = true;
				d[b] = d[a] + 1;
				if (b == t) return d[b];
				Q.push(b);
			}
		}
		return d[t];
	}
};
Flow flow( 1001 );

