struct ArticulationPoints {
	vector<bool> is_ap, vis;
	vi tin, low;
	int t;

	int dfs(vector<vi>& adj, int u, int p=-1) {
		vis[u] = true;
		tin[u] = low[u] = t++;
		int c = 0;
		for (int v : adj[u]) {
			if (v == p) continue;
			if (vis[v]) low[u] = min(low[u], tin[v]);
			else {
				++c;
				dfs(adj, v, u);
				low[u] = min(low[u], low[v]);
				if (p != -1 && low[v] >= tin[u]) is_ap[u] = 1;
			}
		}
		return c;
	}
	ArticulationPoints(vector<vi>& adj) {
		int n = adj.size();
		t = 0;
		is_ap.resize(n, false);
		vis.resize(n, false);
		tin.resize(n, -1);
		low.resize(n, -1);
		for (int u = 0; u < n; ++u)
			if (!vis[u])
				is_ap[u] = dfs(adj, u) > 1;
	}
};
