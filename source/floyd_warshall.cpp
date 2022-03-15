vector<vll> floyd_warshall(vector<vll>& g) {
	int n = g.size();
	vector<vll> dist = g;
	for(int i = 0; i < n; i++) dist[i][i] = min(dist[i][i], 0LL);
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(dist[i][k] != INF && dist[k][j] != INF)
					dist[i][j] = min(
						dist[i][j],
						max(-INF, dist[i][k] + dist[k][j])
					);
	for(int k = 0; k < n; k++)
		if(dist[k][k] < 0)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					if(dist[i][k] != INF && dist[k][j] != INF)
						dist[i][j] = -INF;
	return dist;
}