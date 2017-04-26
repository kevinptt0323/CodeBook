#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

struct GenMatch { // 1-base
	static const int MAXN = 514;
	int V;
	bool edg[MAXN][MAXN];
	int pr[MAXN];
	bool inq[MAXN], inb[MAXN], inp[MAXN];
	queue<int> qq;
	int st, ed;
	int bk[MAXN], djs[MAXN];
	void init(int _V) {
		V = _V;
		memset(edg, 0, sizeof(edg));
		for(int i=0; i<=V; i++) {
			pr[i] = bk[i] = djs[i] = 0;
			inq[i] = inb[i] = 0;
		}
	}
	void add_edge(int u, int v) {
		edg[u][v] = edg[v][u] = 1;
	}
	int lca(int u,int v) {
		for (int i=0; i<=V; i++) inp[i] = 0;
		while(1) {
			u = djs[u];
			inp[u] = true;
			if (u==st) break;
			u = bk[pr[u]];
		}
		while(1) {
			v = djs[v];
			if (inp[v]) return v;
			v = bk[pr[v]];
		}
	}
	void upd(int u, int idx) {
		int v;
		while (djs[u]!=idx) {
			v = pr[u];
			inb[djs[u]] = inb[djs[v]] = true;
			u = bk[v];
			if (djs[u]!=idx) bk[u] = v;
		}
	}
	void blo(int u, int v) {
		int nb = lca(u, v);
		for (int i=0; i<=V; i++) inb[i] = false;
		upd(u, nb);
		upd(v, nb);
		if (djs[u]!=nb) bk[u] = v;
		if (djs[v]!=nb) bk[v] = u;
		for (int tu=1; tu<=V; tu++)
			if (inb[djs[tu]]) {
				djs[tu] = nb;
				if(!inq[tu]){
					qq.push(tu);
					inq[tu] = 1;
				}
			}
	}
	void flow() {
		for (int i=1; i<=V; i++) {
			inq[i] = false;
			bk[i] = 0;
			djs[i] = i;
		}

		while(qq.size()) qq.pop();
		qq.push(st);
		inq[st] = 1;
		ed = 0;
		while(qq.size()) {
			int u = qq.front(); qq.pop();
			for(int v = 1; v <= V; v++)
				if (edg[u][v] && djs[u]!=djs[v] && pr[u]!=v) {
					if (v==st || (pr[v]>0 && bk[pr[v]]>0))
						blo(u,v);
					else if (!bk[v]) {
						bk[v] = u;
						if (pr[v]>0) {
							if (!inq[pr[v]]) qq.push(pr[v]);
						} else {
							ed=v;
							return;
						}
					}
				}
		}
	}
	void aug() {
		int u = ed, v, w;
		while(u > 0) {
			v = bk[u];
			w = pr[v];
			pr[v] = u;
			pr[u] = v;
			u = w;
		}
	}
	int solve() {
		int ans = 0;
		for (int i=0; i<=V; i++) pr[i] = 0;
		for (int u=1; u<=V; u++)
			if (!pr[u]) {
				st = u;
				flow();
				if (ed>0) {
					aug();
					ans++;
				}
			}
		return ans;
	}
} G;

int main() {
	G.init(100);
	for(int i=0; i<10; i++) {
		int u, v;
		cin >> u >> v;
		G.add_edge(u, v);
	}
	cout << G.solve() << endl;
}
