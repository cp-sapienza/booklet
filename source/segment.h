#pragma once
#include "common.h"

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
	Node query(int x, int y) { // [x, y]
		Node left = unit, right = unit;
		for(x += n, y += n + 1; x < y; x /= 2, y /= 2) {
			if(x&1) left = merge(left, st[x++]);
			if(y&1) right = merge(st[--y], right);
		}
		return merge(left, right);
	}
	// Optional features start here
	/* condition on result of lower_bound(k) */
	bool cmp(Node nd, int k) { return nd >= k; } 
	/* Returns lowest i such that cmp(query(0, i), k) is true 
		(or -1 if such i does not exist) in O(log N).
		Only works where binary searching cmp(query(0, i), k) would work, but it's faster
	*/
	int lower_bound(int k) {
		if(!cmp(st[1], k))
			return -1;
		int p = 1;
		Node part = unit;
		while(p < n)
		{
			p <<= 1;
			if(!cmp(merge(part, st[p]), k)) {
				part = merge(part, st[p++]);
			}
		}
		return p - n;
	}
};
