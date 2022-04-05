vector<vector<pair<int, ll>>> prim(const vector<vector<pair<int, ll>>>& adj) {
	int n = adj.size();
	vector<vector<pair<int, ll>>> mst(n);
	vector<bool> chosen(n);
	vector<pair<int, ll>> min_edge(n, {-1, INF});
	min_edge[0].second = 0LL;
	set<pair<ll, int>> s;
	s.insert({0LL, 0});

	for (int i = 0; i < n; ++i) {
		if (s.empty()) return {};
		int u = s.begin()->second;
		chosen[u] = true;
		s.erase(s.begin());
		if (min_edge[u].first != -1) {
			mst[u].push_back(min_edge[u]);
			mst[min_edge[u].first].push_back({u, min_edge[u].second});
		}
		for (auto [v, d] : adj[u])
			if (!chosen[v] && d < min_edge[v].second) {
				s.erase({min_edge[v].second, v});
				min_edge[v] = {u, d};
				s.insert({d, v});
			}
	}

	return mst;
}
