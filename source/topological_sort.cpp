vi topological_sort(vector<vi>& adj) {
	int n = adj.size();
	vi in_degree(n, 0);
	for (int u = 0; u < n; ++u)
		for (int v : adj[u])
			++in_degree[v];

	queue<int> q;
	for (int u = 0; u < n; ++u)
		if (in_degree[u] == 0)
			q.push(u);

	int index = 0;
	vi order(n);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		order[index++] = u;
		for (int v : adj[u]) {
			--in_degree[v];
			if (in_degree[v] == 0)
				q.push(v);
		}
	}

	if (index != n)
		return {};
	return order;
}
