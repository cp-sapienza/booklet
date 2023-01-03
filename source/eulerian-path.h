#pragma once
#include "common.h"

struct edge {
	int value;
	list<edge>::iterator it;
};
struct eulerPath {
	vector<list<edge>> adj;
	vi result;
	int n;
	void calc() {
		int odds = 0, start = 0;
		for(int i = 0; i < n; ++i) {
			if(adj[i].size() % 2) {
				++odds;
				start = i;
			}
		}
		// odds == 2 => eulerian path; odds == 0 => eulerian cycle; else there's no solution
		assert(odds == 2 || odds == 0); 
		stack<int> st;
		st.push(start);
		while(st.size()) {
			int v = st.top();
			while(!adj[v].empty()) {
				int u = adj[v].front().value;
				auto reversed = adj[v].front().it;
				adj[v].erase(adj[v].begin());
				adj[u].erase(reversed);
				st.push(u);
				v = st.top();
			}
			result.push_back(st.top());
			st.pop();
		}
	}
	eulerPath(int sz) : n(sz) {
		adj.resize(n);
	}
	void addEdge(int a, int b) {
		adj[a].push_front({b, adj[a].end()});
		auto ita = adj[a].begin();
		adj[b].push_front({a, ita});
		ita->it = adj[b].begin();
	}
};
