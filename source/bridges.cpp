struct Bridges {
	vector<pair<int, int>> edges;
	vector<bool> vis;
	vi tin, low;
	int t;

	void dfs(vector<vi>& adj, int u, int p=-1) {
		vis[u] = true;
		tin[u] = low[u] = t++;
		for (int v : adj[u]) {
			if (v == p) continue;
			if (vis[v]) low[u] = min(low[u], tin[v]);
			else {
				dfs(adj, v, u);
				low[u] = min(low[u], low[v]);
				if (low[v] > tin[u]) edges.push_back({u, v});
			}
		}
	}
	Bridges(vector<vi>& adj) {
		int n = adj.size();
		t = 0;
		vis.resize(n, false);
		tin.resize(n, -1);
		low.resize(n, -1);
		for (int u = 0; u < n; ++u)
			if (!vis[u])
				dfs(adj, u);
	}
};
