struct SparseTable {
	// Any idempotent operation
	int op(int a, int b) { return min(a, b); }

	vector<vi> tab;
	SparseTable(const vi& data) {
		tab.push_back(vi(data));
		for(int p = 0; (2<<p) <= ssize(data); ++p) {
			tab.emplace_back(data.size() - (2<<p) + 1, 0);
			for(int i = 0; i + (2<<p) <= ssize(data); i++)
				tab[p+1][i] = op(tab[p][i], tab[p][i + (1<<p)]);
		}
	}
	int query(int a, int b) { // [a, b]
		// assert(a <= b);
		int p = __builtin_clz(1) - __builtin_clz(b-a+1);
		return op(tab[p][a], tab[p][b - (1<<p) + 1]);
	}
};
