class Tree {
	vector<vector<int>> lift;
	vector<int> depth;
	int dim;

	void dfs(vector<int> &parent, vector<vector<int>> &adj, int u=0, int p=0, int d=0) {
		parent[u] = p;
		depth[u] = d;
		for (int v : adj[u]) {
			if (v != p)
				dfs(parent, adj, v, u, d + 1);
		}
	}

	pair<int, int> lca_and_distance(int u, int v) {
		int distance = 0;

		if (depth[u] < depth[v]) swap(u, v);
		int k = depth[u] - depth[v];
		distance += k;

		u = get_kth_ancestor(u, k);
		if (u == v)
			return {u, distance};

		for (int i = dim - 1; i >= 0; --i) {
			if (lift[u][i] != lift[v][i]) {
				distance += (1 << (i + 1));
				u = lift[u][i];
				v = lift[v][i];
			}
		}

		return {lift[u][0], distance + 2};
	}

public:

	Tree(vector<vector<int>> &adj, int root=0) {
		int n = adj.size();
		depth.resize(n, 0);

		vector<int> parent(n, 0);
		dfs(parent, adj, root);

		dim = 0;
		while (n >= (1 << dim))
			++dim;

		lift.resize(n, vector<int>(dim));

		for (int i = 0; i < n; ++i)
			lift[i][0] = parent[i];

		for (int j = 1; j < dim; ++j) {
			for (int i = 0; i < n; ++i) {
				int prev = lift[i][j-1];
				lift[i][j] = lift[prev][j-1];
			}
		}
	}

	int get_depth(int u) {
		return depth[u];
	}

	// Returns the k-th ancestor of node u, if not present returns -1
	// Time: O(logN)
	int get_kth_ancestor(int u, int k) {
		if (k > depth[u])
			return -1;

		for (int i = 0; i < dim; ++i) {
			if (k & (1 << i))
				u = lift[u][i];
		}

		return u;
	}

	// Returns the lowest common ancestor of two nodes
	// Time: O(logN)
	int get_lca(int u, int v) {
		return lca_and_distance(u, v).first;
	}

	// Returns the distance between two nodes
	// Time: O(logN)
	int get_distance(int u, int v) {
		return lca_and_distance(u, v).second;
	}
};