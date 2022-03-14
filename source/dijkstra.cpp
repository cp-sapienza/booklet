vector<ll> dijkstra(vector<vector<pair<int,ll>>>& adj, int src) {
	int n = adj.size();
	vector<ll> dist(n, INF);
	dist[src] = 0LL;
	set<pair<ll, int>> s{{0LL, src}};

	while (!s.empty()) {
		int u = s.begin()->second;
		s.erase(s.begin());

		for(auto [v, d] : adj[u]) {
			if (dist[u] + d < dist[v]) {
				s.erase({dist[v], v});
				dist[v] = dist[u] + d;
				s.insert({dist[v], v});
			}
		}
	}
	return dist;
}
