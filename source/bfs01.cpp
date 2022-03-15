vector<ll> bfs01(vector<vector<pair<int,int>>>& g, int start) {
	deque<int> q;
	q.push_back(start);
	vector<ll> dist(g.size(), INF);
	dist[start] = 0;

	while(!q.empty()) {
		int u = q.front(); q.pop_front();
		for(auto [v,d] : g[u]) {
			if(dist[v] > dist[u] + d) {
				dist[v] = dist[u] + d;
				if(d == 0) q.push_front(v);
				else q.push_back(v);
			}
		}
	}
	return dist;
}