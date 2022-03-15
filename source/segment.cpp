struct SegmentTree {
	using Node = int;
	Node unit = Node(0); // s.t. for every x merge(x, unit) = x
	Node merge(Node a, Node b) { return a + b; }

	int n;
	vector<Node> st;

	SegmentTree(const vector<int>& data) {
		n = 1;
		while(n < ssize(data)) n *= 2;
		st.assign(2*n, unit);
		for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
		for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
	}
	void update(int p, int v) {
		st[p += n] = Node{v};
		for(p /= 2; p > 0; p /= 2) st[p] = merge(st[2*p], st[2*p+1]);
	}
	Node query(int x, int y) // [x, y] {
		Node left = unit, right = unit;
		for(x += n, y += n + 1; x < y; x /= 2, y /= 2) {
			if(x&1) left = merge(left, st[x++]);
			if(y&1) right = merge(st[--y], right);
		}
		return merge(left, right);
	}
};
