struct UFDS {
	vi parent, rank, sz;
	int num_components;

	UFDS(int N) : parent(N, 0), rank(N, 0), sz(N, 1), num_components(N) {
		iota(parent.begin(), parent.end(), 0);
	}
	int find(int x) {
		if(x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	bool merge(int a, int b) {
		a = find(a); b = find(b);
		if(a == b) return false;
		if(rank[a] > rank[b]) swap(a, b);

		parent[a] = b;
		sz[b] += sz[a];
		if(rank[a] == rank[b]) rank[b]++;
		num_components--;
		return true;
	}
	bool same(int a, int b) { return find(a) == find(b); }
	int size(int x) { return sz[find(x)]; }
};
