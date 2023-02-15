#pragma once
#include "common.h"
#include "push_relabel.h"
#include "bipartite_matching.h"


pair<vi, vi> mvc(vector<pair<int,int>>& edges, int n, int m, bool ind_set=false) {
	auto bm = bipartite_matching(edges, n, m);
	set<pair<int, int>> st(all(bm));
	vector<vi> gr (n+m);
	vector<bool> matched(n+m, 0), vis(n+m, 0);
	for(auto [a, b] : bm) {
		matched[a] = matched[b+n] = 1;
		gr[b+n].push_back(a);
	}

	for(auto [a, b] : edges)
		if(!st.count({a, b}))
			gr[a].push_back(b+n);

	queue<int> q;
	for(int i = 0; i < n; i++)
		if(!matched[i])
			q.push(i);
	while(q.size()) {
		int p = q.front(); q.pop();
		vis[p] = 1;
		for(int x : gr[p])
			if(!vis[x]) 
				q.push(x);
	}

	pair<vi, vi> res;
	for(int i = 0; i < n; i++)
		if(vis[i] == ind_set)
			res.first.push_back(i);
	for(int i = 0; i < m; i++)
		if(vis[i+n] != ind_set)
			res.second.push_back(i);
	return res;
}
