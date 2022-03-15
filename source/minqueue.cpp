struct MinQueue {
	void push(int i, int v) {
		// for maxqueue, change to <=
		while(!q.empty() && q.back().first >= v)
			q.pop_back();
		q.push_back({v,i});
	}
	void popuntil(int i) {
		while(!q.empty() && q.front().second <= i)
			q.pop_front();
	}
	int min() {
		return q.front().first;
	}
	deque<pair<int,int>> q;
};