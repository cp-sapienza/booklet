
struct centroid
{
	int n;
	vector<vector<int>> adj;
	vi sz;
	vector<bool> rm;

	int dfs(int p, int prev=-1)
	{
		sz[p] = 1;
		for(int nx:adj[p])
			if(nx!=prev && !rm[nx])
				sz[p] += dfs(nx, p);
		return sz[p];
	}

	int find(int p, int msz, int prev=-1)
	{
		for(int nx:adj[p])
			if(!rm[nx] && nx!=prev && sz[nx]>msz)
				return find(nx, msz, p);
		return p;
	}

	centroid(int p, vector<vi> const &ad)
	{
		adj = ad;
		n = adj.size();
		sz.resize(n);
		rm.resize(n, 0);
		deco(p);
	}

	void deco(int p) // important: in the custom visits DON'T visit nodes with rm[node] == true
	{
		int c = find(p, dfs(p)/2);
		rm[c] = true;

		// add stuff or a visit here

		for(int x:adj[c])
			if(!rm[x])
				deco(x);

		// you can do bottom-up calculations here
		rm[c] = false; // for bottom-up only
	}

};
