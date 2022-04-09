struct hld
{
	vi parent, depth, heavy, head, pos;
	vector<vi> adj;
	int cur_pos;

	LazyST seg{{}};

	int dfs(int v)
	{
		int size = 1;
		int mx = 0;
		for (int c : adj[v]) {
			if (c != parent[v]) {
				parent[c] = v;
				depth[c] = depth[v] + 1;
				int sub_s = dfs(c);
				size += sub_s;
				if (sub_s > mx)
					mx = sub_s, heavy[v] = c;
			}
		}
		return size;
	}

	void decompose(int v, int h)
	{
		head[v] = h, pos[v] = cur_pos++;
		if (heavy[v] != -1)
			decompose(heavy[v], h);
		for (int c : adj[v]) {
			if (c != parent[v] && c != heavy[v])
				decompose(c, c);
		}
	}

	hld(vector<vi> const& ad, vector<int> w, int root = 0)
	{
		adj = ad;
		int n = ad.size();
		parent = vi(n);
		depth = vi(n);
		heavy = vi(n, -1);
		head = vi(n);
		pos = vi(n);
		cur_pos = root;
		dfs(root);
		decompose(root, root);
		vector<int> data(ad.size());
		for(int i=0;i<n;i++)
			data[pos[i]] = w[i];
		seg = LazyST(data);
	}

	// update is kinda the same, so consider copying and changing what's different
	LazyST::Node query(int a, int b)
	{
		auto res = seg.unit;
		while(head[a] != head[b])
		{
			if(depth[head[a]] > depth[head[b]])
				swap(a, b);
			res = seg.merge(res, seg.query(pos[head[b]], pos[b]));
			b = parent[head[b]];
		}

		// query on vertices
		if(depth[a] > depth[b])
			swap(a, b);
		return seg.merge(res, seg.query(pos[a], pos[b]));

		// query on edges
		if(a == b)
			return res;
		if(depth[a] > depth[b])
			swap(a, b);
		return seg.merge(res, seg.query(pos[heavy[a]], pos[b]));
	}

	void update(int a, int b, LazyST::Update v)
	{
		while(head[a] != head[b])
		{
			if(depth[head[a]] > depth[head[b]])
				swap(a, b);
			seg.update(pos[head[b]], pos[b], v);
			b = parent[head[b]];
		}

		// update for vertices
		if(depth[a] > depth[b])
			swap(a, b);
		seg.update(pos[a], pos[b], v);
		return;
		// update for edges
		if(a == b)
			return;
		if(depth[a] > depth[b])
			swap(a, b);
		seg.update(pos[heavy[a]], pos[b], v);
	}
};
