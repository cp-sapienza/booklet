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

	void init_cond_adj() {
		cond_adj.resize(cc);
		for (int u = 0; u < ssize(adj); ++u)
			for (int v : adj[u])
				if (comp[u] != comp[v])
					cond_adj[comp[u]].push_back(comp[v]);
		for (vi& v : cond_adj) {
			sort(all(v));
			v.erase(unique(all(v)), v.end());
		}
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
