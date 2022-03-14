vector<ll> bellman_ford(vector<array<int, 3>>& edges, int v, int src) {
	vector<ll> dist(v, INF);
	dist[src] = 0LL;

	bool relaxed = true;
	for (int i = 0; i < v - 1 && relaxed; ++i) {
		relaxed = false;
		for (auto [start, end, weight] : edges) {
			if (dist[start] != INF && dist[start] + weight < dist[end]) {
				dist[end] = dist[start] + weight;
				relaxed = true;
			}
		}
	}

	for (int i = 0; i < v - 1 && relaxed; ++i) {
		relaxed = false;
		for (auto [start, end, weight] : edges) {
			if (dist[start] == -INF || (dist[start] != INF && dist[start] + weight < dist[end])) {
				dist[end] = -INF;
				relaxed = true;
			}
		}
	}

	return dist;
}
