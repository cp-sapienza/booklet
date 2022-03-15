struct PersistentST {
	using Value = ll;
	Value unit = Value(0);
	Value merge(Value a, Value b) { return a + b; }

	struct Vertex {
		const Value val;
		int sx = -1, dx = -1;
		Vertex(Value v, int _sx, int _dx) : val(v), sx(_sx), dx(_dx) {}
		Vertex(Value v) : val(v) {}
	};

	int n;
	vector<Vertex> st;
	vector<int> roots;

	PersistentST(const vector<int>& data) {
		n = data.size();
		roots.push_back(build(0, n-1, data));
	}
	template<typename... Args> int alloc(Args... args) {
		st.emplace_back(args...);
		return st.size() - 1;
	}
	int build(int l, int r, const vector<int>& data) {
		if(l == r) return alloc(Value{data[l]});
		int sx = build(l, (l+r)/2, data);
		int dx = build((l+r)/2+1, r, data);
		return alloc(merge(st[sx].val, st[dx].val), sx, dx);
	}
	int update(int u, int l, int r, int p, int v) {
		if(r < p || l > p) return u;
		if(l == r) return alloc(Value{v});
		else {
			int sx = update(st[u].sx, l, (l+r)/2, p, v);
			int dx = update(st[u].dx, (l+r)/2+1, r, p, v);
			return alloc(merge(st[sx].val, st[dx].val), sx, dx);
		}
	}
	Value query(int u, int l, int r, int x, int y) {
		if(r < x || l > y) return unit;
		if(l >= x && r <= y) return st[u].val;
		return merge(
			query(st[u].sx, l, (l+r)/2, x, y),
			query(st[u].dx, (l+r)/2+1, r, x, y)
		);
	}
	void update(int ver, int p, int v) { roots[ver] = update(roots[ver], 0, n-1, p, v); }
	Value query(int ver, int x, int y) { return query(roots[ver], 0, n-1, x, y); }
	void duplicate(int ver) { roots.push_back(roots[ver]); }
};