#pragma once
#include "common.h"

struct UFDS {
	vi parent, rank, sz;
	int num_components;

	UFDS(int N) : parent(N, -1), rank(N, 0), sz(N, 1), num_components(N) {}
	int find(int x) {
		if(parent[x] == -1) return x;
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
