#pragma once
#include "common.h"

struct LazyST {
	using Node = ll;
	using Update = ll;

	Node unit = Node(0); // s.t. for every x merge(x, unit) = x
	Update no_update = Update(0); // null update

	Node merge(Node a, Node b) {
		return a + b;
	}
	void update_node(Node& a, Update upd, int l, int r) {
		a += upd * (r - l + 1);
	}
	Update combine_updates(Update prev, Update upd) {
		return prev + upd;
	}

	int n;
	vector<Node> st;
	vector<Update> lz;

	LazyST(const vector<int>& data) {
		n = 1;
		while(n < ssize(data)) n *= 2;
		st.assign(2*n, unit);
		lz.assign(n, no_update);

		for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
		for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
	}
	void push(int u, int l, int r) {
		if(u >= n) return;
		if(lz[u] != no_update) {
			update_node(st[2*u], lz[u], l, (l+r)/2);
			update_node(st[2*u+1], lz[u], (l+r)/2+1, r);
			if(2*u < n) {
				lz[2*u] = combine_updates(lz[2*u], lz[u]);
				lz[2*u+1] = combine_updates(lz[2*u+1], lz[u]);
			}
			lz[u] = no_update;
		}
	}
	Node query(int u, int l, int r, int x, int y) {
		if(r < x || l > y) return unit;
		if(l >= x && r <= y) return st[u];
		push(u, l, r);
		return merge(
			query(2*u, l, (l+r)/2, x, y),
			query(2*u+1, (l+r)/2+1, r, x, y)
		);
	}
	void update(int u, int l, int r, int x, int y, Update v) {
		if(r < x || l > y) return;
		if(l >= x && r <= y) {
			update_node(st[u], v, l, r);
			if(u < n)
				lz[u] = combine_updates(lz[u], v);
		} else {
			push(u, l, r);
			update(2*u, l, (l+r)/2, x, y, v);
			update(2*u+1, (l+r)/2+1, r, x, y, v);
			st[u] = merge(st[2*u], st[2*u+1]);
		}
	}
	// [x, y]
	Node query(int x, int y) { return query(1, 0, n-1, x, y); }
	void update(int x, int y, Update v) { return update(1, 0, n-1, x, y, v); }

	// Optional features start here
	// condition on result of lower_bound(k)
	bool cmp(Node nd, int k) { return nd >= k; }
	// Returns lowest i such that cmp(query(0, i), k) is true
	// (or -1 if such i does not exist) in O(log N).
	// Only works where binary searching cmp(query(0, i), k) would work, but it's faster
	int lower_bound(int k) {
		if(!cmp(st[1], k))
			return -1;
		int p = 1, l = 0, r = n-1;
		Node part = unit;
		while(p < n)
		{
			push(p, l, r);
			p <<= 1;
			if(!cmp(merge(part, st[p]), k)) {
				part = merge(part, st[p++]);
				l = (l+r)/2+1;
			}
			else r = (l+r)/2;
		}
		return p - n;
	}
};
