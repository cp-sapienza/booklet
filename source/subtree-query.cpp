struct SubtreeSegment {
	SegmentTree seg{{}};
	vi sz, ord;
	int curr_ord = 0;

	int dfs(const vector<vi> &ad, int p, int prev = -1) {
		ord[p] = curr_ord++;
		sz[p] = 1;
		for(int x:ad[p])
			if(x != prev)
				sz[p] += dfs(ad, x, p);
		return sz[p];
	}

	SubtreeSegment(const vector<vi> &ad, const vi &w, int root) {
		int n = ssize(ad);
		sz.resize(n);
		ord.resize(n);
		dfs(ad, root);
		vi data(n);
		for(int i=0;i<n;i++)
			data[ord[i]] = w[i];
		seg = SegmentTree(data);
	}

	SegmentTree::Node query(int v) {
		return seg.query(ord[v], ord[v]+sz[v]-1);
	}

	// point update
	void update(int v, SegmentTree::Node val) {
		seg.update(ord[v], val);
	}

	// for whole subtree updates on LazyST
	//(change SegmentTree to LazyST to use this one)
/*
	void update(int v, LazyST::Update upd) {
		seg.update(ord[v], ord[v]+sz[v]-1, upd);
	}
*/
};
