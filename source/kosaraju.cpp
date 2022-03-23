struct Kosaraju {
	vector<vi> adj, radj, cond_adj;
	vector<bool> vis;
	vi comp, order;
	int cc = 0;

	void init_radj() {
		int n = adj.size();
		radj.resize(n);
		for (int u = 0; u < n; ++u)
			for (int v : adj[u])
				radj[v].push_back(u);
	}

	void dfs1(int u) {
		vis[u] = true;
		for (int v : adj[u])
			if (!vis[v])
				dfs1(v);
		order.push_back(u);
	}

	void dfs2(int u) {
		vis[u] = true;
		comp[u] = cc;
		for (int v : radj[u])
			if (!vis[v])
				dfs2(v);
	}


	void init_cond_adj()
	{
		vector<vi> complist(cc);
		vi added(cc, -1);
		cond_adj.resize(cc);

		for(int i=0;i<ssize(adj);i++)
			complist[comp[i]].push_back(i);
		for(int i=0;i<cc;i++)
			for(int from:complist[i])
				for(int to:adj[from])
					if(comp[to] != i && added[comp[to]]!=i) {
						cond_adj[i].push_back(comp[to]);
						added[comp[to]] = i;
					}
	}

	Kosaraju(vector<vi>& g) {
		adj = g;
		init_radj();
		int n = adj.size();
		vis.resize(n);
		comp.resize(n);
		for (int u = 0; u < n; ++u)
			if (!vis[u])
				dfs1(u);
		vis.assign(n, false);
		reverse(all(order));
		for (int u : order)
			if (!vis[u])
				dfs2(u), ++cc;
		init_cond_adj();
	}
};
