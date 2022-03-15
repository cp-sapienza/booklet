vector<vector<pair<int, ll>>> prim(const vector<vector<ll>>& mat) {
	int n = mat.size();
	vector<vector<pair<int, ll>>> mst(n);
	vector<bool> chosen(n);
	vector<pair<int, ll>> min_edge(n, {-1, INF});
	min_edge[0].second = 0LL;

	for (int _ = 0; _ < n; ++_) {
		int u = -1;
		for (int v = 0; v < n; ++v)
			if (!chosen[v] && (u == -1 || min_edge[v].second < min_edge[u].second))
				u = v;
		if (min_edge[u].second == INF) return {};
		if (min_edge[u].first != -1) {
			mst[u].push_back(min_edge[u]);
			mst[min_edge[u].first].push_back({u, min_edge[u].second});
		}
		chosen[u] = true;
		for (int v = 0; v < n; ++v)
			if (!chosen[v] && mat[u][v] < min_edge[v].second)
				min_edge[v] = {u, mat[u][v]};
	}

	return mst;
}
