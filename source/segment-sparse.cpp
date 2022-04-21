struct SparseST {

	using Value = ll;
	using Update = ll;
	ll inf = 1e9;
	Value unit = Value(0);
	static const Update no_update = Update{0}; // null update

	Value merge(Value a, Value b) { return a + b; }

	struct Vertex {
		Value val;
		int l = -1, r = -1;
		Update upd = no_update;
		Vertex(Value v, ll _sx, ll _dx) : val(v), l(_sx), r(_dx) {}
		Vertex(Value v) : val(v) {}
	};


	void update_node(Vertex& a, Update upd, ll l, ll r) {
		a.val = upd * (r - l + 1);
	}
	Update combine_updates(Update prev, Update upd) {
		return upd;
	}

	vector<Vertex> st{Vertex{unit}};


	void push(int u, ll l, ll r) {
		if(l == r) return;
		if(st[u].l == -1) {
			st[u].l = ssize(st);
			st.push_back(Vertex(unit));
		}
		if(st[u].r == -1) {
			st[u].r = ssize(st);
			st.push_back(Vertex(unit));
		}
		if(st[u].upd != no_update) {
			update_node(st[st[u].l], st[u].upd, l, (l+r)/2);
			update_node(st[st[u].r], st[u].upd, (l+r)/2+1, r);
			if(l < r) {
				st[st[u].l].upd = combine_updates(st[st[u].l].upd, st[u].upd);
				st[st[u].r].upd = combine_updates(st[st[u].r].upd, st[u].upd);
			}
			st[u].upd = no_update;
		}
	}

	void update(int u, ll l, ll r, ll x, ll y, Update v) {
		if(r < x || y < l) return;
		if(x <= l && r <= y) {
			update_node(st[u], v, l, r);
			if(l != r)
				st[u].upd = combine_updates(st[u].upd, v);
		}
		else {
			push(u, l, r);
			update(st[u].l, l, (l+r)/2, x, y, v);
			update(st[u].r, (l+r)/2+1, r, x, y, v);
			st[u].val = merge(st[st[u].l].val, st[st[u].r].val);
		}
	}

	Value query(int u, ll l, ll r, ll x, ll y) {
		if(r < x || l > y) return unit;
		if(l >= x && r <= y)
		{
			return st[u].val;
		}
		push(u, l, r);
		return merge(
			query(st[u].l, l, (l+r)/2, x, y),
			query(st[u].r, (l+r)/2+1, r, x, y)
		);
	}

	// [x, y]
	Value query(ll x, ll y) { return query(0, 0, inf, x, y); }
	void update(ll x, ll y, Update v) { update(0, 0, inf, x, y, v); }
};