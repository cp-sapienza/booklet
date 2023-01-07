#pragma once
#include "common.h"

vi euler_walk(vector<vector<pair<int, int>>>& adj, int E, int src = 0, bool directed = 0) {
	int n = ssize(adj), odds = 0;
	vi indeg(n, 0);
	if(directed)
		for(auto &v: adj)
			for(auto [dest, ind]: v)
				indeg[dest]++;
	bool srcgood = (directed? indeg[src] != ssize(adj[src]) : ssize(adj[src]) % 2 == 1);
	for(int i = 0; i < n; ++i) {
		int incr = (directed? abs(ssize(adj[i]) - indeg[i]) : ssize(adj[i]) % 2);
		odds += incr;
		if(!srcgood && incr) src = i;
	}
	if(odds > 2) return {};
	vi result, inds(n, 0);
	vector<bool> used(E, 0);
	stack<int> st;
	st.push(src);
	while(st.size()) {
		int v = st.top();
		if(inds[v] == ssize(adj[v])) {
			result.push_back(v);
			st.pop();
			continue;
		}
		int ind = inds[v]++;
		auto [dst, id] = adj[v][ind];
		if(used[id]) continue;
		used[id] = true;
		st.push(dst);
	}
	if(ssize(result) != E+1) return {};
	reverse(all(result));
	return result;
}
