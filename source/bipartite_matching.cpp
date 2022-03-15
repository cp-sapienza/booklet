vector<pair<int,int>> bipartite_matching(vector<pair<int,int>>& edges, int n, int m) {
	PushRelabel pr(n+m+2);
	for(auto e : edges) pr.add_edge(e.first, n+e.second, 1);
	for(int i = 0; i < n; i++) pr.add_edge(n+m, i, 1);
	for(int i = 0; i < m; i++) pr.add_edge(n+i, n+m+1, 1);
	pr.calc(n+m, n+m+1);

	vector<pair<int,int>> res;
	for(int i = 0; i < n; i++)
		for(auto e : pr.g[i])
			if(e.f > 0)
				res.push_back({i, e.dest-n});
	return res;
}