#include "common.h"

struct LazystentST {
	using Value = ll;
	using Update = ll;
	Value unit = Value(0);
	#define no_update 0
	Value merge(Value a, Value b) { return a + b; }
	Value updated_val(Value a, Update upd, int l, int r) {
		return a + upd * (r - l + 1);
	}
	Update combine_updates(Update prev, Update upd) {
		return prev + upd;
	}

	struct Vertex {
		const Value val;
		int sx = -1, dx = -1;
		Update upd;
		Vertex(Value v, int _sx, int _dx, Update up = no_update) : val(v), sx(_sx), dx(_dx), upd(up) {}
		Vertex(Value v) : val(v), upd(no_update) {}
	};
	int n;
	vector<int> roots;
	vector<Vertex> st;


	LazystentST(const vector<int>& data) {
		n = ssize(data);
		roots.push_back(build(0, n-1, data));
	}
	template<typename... Args> int alloc(Args... args) {
		st.emplace_back(args...);
		return st.size() - 1;
	}
	int build(int l, int r, const vector<int>& data) {
		if(l == r) return alloc(Value{data[l]});
		int lson = build(l, (l+r)/2, data);
		int rson = build((l+r)/2+1, r, data);
		return alloc(merge(st[lson].val, st[rson].val), lson, rson);
	}

	void push(int u, int l, int r) {
		if(st[u].upd == no_update) return;
		if(l != r) {
			assert(st[u].dx != -1 && st[u].sx != -1);
			Value lval = updated_val(st[st[u].sx].val, st[u].upd, l, (l+r)/2),
				rval = updated_val(st[st[u].dx].val, st[u].upd, (l+r)/2+1, r);
			st[u].sx = alloc(lval, st[st[u].sx].sx, st[st[u].sx].dx, combine_updates(st[st[u].sx].upd, st[u].upd));
			st[u].dx = alloc(rval, st[st[u].dx].sx, st[st[u].dx].dx, combine_updates(st[st[u].dx].upd, st[u].upd));
		}
		st[u].upd = no_update;
	}
	int update(int u, int l, int r, int x, int y, Update up) {
		if(r < x || l > y) return u;
		if(x <= l && r <= y) {
			Value val = updated_val(st[u].val, up, l, r);
			return alloc(val, st[u].sx, st[u].dx, combine_updates(up, st[u].upd));
		}
		else {
			push(u, l, r);
			int lson = update(st[u].sx, l, (l+r)/2, x, y, up);
			int rson = update(st[u].dx, (l+r)/2+1, r, x, y, up);
			return alloc(merge(st[lson].val, st[rson].val), lson, rson);
		}
	}
	Value query(int u, int l, int r, int x, int y) {
		if(r < x || l > y) return unit;
		if(x <= l && r <= y) return st[u].val;
		push(u, l, r);
		return merge(
			query(st[u].sx, l, (l+r)/2, x, y),
			query(st[u].dx, (l+r)/2+1, r, x, y)
		);
	}
	void update(int ver, int x, int y, int v) { roots[ver] = update(roots[ver], 0, n-1, x, y, v); }
	Value query(int ver, int x, int y) { return query(roots[ver], 0, n-1, x, y); }
	void duplicate(int ver) { roots.push_back(roots[ver]); }

	// Optional: replaces range [x, y] in version ver with the same range of version src
	int replace(int u, int v, int l, int r, int x, int y) {
		if(r < x || l > y) return u;
		if(x <= l && r <= y) return v;
		else {
			push(u, l, r); // <- delete this two lines 
			push(v, l, r); // <- for the non-lazy version
			int lson = replace(st[u].sx, st[v].sx, l, (l+r)/2, x, y);
			int rson = replace(st[u].dx, st[v].dx, (l+r)/2+1, r, x, y);
			return alloc(merge(st[lson].val, st[rson].val), lson, rson);
		}
	}
	void replace(int ver, int src, int x, int y) { roots[ver] = replace(roots[ver], roots[src], 0, n-1, x, y); }
};
